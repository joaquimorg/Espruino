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
//#include "jswrap_terminal.h"
#include "jsflash.h"
//#include "graphics.h"
//#include "bitmap_font_6x8.h"
#include "jswrap_bluetooth.h"
#include "app_timer.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_soc.h"
#include "nrf_saadc.h"
#include "nrf5x_utils.h"

#include "bluetooth.h" // for self-test
#include "jsi2c.h" // accelerometer/etc

//#include "lcd_spilcd.h"
//#include "jswrap_graphics.h"

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

/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "lock",
  "params" : [["on","bool","`true` if screen is locked, `false` if it is unlocked and touchscreen/buttons will work"]],
  "ifdef" : "PINETIME40"
}
Has the screen been locked? Also see `Pinetime.isLocked()`
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


JsVar *promiseBeep;
JsVar *promiseBuzz;
unsigned short beepFreq;
unsigned char buzzAmt;

int twistThreshold = 800;
int twistMaxY = -800;
int twistTimeout = 1000;

#define TIMER_MAX 60000 // 60 sec - enough to fit in uint16_t without overflow if we add ACCEL_POLL_INTERVAL
#define DEFAULT_ACCEL_POLL_INTERVAL 80 // in msec - 12.5 hz to match accelerometer
#define DEFAULT_BTN_LOAD_TIMEOUT 1500
#define DEFAULT_LCD_POWER_TIMEOUT 30000
#define DEFAULT_BACKLIGHT_TIMEOUT DEFAULT_LCD_POWER_TIMEOUT
#define DEFAULT_LOCK_TIMEOUT 30000


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
  JSPF_ENABLE_BEEP = 1 << 11,
  JSPF_ENABLE_BUZZ = 1 << 12,

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

void jswrap_pinetime40_setLCDPowerBacklight(bool isOn);

APP_TIMER_DEF(m_peripheral_poll_timer_id);
volatile uint16_t pollInterval; // in ms


/// LCD Brightness - 255=full
uint8_t lcdBrightness;

void graphicsInternalFlip() {
  //lcdFlip_SPILCD(&graphicsInternal);
}

/// Flip buffer contents with the screen.
void lcd_flip(JsVar* parent, bool all) {
  graphicsInternalFlip();
}


NO_INLINE void jswrap_pinetime40_setTheme() {
  /*graphicsTheme.fg = GRAPHICS_COL_RGB_TO_16(255, 255, 255);
  graphicsTheme.bg = GRAPHICS_COL_RGB_TO_16(0, 0, 0);
  graphicsTheme.fg2 = GRAPHICS_COL_RGB_TO_16(255, 255, 255);
  graphicsTheme.bg2 = GRAPHICS_COL_RGB_TO_16(0, 0, 63);
  graphicsTheme.fgH = GRAPHICS_COL_RGB_TO_16(255, 255, 255);
  graphicsTheme.bgH = GRAPHICS_COL_RGB_TO_16(0, 95, 190);
  graphicsTheme.dark = true;*/
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
      //jsiConsolePrintf("BT\n");
      inactivityTimer = 0;
      if (state) {
        bool ignoreBtnUp = false;
        if (lcdPowerTimeout && !(pinetimeFlags&JSPF_LCD_ON) && state) {
          pinetimeTasks |= JSPT_LCD_ON;
          ignoreBtnUp = true;
          //jsiConsolePrintf("LCD on BT\n");
        }
        if (backlightTimeout && !(pinetimeFlags&JSPF_LCD_BL_ON) && state) {
          pinetimeTasks |= JSPT_LCD_BL_ON;
          ignoreBtnUp = true;
          //jsiConsolePrintf("BL on BT\n");
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
  if (jshPinGetValue(BTN1_PININDEX))
    jshKickWatchDog();

  // power on display if a button is pressed
  if (inactivityTimer < TIMER_MAX)
    inactivityTimer += pollInterval;
  // If button is held down, trigger a soft reset so we go back to the clock
  if (!jshPinGetValue(HOME_BTN_PININDEX)) {
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
    //jsiConsolePrintf("JSPT_LCD_BL_OFF\n");
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

static void jswrap_pinetime40_setLCDPowerController(bool isOn) {
/*
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
*/
}

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "setBacklight",
    "generate" : "jswrap_pinetime40_setLCDPowerBacklight",
    "params" : [
      ["isOn","bool","True if the LCD backlight should be on, false if not"]
    ],
    "ifdef" : "PINETIME40"
}
This function can be used to turn Pinetime LCD backlight off or on.

This function resets the Pinetime 'activity timer' (like pressing a button or
the screen would) so after a time period of inactivity set by
`Pinetime.setOptions({backlightTimeout: X});` the backlight will turn off.

If you want to keep the backlight on permanently (until apps are changed) you can
do:

```
Pinetime.setOptions({backlightTimeout: 0}) // turn off the timeout
Pinetime.setBacklight(1); // keep screen on
```

Of course, the backlight depends on `Pinetime.setLCDPower` too, so any lcdPowerTimeout/setLCDTimeout will
also turn the backlight off. The use case is when you require the backlight timeout
to be shorter than the power timeout. 
*/
/// Turn just the backlight on or off (or adjust brightness)
void jswrap_pinetime40_setLCDPowerBacklight(bool isOn) {
  if (isOn) pinetimeFlags |= JSPF_LCD_BL_ON;
  else pinetimeFlags &= ~JSPF_LCD_BL_ON;

  jswrap_pinetime40_pwrBacklight(isOn && (lcdBrightness>0));
  
  if (isOn && lcdBrightness > 0 && lcdBrightness < 255) {
    jshPinAnalogOutput(LCD_BL, lcdBrightness/256.0, 200, JSAOF_NONE);
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
  
  jswrap_pinetime40_setLCDPowerController(isOn);
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
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "setLCDTimeout",
    "generate" : "jswrap_pinetime40_setLCDTimeout",
    "params" : [
      ["isOn","float","The timeout of the display in seconds, or `0`/`undefined` to turn power saving off. Default is 10 seconds."]
    ],
    "ifdef" : "PINETIME40"
}
This function can be used to turn pinetime40's LCD power saving on or off.

With power saving off, the display will remain in the state you set it with
`Pinetime.setLCDPower`.

With power saving on, the display will turn on if a button is pressed, the watch
is turned face up, or the screen is updated (see `Pinetime.setOptions` for
configuration). It'll turn off automatically after the given timeout.

**Note:** This function also sets the Backlight and Lock timeout (the time at
which the touchscreen/buttons start being ignored). To set both separately, use
`Pinetime.setOptions`
*/
void jswrap_pinetime40_setLCDTimeout(JsVarFloat timeout) {
  if (!isfinite(timeout))
    timeout=0;
  else if (timeout<0) timeout=0;

  backlightTimeout = timeout*1000;
  //lockTimeout = timeout*1000;
}


/*TYPESCRIPT
type PinetimeOptions<Boolean = boolean> = {
  wakeOnBTN1: Boolean;
  wakeOnFaceUp: Boolean;
  wakeOnTouch: Boolean;
  wakeOnTwist: Boolean;
  twistThreshold: number;
  twistMaxY: number;
  twistTimeout: number;
  powerSave: boolean;
  lcdPowerTimeout: number;
  backlightTimeout: number;
  btnLoadTimeout: number;
};
*/
/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "setOptions",
    "generate" : "jswrap_pinetime40_setOptions",
    "params" : [
      ["options","JsVar",""]
    ],
    "ifdef" : "PINETIME40",
    "typescript" : "setOptions(options: { [key in keyof PinetimeOptions]?: PinetimeOptions<ShortBoolean>[key] }): void;"
}
Set internal options used for gestures, etc...

*/
JsVar * _jswrap_pinetime40_setOptions(JsVar *options, bool createObject) {
  bool wakeOnBTN1 = pinetimeFlags&JSPF_WAKEON_BTN1;
  bool wakeOnFaceUp = pinetimeFlags&JSPF_WAKEON_FACEUP;
  bool wakeOnTouch = pinetimeFlags&JSPF_WAKEON_TOUCH;
  bool wakeOnTwist = false;//pinetimeFlags&JSPF_WAKEON_TWIST;
  bool powerSave = pinetimeFlags&JSPF_POWER_SAVE;
  int stepCounterThresholdLow, stepCounterThresholdHigh; // ignore these with new step counter

#ifdef TOUCH_DEVICE
  int touchX1 = touchMinX;
  int touchY1 = touchMinY;
  int touchX2 = touchMaxX;
  int touchY2 = touchMaxY;
#endif
  jsvConfigObject configs[] = {
      {"stepCounterThresholdLow", JSV_INTEGER, &stepCounterThresholdLow},
      {"stepCounterThresholdHigh", JSV_INTEGER, &stepCounterThresholdHigh},
      {"wakeOnBTN1", JSV_BOOLEAN, &wakeOnBTN1},
      {"wakeOnFaceUp", JSV_BOOLEAN, &wakeOnFaceUp},
      {"wakeOnTouch", JSV_BOOLEAN, &wakeOnTouch},
      {"twistThreshold", JSV_INTEGER, &twistThreshold},
      {"twistTimeout", JSV_INTEGER, &twistTimeout},
      {"twistMaxY", JSV_INTEGER, &twistMaxY},
      {"powerSave", JSV_BOOLEAN, &powerSave},      
      {"lcdPowerTimeout", JSV_INTEGER, &lcdPowerTimeout},
      {"backlightTimeout", JSV_INTEGER, &backlightTimeout},
      {"btnLoadTimeout", JSV_INTEGER, &btnLoadTimeout},
#ifdef TOUCH_DEVICE
      {"touchX1", JSV_INTEGER, &touchX1},
      {"touchY1", JSV_INTEGER, &touchY1},
      {"touchX2", JSV_INTEGER, &touchX2},
      {"touchY2", JSV_INTEGER, &touchY2},
#endif
  };
  if (createObject) {
    return jsvCreateConfigObject(configs, sizeof(configs) / sizeof(jsvConfigObject));
  }
  if (jsvReadConfigObject(options, configs, sizeof(configs) / sizeof(jsvConfigObject))) {
    pinetimeFlags = (pinetimeFlags&~JSPF_WAKEON_BTN1) | (wakeOnBTN1?JSPF_WAKEON_BTN1:0);
    pinetimeFlags = (pinetimeFlags&~JSPF_WAKEON_FACEUP) | (wakeOnFaceUp?JSPF_WAKEON_FACEUP:0);
    pinetimeFlags = (pinetimeFlags&~JSPF_WAKEON_TOUCH) | (wakeOnTouch?JSPF_WAKEON_TOUCH:0);
    //pinetimeFlags = (pinetimeFlags&~JSPF_WAKEON_TWIST) | (wakeOnTwist?JSPF_WAKEON_TWIST:0);
    pinetimeFlags = (pinetimeFlags&~JSPF_POWER_SAVE) | (powerSave?JSPF_POWER_SAVE:0);
    if (lcdPowerTimeout<0) lcdPowerTimeout=0;
    if (backlightTimeout<0) backlightTimeout=0;

#ifdef TOUCH_DEVICE
    touchMinX = touchX1;
    touchMinY = touchY1;
    touchMaxX = touchX2;
    touchMaxY = touchY2;
#endif
  }
  return 0;
}
void jswrap_pinetime40_setOptions(JsVar *options) {
  _jswrap_pinetime40_setOptions(options, false);
}
/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "getOptions",
    "generate" : "jswrap_pinetime40_getOptions",
    "return" : ["JsVar","The current state of all options"],
    "ifdef" : "PINETIME40",
    "typescript" : "getOptions(): PinetimeOptions;"
}
Return the current state of options as set by `Pinetime.setOptions`
*/
JsVar *jswrap_pinetime40_getOptions() {
  return _jswrap_pinetime40_setOptions(NULL, true);
}


/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "isLCDOn",
    "generate" : "jswrap_pinetime40_isLCDOn",
    "return" : ["bool","Is the display on or not?"],
    "ifdef" : "PINETIME40"
}
Also see the `Pinetime.lcdPower` event
*/
// emscripten bug means we can't use 'bool' as return value here!
int jswrap_pinetime40_isLCDOn() {
  return (pinetimeFlags&JSPF_LCD_ON)!=0;
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
  jshPinOutput(TOUCH_PIN_RST, 1);
  jshDelayMicroseconds(1000);
  jshPinOutput(TOUCH_PIN_RST, 0);
  jshDelayMicroseconds(1000);
  jshPinOutput(TOUCH_PIN_RST, 1);

  unsigned char buf[2];
  // 0xEE - CST816_REG_NOR_SCAN_PER - 0x01
  buf[0]=0xEE;
  buf[1]=0x01;
  jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 2, buf, true);
  // 0xFA - CST816_REG_IRQ_CTL - 0x60
  buf[0]=0xFA;
  buf[1]=0x60;
  jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 2, buf, true);
  // 0xFB - CST816_REG_AUTO_RESET - 0x0
  buf[0]=0xFB;
  buf[1]=0x0;
  jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 2, buf, true);
  // 0xFC - CST816_REG_LONG_PRESS_TIME - 0x10
  buf[0]=0xFC;
  buf[1]=0x10;
  jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 2, buf, true);
  // 0xED - CST816_REG_IRQ_PLUSE_WIDTH - 0x02  
  buf[0]=0xED;
  buf[1]=0x02;
  jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 2, buf, true);


  /*graphicsStructInit(&graphicsInternal, LCD_WIDTH, LCD_HEIGHT, LCD_BPP);
  graphicsInternal.data.type = JSGRAPHICSTYPE_SPILCD;
  graphicsInternal.data.flags = 0;
  graphicsInternal.data.fontSize = JSGRAPHICS_FONTSIZE_6X8 + 1; // 4x6 size is default
  lcdInit_SPILCD(&graphicsInternal);
  lcdSetCallbacks_SPILCD(&graphicsInternal);

  // set default graphics themes - before we even start to load settings.json
  jswrap_pinetime40_setTheme();
  graphicsFillRect(&graphicsInternal, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, graphicsTheme.bg2);
  */
  jsiConsolePrintf("HWINIT DONE\n");
}

JsVar* jswrap_pinetime_getLogo();

/*JSON{
  "type" : "init",
  "generate" : "jswrap_pinetime40_init"
}*/
NO_INLINE void jswrap_pinetime40_init() {
  
  IOEventFlags channel;

  bool firstRun = jsiStatus & JSIS_FIRST_BOOT; // is this the first time jswrap_pinetime40_init was called?

  jshSetPinShouldStayWatched(BTN1_PININDEX, true);
  channel = jshPinWatch(BTN1_PININDEX, true, JSPW_NONE);
  if (channel != EV_NONE) jshSetEventCallback(channel, btn1Handler);

  jshSetPinShouldStayWatched(TOUCH_PIN_IRQ, true);
  channel = jshPinWatch(TOUCH_PIN_IRQ, true, JSPW_NONE);
  if (channel != EV_NONE) jshSetEventCallback(channel, touchHandler);

  JsVar *settingsFN = jsvNewFromString("setting.json");
  JsVar *settings = jswrap_storage_readJSON(settingsFN,true);
  jsvUnLock(settingsFN);
  /*JsVar *v;

  // Load themes from the settings.json file
  jswrap_pinetime40_setTheme();
  v = jsvIsObject(settings) ? jsvObjectGetChildIfExists(settings,"theme") : 0;
  if (jsvIsObject(v)) {
    graphicsTheme.fg = jsvGetIntegerAndUnLock(jsvObjectGetChildIfExists(v,"fg"));
    graphicsTheme.bg = jsvGetIntegerAndUnLock(jsvObjectGetChildIfExists(v,"bg"));
    graphicsTheme.fg2 = jsvGetIntegerAndUnLock(jsvObjectGetChildIfExists(v,"fg2"));
    graphicsTheme.bg2 = jsvGetIntegerAndUnLock(jsvObjectGetChildIfExists(v,"bg2"));
    graphicsTheme.fgH = jsvGetIntegerAndUnLock(jsvObjectGetChildIfExists(v,"fgH"));
    graphicsTheme.bgH = jsvGetIntegerAndUnLock(jsvObjectGetChildIfExists(v,"bgH"));
    graphicsTheme.dark = jsvGetBoolAndUnLock(jsvObjectGetChildIfExists(v,"dark"));
  }
  jsvUnLock(v);*/

  jsvUnLock(settings);

  /*
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

  
  if (!firstRun) {
    // Display a loading screen
    // Check for a '.loading' file
    JsVar *img = jsfReadFile(jsfNameFromString(".loading"),0,0);
    if (jsvIsString(img)) {
      if (jsvGetStringLength(img)>3) {
        // if it exists and is big enough to store an image, render the image in the middle of the screen
        int w,h;
        w = (int)(unsigned char)jsvGetCharInString(img, 0);
        h = (int)(unsigned char)jsvGetCharInString(img, 1);
        jsvUnLock2(jswrap_graphics_drawImage(graphics,img,(LCD_WIDTH-w)/2,(LCD_HEIGHT-h)/2,NULL),img);
        graphicsInternalFlip();
      }
      // else if <3 bytes we don't render anything
    } else {
      // otherwise render the standard 'Loading...' box
      int x = LCD_WIDTH/2;
      int y = LCD_HEIGHT/2;
      graphicsFillRect(&graphicsInternal, x-49, y-19, x+49, y+19, graphicsTheme.bg);
      graphicsInternal.data.fgColor = graphicsTheme.fg;
      graphicsDrawRect(&graphicsInternal, x-50, y-20, x+50, y+20);
      y -= 4;
      x -= 4*6;
      const char *s = "Loading...";
      while (*s) {
        graphicsDrawChar6x8(&graphicsInternal, x, y, *s, 1, 1, false);
        x+=6;
        s++;
      }
      graphicsInternalFlip();
    }
  } else {
    graphicsInternal.data.fontSize = JSGRAPHICS_FONTSIZE_6X8 + 1; // 4x6 size is default
    graphicsClear(&graphicsInternal);

    int w, h, y;
    h = 0;
    JsVar* img = jsfReadFile(jsfNameFromString(".splash"), 0, 0);
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
  }  
  */

  buzzAmt = 0;
  beepFreq = 0;

  if (firstRun) {

    pinetimeFlags = JSPF_DEFAULT | JSPF_LCD_ON | JSPF_LCD_BL_ON; // includes pinetimeFlags
    lcdBrightness = 128;

    jshEnableWatchDog(10); // 5 second watchdog

    pollInterval = DEFAULT_ACCEL_POLL_INTERVAL;

    uint32_t err_code = app_timer_create(&m_peripheral_poll_timer_id,
      APP_TIMER_MODE_REPEATED,
      peripheralPollHandler);
    jsble_check_error(err_code);
    app_timer_start(m_peripheral_poll_timer_id, APP_TIMER_TICKS(pollInterval), NULL);

    //jsiConsolePrintf("FIRST INIT DONE\n");
    //jsvUnLock(jspEvaluate("setTimeout(Pinetime.load,1000)", true));
  }
  /*else
  {
    jsiConsolePrintf("HOT INIT DONE\n");
  }*/

  //pinetimeFlags |= JSPF_POWER_SAVE; // ensure we turn power-save on by default every restart
  //pinetimeFlags |= JSPF_LCD_BL_ON; // ensure we turn power-save on by default every restart
  inactivityTimer = 0; // reset the LCD timeout timer
  btnLoadTimeout = DEFAULT_BTN_LOAD_TIMEOUT;
  lcdPowerTimeout = DEFAULT_LCD_POWER_TIMEOUT;
  backlightTimeout = DEFAULT_BACKLIGHT_TIMEOUT;
  //lockTimeout = DEFAULT_LOCK_TIMEOUT;
  lcdWakeButton = 0;

  // touch
  touchStatus = TS_NONE;
  touchLastState = 0;
  //touchLastState2 = 0;

  // If the home button is still pressed when we're restarting, set up
  // lcdWakeButton so the event for button release is 'eaten'
  if (jshPinGetValue(HOME_BTN_PININDEX))
    lcdWakeButton = HOME_BTN;


  //jsiConsolePrintf("pinetimeFlags %d\n",pinetimeFlags);
}

/*JSON{
  "type" : "idle",
  "generate" : "jswrap_pinetime40_idle"
}*/
bool jswrap_pinetime40_idle() {
  JsVar *pinetime =jsvObjectGetChildIfExists(execInfo.root, "Pinetime");

  if (!pinetime) {
    pinetimeTasks = JSPT_NONE;
  }
  if (pinetimeTasks != JSPT_NONE) {
    if (pinetimeTasks & JSPT_LCD_OFF) jswrap_pinetime40_setLCDPower(0);
    if (pinetimeTasks & JSPT_LCD_ON) jswrap_pinetime40_setLCDPower(1);
    if (pinetimeTasks & JSPT_LCD_BL_OFF) jswrap_pinetime40_setLCDPowerBacklight(0);
    if (pinetimeTasks & JSPT_LCD_BL_ON) jswrap_pinetime40_setLCDPowerBacklight(1);
    if (pinetimeTasks & JSPT_LOCK) jswrap_pinetime40_setLocked(1);
    if (pinetimeTasks & JSPT_UNLOCK) jswrap_pinetime40_setLocked(0);
    if (pinetimeTasks & JSPT_RESET) jsiStatus |= JSIS_TODO_FLASH_LOAD;


    if (pinetimeTasks & JSPT_MIDNIGHT) {
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"midnight", NULL, 0);
    }
  
    if (pinetimeTasks & JSPT_CHARGE_EVENT) {
      JsVar *charging = jsvNewFromBool(wasCharging);
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"charging", &charging, 1);
      jsvUnLock(charging);
    }

    if (pinetimeTasks & JSPT_SWIPE) {
      JsVar *o[2] = {
          jsvNewFromInteger((touchGesture==TG_SWIPE_LEFT)?-1:((touchGesture==TG_SWIPE_RIGHT)?1:0)),
          jsvNewFromInteger((touchGesture==TG_SWIPE_UP)?-1:((touchGesture==TG_SWIPE_DOWN)?1:0)),
      };
      touchGesture = TG_SWIPE_NONE;
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"swipe", o, 2);
      jsvUnLockMany(2,o);
    }
    if (pinetimeTasks & JSPT_TOUCH_MASK) {
      JsVar *o[2] = {
          jsvNewFromInteger(((pinetimeTasks & JSPT_TOUCH_LEFT)?1:0) |
                            ((pinetimeTasks & JSPT_TOUCH_RIGHT)?2:0)),
          jsvNewObject()
      };
      int x = touchX;
      int y = touchY;
      if (x<0) x=0;
      if (y<0) y=0;
      if (x>=LCD_WIDTH) x=LCD_WIDTH-1;
      if (y>=LCD_HEIGHT) y=LCD_HEIGHT-1;
      jsvObjectSetChildAndUnLock(o[1], "x", jsvNewFromInteger(x));
      jsvObjectSetChildAndUnLock(o[1], "y", jsvNewFromInteger(y));
      jsvObjectSetChildAndUnLock(o[1], "type", jsvNewFromInteger(touchType));
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"touch", o, 2);
      jsvUnLockMany(2,o);
    }
  }
  if (pinetimeTasks & JSPT_DRAG) {
    JsVar *o = jsvNewObject();
    jsvObjectSetChildAndUnLock(o, "x", jsvNewFromInteger(touchX));
    jsvObjectSetChildAndUnLock(o, "y", jsvNewFromInteger(touchY));
    jsvObjectSetChildAndUnLock(o, "b", jsvNewFromInteger(touchPts));
    jsvObjectSetChildAndUnLock(o, "dx", jsvNewFromInteger(lastTouchPts ? touchX-lastTouchX : 0));
    jsvObjectSetChildAndUnLock(o, "dy", jsvNewFromInteger(lastTouchPts ? touchY-lastTouchY : 0));
    jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"drag", &o, 1);
    jsvUnLock(o);
    lastTouchX = touchX;
    lastTouchY = touchY;
    lastTouchPts = touchPts;
  }

  jsvUnLock(pinetime);
  pinetimeTasks = JSPT_NONE;
  /*
  // Automatically flip!
  if (graphicsInternal.data.modMaxX >= graphicsInternal.data.modMinX) {
    graphicsInternalFlip();
  }
  */
  // resolve any beep/buzz promises
  if (promiseBuzz && !buzzAmt) {
    jspromise_resolve(promiseBuzz, 0);
    jsvUnLock(promiseBuzz);
    promiseBuzz = 0;
  }
  if (promiseBeep && !beepFreq) {
    jspromise_resolve(promiseBeep, 0);
    jsvUnLock(promiseBeep);
    promiseBeep = 0;
  }

  return false;
}


/*JSON{
  "type" : "kill",
  "generate" : "jswrap_pinetime40_kill"
}*/
void jswrap_pinetime40_kill() {

  // Graphics var is getting removed, so set this to null.
  /*jsvUnLock(graphicsInternal.graphicsVar);
  graphicsInternal.graphicsVar = NULL;*/

}



/*******************************************************************/

// Convert Touchscreen gesture based on graphics orientation
TouchGestureType touchSwipeRotate(TouchGestureType g) {
  // gesture is the value that comes straight from the touchscreen
  /*if (graphicsInternal.data.flags & JSGRAPHICSFLAGS_INVERT_X) {
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
  }*/
  return g;
}

void touchHandlerInternal(int tx, int ty, int pts, int gesture) {
  // ignore if locked
  if (pinetimeFlags & JSPF_LOCKED) return;  
  // deal with the case where we rotated the Bangle.js screen
  //deviceToGraphicsCoordinates(&graphicsInternal, &tx, &ty);

  int dx = tx-touchX;
  int dy = ty-touchY;

  touchX = tx;
  touchY = ty;
  touchPts = pts;
  JsPinetimeTasks lastPinetimeTasks = pinetimeTasks;  

  //static int lastGesture = 0;
  //if (gesture!=lastGesture) {

    //jsiConsolePrintf("TS = x:%d y:%d pts:%d gest:%d\n", tx,ty,pts,gesture);

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
  //}

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

  //lastGesture = gesture;
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

  //jsiConsolePrintf("TS = %d:%d:%d:%d:%d:%d\n", buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);

  int tx = buf[3]/* | ((buf[2] & 0x0F)<<8)*/; // top bits are never used on our touchscreen
  int ty = buf[5]/* | ((buf[4] & 0x0F)<<8)*/;
  if (tx >= 250) tx = 0; // on some devices, 251-255 gets reported for touches right at the top of the screen
  if (ty >= 250) ty = 0;
  touchHandlerInternal(
    (tx - touchMinX) * LCD_WIDTH / (touchMaxX - touchMinX), // touchX
    (ty - touchMinY) * LCD_HEIGHT / (touchMaxY - touchMinY), // touchY
    buf[2], // touchPts
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
  /*if (!o) return 0;
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
  */
  return o;
}

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "isLocked",
    "generate" : "jswrap_pinetime40_isLocked",
    "return" : ["bool","Is the screen locked or not?"],
    "ifdef" : "PINETIME40"
}
*/
// emscripten bug means we can't use 'bool' as return value here!
int jswrap_pinetime40_isLocked() {
  return (pinetimeFlags&JSPF_LOCKED)!=0;
}


static NO_INLINE void _jswrap_pinetime40_setVibration() {
  int beep = 0;
  if (pinetimeFlags & JSPF_BEEP_VIBRATE)
    beep = beepFreq;

  if (buzzAmt==0 && beep==0)
    jshPinOutput(VIBRATE_PIN,0); // vibrate off
  else if (beep==0) { // vibrate only
    jshPinAnalogOutput(VIBRATE_PIN, 0.4 + buzzAmt*0.6/255, 1000, JSAOF_NONE);
  } else { // beep and vibrate
    jshPinAnalogOutput(VIBRATE_PIN, 0.2 + buzzAmt*0.6/255, beep, JSAOF_NONE);
  }
}

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "beep",
    "generate" : "jswrap_pinetime40_beep",
    "params" : [
      ["time","int","[optional] Time in ms (default 200)"],
      ["freq","int","[optional] Frequency in hz (default 4000)"]
    ],
    "return" : ["JsVar","A promise, completed when beep is finished"],
    "return_object":"Promise",
    "ifdef" : "PINETIME40"
}
Use the piezo speaker to Beep for a certain time period and frequency
*/
void jswrap_pinetime40_beep_callback() {
  beepFreq = 0;
  if (pinetimeFlags & JSPF_BEEP_VIBRATE) {
    _jswrap_pinetime40_setVibration();
  }
  jshHadEvent();
}

JsVar *jswrap_pinetime40_beep(int time, int freq) {
  if (freq<=0) freq=4000;
  if (freq>60000) freq=60000;
  if (time<=0) time=200;
  if (time>5000) time=5000;
  if (promiseBeep) {
    JsVar *fn = jsvNewNativeFunction((void (*)(void))jswrap_pinetime40_beep, JSWAT_JSVAR|(JSWAT_INT32<<JSWAT_BITS)|(JSWAT_INT32<<(JSWAT_BITS*2)));
    JsVar *v;
    v=jsvNewFromInteger(time);jsvAddFunctionParameter(fn, 0, v);jsvUnLock(v); // bind param 1
    v=jsvNewFromInteger(freq);jsvAddFunctionParameter(fn, 0, v);jsvUnLock(v); // bind param 2
    JsVar *promise = jswrap_promise_then(promiseBeep, fn, NULL);
    jsvUnLock(fn);
    return promise;
  }
  promiseBeep = jspromise_create();
  if (!promiseBeep) return 0;

  if (pinetimeFlags & JSPF_ENABLE_BEEP) {
    beepFreq = freq;
    if (pinetimeFlags & JSPF_BEEP_VIBRATE) {
      _jswrap_pinetime40_setVibration();
    }
  }
  jstExecuteFn(jswrap_pinetime40_beep_callback, NULL, jshGetTimeFromMilliseconds(time), 0, NULL);
  return jsvLockAgain(promiseBeep);
}

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "buzz",
    "generate" : "jswrap_pinetime40_buzz",
    "params" : [
      ["time","int","[optional] Time in ms (default 200)"],
      ["strength","float","[optional] Power of vibration from 0 to 1 (Default 1)"]
    ],
    "return" : ["JsVar","A promise, completed when vibration is finished"],
    "return_object":"Promise",
    "ifdef" : "PINETIME40"
}
Use the vibration motor to buzz for a certain time period
*/
void jswrap_pinetime40_buzz_callback() {
  buzzAmt = 0;
  _jswrap_pinetime40_setVibration();
  jshHadEvent();
}

JsVar *jswrap_pinetime40_buzz(int time, JsVarFloat amt) {
  if (!isfinite(amt)|| amt>1) amt=1;
  if (amt<0) amt=0;
  if (time<=0) time=200;
  if (time>5000) time=5000;
  if (promiseBuzz) {
    JsVar *fn = jsvNewNativeFunction((void (*)(void))jswrap_pinetime40_buzz, JSWAT_JSVAR|(JSWAT_INT32<<JSWAT_BITS)|(JSWAT_JSVARFLOAT<<(JSWAT_BITS*2)));
    JsVar *v;
    v=jsvNewFromInteger(time);jsvAddFunctionParameter(fn, 0, v);jsvUnLock(v); // bind param 1
    v=jsvNewFromFloat(amt);jsvAddFunctionParameter(fn, 0, v);jsvUnLock(v); // bind param 2
    JsVar *promise = jswrap_promise_then(promiseBuzz, fn, NULL);
    jsvUnLock(fn);
    return promise;
  }
  promiseBuzz = jspromise_create();
  if (!promiseBuzz) return 0;

  buzzAmt = (unsigned char)(amt*255);
  if (jstExecuteFn(jswrap_pinetime40_buzz_callback, NULL, jshGetTimeFromMilliseconds(time), 0, NULL)) {
    // task schedule succeeded - start buzz
    if (pinetimeFlags & JSPF_ENABLE_BUZZ) {
      _jswrap_pinetime40_setVibration();
    }
  } else
    buzzAmt = 0;

  return jsvLockAgain(promiseBuzz);
}

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "setLocked",
    "generate" : "jswrap_pinetime40_setLocked",
    "params" : [
      ["isLocked","bool","`true` if the Bangle is locked (no user input allowed)"]
    ],
    "ifdef" : "PINETIME40"
}
This function can be used to lock or unlock Bangle.js (e.g. whether buttons and
touchscreen work or not)
*/
void jswrap_pinetime40_setLocked(bool isLocked) {
  if (isLocked) {
    unsigned char buf[2];
    buf[0]=0xE5;
    buf[1]=0x03;
    jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 2, buf, true);
  } else { // best way to wake up is to reset
    jshPinOutput(TOUCH_PIN_RST, 1);
    jshDelayMicroseconds(1000);
    jshPinOutput(TOUCH_PIN_RST, 0);
    jshDelayMicroseconds(1000);
    jshPinOutput(TOUCH_PIN_RST, 1);
    jshDelayMicroseconds(1000);
  }

  if ((pinetimeFlags&JSPF_LOCKED) != isLocked) {
    JsVar *pinetime =jsvObjectGetChildIfExists(execInfo.root, "Pinetime");
    if (pinetime) {
      JsVar *v = jsvNewFromBool(isLocked);
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"lock", &v, 1);
      jsvUnLock(v);
    }
    jsvUnLock(pinetime);
  }
  if (isLocked) pinetimeFlags |= JSPF_LOCKED;
  else pinetimeFlags &= ~JSPF_LOCKED;
  // Reset inactivity timer so we will lock ourselves after a delay
  inactivityTimer = 0;
}

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "setLCDOffset",
    "generate" : "jswrap_pinetime40_setLCDOffset",
    "params" : [
      ["y","int","The amount of pixels to shift the LCD up or down"]
    ],
    "ifdef" : "PINETIME40"
}
This can be used to move the displayed memory area up or down temporarily. It's
used for displaying notifications while keeping the main display contents
intact.
*/
void jswrap_pinetime40_setLCDOffset(int y) {
//#ifdef LCD_CONTROLLER_ST7789_8BIT
  //lcdST7789_setYOffset(y);
//#endif
}

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "setHRMPower",
    "generate" : "jswrap_pinetime40_setHRMPower",
    "params" : [
      ["isOn","bool","True if the heart rate monitor should be on, false if not"],
      ["appID","JsVar","A string with the app's name in, used to ensure one app can't turn off something another app is using"]
    ],
    "return" : ["bool","Is HRM on?"],
    "ifdef" : "PINETIME40",
    "typescript" : "setHRMPower(isOn: ShortBoolean, appID: string): boolean;"
}
Set the power to the Heart rate monitor

When on, data is output via the `HRM` event on `Pinetime`:

```
Bangle.setHRMPower(true, "myapp");
Bangle.on('HRM',print);
```

*When on, the Heart rate monitor draws roughly 5mA*
*/
bool jswrap_pinetime40_setHRMPower(bool isOn, JsVar *appId) {

  return false;

}

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "load",
    "generate_js" : "libs/js/pinetime40/load.min.js",
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


/*TYPESCRIPT
type SetUIArg<Mode> = Mode | {
  mode: Mode,
  back?: () => void,
  remove?: () => void,
  redraw?: () => void,
};
*/

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "setUI",
    "generate_js" : "libs/js/pinetime40/Pinetime_setUI.min.js",
    "params" : [
      ["type","JsVar","The type of UI input: 'updown', 'leftright', 'clock', 'clockupdown' or undefined to cancel. Can also be an object (see below)"],
      ["callback","JsVar","A function with one argument which is the direction"]
    ],
    "ifdef" : "PINETIME40",
    "typescript" : [
      "setUI(type?: undefined): void;",
      "setUI(type: SetUIArg<\"updown\" | \"leftright\">, callback: (direction?: -1 | 1) => void): void;",
      "setUI(type: SetUIArg<\"clock\">): void;",
      "setUI(type: SetUIArg<\"clockupdown\">, callback?: (direction: -1 | 1) => void): void;",
      "setUI(type: SetUIArg<\"custom\"> & { touch?: TouchCallback; swipe?: SwipeCallback; drag?: DragCallback; btn?: (n: 1 | 2 | 3) => void; clock?: boolean | 0 | 1 }): void;"
    ]
}
This puts Pinetime into the specified UI input mode, and calls the callback
provided when there is user input.

Currently supported interface types are:

* 'updown' - UI input with upwards motion `cb(-1)`, downwards motion `cb(1)`,
  and select `cb()`
  * Pinetime uses touchscreen swipe up/down and tap
* 'leftright' - UI input with left motion `cb(-1)`, right motion `cb(1)`, and
  select `cb()`
  * Pinetime uses touchscreen swipe left/right and tap/BTN1 for select
* 'clock' - called for clocks. Sets `Pinetime.CLOCK=1` and allows a button to
  start the launcher
  * Pinetime BTN1 starts the launcher
* 'clockupdown' - called for clocks. Sets `Pinetime.CLOCK=1`, allows a button to
  start the launcher, but also provides up/down functionality
  * Pinetime BTN1 starts the launcher, touchscreen tap in top/bottom right
    hand side calls `cb(-1)` and `cb(1)`
* `{mode:"custom", ...}` allows you to specify custom handlers for different
  interactions. See below.
* `undefined` removes all user interaction code

While you could use setWatch/etc manually, the benefit here is that you don't
end up with multiple `setWatch` instances, and the actual input method (touch,
or buttons) is implemented dependent on the watch (Pinetime 1 or 2)

**Note:** You can override this function in boot code to change the interaction
mode with the watch. For instance you could make all clocks start the launcher
with a swipe by using:

```
(function() {
  var sui = Pinetime.setUI;
  Pinetime.setUI = function(mode, cb) {
    if (mode!="clock") return sui(mode,cb);
    sui(); // clear
    Pinetime.CLOCK=1;
    Pinetime.swipeHandler = Pinetime.showLauncher;
    Pinetime.on("swipe", Pinetime.swipeHandler);
  };
})();
```

The first argument can also be an object, in which case more options can be
specified:

```
Pinetime.setUI({
  mode : "custom",
  back : function() {}, // optional - add a 'back' icon in top-left widget area and call this function when it is pressed , also call it when the hardware button is clicked (does not override btn if defined)
  remove : function() {}, // optional - add a handler for when the UI should be removed (eg stop any intervals/timers here)
  redraw : function() {}, // optional - add a handler to redraw the UI. Not needed but it can allow widgets/etc to provide other functionality that requires the screen to be redrawn
  touch : function(n,e) {}, // optional - (mode:custom only) handler for 'touch' events
  swipe : function(dir) {}, // optional - (mode:custom only) handler for 'swipe' events
  drag : function(e) {}, // optional - (mode:custom only) handler for 'drag' events (Pinetime 2 only)
  btn : function(n) {}, // optional - (mode:custom only) handler for 'button' events (n==1 on Pinetime 2, n==1/2/3 depending on button for Pinetime 1)
  clock : 0 // optional - if set the behavior of 'clock' mode is added (does not override btn if defined)
});
```

If `remove` is specified, `Pinetime.showLauncher`, `Pinetime.showClock`, `Pinetime.load` and some apps
may choose to just call the `remove` function and then load a new app without resetting Pinetime.
As a result, **if you specify 'remove' you should make sure you test that after calling `Pinetime.setUI()`
without arguments your app is completely unloaded**, otherwise you may end up with memory leaks or
other issues when switching apps. Please see http://www.espruino.com/Pinetime+Fast+Load for more details on this.
*/

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "showLauncher",
    "generate_js" : "libs/js/pinetime40/Pinetime_showLauncher.min.js",
    "ifdef" : "PINETIME40"
}
Load the Pinetime app launcher, which will allow the user to select an
application to launch.
*/

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "showClock",
    "generate_js" : "libs/js/banglejs/Bangle_showClock.min.js",
    "ifdef" : "PINETIME40"
}
Load the Pinetime clock - this has the same effect as calling `Pinetime.load()`.
*/

/*JSON{
    "type" : "staticmethod",
    "class" : "E",
    "name" : "showScroller",
    "generate_js" : "libs/js/pinetime40/E_showScroller.min.js",
    "params" : [
      ["options","JsVar","An object containing `{ h, c, draw, select, back, remove }` (see below) "]
    ],
    "return" : ["JsVar", "A menu object with `draw()` and `drawItem(itemNo)` functions" ],
    "ifdef" : "PINETIME40",
    "typescript" : [
      "showScroller(options?: { h: number, c: number, draw: (idx: number, rect: { x: number, y: number, w: number, h: number }) => void, select: (idx: number, touch?: {x: number, y: number}) => void, back?: () => void, remove?: () => void }): { draw: () => void, drawItem: (itemNo: number) => void };",
      "showScroller(): void;"
    ]
}
Display a scrollable menu on the screen, and set up the buttons/touchscreen to
navigate through it and select items.

Supply an object containing:

```
{
  h : 24, // height of each menu item in pixels
  c : 10, // number of menu items
  // a function to draw a menu item
  draw : function(idx, rect) { ... }
  // a function to call when the item is selected, touch parameter is only relevant
  // for Pinetime and contains the coordinates touched inside the selected item
  select : function(idx, touch) { ... }
  // optional function to be called when 'back' is tapped
  back : function() { ...}
  // Pinetime: optional function to be called when the scroller should be removed
  remove : function() {}
}
```

For example to display a list of numbers:

```
E.showScroller({
  h : 40, c : 8,
  draw : (idx, r) => {
    g.setBgColor((idx&1)?"#666":"#999").clearRect(r.x,r.y,r.x+r.w-1,r.y+r.h-1);
    g.setFont("6x8:2").drawString("Item Number\n"+idx,r.x+10,r.y+4);
  },
  select : (idx) => console.log("You selected ", idx)
});
```

To remove the scroller, just call `E.showScroller()`
*/

/*JSON{
    "type" : "staticmethod",
    "class" : "E",
    "name" : "showPrompt",
    "generate_js" : "libs/js/pinetime40/E_showPrompt.min.js",
    "params" : [
      ["message","JsVar","A message to display. Can include newlines"],
      ["options","JsVar","[optional] an object of options (see below)"]
    ],
    "return" : ["JsVar","A promise that is resolved when 'Ok' is pressed"],
    "ifdef" : "PINETIME40",
    "typescript" : [
      "showPrompt<T = boolean>(message: string, options?: { title?: string, buttons?: { [key: string]: T }, image?: string, remove?: () => void }): Promise<T>;",
      "showPrompt(): void;"
    ]
}

Displays a full screen prompt on the screen, with the buttons requested (or
`Yes` and `No` for defaults).

When the button is pressed the promise is resolved with the requested values
(for the `Yes` and `No` defaults, `true` and `false` are returned).

```
E.showPrompt("Do you like fish?").then(function(v) {
  if (v) print("'Yes' chosen");
  else print("'No' chosen");
});
// Or
E.showPrompt("How many fish\ndo you like?",{
  title:"Fish",
  buttons : {"One":1,"Two":2,"Three":3}
}).then(function(v) {
  print("You like "+v+" fish");
});
// Or
E.showPrompt("Continue?", {
  title:"Alert",
  img:atob("FBQBAfgAf+Af/4P//D+fx/n+f5/v+f//n//5//+f//n////3//5/n+P//D//wf/4B/4AH4A=")}).then(function(v) {
  if (v) print("'Yes' chosen");
  else print("'No' chosen");
});
```

To remove the prompt, call `E.showPrompt()` with no arguments.

The second `options` argument can contain:

```
{
  title: "Hello",                       // optional Title
  buttons : {"Ok":true,"Cancel":false}, // optional list of button text & return value
  img: "image_string"                   // optional image string to draw
  remove: function() { }                // Pinetime: optional function to be called when the prompt is removed
}
```
*/


/*JSON{
    "type" : "staticmethod",
    "class" : "E",
    "name" : "showMenu",
    "generate_js" : "libs/js/pinetime40/E_showMenu.min.js",
    "params" : [
      ["menu","JsVar","An object containing name->function mappings to to be used in a menu"]
    ],
    "return" : ["JsVar", "A menu object with `draw`, `move` and `select` functions" ],
    "ifdef" : "PINETIME40",
    "typescript": [
      "showMenu(menu: Menu): MenuInstance;",
      "showMenu(): void;"
    ]
}
Display a menu on the screen, and set up the buttons to navigate through it.

Supply an object containing menu items. When an item is selected, the function
it references will be executed. For example:

```
var boolean = false;
var number = 50;
// First menu
var mainmenu = {
  "" : { title : "-- Main Menu --" }, // options
  "LED On" : function() { LED1.set(); },
  "LED Off" : function() { LED1.reset(); },
  "Submenu" : function() { E.showMenu(submenu); },
  "A Boolean" : {
    value : boolean,
    format : v => v?"On":"Off",
    onchange : v => { boolean=v; }
  },
  "A Number" : {
    value : number,
    min:0,max:100,step:10,
    onchange : v => { number=v; }
  },
  "Exit" : function() { E.showMenu(); }, // remove the menu
};
// Submenu
var submenu = {
  "" : { title : "-- SubMenu --",
         back : function() { E.showMenu(mainmenu); } },
  "One" : undefined, // do nothing
  "Two" : undefined // do nothing
};
// Actually display the menu
E.showMenu(mainmenu);
```

The menu will stay onscreen and active until explicitly removed, which you can
do by calling `E.showMenu()` without arguments.

See http://www.espruino.com/graphical_menu for more detailed information.

On Pinetime there are a few additions over the standard `graphical_menu`:

* The options object can contain:
  * `back : function() { }` - add a 'back' button, with the function called when
    it is pressed
  * `remove : function() { }` - add a handler function to be called when the
    menu is removed
  * (Pinetime) `scroll : int` - an integer specifying how much the initial
    menu should be scrolled by
* The object returned by `E.showMenu` contains:
  * (Pinetime) `scroller` - the object returned by `E.showScroller` -
    `scroller.scroll` returns the amount the menu is currently scrolled by
* In the object specified for editable numbers:
  * (Pinetime) the `format` function is called with `format(value)` in the
    main menu, `format(value,1)` when in a scrollable list, or `format(value,2)`
    when in a popup window.

You can also specify menu items as an array (rather than an Object). This can be
useful if you have menu items with the same title, or you want to `push` menu
items onto an array:

```
var menu = [
  { title:"Something", onchange:function() { print("selected"); } },
  { title:"On or Off", value:false, onchange: v => print(v) },
  { title:"A Value", value:3, min:0, max:10, onchange: v => print(v) },
];
menu[""] = { title:"Hello" };
E.showMenu(menu);
```
*/