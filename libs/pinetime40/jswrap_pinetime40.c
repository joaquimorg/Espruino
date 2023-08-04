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
#include "jsflash.h"
#include "jswrap_bluetooth.h"
#include "app_timer.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_soc.h"
#include "nrf_saadc.h"
#include "nrf5x_utils.h"

#include "bluetooth.h" // for self-test
#include "jsi2c.h" // accelerometer/etc

#include "jswrap_lvgl.h"
#include "lcd_spi_nrf.h"
#include "lvgl.h"

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[LCD_WIDTH * LCD_HEIGHT / 10];                        /*Declare a buffer for 1/10 screen size*/


/*TYPESCRIPT
declare const BTN1: Pin;

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

#define HOME_BTN 1
#define HOME_BTN_PININDEX    BTN1_PININDEX

volatile uint16_t inactivityTimer; // in ms
volatile uint16_t homeBtnTimer; // in ms
int btnLoadTimeout; // in ms
int lcdPowerTimeout; // in ms
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
  JSPF_NONE,
  JSPF_WAKEON_FACEUP = 1 << 0,
  JSPF_WAKEON_BTN1 = 1 << 1,
  JSPF_WAKEON_TOUCH = 1 << 2,
  JSPF_BEEP_VIBRATE = 1 << 3,
  JSPF_ACCEL_LISTENER = 1 << 4, ///< we have a listener for accelerometer data
  JSPF_POWER_SAVE = 1 << 5, ///< if no movement detected for a while, lower the accelerometer poll interval
  JSPF_HRM_ON = 1 << 6,
  JSPF_LCD_ON = 1 << 7,
  JSPF_HRM_INSTANT_LISTENER = 1 << 9,
  JSPF_ENABLE_BEEP = 1 << 10,
  JSPF_ENABLE_BUZZ = 1 << 11,

  JSPF_DEFAULT = ///< default at power-on
  JSPF_WAKEON_BTN1 | JSPF_WAKEON_FACEUP
} JsPinetimeFlags;
volatile JsPinetimeFlags pinetimeFlags = JSPF_NONE;


typedef enum {
  JSPT_NONE,
  JSPT_RESET = 1 << 0, ///< reset the watch and reload code from flash
  JSPT_LCD_ON = 1 << 1, ///< LCD controller
  JSPT_LCD_OFF = 1 << 2,
  JSPT_ACCEL_DATA = 1 << 7, ///< need to push xyz data to JS
  JSPT_ACCEL_TAPPED = 1 << 8, ///< tap event detected
  JSPT_MAG_DATA = 1 << 9, ///< need to push magnetometer data to JS
  JSPT_GESTURE_DATA = 1 << 10, ///< we have data from a gesture
  JSPT_HRM_DATA = 1 << 11, ///< Heart rate data is ready for analysis
  JSPT_CHARGE_EVENT = 1 << 12, ///< we need to fire a charging event
  JSPT_STEP_EVENT = 1 << 13, ///< we've detected a step via the pedometer
  JSPT_FACE_UP = 1 << 14, ///< Watch was turned face up/down (faceUp holds the actual state)
  JSPT_ACCEL_INTERVAL_DEFAULT = 1 << 15, ///< reschedule accelerometer poll handler to default speed
  JSPT_ACCEL_INTERVAL_POWERSAVE = 1 << 16, ///< reschedule accelerometer poll handler to powersave speed
  JSPT_HRM_INSTANT_DATA = 1 << 17, ///< Instant heart rate data
  JSPT_HEALTH = 1 << 18, ///< New 'health' event
  JSPT_MIDNIGHT = 1 << 19, ///< Fired at midnight each day - for housekeeping tasks
} JsPinetimeTasks;
JsPinetimeTasks pinetimeTasks;

void jswrap_pinetime40_setLCDPowerBacklight(bool isOn);

APP_TIMER_DEF(m_peripheral_poll_timer_id);
volatile uint16_t pollInterval; // in ms

/// LCD Brightness - 255=full
uint8_t lcdBrightness;


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
  if (lcdPowerTimeout) {
    if ((pinetimeFlags&JSPF_WAKEON_BTN1)&&(button==1)) {
      // if a 'hard' button, turn LCD on      
      inactivityTimer = 0;
      if (state) {
        bool ignoreBtnUp = false;
        if (lcdPowerTimeout && !(pinetimeFlags&JSPF_LCD_ON) && state) {
          pinetimeTasks |= JSPT_LCD_ON;
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
  // if not off, add to the event queue for normal processing for watches
  if (!(pinetimeFlags&JSPF_LCD_ON))
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


void jswrap_pinetime40_setLCDPowerBacklight(bool isOn) {

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
  lcdPowerTimeout = timeout*1000;  
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
      {"btnLoadTimeout", JSV_INTEGER, &btnLoadTimeout},
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

/* ----------------------------- LVGL --------------------------------- */

void disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p) {

  //if ((pinetimeFlags & JSPF_LCD_ON) == 0) return;

  uint32_t width = (area->x2 - area->x1) + 1;
  uint32_t height = (area->y2 - area->y1) + 1;  

  lcdFlip_SPINRF(area->x1, area->y1, width, height, (uint8_t *)color_p);

  lv_disp_flush_ready(disp);         /* Indicate you are ready with the flushing*/
}

void touchpad_read(lv_indev_t * indev, lv_indev_data_t * data) {

  if ((pinetimeFlags & JSPF_LCD_ON) == 0) return;

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

  if(buf[1] == 1) {
    data->state = LV_INDEV_STATE_PRESSED;
    data->point.x = buf[3];
    data->point.y = buf[5];
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}


typedef struct _lvgl_file_header{
  uint32_t size;
  uint32_t addr;
  uint32_t pos;
} lvgl_file_header;

void * fs_open_cb(struct _lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode) {  
  JsfFileName fn = jsfNameFromString(path);

  JsfFileHeader header;
  uint32_t addr = jsfFindFile(fn, &header);
  if (!addr) return NULL;
  int fileLen = (int)jsfGetFileSize(&header);  

  lvgl_file_header *lv_file = (lvgl_file_header*) malloc(sizeof(lvgl_file_header));
  lv_file->size = fileLen;
  lv_file->addr = addr;
  lv_file->pos = 0;

  //jsiConsolePrintf("\n file open : (p)%s : (a)%x : (l)%x : (f)%x\n", path, addr, fileLen, lv_file);

  return lv_file;
}


lv_fs_res_t fs_close_cb(struct _lv_fs_drv_t * drv, void * file_p) {
  struct _lvgl_file_header *f = (lvgl_file_header*)file_p;
  //jsiConsolePrintf("\n file close : %x : (a)%x : (l)%x \n", f, f->addr, f->size);
  free(f);
  return LV_FS_RES_OK; 
}

lv_fs_res_t fs_read_cb(struct _lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br) {
  struct _lvgl_file_header *f = (lvgl_file_header*)file_p;
  //jsiConsolePrintf("\n file read : %x : (a)%x : (l)%x - %x \n", f, f->addr, f->size, btr);
  *br = btr;
  //buf = (unsigned char*) malloc(btr);
  jshFlashRead((unsigned char*)buf, f->addr + f->pos, btr);
  f->pos += btr;
  return LV_FS_RES_OK; 
}

lv_fs_res_t fs_seek_cb(struct _lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence) {
  struct _lvgl_file_header *f = (lvgl_file_header*)file_p;
  //jsiConsolePrintf("\n file seek : %x : (a)%x : (l)%x : (p)%x \n", f, f->addr, f->size, pos);
  f->pos = pos;
  return LV_FS_RES_OK; 
}

void js_log_cb(const char * buf) {
  jsiConsolePrintf("LVGL : %s\n", buf);
}


void jswrap_pinetime40_lvglinit() {

  static lv_disp_drv_t disp_drv;        /*Descriptor of a display driver*/

  lv_init();

#if LV_USE_LOG
  lv_log_register_print_cb(js_log_cb);
#endif

  //Initialize the display
  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, LCD_WIDTH * LCD_HEIGHT / 10);  /*Initialize the display buffer.*/

  lv_disp_drv_init(&disp_drv);        /*Basic initialization*/
  disp_drv.flush_cb = disp_flush;     /*Set your driver function*/
  disp_drv.draw_buf = &draw_buf;      /*Assign the buffer to the display*/
  disp_drv.hor_res = LCD_WIDTH;       /*Set the horizontal resolution of the display*/
  disp_drv.ver_res = LCD_HEIGHT;      /*Set the vertical resolution of the display*/
  lv_disp_drv_register(&disp_drv);    /*Finally register the driver*/

  static lv_indev_drv_t indev_drv;    /*Descriptor of a input device driver*/
  lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = touchpad_read;  /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);  /*Finally register the driver*/


  static lv_fs_drv_t drv;                   /*Needs to be static or global*/
  lv_fs_drv_init(&drv);                     /*Basic initialization*/

  drv.letter = 'F';

  drv.cache_size = 512;           /*Cache size for reading in bytes. 0 to not cache.*/

  drv.ready_cb = NULL;               /*Callback to tell if the drive is ready to use */
  drv.open_cb = fs_open_cb;                 /*Callback to open a file */
  drv.close_cb = fs_close_cb;               /*Callback to close a file */
  drv.read_cb = fs_read_cb;                 /*Callback to read a file */
  drv.write_cb = NULL;               /*Callback to write a file */
  drv.seek_cb = fs_seek_cb;                 /*Callback to seek in a file (Move cursor) */
  drv.tell_cb = NULL;                 /*Callback to tell the cursor position  */

  drv.dir_open_cb = NULL;         /*Callback to open directory to read its content */
  drv.dir_read_cb = NULL;         /*Callback to read a directory's content */
  drv.dir_close_cb = NULL;       /*Callback to close a directory */

  //drv.user_data = fs_user_data;             /*Any custom data if required*/

  lv_fs_drv_register(&drv);   

  // Set default theme
  lv_disp_t *dispp = lv_disp_get_default();
  lv_theme_t *theme = lv_theme_default_init(
    dispp, 
    lv_palette_main(LV_PALETTE_BLUE), 
    lv_palette_main(LV_PALETTE_RED),
    true, 
    LV_FONT_DEFAULT);
  lv_disp_set_theme(dispp, theme);


}

/* ----------------------------- LVGL --------------------------------- */

void touchHandler(bool state, IOEventFlags flags) {
  
  if (state) return; // only interested in when low
  if ((pinetimeFlags & JSPF_LCD_ON) == 0) return;

  // Reset inactivity timer so we will lock ourselves after a delay
  inactivityTimer = 0;

}

/*******************************************************************/


/*JSON{
  "type" : "hwinit",
  "generate" : "jswrap_pinetime40_hwinit"
}*/
NO_INLINE void jswrap_pinetime40_hwinit() {

  jshPinOutput(VIBRATE_PIN,0);
  
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

  lcdInit_SPINRF();

  jswrap_pinetime40_lvglinit();

  jsiConsolePrintf("HWINIT DONE\n");
}

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

  /*JsVar *settingsFN = jsvNewFromString("setting.json");
  JsVar *settings = jswrap_storage_readJSON(settingsFN,true);
  jsvUnLock(settingsFN);

  jsvUnLock(settings);*/

  if (!firstRun) {
    
    lv_obj_clean(lv_scr_act());
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *label = lv_label_create( lv_scr_act() );
    lv_label_set_text( label, "Loading..." );
    lv_obj_center(label);

    /*lv_obj_t * spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
    lv_obj_set_size(spinner, 200, 200);
    lv_obj_center(spinner);*/
    //lv_timer_handler();

  } else {
  
    char addrStr[20];
    JsVar* addr = jswrap_ble_getAddress(); // Write MAC address in bottom right
    jsvGetString(addr, addrStr, sizeof(addrStr));
    jsvUnLock(addr);

    /* Create simple label */
    //lv_obj_clean(lv_scr_act());    
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000055), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *label = lv_label_create( lv_scr_act() );
    lv_label_set_text_fmt( label, "Pinetime 40 - LVGL\n\nEspruino %s\n%s\n\njoaquim.org", JS_VERSION, addrStr);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_center(label);
    //lv_obj_t *img1= lv_img_create(lv_scr_act());
    //lv_img_set_src(img1, "F:mario.bin");

    //lv_timer_handler();
  }  
  

  buzzAmt = 0;
  beepFreq = 0;

  if (firstRun) {

    pinetimeFlags = JSPF_DEFAULT | JSPF_LCD_ON ; // includes pinetimeFlags
    lcdBrightness = 128;

    jshEnableWatchDog(10); // 5 second watchdog

    pollInterval = DEFAULT_ACCEL_POLL_INTERVAL;

    uint32_t err_code = app_timer_create(&m_peripheral_poll_timer_id,
      APP_TIMER_MODE_REPEATED,
      peripheralPollHandler);
    jsble_check_error(err_code);
    app_timer_start(m_peripheral_poll_timer_id, APP_TIMER_TICKS(pollInterval), NULL);    

    //jsiConsolePrintf("FIRST INIT DONE\n");

    // hack for lvgl update...
    //jsvUnLock(jspEvaluate("setInterval(lvgl.timerHandler,50)", true));

    jsvUnLock(jspEvaluate("setTimeout(Pinetime.load,5000)", true));

  }

  pinetimeFlags |= JSPF_LCD_ON;
  inactivityTimer = 0; // reset the LCD timeout timer
  btnLoadTimeout = DEFAULT_BTN_LOAD_TIMEOUT;
  lcdPowerTimeout = DEFAULT_LCD_POWER_TIMEOUT;  
  lcdWakeButton = 0;


  // If the home button is still pressed when we're restarting, set up
  // lcdWakeButton so the event for button release is 'eaten'
  if (jshPinGetValue(HOME_BTN_PININDEX))
    lcdWakeButton = HOME_BTN;
  
  //jsiConsolePrintf("pinetimeFlags %d\n",pinetimeFlags);

  //JsSysTime period = jshGetTimeFromMilliseconds(50);
  //jstExecuteFn(jswrap_lvgl_timerHandler, 0, period, (uint32_t)period, NULL);

  jspEvaluate("setInterval(LVGL.timer_handler,25)", true);

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
    if (pinetimeTasks & JSPT_RESET) jsiStatus |= JSIS_TODO_FLASH_LOAD;

    if (pinetimeTasks & JSPT_MIDNIGHT) {
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"midnight", NULL, 0);
    }
  
    if (pinetimeTasks & JSPT_CHARGE_EVENT) {
      JsVar *charging = jsvNewFromBool(wasCharging);
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"charging", &charging, 1);
      jsvUnLock(charging);
    }

  }
  
  jsvUnLock(pinetime);
  pinetimeTasks = JSPT_NONE;

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
Pinetime.setHRMPower(true, "myapp");
Pinetime.on('HRM',print);
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
