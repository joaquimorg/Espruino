/*
 * ----------------------------------------------------------------------------
 * Graphics Backend for drawing to SPI displays
 * ----------------------------------------------------------------------------
 */

#include "platform_config.h"
#include "jsutils.h"
#include "jshardware.h"
#include "jsparse.h"
#include "lcd_spi_nrf.h"
#include "lcd_spilcd_info.h"
#if defined(NRF52_SERIES)
#include "nrf_gpio.h"
#endif

#define LCD_SPI EV_SPI1

// ======================================================================


// ======================================================================

void lcdCmd_SPINRF(int cmd, int dataLen, const unsigned char *data) {
#ifdef ESPR_USE_SPI3
  // anomaly 195 workaround - enable SPI before use
  *(volatile uint32_t *)0x4002F500 = 7;
#endif
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
#ifdef ESPR_USE_SPI3
  // anomaly 195 workaround - disable SPI when done
  *(volatile uint32_t *)0x4002F500 = 0;
  *(volatile uint32_t *)0x4002F004 = 1;
#endif
}

void lcdSendInitCmd_SPINRF() {
  // Send initialization commands to ST7735
  const unsigned char *cmd = SPILCD_INIT_CODE;
  while(cmd[CMDINDEX_DATALEN]!=255) {
    lcdCmd_SPINRF(cmd[CMDINDEX_CMD], cmd[CMDINDEX_DATALEN], &cmd[3]);
    if (cmd[CMDINDEX_DELAY])
      jshDelayMicroseconds(1000*cmd[CMDINDEX_DELAY]);
    cmd += 3 + cmd[CMDINDEX_DATALEN];
  }
}

// ======================================================================


void lcdFlip_SPINRF(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t* data) {
  
#ifdef ESPR_USE_SPI3
  // anomaly 195 workaround - enable SPI before use
  *(volatile uint32_t *)0x4002F500 = 7;
#endif

  unsigned char buffer1[4];

  jshPinSetValue(LCD_SPI_CS, 0);
  jshPinSetValue(LCD_SPI_DC, 0); // command
  buffer1[0] = SPILCD_CMD_WINDOW_X;
  jshSPISendMany(LCD_SPI, buffer1, NULL, 1, NULL);
  jshPinSetValue(LCD_SPI_DC, 1); // data
  buffer1[0] = (x >> 8);
  buffer1[1] = x;
  buffer1[2] = ((x + w - 1) >> 8);
  buffer1[3] = (x + w - 1);
  jshSPISendMany(LCD_SPI, buffer1, NULL, 4, NULL);
  jshPinSetValue(LCD_SPI_DC, 0); // command
  buffer1[0] = SPILCD_CMD_WINDOW_Y;
  jshSPISendMany(LCD_SPI, buffer1, NULL, 1, NULL);
  jshPinSetValue(LCD_SPI_DC, 1); // data
  buffer1[0] = (y >> 8);
  buffer1[1] = y;
  buffer1[2] = ((y + h - 1) >> 8);
  buffer1[3] = ((y + h - 1) & 0xFF);
  jshSPISendMany(LCD_SPI, buffer1, NULL, 4, NULL);
  jshPinSetValue(LCD_SPI_DC, 0); // command
  buffer1[0] = SPILCD_CMD_DATA;
  jshSPISendMany(LCD_SPI, buffer1, NULL, 1, NULL);
  jshPinSetValue(LCD_SPI_DC, 1); // data

  // FIXME: hack because SPI send on NRF52 fails for >65k transfers
  // we should fix this in jshardware.c

  int c = (w * h) * 2;
  while (c) {
    int n = c;
    if (n>65535) n=65535;
    jshSPISendMany(
        LCD_SPI,
        data,
        0,
        n,
        NULL);
    if (jspIsInterrupted()) break;
    data+=n;
    c-=n;
  }
  jshPinSetValue(LCD_SPI_CS,1);
#ifdef ESPR_USE_SPI3
  // anomaly 195 workaround - disable SPI when done
  *(volatile uint32_t *)0x4002F500 = 0;
  *(volatile uint32_t *)0x4002F004 = 1;
#endif

}


void lcdInit_SPINRF() {

#ifdef LCD_BL
  jshPinOutput(LCD_BL, 1);
#endif
#ifdef LCD_EN
  jshPinOutput(LCD_EN, 1);
#endif
  jshPinOutput(LCD_SPI_CS,1);
  jshPinOutput(LCD_SPI_DC,1);
  jshPinOutput(LCD_SPI_SCK,1);
  jshPinOutput(LCD_SPI_MOSI,1);
#ifdef LCD_SPI_RST
  jshPinOutput(LCD_SPI_RST,0);
  jshDelayMicroseconds(1000);
  jshPinOutput(LCD_SPI_RST, 1);
  jshDelayMicroseconds(2000);
#endif
  JshSPIInfo inf;
  jshSPIInitInfo(&inf);
#ifndef LCD_SPI_BITRATE
#define LCD_SPI_BITRATE 8000000
#endif
  inf.baudRate = LCD_SPI_BITRATE;
  inf.pinMOSI = LCD_SPI_MOSI;
#ifdef LCD_SPI_MISO
  inf.pinMISO = LCD_SPI_MISO;
#endif
  inf.pinSCK = LCD_SPI_SCK;
  jshSPISetup(LCD_SPI, &inf);
#if defined(NRF52_SERIES) // configure 'high drive' for GPIOs
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
#endif

  lcdSendInitCmd_SPINRF();
}


