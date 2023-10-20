/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * Graphics Backend for drawing to ST7789
 * ----------------------------------------------------------------------------
 */

#include "platform_config.h"
#include "jsutils.h"
#include "lcd_st7789v.h"
#include "jswrap_graphics.h"
#include "lcd_arraybuffer.h" // for lcd*_ArrayBuffer_flat8
#include "jshardware.h"
#include "jswrapper.h"
#include "nrf_gpio.h"


#define LCD_SPI_UNBUF_LEN SPISENDMANY_BUFFER_SIZE
#define LCD_SPI EV_SPI1

static int _lastx=-1;
static int _lasty=-1;
static uint16_t _chunk_buffer[LCD_SPI_UNBUF_LEN];
static int _chunk_index = 0;

#define CMDINDEX_CMD   0
#define CMDINDEX_DELAY 1
#define CMDINDEX_DATALEN  2
static const uint8_t ST7789_INIT_CODE[] = {
  // CMD,DELAY,DATA_LEN,D0,D1,D2...
    0x11,0,0,
    // This is an unrotated screen
    0x36,0,1,0, // MADCTL
    // These 2 rotate the screen by 180 degrees
    //0x36,0,1,0xC0, // MADCTL
    //0x37,0,2,0,80, // Vertical scroll

    0x3A,0,1,0x55, // COLMOD - interface pixel format - 16bpp
    0xB2,0,5,0xC,0xC,0,0x33,0x33,
    0xB7,0,1,0,
    0xBB,0,1,0x3E,
    0xC2,0,1,1,
    0xC3,0,1,0x19,
    0xC4,0,1,0x20,
    0xC5,0,1,0xF,
    0xD0,0,2,0xA4,0xA1,
    // https://github.com/espruino/Espruino/issues/1758
    0xe0,0,14,0xd0,6,0xc,9,9,0x25,0x2e,0x33,0x45,0x36,0x12,0x12,0x2e,0x34,
    0xe1,0,14,0xd0,6,0xc,9,9,0x25,0x2e,0x33,0x45,0x36,0x12,0x12,0x2e,0x34,
    //0xe0,0,14,0x70,0x15,0x20,0x15,0x10,0x09,0x48,0x33,0x53,0x0B,0x19,0x15,0x2a,0x2f,
    //0xe1,0,14,0x70,0x15,0x20,0x15,0x10,0x09,0x48,0x33,0x53,0x0B,0x19,0x15,0x2a,0x2f,
    0x29,0,0,
    0x21,0,0,
    // End
    0, 0, 255/*DATA_LEN = 255 => END*/
};

// ====================================================================================


static void spi_cmd(const uint8_t cmd) {
  jshPinSetValue(LCD_SPI_DC, 0);
  jshSPISend(LCD_SPI, cmd);
  jshPinSetValue(LCD_SPI_DC, 1);
}

static inline void spi_data(const uint8_t *data, int len) {
  jshSPISendMany(LCD_SPI, data, NULL, len, NULL);
}


void lcdCmd(int cmd, int dataLen, const unsigned char *data) {
  jshPinSetValue(LCD_SPI_DC, 0); // command
  jshPinSetValue(LCD_SPI_CS, 0);
  jshSPISend(LCD_SPI, cmd);
  if (dataLen) {
    jshPinSetValue(LCD_SPI_DC, 1); // data
    while (dataLen) {
      jshSPISend(LCD_SPI, *(data++));
      dataLen--;
    }
  }
  jshPinSetValue(LCD_SPI_CS, 1);
}

void lcdSendInitCmd() {
  // Send initialization commands
  const unsigned char *cmd = ST7789_INIT_CODE;
  while(cmd[CMDINDEX_DATALEN]!=255) {
    lcdCmd(cmd[CMDINDEX_CMD], cmd[CMDINDEX_DATALEN], &cmd[3]);
    if (cmd[CMDINDEX_DELAY])
      jshDelayMicroseconds(1000*cmd[CMDINDEX_DELAY]);
    cmd += 3 + cmd[CMDINDEX_DATALEN];
  }
}

// ====================================================================================

static void flush_chunk_buffer() {
  if(_chunk_index == 0) return;
  spi_data((uint8_t *)&_chunk_buffer, _chunk_index*2);
  _chunk_index = 0;
}

static inline bool willFlush() {
  return _chunk_index == LCD_SPI_UNBUF_LEN - 1;
}

static inline _put_pixel( uint16_t c) {
  _chunk_buffer[_chunk_index++] = c;
  if (_chunk_index==LCD_SPI_UNBUF_LEN) flush_chunk_buffer();
}

 /// flush chunk buffer to screen
void lcdST7789_flip() {
  if(_chunk_index == 0) return;
  jshPinSetValue(LCD_SPI_CS, 0);
  flush_chunk_buffer();
  jshPinSetValue(LCD_SPI_CS, 1);
}

void disp_spi_transfer_addrwin(int x1, int y1, int x2, int y2) {
  unsigned char wd[4];
  //flush_chunk_buffer();
  /*x1 += _colstart;
  y1 += _rowstart;
  x2 += _colstart;
  y2 += _rowstart;*/
  spi_cmd(0x2A);
  wd[0] = x1>>8;
  wd[1] = x1 & 0xFF;
  wd[2] = x2>>8;
  wd[3] = x2 & 0xFF;
  spi_data((uint8_t *)&wd, 4);
  spi_cmd(0x2B);
  wd[0] = y1>>8;
  wd[1] = y1 & 0xFF;
  wd[2] = y2>>8;
  wd[3] = y2 & 0xFF;
  spi_data((uint8_t *)&wd, 4);
  spi_cmd(0x2C);
}


void lcdST7789_setPixel(JsGraphics *gfx, int x, int y, unsigned int col) {

  uint16_t color =   (col>>8) | (col<<8); 
  if (x!=_lastx+1 || y!=_lasty) {
    jshPinSetValue(LCD_SPI_CS, 0);
    disp_spi_transfer_addrwin(x, y, gfx->data.width, y+1);  
    jshPinSetValue(LCD_SPI_CS, 1); //will never flush after 
    _put_pixel(color);
    _lastx = x;
    _lasty = y;
  } else {
    _lastx++; 
    if (willFlush()){
      jshPinSetValue(LCD_SPI_CS, 0);
      _put_pixel(color);
      jshPinSetValue(LCD_SPI_CS, 1);
    } else {
      _put_pixel(color);
    } 
  }

}

void lcdST7789_fillRect(JsGraphics *gfx, int x1, int y1, int x2, int y2, unsigned int col) {
  int pixels = (1+x2-x1)*(1+y2-y1); 
  uint16_t color =   (col>>8) | (col<<8); 
  jshPinSetValue(LCD_SPI_CS, 0);
  disp_spi_transfer_addrwin(x1, y1, x2, y2);
  for (int i=0; i<pixels; i++) _put_pixel(color);
  jshPinSetValue(LCD_SPI_CS, 1);
  _lastx=-1;
  _lasty=-1;
}

// ====================================================================================

void lcdST7789_init(JsGraphics *gfx) {
  gfx->data.width = LCD_WIDTH;
  gfx->data.height = LCD_HEIGHT;
  gfx->data.bpp = LCD_BPP;

  //lcdSetPalette_SPILCD(0);

  jshPinOutput(LCD_SPI_CS,1);
  jshPinOutput(LCD_SPI_DC,1);
  jshPinOutput(LCD_SPI_SCK,1);
  jshPinOutput(LCD_SPI_MOSI,1);

  jshPinOutput(LCD_SPI_RST,0);
  jshDelayMicroseconds(1000);
  jshPinOutput(LCD_SPI_RST, 1);
  jshDelayMicroseconds(2000);

  JshSPIInfo inf;
  jshSPIInitInfo(&inf);
#ifndef LCD_SPI_BITRATE
#define LCD_SPI_BITRATE 8000000
#endif
  inf.baudRate = LCD_SPI_BITRATE;
  inf.pinMOSI = LCD_SPI_MOSI;
  inf.pinSCK = LCD_SPI_SCK;
  jshSPISetup(LCD_SPI, &inf);

  nrf_gpio_cfg(
      LCD_SPI_MOSI,
      GPIO_PIN_CNF_DIR_Output,
      GPIO_PIN_CNF_INPUT_Disconnect,
      GPIO_PIN_CNF_PULL_Disabled,
      GPIO_PIN_CNF_DRIVE_H0H1,
      GPIO_PIN_CNF_SENSE_Disabled);
  nrf_gpio_cfg(
      LCD_SPI_SCK,
      GPIO_PIN_CNF_DIR_Output,
      GPIO_PIN_CNF_INPUT_Disconnect,
      GPIO_PIN_CNF_PULL_Disabled,
      GPIO_PIN_CNF_DRIVE_H0H1,
      GPIO_PIN_CNF_SENSE_Disabled);

  lcdSendInitCmd();
  
}

void lcdST7789_setCallbacks(JsGraphics *gfx) {
    gfx->setPixel = lcdST7789_setPixel;
    gfx->fillRect = lcdST7789_fillRect;
}

