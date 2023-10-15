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
    //0xe0,0,14,0xd0,6,0xc,9,9,0x25,0x2e,0x33,0x45,0x36,0x12,0x12,0x2e,0x34,
    //0xe1,0,14,0xd0,6,0xc,9,9,0x25,0x2e,0x33,0x45,0x36,0x12,0x12,0x2e,0x34,
    0xe0,0,14,0x70,0x15,0x20,0x15,0x10,0x09,0x48,0x33,0x53,0x0B,0x19,0x15,0x2a,0x2f,
    0xe1,0,14,0x70,0x15,0x20,0x15,0x10,0x09,0x48,0x33,0x53,0x0B,0x19,0x15,0x2a,0x2f,
    0x29,0,0,
    0x21,0,0,
    // End
    0, 0, 255/*DATA_LEN = 255 => END*/
};
const int LCD_BUFFER_HEIGHT = 320;
LCDST7789Mode lcdMode;
int lcdNextX, lcdNextY;
/// Vertical scrolling (change the scan start address on the LCD)
int lcdScrollY;
/// For notifications, we keep lcdScroll the same but then shift the LCD start address anyway
int lcdOffsetY;

/* We have to be careful about this since we can
write faster than the LCD is happy about

#define LCD_SCK_CLR() NRF_P0->OUTCLR = 1<<LCD_PIN_SCK
#define LCD_SCK_SET() NRF_P0->OUTSET = 1<<LCD_PIN_SCK
#define LCD_CS_CLR() nrf_gpio_pin_clear(LCD_PIN_CS);
#define LCD_CS_SET() nrf_gpio_pin_set(LCD_PIN_CS);
#define LCD_DC_COMMAND() nrf_gpio_pin_clear(LCD_PIN_DC);
#define LCD_DC_DATA() nrf_gpio_pin_set(LCD_PIN_DC);
#define LCD_SCK_CLR() nrf_gpio_pin_clear(LCD_PIN_SCK);
#define LCD_SCK_SET() nrf_gpio_pin_set(LCD_PIN_SCK);
#define LCD_CS_CLR() jshPinSetValue(LCD_PIN_CS,0);
#define LCD_CS_SET() jshPinSetValue(LCD_PIN_CS,1);
#define LCD_DC_COMMAND() jshPinSetValue(LCD_PIN_DC,0);
#define LCD_DC_DATA() jshPinSetValue(LCD_PIN_DC,1);
*/

// Enable fast SPI by writing direct to registers
#if LCD_SPI_SCK<32
#define LCD_SPI_SCK_SET() (*(volatile uint32_t*)0x50000508)=1<<LCD_SPI_SCK
#define LCD_SPI_SCK_CLEAR() (*(volatile uint32_t*)0x5000050C)=1<<LCD_SPI_SCK
#else
#define LCD_SPI_SCK_SET() (*(volatile uint32_t*)0x50000808)=1<<(LCD_SPI_SCK-32)
#define LCD_SPI_SCK_CLEAR() (*(volatile uint32_t*)0x5000080C)=1<<(LCD_SPI_SCK-32)
#endif
#if LCD_SPI_MOSI<32
#define LCD_SPI_MOSI_SET() (*(volatile uint32_t*)0x50000508)=1<<LCD_SPI_MOSI
#define LCD_SPI_MOSI_CLEAR() (*(volatile uint32_t*)0x5000050C)=1<<LCD_SPI_MOSI
#else
#define LCD_SPI_MOSI_SET() (*(volatile uint32_t*)0x50000808)=1<<(LCD_SPI_MOSI-32)
#define LCD_SPI_MOSI_CLEAR() (*(volatile uint32_t*)0x5000080C)=1<<(LCD_SPI_MOSI-32)
#endif

void lcd_wr(int data) {
  for (int bit=7;bit>=0;bit--) {
    LCD_SPI_SCK_CLEAR();
    if ((data>>bit)&1) LCD_SPI_MOSI_SET();
    else LCD_SPI_MOSI_CLEAR();
    LCD_SPI_SCK_SET();
  }
}
void lcd_wr16(bool allFF) {
  if (allFF) LCD_SPI_MOSI_SET();
  else LCD_SPI_MOSI_CLEAR();
  for (int bit=0;bit<16;bit++) {
    LCD_SPI_SCK_CLEAR();
    LCD_SPI_SCK_SET();
  }
}

#define LCD_CS_CLR() NRF_P0->OUTCLR = 1<<LCD_SPI_CS
#define LCD_CS_SET() NRF_P0->OUTSET = 1<<LCD_SPI_CS
#define LCD_DC_COMMAND() NRF_P0->OUTCLR = 1<<LCD_SPI_DC
#define LCD_DC_DATA() NRF_P0->OUTSET = 1<<LCD_SPI_DC
#define LCD_SCK_CLR() jshPinSetValue(LCD_SPI_SCK,0);
#define LCD_SCK_SET() jshPinSetValue(LCD_SPI_SCK,1);
#define LCD_SCK_CLR_FAST() LCD_SPI_SCK_SET();
#define LCD_SCK_SET_FAST() LCD_SPI_SCK_CLEAR();

#define LCD_DATA(data) {lcd_wr(data);}
#define LCD_WR(data) {lcd_wr(data);LCD_SCK_CLR();LCD_SCK_SET();}

void lcd_send_cmd(uint8_t cmd) {
  LCD_CS_CLR();
  LCD_DC_COMMAND(); // command
  LCD_WR(cmd);
  LCD_CS_SET();
}
void lcd_send_data(uint8_t cmd) {
  LCD_CS_CLR();
  LCD_DC_DATA(); // data
  LCD_WR(cmd);
  LCD_CS_SET();
}


void lcdST7789_cmd(int cmd, int dataLen, const uint8_t *data) {
  LCD_CS_CLR();
  LCD_DC_COMMAND(); // command
  LCD_WR(cmd);
  if (dataLen) {
    LCD_DC_DATA(); // data
    while (dataLen) {
      LCD_WR(*(data++));
      dataLen--;
    }
  }
  LCD_CS_SET();
}

// Update LCD scroll position
void lcdST7789_scrollCmd() {
  int offs = lcdScrollY + lcdOffsetY;
  if (lcdMode == LCDST7789_MODE_DOUBLEBUFFERED)
    offs += 120;
  if (offs>=320) offs -= 320;
  if (offs<0) offs += 320;
  uint8_t buf[2];
  buf[0] = offs>>8;
  buf[1] = offs;
  lcdST7789_cmd(0x37,2,buf);
}

/** Allow the LCD to be shifted vertically while still drawing in the normal position.
 * Use this to display notifications while keeping the original data on the screen */
void lcdST7789_setYOffset(int y) {
  if (y<-80) y=-80;
  if (y>80) y=80;
  lcdOffsetY = y;
  lcdST7789_scrollCmd();
}

void lcdST7789_setMode(LCDST7789Mode mode) {
  if (lcdMode != mode) {
    uint8_t buf[4];
    lcdMode = mode;
    switch (lcdMode) {
    case LCDST7789_MODE_NULL: break;
    case LCDST7789_MODE_UNBUFFERED:
    case LCDST7789_MODE_BUFFER_120x120:
    case LCDST7789_MODE_BUFFER_80x80:

      lcdST7789_cmd(0x13,0,NULL);
      lcdScrollY = 0;
      lcdST7789_scrollCmd();
      break;
    case LCDST7789_MODE_DOUBLEBUFFERED:
      buf[0] = 0;
      buf[1] = 40;
      buf[2] = 0;
      buf[3] = 199;
      lcdST7789_cmd(0x30,4,buf);
      lcdST7789_cmd(0x12,0,NULL);
      lcdScrollY = 0;
      lcdST7789_scrollCmd();
      break;
    }
  }
}

LCDST7789Mode lcdST7789_getMode() {
  return lcdMode;
}

/*
void lcdST7789_flip(JsGraphics *gfx) {
  switch (lcdMode) {
    case LCDST7789_MODE_NULL: break;
    case LCDST7789_MODE_UNBUFFERED:
      // unbuffered - flip has no effect
    break;
    case LCDST7789_MODE_DOUBLEBUFFERED: {
      // buffered - flip using LCD itself
      if (lcdScrollY==0) {
        lcdScrollY = 160;
      } else {
        lcdScrollY = 0;
      }
      lcdST7789_scrollCmd();
    } break;
    case LCDST7789_MODE_BUFFER_120x120: {
      // offscreen buffer - BLIT
      JsVar *buffer = jsvObjectGetChild(gfx->graphicsVar, "buffer", 0);
      JsVar *str = jsvGetArrayBufferBackingString(buffer);
      if (str) {
        JsvStringIterator it;
        jsvStringIteratorNew(&it, str, 0);
        lcdST7789_blit8Bit(0,0,120,120,2,&it,PALETTE_8BIT);
        jsvStringIteratorFree(&it);
      }
      jsvUnLock2(str,buffer);
    } break;
    case LCDST7789_MODE_BUFFER_80x80: {
      // offscreen buffer - BLIT
      JsVar *buffer = jsvObjectGetChild(gfx->graphicsVar, "buffer", 0);
      JsVar *str = jsvGetArrayBufferBackingString(buffer);
      if (str) {
        JsvStringIterator it;
        jsvStringIteratorNew(&it, str, 0);
        lcdST7789_blit8Bit(0,0,80,80,3,&it,PALETTE_8BIT);
        jsvStringIteratorFree(&it);
      }
      jsvUnLock2(str,buffer);
    } break;
  }
}
*/

// Start blit with raw data (lcdScrollY already applied)
void lcdST7789_blitStartRaw(int x1, int y1, int x2, int y2) {
  lcdNextY=-1;
  lcdNextX=-1;

  LCD_CS_CLR();
  LCD_DC_COMMAND(); // command
  LCD_WR(0x2A);
  LCD_DC_DATA(); // data
  LCD_WR(0);
  LCD_WR(x1);
  LCD_WR(0);
  LCD_WR(x2);
  LCD_DC_COMMAND(); // command
  LCD_WR(0x2B);
  LCD_DC_DATA(); // data
  LCD_WR(y1 >> 8);
  LCD_WR(y1);
  LCD_WR(y2 >> 8);
  LCD_WR(y2);
  LCD_DC_COMMAND(); // command
  LCD_WR(0x2C);
  LCD_DC_DATA(); // data

}
/// Starts a blit operation - call this, then blitPixel (a lot) then blitEnd. No bounds checking
void lcdST7789_blitStart(int x, int y, int w, int h) {
  int x1 = x;
  int y1 = y+lcdScrollY;
  if (y1>=LCD_BUFFER_HEIGHT) y1-=LCD_BUFFER_HEIGHT;
  int x2 = x+w;
  int y2 = y+h+lcdScrollY;
  if (y2>=LCD_BUFFER_HEIGHT) y2-=LCD_BUFFER_HEIGHT;
  lcdST7789_blitStartRaw(x1,y1,x2,y2);
}
ALWAYS_INLINE void lcdST7789_blitPixel(unsigned int col) {

  /* FIXME: Handle case where scrolling means
   * we wrap around the memory area - see what
   * lcdST7789_fillRect does */
  LCD_DATA(col>>8);
  asm("nop");asm("nop");
  LCD_SCK_CLR_FAST();
  LCD_SCK_SET_FAST();
  LCD_DATA(col);
  asm("nop");asm("nop");
  LCD_SCK_CLR_FAST();
  LCD_SCK_SET_FAST();

}
void lcdST7789_blitEnd() {

  LCD_CS_SET();

}

void lcdST7789_blit1Bit(int x, int y, int w, int h, int scale, JsvStringIterator *pixels, const uint16_t *palette) {
  int y1 = y + lcdScrollY;
  int y2 = y + h*scale + lcdScrollY;
  if (y1>=LCD_BUFFER_HEIGHT) y1-=LCD_BUFFER_HEIGHT;
  if (y2>=LCD_BUFFER_HEIGHT) y2-=LCD_BUFFER_HEIGHT;
  lcdST7789_blitStartRaw(x,y1, x+(w*scale)-1,(y2>y1)?y2:239);
  int bitData = jsvStringIteratorGetCharAndNext(pixels);
  int bitCnt = 8;
  for (int y=0;y<h;y++) {
    JsvStringIterator lastPixels;
    jsvStringIteratorClone(&lastPixels, pixels);
    int lastBitData = bitData;
    int lastBitCnt = bitCnt;
    for (int n=1;n<=scale;n++) {
      y1++;
      if (y1>=LCD_BUFFER_HEIGHT) {
        lcdST7789_blitEnd();
        lcdST7789_blitStartRaw(x,0, x+(w*scale)-1,y2);
      }
      for (int x=0;x<w;x++) {
        uint16_t c = palette[(bitData>>7)&1];
        bitData <<= 1;
        bitCnt--;
        if (bitCnt==0) {
          bitData = jsvStringIteratorGetCharAndNext(pixels);
          bitCnt = 8;
        }
        for (int s=0;s<scale;s++)
          lcdST7789_blitPixel(c);
      }
      // display the same row multiple times if needed
      if (n<scale) {
        jsvStringIteratorFree(pixels);
        jsvStringIteratorClone(pixels, &lastPixels);
        bitData = lastBitData;
        bitCnt = lastBitCnt;
      }
    }
    jsvStringIteratorFree(&lastPixels);
  }
  lcdST7789_blitEnd();
}

void lcdST7789_blit8Bit(int x, int y, int w, int h, int scale, JsvStringIterator *pixels, const uint16_t *palette) {
  int y1 = y + lcdScrollY;
  int y2 = y + h*scale + lcdScrollY;
  if (y1>=LCD_BUFFER_HEIGHT) y1-=LCD_BUFFER_HEIGHT;
  if (y2>=LCD_BUFFER_HEIGHT) y2-=LCD_BUFFER_HEIGHT;
  lcdST7789_blitStartRaw(x,y1, x+(w*scale)-1,(y2>y1)?y2:239);
  for (int y=0;y<h;y++) {
    JsvStringIterator lastPixels;
    jsvStringIteratorClone(&lastPixels, pixels);
    for (int n=1;n<=scale;n++) {
      y1++;
      if (y1>=LCD_BUFFER_HEIGHT) {
        lcdST7789_blitEnd();
        lcdST7789_blitStartRaw(x,0, x+(w*scale)-1,y2);
      }
      if (scale==1) {
        for (int x=0;x<w;x++) {
          lcdST7789_blitPixel(palette[(uint8_t)jsvStringIteratorGetCharAndNext(pixels)]);
        }
      } else if (scale==2) {
        for (int x=0;x<w;x++) {
          uint16_t c = palette[(uint8_t)jsvStringIteratorGetCharAndNext(pixels)];
          lcdST7789_blitPixel(c);
          lcdST7789_blitPixel(c);
        }
      } else if (scale==3) {
        for (int x=0;x<w;x++) {
          uint16_t c = palette[(uint8_t)jsvStringIteratorGetCharAndNext(pixels)];
          lcdST7789_blitPixel(c);
          lcdST7789_blitPixel(c);
          lcdST7789_blitPixel(c);
        }
      } else { // fallback for not 1/2/3 scale
        for (int x=0;x<w;x++) {
          uint16_t c = palette[(uint8_t)jsvStringIteratorGetCharAndNext(pixels)];
          for (int s=0;s<scale;s++)
            lcdST7789_blitPixel(c);
        }
      }
      // display the same row multiple times if needed
      if (n<scale) {
        jsvStringIteratorFree(pixels);
        jsvStringIteratorClone(pixels, &lastPixels);
      }
    }
    jsvStringIteratorFree(&lastPixels);
  }
  lcdST7789_blitEnd();
}


void lcdST7789_scroll(JsGraphics *gfx, int xdir, int ydir, int x1, int y1, int x2, int y2) {
  // No way this is going to work double buffered!
  //if (lcdMode != LCDST7789_MODE_UNBUFFERED) return;
  // we can't scroll a window either
  //if (x1!=0 || y1!=0 || x2!=LCD_HEIGHT-1 || y2!=LCD_HEIGHT-1) return;
  /* We can't read data back, so we can't do left/right scrolling!
  However we can change our index in the memory buffer window
  which allows us to use the LCD itself for scrolling */
  /*lcdScrollY-=ydir;
  while (lcdScrollY<0) lcdScrollY+=LCD_BUFFER_HEIGHT;
  while (lcdScrollY>=LCD_BUFFER_HEIGHT) lcdScrollY-=LCD_BUFFER_HEIGHT;
  lcdST7789_scrollCmd();*/
}

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
  flush_chunk_buffer();
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
  
  lcdNextX = -1;
  lcdNextY = -1;
  lcdScrollY = 0;
  lcdOffsetY = 0;
  lcdMode = LCDST7789_MODE_UNBUFFERED;
}

void lcdST7789_setCallbacks(JsGraphics *gfx) {
    gfx->setPixel = lcdST7789_setPixel;
    gfx->fillRect = lcdST7789_fillRect;
}

