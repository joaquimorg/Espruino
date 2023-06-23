#include <jswrap_pinetime40.h>

#include "jsinteractive.h"
#include "jsdevices.h"
#include "jsnative.h"
#include "jshardware.h"
#include "jsdevices.h"
#include "jspin.h"
#include "jstimer.h"
#include "jswrap_promise.h"
#include "jswrap_date.h"
#include "jswrap_math.h"
#include "jswrap_storage.h"
#include "jswrap_array.h"
#include "jswrap_arraybuffer.h"
#include "jswrap_heatshrink.h"
#include "jswrap_espruino.h"
#include "jswrap_terminal.h"
#include "jsflash.h"
#include "graphics.h"
#include "bitmap_font_6x8.h"
#include "jswrap_bluetooth.h"
#include "app_timer.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_soc.h"
#include "nrf_saadc.h"
#include "nrf5x_utils.h"

#include "bluetooth.h" // for self-test
#include "jsi2c.h" // accelerometer/etc

#include "lcd_spilcd.h"
#include "lcd_spi_unbuf.h"
#include "jswrap_graphics.h"

#define DEFAULT_ACCEL_POLL_INTERVAL 80 // in msec - 12.5 hz to match accelerometer

JshI2CInfo i2cTouch;
#define TOUCH_I2C &i2cTouch

APP_TIMER_DEF(m_peripheral_poll_timer_id);

volatile uint16_t pollInterval; // in ms

/*TYPESCRIPT
declare const BTN1: Pin;

declare const g: Graphics<false>;

/*JSON{
  "type": "class",
  "class" : "Pinetime40",
  "ifdef" : "PINETIME40JS"
}
*/
/*TYPESCRIPT{
  "class" : "Pinetime40"
}
static CLOCK: ShortBoolean;
static strokes: undefined | { [key: string]: Unistroke };
*/
/*TYPESCRIPT
type ShortBoolean = boolean | 0 | 1;
*/


void graphicsInternalFlip() {
  //lcdFlip_SPILCD(&graphicsInternal);
}

/// Flip buffer contents with the screen.
void lcd_flip(JsVar* parent, bool all) {
#ifdef LCD_WIDTH
  if (all) {
    graphicsInternal.data.modMinX = 0;
    graphicsInternal.data.modMinY = 0;
    graphicsInternal.data.modMaxX = LCD_WIDTH - 1;
    graphicsInternal.data.modMaxY = LCD_HEIGHT - 1;
  }
  graphicsInternalFlip();
#endif
}


NO_INLINE void jswrap_pinetime40_setTheme() {
  graphicsTheme.fg = GRAPHICS_COL_RGB_TO_16(255, 255, 255);
  graphicsTheme.bg = GRAPHICS_COL_RGB_TO_16(0, 0, 255);
  graphicsTheme.fg2 = GRAPHICS_COL_RGB_TO_16(255, 255, 255);
  graphicsTheme.bg2 = GRAPHICS_COL_RGB_TO_16(0, 0, 63);
  graphicsTheme.fgH = GRAPHICS_COL_RGB_TO_16(255, 255, 255);
  graphicsTheme.bgH = GRAPHICS_COL_RGB_TO_16(0, 95, 190);
  graphicsTheme.dark = true;
}

/* Scan peripherals for any data that's needed
 * Also, holding down both buttons will reboot */
void peripheralPollHandler() {

  jshKickWatchDog();

}

/*JSON{
  "type" : "hwinit",
  "generate" : "jswrap_pinetime40_hwinit"
}*/
NO_INLINE void jswrap_pinetime40_hwinit() {

  jshPinOutput(LCD_BL, 1); // Backlight

  /*jshI2CInitInfo(&i2cTouch);
  i2cTouch.bitrate = 0x7FFFFFFF; // make it as fast as we can go
  i2cTouch.pinSDA = TOUCH_PIN_SDA;
  i2cTouch.pinSCL = TOUCH_PIN_SCL;
  jsi2cSetup(&i2cTouch);*/

  // Touch init
  jshPinOutput(TOUCH_PIN_RST, 0);
  jshDelayMicroseconds(1000);
  jshPinOutput(TOUCH_PIN_RST, 1);

  graphicsStructInit(&graphicsInternal, LCD_WIDTH, LCD_HEIGHT, LCD_BPP);
  graphicsInternal.data.type = JSGRAPHICSTYPE_SPILCD;
  graphicsInternal.data.flags = 0;
  graphicsInternal.data.fontSize = JSGRAPHICS_FONTSIZE_6X8 + 1; // 4x6 size is default
  //lcdInit_SPILCD(&graphicsInternal);
  //graphicsSetCallbacks(&graphicsInternal);
  lcd_spi_unbuf_setCallbacks(&graphicsInternal);
  // set default graphics themes - before we even start to load settings.json
  jswrap_pinetime40_setTheme();
  graphicsFillRect(&graphicsInternal, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, graphicsTheme.bg);

}

/*JSON{
  "type" : "init",
  "generate" : "jswrap_pinetime40_init"
}*/
NO_INLINE void jswrap_pinetime40_init() {

  // Reset global graphics instance
  graphicsStructResetState(&graphicsInternal);

  // Create backing graphics object for LCD
  JsVar* graphics = jspNewObject(0, "Graphics");
  // if there's nothing in the Graphics object, we assume it's for the built-in graphics
  if (!graphics) return; // low memory
  // add it as a global var
  jsvObjectSetChild(execInfo.root, "g", graphics);
  jsvObjectSetChild(execInfo.hiddenRoot, JS_GRAPHICS_VAR, graphics);
  graphicsInternal.graphicsVar = graphics;

  // Create 'flip' fn
  JsVar* fn = jsvNewNativeFunction((void (*)(void))lcd_flip, JSWAT_VOID | JSWAT_THIS_ARG | (JSWAT_BOOL << (JSWAT_BITS * 1)));
  jsvObjectSetChildAndUnLock(graphics, "flip", fn);


  // otherwise render the standard 'Loading...' box
  int x = LCD_WIDTH / 2;
  int y = LCD_HEIGHT / 2;
  graphicsFillRect(&graphicsInternal, x - 49, y - 19, x + 49, y + 19, graphicsTheme.bg);
  graphicsInternal.data.fgColor = graphicsTheme.fg;
  graphicsDrawRect(&graphicsInternal, x - 50, y - 20, x + 50, y + 20);
  y -= 4;
  x -= 4 * 6;
  const char* s = "Loading...";
  while (*s) {
    graphicsDrawChar6x8(&graphicsInternal, x, y, *s, 1, 1, false);
    x += 6;
    s++;
  }
  graphicsInternalFlip();

  jshEnableWatchDog(5); // 5 second watchdog

  pollInterval = DEFAULT_ACCEL_POLL_INTERVAL;

  uint32_t err_code = app_timer_create(&m_peripheral_poll_timer_id,
    APP_TIMER_MODE_REPEATED,
    peripheralPollHandler);
  jsble_check_error(err_code);
  app_timer_start(m_peripheral_poll_timer_id, APP_TIMER_TICKS(pollInterval), NULL);

  graphicsStructResetState(&graphicsInternal);

}

/*JSON{
  "type" : "idle",
  "generate" : "jswrap_pinetime40_idle"
}*/
bool jswrap_pinetime40_idle() {
  return false;
}


/*JSON{
  "type" : "kill",
  "generate" : "jswrap_pinetime40_kill"
}*/
void jswrap_pinetime40_kill() {

  // Graphics var is getting removed, so set this to null.
  jsvUnLock(graphicsInternal.graphicsVar);
  graphicsInternal.graphicsVar = NULL;

}

