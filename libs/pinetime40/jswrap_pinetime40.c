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
#include "jswrap_graphics.h"

#define DEFAULT_ACCEL_POLL_INTERVAL 80 // in msec - 12.5 hz to match accelerometer

JshI2CInfo i2cTouch;
#define TOUCH_I2C &i2cTouch

APP_TIMER_DEF(m_peripheral_poll_timer_id);
volatile uint16_t pollInterval; // in ms

// Nordic app timer to handle backlight PWM
APP_TIMER_DEF(m_backlight_on_timer_id);
APP_TIMER_DEF(m_backlight_off_timer_id);
#define BACKLIGHT_PWM_INTERVAL 15 // in msec - 67Hz PWM

/// LCD Brightness - 255=full
uint8_t lcdBrightness;
/// Actual LCD brightness (if we fade to a new brightness level)
uint8_t realLcdBrightness;
bool lcdFadeHandlerActive;

/*JSON{
    "type": "class",
    "class" : "Pinetime",
    "ifdef" : "PINETIME40"
}
Class containing utility functions for
[Pinetime40.js](https://www.joaquim.org/pinetime-upgrade-board)
*/


void graphicsInternalFlip() {
  lcdFlip_SPILCD(&graphicsInternal);  
}

/// Flip buffer contents with the screen.
void lcd_flip(JsVar* parent, bool all) {
  graphicsInternalFlip();
}


NO_INLINE void jswrap_pinetime40_setTheme() {
  graphicsTheme.fg = GRAPHICS_COL_RGB_TO_16(255, 255, 255);
  graphicsTheme.bg = GRAPHICS_COL_RGB_TO_16(0, 0, 0);
  graphicsTheme.fg2 = GRAPHICS_COL_RGB_TO_16(255, 255, 255);
  graphicsTheme.bg2 = GRAPHICS_COL_RGB_TO_16(0, 0, 63);
  graphicsTheme.fgH = GRAPHICS_COL_RGB_TO_16(255, 255, 255);
  graphicsTheme.bgH = GRAPHICS_COL_RGB_TO_16(0, 95, 190);
  graphicsTheme.dark = true;
}

void btnHandlerCommon(int button, bool state, IOEventFlags flags) {
}

/* Scan peripherals for any data that's needed
 * Also, holding down both buttons will reboot */
void peripheralPollHandler() {
  jshKickWatchDog();
}

void btn1Handler(bool state, IOEventFlags flags) {
  btnHandlerCommon(1,state,flags);
}

void jswrap_pinetime40_pwrBacklight(bool on) {
  jshPinOutput(LCD_BL, on);
}

void backlightOnHandler() {
  //if (i2cBusy) return;
  jswrap_pinetime40_pwrBacklight(true); // backlight on
  //app_timer_start(m_backlight_off_timer_id, APP_TIMER_TICKS(BACKLIGHT_PWM_INTERVAL, APP_TIMER_PRESCALER) * lcdBrightness >> 8, NULL);
}
void backlightOffHandler() {
  //if (i2cBusy) return;
  jswrap_pinetime40_pwrBacklight(false); // backlight off
}

/*JSON{
  "type" : "hwinit",
  "generate" : "jswrap_pinetime40_hwinit"
}*/
NO_INLINE void jswrap_pinetime40_hwinit() {

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
  lcdInit_SPILCD(&graphicsInternal);
  lcdSetCallbacks_SPILCD(&graphicsInternal);

  // set default graphics themes - before we even start to load settings.json
  jswrap_pinetime40_setTheme();
  graphicsFillRect(&graphicsInternal, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, graphicsTheme.bg2);

  jsiConsolePrintf("HWINIT DONE\n");
}

JsVar *jswrap_pinetime_getLogo();

/*JSON{
  "type" : "init",
  "generate" : "jswrap_pinetime40_init"
}*/
NO_INLINE void jswrap_pinetime40_init() {

   IOEventFlags channel;

   static bool firstStart = true;

  // Backlight
  jswrap_pinetime40_pwrBacklight(true);

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

  graphicsInternal.data.fontSize = JSGRAPHICS_FONTSIZE_6X8+1; // 4x6 size is default
  graphicsClear(&graphicsInternal);

  JsVar *img = jsfReadFile(jsfNameFromString(".splash"),0,0);
  int w,h,y;
  h = 0;
  if (jsvIsString(img) || jsvGetStringLength(img)) { 
    w = (int)(unsigned char)jsvGetCharInString(img, 0);
    h = (int)(unsigned char)jsvGetCharInString(img, 1);
    y=(LCD_HEIGHT-h)/2;
    jsvUnLock2(jswrap_graphics_drawImage(graphics,img,(LCD_WIDTH-w)/2,y,NULL),img);    
  } else {
    y=LCD_HEIGHT/2;
  }  
  if (h > 0) y += h + 10;  
  char addrStr[20];
  JsVar *addr = jswrap_ble_getAddress(); // Write MAC address in bottom right
  jsvGetString(addr, addrStr, sizeof(addrStr));
  jsvUnLock(addr);
  jswrap_graphics_drawCString(&graphicsInternal,60,y,JS_VERSION);
  jswrap_graphics_drawCString(&graphicsInternal,60,y+10,"Espruino - nRF52840");
  jswrap_graphics_drawCString(&graphicsInternal,60,y+20,addrStr);
  jswrap_graphics_drawCString(&graphicsInternal,60,y+30,"PineTime 40 - joaquim.org");

  graphicsInternalFlip();
  graphicsStructResetState(&graphicsInternal);

  
  jshEnableWatchDog(5); // 5 second watchdog

  pollInterval = DEFAULT_ACCEL_POLL_INTERVAL;

  uint32_t err_code = app_timer_create(&m_peripheral_poll_timer_id,
    APP_TIMER_MODE_REPEATED,
    peripheralPollHandler);
  jsble_check_error(err_code);
  app_timer_start(m_peripheral_poll_timer_id, APP_TIMER_TICKS(pollInterval), NULL);


  // Backlight PWM
  err_code = app_timer_create(&m_backlight_on_timer_id,
                        APP_TIMER_MODE_REPEATED,
                        backlightOnHandler);
  jsble_check_error(err_code);
  err_code = app_timer_create(&m_backlight_off_timer_id,
                      APP_TIMER_MODE_SINGLE_SHOT,
                      backlightOffHandler);
  jsble_check_error(err_code);

  jshSetPinShouldStayWatched(BTN1_PININDEX,true);

  channel = jshPinWatch(BTN1_PININDEX, true, JSPW_NONE);
  if (channel!=EV_NONE) jshSetEventCallback(channel, btn1Handler);

  jsiConsolePrintf("INIT DONE\n");


  firstStart = false;

  //jsvUnLock(jspEvaluate("setTimeout(Pinetime.load,5000);",true));

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


/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "load",
    "generate_js" : "libs/js/pinetime40/load.js",
    "params" : [
      ["file","JsVar","[optional] A string containing the file name for the app to be loaded"]
    ],
    "ifdef" : "PINETIME40",
    "typescript": [
      "load(file: string): void;",
      "load(): void;"
    ]
}
*/
