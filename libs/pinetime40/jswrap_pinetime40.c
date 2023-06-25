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

typedef enum {
  TS_NONE = 0,
  TS_LEFT = 1,
  TS_RIGHT = 2,
  TS_BOTH = 3,
  TS_SWIPED = 4
} TouchState;
TouchState touchLastState;
TouchState touchStatus;
typedef enum {
  TG_SWIPE_NONE,
  TG_SWIPE_LEFT,
  TG_SWIPE_RIGHT,
  TG_SWIPE_UP,
  TG_SWIPE_DOWN,
} TouchGestureType;
TouchGestureType touchGesture;
short lastTouchX, lastTouchY;
short touchX, touchY;
bool touchPts, lastTouchPts;
unsigned char touchType;
short touchMinX = 0, touchMinY = 0, touchMaxX = 240, touchMaxY = 240;

void touchHandler(bool state, IOEventFlags flags);

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

/// get battery percentage
JsVarInt jswrap_pinetime40_getBattery() {

  JsVarFloat v = jshPinAnalog(BAT_PIN_VOLTAGE);

  const JsVarFloat vlo = 0.3100;
  const JsVarFloat vhi = 0.4255; 

  int pc = (v-vlo)*100/(vhi-vlo);
  if (pc>100) pc=100;
  if (pc<0) pc=0;
  return pc;

}

void btnHandlerCommon(int button, bool state, IOEventFlags flags) {
  if (state) {
    jsiConsolePrintf("BT1 Pressed...\n");
  }
}

/* Scan peripherals for any data that's needed
 * Also, holding down both buttons will reboot */
void peripheralPollHandler() {
  jshKickWatchDog();
}

void btn1Handler(bool state, IOEventFlags flags) {
  btnHandlerCommon(1, state, flags);
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

  jshI2CInitInfo(&i2cTouch);
  i2cTouch.bitrate = 0x7FFFFFFF; // make it as fast as we can go
  i2cTouch.pinSDA = TOUCH_PIN_SDA;
  i2cTouch.pinSCL = TOUCH_PIN_SCL;
  jsi2cSetup(&i2cTouch);

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

JsVar* jswrap_pinetime_getLogo();

/*JSON{
  "type" : "init",
  "generate" : "jswrap_pinetime40_init"
}*/
NO_INLINE void jswrap_pinetime40_init() {

  IOEventFlags channel;

  static bool firstStart = true;  

  // Backlight
  jswrap_pinetime40_pwrBacklight(true);

  jshSetPinShouldStayWatched(BTN1_PININDEX, true);
  channel = jshPinWatch(BTN1_PININDEX, true, JSPW_NONE);
  if (channel != EV_NONE) jshSetEventCallback(channel, btn1Handler);

  jshSetPinShouldStayWatched(TOUCH_PIN_IRQ, true);
  channel = jshPinWatch(TOUCH_PIN_IRQ, true, JSPW_NONE);
  if (channel != EV_NONE) jshSetEventCallback(channel, touchHandler);

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

  graphicsInternal.data.fontSize = JSGRAPHICS_FONTSIZE_6X8 + 1; // 4x6 size is default
  graphicsClear(&graphicsInternal);

  JsVar* img = jsfReadFile(jsfNameFromString(".splash"), 0, 0);
  int w, h, y;
  h = 0;
  if (jsvIsString(img) || jsvGetStringLength(img)) {
    w = (int)(unsigned char)jsvGetCharInString(img, 0);
    h = (int)(unsigned char)jsvGetCharInString(img, 1);
    y = (LCD_HEIGHT - h) / 2;
    jsvUnLock2(jswrap_graphics_drawImage(graphics, img, (LCD_WIDTH - w) / 2, y, NULL), img);
  }
  else {
    y = LCD_HEIGHT / 2;
  }
  if (h > 0) y += h + 10;
  char addrStr[20];
  JsVar* addr = jswrap_ble_getAddress(); // Write MAC address in bottom right
  jsvGetString(addr, addrStr, sizeof(addrStr));
  jsvUnLock(addr);
  jswrap_graphics_drawCString(&graphicsInternal, 60, y, JS_VERSION);
  jswrap_graphics_drawCString(&graphicsInternal, 60, y + 10, "Espruino - nRF52840");
  jswrap_graphics_drawCString(&graphicsInternal, 60, y + 20, addrStr);
  jswrap_graphics_drawCString(&graphicsInternal, 60, y + 30, "PineTime 40 - joaquim.org");

  graphicsInternalFlip();
  graphicsStructResetState(&graphicsInternal);

  if (firstStart) {
    jshEnableWatchDog(10); // 5 second watchdog

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


    jsiConsolePrintf("FIRST INIT DONE\n");
    jsvUnLock(jspEvaluate("setTimeout(Pinetime.load,1000)", true));
  }
  else
  {
    jsiConsolePrintf("HOT INIT DONE\n");
  }


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



/*******************************************************************/

// Convert Touchscreen gesture based on graphics orientation
TouchGestureType touchSwipeRotate(TouchGestureType g) {
  // gesture is the value that comes straight from the touchscreen
  if (graphicsInternal.data.flags & JSGRAPHICSFLAGS_INVERT_X) {
    if (g == TG_SWIPE_LEFT) g = TG_SWIPE_RIGHT;
    else if (g == TG_SWIPE_RIGHT) g = TG_SWIPE_LEFT;
  }
  if (graphicsInternal.data.flags & JSGRAPHICSFLAGS_INVERT_Y) {
    if (g == TG_SWIPE_UP) g = TG_SWIPE_DOWN;
    else if (g == TG_SWIPE_DOWN) g = TG_SWIPE_UP;
  }
  if (graphicsInternal.data.flags & JSGRAPHICSFLAGS_SWAP_XY) {
    if (g == TG_SWIPE_LEFT) g = TG_SWIPE_UP;
    else if (g == TG_SWIPE_RIGHT) g = TG_SWIPE_DOWN;
    else if (g == TG_SWIPE_UP) g = TG_SWIPE_LEFT;
    else if (g == TG_SWIPE_DOWN) g = TG_SWIPE_RIGHT;
  }
  return g;
}

void touchHandlerInternal(int tx, int ty, int pts, int gesture) {
  // ignore if locked
  // deal with the case where we rotated the screen
  deviceToGraphicsCoordinates(&graphicsInternal, &tx, &ty);

  int dx = tx - touchX;
  int dy = ty - touchY;

  touchX = tx;
  touchY = ty;
  touchPts = pts;

  static int lastGesture = 0;
  if (gesture != lastGesture) {
    switch (gesture) { // gesture
    case 0:break; // no gesture
    case 1: // slide down
      touchGesture = touchSwipeRotate(TG_SWIPE_DOWN);
      //jsiConsolePrintf("TS D\n");
      break;
    case 2: // slide up
      touchGesture = touchSwipeRotate(TG_SWIPE_UP);
      //jsiConsolePrintf("TS U\n");
      break;
    case 3: // slide left
      touchGesture = touchSwipeRotate(TG_SWIPE_LEFT);
      //jsiConsolePrintf("TS L\n");
      break;
    case 4: // slide right
      touchGesture = touchSwipeRotate(TG_SWIPE_RIGHT);
      //jsiConsolePrintf("TS R\n");
      break;
    case 5: // single click
      jsiConsolePrintf("TS click\n");
      touchType = 0;
      break;
    case 0x0B:     // double touch

      touchType = 1;
      break;
    case 0x0C:     // long touch

      touchType = 2;
      break;
    }

    jshHadEvent();
  }

  if (touchPts != lastTouchPts || lastTouchX != touchX || lastTouchY != touchY) {

    // ensure we don't sleep if touchscreen is being used
    //inactivityTimer = 0;
  }
  // Ensure we process events if we modified bangleTasks
  /*if (lastBangleTasks != bangleTasks)
    jshHadEvent();*/

  lastGesture = gesture;
}

void touchHandler(bool state, IOEventFlags flags) {
  if (state) return; // only interested in when low
  // Ok, now get touch info
  unsigned char buf[6];
  buf[0] = 1;
  jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 1, buf, false);
  jsi2cRead(TOUCH_I2C, TOUCH_ADDR, 6, buf, true);

  // 0: Gesture type
  // 1: touch pts (0 or 1)
  // 2: Status / X hi (0x00 first, 0x80 pressed, 0x40 released)
  // 3: X lo (0..160)
  // 4: Y hi
  // 5: Y lo (0..160)

  int tx = buf[3]/* | ((buf[2] & 0x0F)<<8)*/; // top bits are never used on our touchscreen
  int ty = buf[5]/* | ((buf[4] & 0x0F)<<8)*/;
  if (tx >= 250) tx = 0; // on some devices, 251-255 gets reported for touches right at the top of the screen
  if (ty >= 250) ty = 0;
  touchHandlerInternal(
    (tx - touchMinX) * LCD_WIDTH / (touchMaxX - touchMinX), // touchX
    (ty - touchMinY) * LCD_HEIGHT / (touchMaxY - touchMinY), // touchY
    buf[1], // touchPts
    buf[0]); // gesture
}


/*******************************************************************/

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
