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

/*TYPESCRIPT
declare const BTN1: Pin;

declare const g: Graphics<false>;

type WidgetArea = "tl" | "tr" | "bl" | "br";
type Widget = {
  area: WidgetArea;
  width: number;
  sortorder?: number;
  draw: (this: Widget, w: Widget) => void;
  x?: number;
  y?: number;
};
declare const WIDGETS: { [key: string]: Widget };
*/

/*JSON{
    "type": "class",
    "class" : "Pinetime",
    "ifdef" : "PINETIME40"
}
Class containing utility functions for
[Pinetime40.js](https://www.joaquim.org/pinetime-upgrade-board)
*/
/*TYPESCRIPT{
  "class" : "Pinetime"
}
static CLOCK: ShortBoolean;
static strokes: undefined | { [key: string]: Unistroke };
*/
/*TYPESCRIPT
type ShortBoolean = boolean | 0 | 1;
*/

/*JSON{
  "type" : "variable",
  "name" : "VIBRATE",
  "generate_full" : "VIBRATE_PIN",
  "ifdef" : "PINETIME40",
  "return" : ["pin",""]
}
The Pinetime's vibration motor.
*/

/*TYPESCRIPT
type AccelData = {
  x: number;
  y: number;
  z: number;
  diff: number;
  mag: number;
};
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "accel",
  "params" : [["xyz","JsVar",""]],
  "ifdef" : "PINETIME40",
  "typescript": "on(event: \"accel\", callback: (xyz: AccelData) => void): void;"
}
Accelerometer data available with `{x,y,z,diff,mag}` object as a parameter.

* `x` is X axis (left-right) in `g`
* `y` is Y axis (up-down) in `g`
* `z` is Z axis (in-out) in `g`
* `diff` is difference between this and the last reading in `g`
* `mag` is the magnitude of the acceleration in `g`

You can also retrieve the most recent reading with `Pinetime.getAccel()`.
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "step",
  "params" : [["up","int","The number of steps since Pinetime was last reset"]],
  "ifdef" : "PINETIME40"
}
Called whenever a step is detected by Pinetime's pedometer.
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "charging",
  "params" : [["charging","bool","`true` if charging"]],
  "ifdef" : "PINETIME40"
}
Is the battery charging or not?
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "lcdPower",
  "params" : [["on","bool","`true` if screen is on"]],
  "ifdef" : "PINETIME40"
}
Has the screen been turned on or off? Can be used to stop tasks that are no
longer useful if nothing is displayed. Also see `Pinetime.isLCDOn()`
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "gesture",
  "params" : [["xyz","JsVar","An Int8Array of XYZXYZXYZ data"]],
  "ifdef" : "PINETIME40",
  "typescript" : "on(event: \"gesture\", callback: (xyz: Int8Array) => void): void;"
}
Emitted when a 'gesture' (fast movement) is detected
*/
/*TYPESCRIPT
type SwipeCallback = (directionLR: -1 | 0 | 1, directionUD?: -1 | 0 | 1) => void;
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "swipe",
  "params" : [["directionLR","int","`-1` for left, `1` for right, `0` for up/down"],
              ["directionUD","int","`-1` for up, `1` for down, `0` for left/right"]],
  "ifdef" : "PINETIME40",
  "typescript" : "on(event: \"swipe\", callback: SwipeCallback): void;"
}
Emitted when a swipe on the touchscreen is detected (a movement from
left->right, right->left, down->up or up->down)
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "touch",
  "params" : [
    ["button","int","`1` for left, `2` for right"],
    ["xy","JsVar","Object of form `{x,y,type}` containing touch coordinates (if the device supports full touch). "]
  ],
  "ifdef" : "PINETIME40",
  "typescript" : "on(event: \"touch\", callback: TouchCallback): void;"
}
Emitted when the touchscreen is pressed
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "midnight",
  "ifdef" : "PINETIME40"
}
Emitted at midnight (at the point the `day` health info is reset to 0).

Can be used for housekeeping tasks that don't want to be run during the day.
*/

#define HOME_BTN 1
#define HOME_BTN_PININDEX    BTN1_PININDEX

volatile uint16_t inactivityTimer; // in ms
volatile uint16_t homeBtnTimer; // in ms
int btnLoadTimeout; // in ms
int lcdPowerTimeout; // in ms
int backlightTimeout; // in ms
JsSysTime lcdWakeButtonTime;
char lcdWakeButton;
volatile uint16_t homeBtnInterruptTimer; // in ms
volatile uint16_t chargeTimer; // in ms
volatile bool wasCharging;


#define TIMER_MAX 60000 // 60 sec - enough to fit in uint16_t without overflow if we add ACCEL_POLL_INTERVAL
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


typedef enum {
  JSPF_NONE,
  JSPF_WAKEON_FACEUP = 1 << 0,
  JSPF_WAKEON_BTN1 = 1 << 1,
  JSPF_WAKEON_TOUCH = 1 << 2,
  JSPF_BEEP_VIBRATE = 1 << 3,
  JSPF_ACCEL_LISTENER = 1 << 4, ///< we have a listener for accelerometer data
  JSPF_POWER_SAVE = 1 << 5, ///< if no movement detected for a while, lower the accelerometer poll interval
  JSPF_HRM_ON = 1 << 6,
  JSPF_LCD_ON = 1 << 7,
  JSPF_LCD_BL_ON = 1 << 8,
  JSPF_LOCKED = 1 << 9,
  JSPF_HRM_INSTANT_LISTENER = 1 << 10,

  JSPF_DEFAULT = ///< default at power-on
  JSPF_WAKEON_BTN1 | JSPF_WAKEON_FACEUP
} JsPinetimeFlags;
volatile JsPinetimeFlags pinetimeFlags = JSPF_NONE;


typedef enum {
  JSPT_NONE,
  JSPT_RESET = 1 << 0, ///< reset the watch and reload code from flash
  JSPT_LCD_ON = 1 << 1, ///< LCD controller (can turn this on without the backlight)
  JSPT_LCD_OFF = 1 << 2,
  JSPT_LCD_BL_ON = 1 << 3, ///< LCD backlight
  JSPT_LCD_BL_OFF = 1 << 4,
  JSPT_LOCK = 1 << 5, ///< watch is locked
  JSPT_UNLOCK = 1 << 6, ///< watch is unlocked
  JSPT_ACCEL_DATA = 1 << 7, ///< need to push xyz data to JS
  JSPT_ACCEL_TAPPED = 1 << 8, ///< tap event detected
  JSPT_MAG_DATA = 1 << 14, ///< need to push magnetometer data to JS
  JSPT_GESTURE_DATA = 1 << 15, ///< we have data from a gesture
  JSPT_HRM_DATA = 1 << 16, ///< Heart rate data is ready for analysis
  JSPT_CHARGE_EVENT = 1 << 17, ///< we need to fire a charging event
  JSPT_STEP_EVENT = 1 << 18, ///< we've detected a step via the pedometer
  JSPT_SWIPE = 1 << 19, ///< swiped over touchscreen, info in touchGesture
  JSPT_TOUCH_LEFT = 1 << 20, ///< touch lhs of touchscreen
  JSPT_TOUCH_RIGHT = 1 << 21, ///< touch rhs of touchscreen
  JSPT_TOUCH_MASK = JSPT_TOUCH_LEFT | JSPT_TOUCH_RIGHT,
  JSPT_DRAG = 1 << 22,
  JSPT_TWIST_EVENT = 1 << 24, ///< Watch was twisted
  JSPT_FACE_UP = 1 << 25, ///< Watch was turned face up/down (faceUp holds the actual state)
  JSPT_ACCEL_INTERVAL_DEFAULT = 1 << 26, ///< reschedule accelerometer poll handler to default speed
  JSPT_ACCEL_INTERVAL_POWERSAVE = 1 << 27, ///< reschedule accelerometer poll handler to powersave speed
  JSPT_HRM_INSTANT_DATA = 1 << 28, ///< Instant heart rate data
  JSPT_HEALTH = 1 << 29, ///< New 'health' event
  JSPT_MIDNIGHT = 1 << 30, ///< Fired at midnight each day - for housekeeping tasks
} JsPinetimeTasks;
JsPinetimeTasks pinetimeTasks;

static void jswrap_pinetime40_setLCDPowerBacklight(bool isOn);

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


/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "isCharging",
    "generate" : "jswrap_pinetime40_isCharging",
    "return" : ["bool","Is the battery charging or not?"],
    "ifdef" : "PINETIME40"
}
*/
// emscripten bug means we can't use 'bool' as return value here!
int jswrap_pinetime40_isCharging() {
#ifdef BAT_PIN_CHARGING
  return !jshPinGetValue(BAT_PIN_CHARGING);
#else
  return 0;
#endif
}

/// get battery percentage
JsVarInt jswrap_pinetime40_getBattery() {

  JsVarFloat v = jshPinAnalog(BAT_PIN_VOLTAGE);

  const JsVarFloat vlo = 0.3100;
  const JsVarFloat vhi = 0.4255;

  int pc = (v - vlo) * 100 / (vhi - vlo);
  if (pc > 100) pc = 100;
  if (pc < 0) pc = 0;
  return pc;

}

void btnHandlerCommon(int button, bool state, IOEventFlags flags) {
// wake up IF LCD power or Lock has a timeout (so will turn off automatically)
  if (lcdPowerTimeout || backlightTimeout) {
    if ((pinetimeFlags&JSPF_WAKEON_BTN1)&&(button==1)) {
      // if a 'hard' button, turn LCD on
      inactivityTimer = 0;
      if (state) {
        bool ignoreBtnUp = false;
        if (lcdPowerTimeout && !(pinetimeFlags&JSPF_LCD_ON) && state) {
          pinetimeTasks |= JSPT_LCD_ON;
          ignoreBtnUp = true;
        }
        if (backlightTimeout && !(pinetimeFlags&JSPF_LCD_BL_ON) && state) {
          pinetimeTasks |= JSPT_LCD_BL_ON;
          ignoreBtnUp = true;
        }
        if (ignoreBtnUp) {
          // This allows us to ignore subsequent button
          // rising or 'bounce' events
          lcdWakeButton = button;
          lcdWakeButtonTime = jshGetSystemTime() + jshGetTimeFromMilliseconds(100);
          return; // don't push button event if the LCD is off
        }
      }
    } else {
      // on touchscreen, keep LCD on if it was in previously
      if (pinetimeFlags&JSPF_LCD_ON)
        inactivityTimer = 0;
      else // else don't push the event
        return;
    }
  }
  // Handle case where pressing 'home' button repeatedly at just the wrong times
  // could cause us to go home!
  if (button == HOME_BTN) homeBtnTimer = 0;
  /* This stops the button 'up' or bounces from being
   propagated if the button was used to wake the LCD up */
  JsSysTime t = jshGetSystemTime();
  if (button == lcdWakeButton) {
    if ((t < lcdWakeButtonTime) || !state) {
      /* If it's a rising edge *or* it's within our debounce
       * period, reset the debounce timer and ignore it */
      lcdWakeButtonTime = t + jshGetTimeFromMilliseconds(100);
      return;
    } else {
      /* if the next event is a 'down', > 100ms after the last event, we propogate it
       and subsequent events */
      lcdWakeButton = 0;
      lcdWakeButtonTime = 0;
    }
  }
  // if not locked, add to the event queue for normal processing for watches
  if (!(pinetimeFlags&JSPF_LOCKED))
    jshPushIOEvent(flags | (state?EV_EXTI_IS_HIGH:0), t);
}

/* Scan peripherals for any data that's needed
 * Also, holding down both buttons will reboot */
void peripheralPollHandler() {

  JsSysTime time = jshGetSystemTime();
  // Handle watchdog
  if ((jshPinGetValue(BTN1_PININDEX)))
    jshKickWatchDog();

  // power on display if a button is pressed
  if (inactivityTimer < TIMER_MAX)
    inactivityTimer += pollInterval;
  // If button is held down, trigger a soft reset so we go back to the clock
  if (jshPinGetValue(HOME_BTN_PININDEX)) {
    if (homeBtnTimer < TIMER_MAX) {
      homeBtnTimer += pollInterval;
      if (btnLoadTimeout && (homeBtnTimer >= btnLoadTimeout)) {
        pinetimeTasks |= JSPT_RESET;
        jshHadEvent();
        homeBtnTimer = TIMER_MAX;
        // Allow home button to break out of debugger
        /*if (jsiStatus & JSIS_IN_DEBUGGER) {
          jsiStatus |= JSIS_EXIT_DEBUGGER;
          execInfo.execute |= EXEC_INTERRUPTED;
        }*/
      }
    }
    if (pinetimeTasks & JSPT_RESET) {
      homeBtnInterruptTimer += pollInterval;
      if (homeBtnInterruptTimer >= 500) {
        // We already wanted to reset but we didn't get back to idle loop in
        // 0.5 sec - let's force a break out of JS execution
        jsiConsolePrintf("Button held down - interrupting JS execution...\n");
        execInfo.execute |= EXEC_INTERRUPTED;
      }
    } else
      homeBtnInterruptTimer = 0;
  } else {
    homeBtnTimer = 0;
    homeBtnInterruptTimer = 0;
  }

  if (lcdPowerTimeout && (pinetimeFlags&JSPF_LCD_ON) && inactivityTimer>=lcdPowerTimeout) {
    // 10 seconds of inactivity, turn off display
    pinetimeTasks |= JSPT_LCD_OFF;
    jshHadEvent();
  }
  if (backlightTimeout && (pinetimeFlags&JSPF_LCD_BL_ON) && inactivityTimer>=backlightTimeout) {
    // 10 seconds of inactivity, turn off display
    pinetimeTasks |= JSPT_LCD_BL_OFF;
    jshHadEvent();
  }

  // check charge status
  if (chargeTimer < TIMER_MAX)
    chargeTimer += pollInterval;
  bool isCharging = jswrap_pinetime40_isCharging();
  if (isCharging != wasCharging) {
    wasCharging = isCharging;
    pinetimeTasks |= JSPT_CHARGE_EVENT;
    chargeTimer = 0;
    jshHadEvent();
  }

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
  app_timer_start(m_backlight_off_timer_id, APP_TIMER_TICKS(BACKLIGHT_PWM_INTERVAL) * lcdBrightness >> 8, NULL);
}
void backlightOffHandler() {
  //if (i2cBusy) return;
  jswrap_pinetime40_pwrBacklight(false); // backlight off
}


static void jswrap_pinetime40_setLCDPowerController(bool isOn) {

  if (isOn) { // wake
    lcdCmd_SPILCD(0x11, 0, NULL); // SLPOUT
    jshDelayMicroseconds(20);
    lcdCmd_SPILCD(0x29, 0, NULL); // DISPON
  } else { // sleep
    lcdCmd_SPILCD(0x28, 0, NULL); // DISPOFF
    jshDelayMicroseconds(20);
    lcdCmd_SPILCD(0x10, 0, NULL); // SLPIN
  }
#ifdef LCD_EN
  jshPinOutput(LCD_EN, isOn); // enable off
#endif
}

static void backlightFadeHandler() {
  int target = (pinetimeFlags & JSPF_LCD_ON) ? lcdBrightness : 0;
  int brightness = realLcdBrightness;
  int step = brightness >> 3; // to make this more linear
  if (step < 4) step = 4;
  if (target > brightness) {
    brightness += step;
    if (brightness > target)
      brightness = target;
  }
  else if (target < brightness) {
    brightness -= step;
    if (brightness < target)
      brightness = target;
  }
  realLcdBrightness = brightness;
  if (brightness == 0) jswrap_pinetime40_pwrBacklight(0);
  else if (realLcdBrightness == 255) jswrap_pinetime40_pwrBacklight(1);
  else {
    jshPinAnalogOutput(LCD_BL, realLcdBrightness / 256.0, 200, JSAOF_NONE);
  }
}

/// Turn just the backlight on or off (or adjust brightness)
static void jswrap_pinetime40_setLCDPowerBacklight(bool isOn) {
  if (isOn) pinetimeFlags |= JSPF_LCD_BL_ON;
  else pinetimeFlags &= ~JSPF_LCD_BL_ON;
  if (!lcdFadeHandlerActive) {
    JsSysTime t = jshGetTimeFromMilliseconds(10);
    jstExecuteFn(backlightFadeHandler, NULL, t, t, NULL);
    lcdFadeHandlerActive = true;
    backlightFadeHandler();
  }
}

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "setLCDPower",
    "generate" : "jswrap_pinetime40_setLCDPower",
    "params" : [
      ["isOn","bool","True if the LCD should be on, false if not"]
    ],
    "ifdef" : "PINETIME40"
}
This function can be used to turn Pinetime's LCD off or on.

This function resets the Pinetime's 'activity timer' (like pressing a button or
the screen would) so after a time period of inactivity set by
`Pinetime.setLCDTimeout` the screen will turn off.

If you want to keep the screen on permanently (until apps are changed) you can
do:

```
Pinetime.setLCDTimeout(0); // turn off the timeout
Pinetime.setLCDPower(1); // keep screen on
```

**When on full, the LCD draws roughly 40mA.** You can adjust When brightness
using `Pinetime.setLCDBrightness`.
*/
void jswrap_pinetime40_setLCDPower(bool isOn) {
  if (isOn) jswrap_pinetime40_setLCDPowerController(1);
  else jswrap_pinetime40_setLCDPowerBacklight(0); // RB: don't turn on the backlight here if fading is enabled
  jswrap_pinetime40_setLCDPowerBacklight(isOn);
  if (((pinetimeFlags & JSPF_LCD_ON) != 0) != isOn) {
    JsVar* pinetime = jsvObjectGetChildIfExists(execInfo.root, "Pinetime");
    if (pinetime) {
      JsVar* v = jsvNewFromBool(isOn);
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"lcdPower", &v, 1);
      jsvUnLock(v);
    }
    jsvUnLock(pinetime);
  }
  inactivityTimer = 0;
  if (isOn) pinetimeFlags |= JSPF_LCD_ON;
  else pinetimeFlags &= ~JSPF_LCD_ON;
}

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "setLCDBrightness",
    "generate" : "jswrap_pinetime40_setLCDBrightness",
    "params" : [
      ["brightness","float","The brightness of Pinetime's display - from 0(off) to 1(on full)"]
    ],
    "ifdef" : "PINETIME40"
}
This function can be used to adjust the brightness of Pinetime's display, and
hence prolong its battery life.

Due to hardware design constraints, software PWM has to be used which means that
the display may flicker slightly when Bluetooth is active and the display is not
at full power.

**Power consumption**

* 0 = 7mA
* 0.1 = 12mA
* 0.2 = 18mA
* 0.5 = 28mA
* 0.9 = 40mA (switching overhead)
* 1 = 40mA
*/
void jswrap_pinetime40_setLCDBrightness(JsVarFloat v) {
  int b = (int)(v * 256 + 0.5);
  if (b < 0) b = 0;
  if (b > 255) b = 255;
  lcdBrightness = b;
  if (pinetimeFlags & JSPF_LCD_ON)  // need to re-run to adjust brightness
    jswrap_pinetime40_setLCDPowerBacklight(1);
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
  //if (pinetimeFlags & JSPF_LOCKED) return;
  // deal with the case where we rotated the Bangle.js screen
  deviceToGraphicsCoordinates(&graphicsInternal, &tx, &ty);

  int dx = tx-touchX;
  int dy = ty-touchY;

  touchX = tx;
  touchY = ty;
  touchPts = pts;
  JsPinetimeTasks lastPinetimeTasks = pinetimeTasks;
  static int lastGesture = 0;
  if (gesture!=lastGesture) {
    switch (gesture) { // gesture
    case 0:break; // no gesture
    case 1: // slide down
      touchGesture = touchSwipeRotate(TG_SWIPE_DOWN);
      pinetimeTasks |= JSPT_SWIPE;
      break;
    case 2: // slide up
      touchGesture = touchSwipeRotate(TG_SWIPE_UP);
      pinetimeTasks |= JSPT_SWIPE;
      break;
    case 3: // slide left
      touchGesture = touchSwipeRotate(TG_SWIPE_LEFT);
      pinetimeTasks |= JSPT_SWIPE;
      break;
    case 4: // slide right
      touchGesture = touchSwipeRotate(TG_SWIPE_RIGHT);
      pinetimeTasks |= JSPT_SWIPE;
      break;
    case 5: // single click
      if (touchX<80) pinetimeTasks |= JSPT_TOUCH_LEFT;
      else pinetimeTasks |= JSPT_TOUCH_RIGHT;
      touchType = 0;
      break;
    case 0x0B:     // double touch
      if (touchX<80) pinetimeTasks |= JSPT_TOUCH_LEFT;
      else pinetimeTasks |= JSPT_TOUCH_RIGHT;
      touchType = 1;
      break;
    case 0x0C:     // long touch
      if (touchX<80) pinetimeTasks |= JSPT_TOUCH_LEFT;
      else pinetimeTasks |= JSPT_TOUCH_RIGHT;
      touchType = 2;
      break;
    }
  }

  if (touchPts!=lastTouchPts || lastTouchX!=touchX || lastTouchY!=touchY) {
    pinetimeTasks |= JSPT_DRAG;
    // ensure we don't sleep if touchscreen is being used
    inactivityTimer = 0;
  }
  // Ensure we process events if we modified pinetimeTasks
  if (lastPinetimeTasks != pinetimeTasks)
    jshHadEvent();

  if (touchPts != lastTouchPts || lastTouchX != touchX || lastTouchY != touchY) {

    // ensure we don't sleep if touchscreen is being used
    inactivityTimer = 0;
  }
  // Ensure we process events if we modified pinetimeTasks
  /*if (lastpinetimeTasks != pinetimeTasks)
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
    "type" : "staticproperty",
    "class" : "Pinetime",
    "name" : "appRect",
    "generate" : "jswrap_pinetime40_appRect",
    "return" : ["JsVar","An object of the form `{x,y,w,h,x2,y2}`"],
    "ifdef" : "PINETIME40",
    "typescript" : "appRect: { x: number, y: number, w: number, h: number, x2: number, y2: number };"
}
Returns the rectangle on the screen that is currently reserved for the app.
*/
JsVar* jswrap_pinetime40_appRect() {
  JsVar* o = jsvNewObject();
  if (!o) return 0;
  JsVar* widgetsVar = jsvObjectGetChildIfExists(execInfo.root, "WIDGETS");
  int top = 0, btm = 0; // size of various widget areas
  // check all widgets and see if any are in the top or bottom areas,
  // set top/btm accordingly
  if (jsvIsObject(widgetsVar)) {
    JsvObjectIterator it;
    jsvObjectIteratorNew(&it, widgetsVar);
    while (jsvObjectIteratorHasValue(&it)) {
      JsVar* widget = jsvObjectIteratorGetValue(&it);
      JsVar* area = jsvObjectGetChildIfExists(widget, "area");
      JsVar* width = jsvObjectGetChildIfExists(widget, "width");
      if (jsvIsString(area) && jsvIsNumeric(width)) {
        char a = jsvGetCharInString(area, 0);
        int w = jsvGetIntegerAndUnLock(width);
        if (a == 't' && w > 0) top = 24;
        if (a == 'b' && w > 0) btm = 24;
      }
      jsvUnLock2(area, widget);
      jsvObjectIteratorNext(&it);
    }
    jsvObjectIteratorFree(&it);
  }
  jsvUnLock(widgetsVar);
  jsvObjectSetChildAndUnLock(o, "x", jsvNewFromInteger(0));
  jsvObjectSetChildAndUnLock(o, "y", jsvNewFromInteger(top));
  jsvObjectSetChildAndUnLock(o, "w", jsvNewFromInteger(graphicsInternal.data.width));
  jsvObjectSetChildAndUnLock(o, "h", jsvNewFromInteger(graphicsInternal.data.height - (top + btm)));
  jsvObjectSetChildAndUnLock(o, "x2", jsvNewFromInteger(graphicsInternal.data.width - 1));
  jsvObjectSetChildAndUnLock(o, "y2", jsvNewFromInteger(graphicsInternal.data.height - (1 + btm)));

  return o;
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

/*JSON{
    "type" : "staticmethod",
    "class" : "E",
    "name" : "showAlert",
    "generate_js" : "libs/js/banglejs/E_showAlert.min.js",
    "params" : [
      ["message","JsVar","A message to display. Can include newlines"],
      ["options","JsVar","[optional] a title for the message or an object containing options"]
    ],
    "return" : ["JsVar","A promise that is resolved when 'Ok' is pressed"],
    "ifdef" : "PINETIME40",
    "typescript" : [
      "showAlert(message?: string, options?: string): Promise<void>;",
      "showAlert(message?: string, options?: { title?: string, remove?: () => void }): Promise<void>;"
    ]
}

Displays a full screen prompt on the screen, with a single 'Ok' button.

When the button is pressed the promise is resolved.

```
E.showAlert("Hello").then(function() {
  print("Ok pressed");
});
// or
E.showAlert("These are\nLots of\nLines","My Title").then(function() {
  print("Ok pressed");
});
```

To remove the window, call `E.showAlert()` with no arguments.
*/

/*JSON{
    "type" : "staticmethod",
    "class" : "E",
    "name" : "showMessage",
    "generate_js" : "libs/js/pinetime40/E_showMessage.min.js",
    "params" : [
      ["message","JsVar","A message to display. Can include newlines"],
      ["options","JsVar","[optional] a title for the message, or an object of options `{title:string, img:image_string}`"]
    ],
    "ifdef" : "PINETIME40",
    "typescript" : "showMessage(message: string, title?: string | { title?: string, img?: string }): void;"
}

A utility function for displaying a full screen message on the screen.

Draws to the screen and returns immediately.

```
E.showMessage("These are\nLots of\nLines","My Title")
```

or to display an image as well as text:

```
E.showMessage("Lots of text will wrap automatically",{
  title:"Warning",
  img:atob("FBQBAfgAf+Af/4P//D+fx/n+f5/v+f//n//5//+f//n////3//5/n+P//D//wf/4B/4AH4A=")
})
```

*/

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "loadWidgets",
    "generate_js" : "libs/js/banglejs/Bangle_loadWidgets.min.js",
    "ifdef" : "PINETIME40"
}
Load all widgets from flash Storage. Call this once at the beginning of your
application if you want any on-screen widgets to be loaded.

They will be loaded into a global `WIDGETS` array, and can be rendered with
`Pinetime.drawWidgets`.
*/

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "drawWidgets",
    "generate_js" : "libs/js/pinetime40/Pinetime_drawWidgets.min.js",
    "ifdef" : "PINETIME40"
}
Draw any onscreen widgets that were loaded with `Pinetime.loadWidgets()`.

Widgets should redraw themselves when something changes - you'll only need to
call drawWidgets if you decide to clear the entire screen with `g.clear()`.
*/


