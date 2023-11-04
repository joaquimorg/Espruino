#include <jswrap_pinetime40.h>

#include "jsinteractive.h"
#include "jsdevices.h"
#include "jsnative.h"
#include "jshardware.h"
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

#define LVGLBUf_SIZE LCD_WIDTH * LCD_HEIGHT / 5

static lv_disp_draw_buf_t draw_buf;
static lv_color_t lvgl_buf1[LVGLBUf_SIZE];


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
  "name" : "CHARGING",
  "generate_full" : "BAT_PIN_CHARGING",
  "ifdef" : "PINETIME40",
  "return" : ["pin",""]
}
The Pinetime's CHARGING Pin.
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


/*JSON{
  "type" : "variable",
  "name" : "ACCELPIN",
  "generate_full" : "ACCEL_PIN_INT",
  "ifdef" : "PINETIME40",
  "return" : ["pin",""]
}
The Pinetime's Accel INT.
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


JsVar* promiseBeep;
JsVar* promiseBuzz;
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


JshI2CInfo i2cInternal;

#define ACCEL_I2C &i2cInternal
#define TOUCH_I2C &i2cInternal
#define HRM_I2C &i2cInternal

struct bma400_dev bma_sensor;

/// Current steps since reset
uint32_t stepCounter;

/* Earth's gravity in m/s^2 */
#define GRAVITY_EARTH     (9.80665f)

static float lsb_to_ms2(int16_t accel_data, uint8_t g_range, uint8_t bit_width) {
  float accel_ms2;
  int16_t half_scale;

  half_scale = 1 << (bit_width - 1);
  accel_ms2 = (GRAVITY_EARTH * accel_data * g_range) / half_scale;

  return accel_ms2;

}


/// How often should we fire 'health' events?
#define HEALTH_INTERVAL 600000 // 10 minutes (600 seconds)
/// Struct with currently tracked health info
typedef struct {
  uint8_t index; ///< time_in_ms / HEALTH_INTERVAL - we fire a new Health event when this changes
  uint16_t stepCount; ///< steps during current period
  uint16_t bpm10;  ///< beats per minute (x10)
  uint8_t bpmConfidence; ///< confidence of current BPM figure
} HealthState;
/// Currently tracked health info during this period
HealthState healthCurrent;
/// Health info during the last period, used when firing a health event
HealthState healthLast;
/// Health data so far this day
HealthState healthDaily;



typedef enum {
  JSPF_NONE,
  JSPF_WAKEON_FACEUP        = 1 << 0,
  JSPF_WAKEON_BTN1          = 1 << 1,
  JSPF_WAKEON_TOUCH         = 1 << 2,
  JSPF_BEEP_VIBRATE         = 1 << 3,
  JSPF_ACCEL_LISTENER       = 1 << 4, ///< we have a listener for accelerometer data
  JSPF_POWER_SAVE           = 1 << 5, ///< if no movement detected for a while, lower the accelerometer poll interval
  JSPF_HRM_ON               = 1 << 6,
  JSPF_LCD_ON               = 1 << 7,
  JSPF_HRM_INSTANT_LISTENER = 1 << 8,
  JSPF_ENABLE_BEEP          = 1 << 9,
  JSPF_ENABLE_BUZZ          = 1 << 10,

  JSPF_DEFAULT = ///< default at power-on
  JSPF_WAKEON_BTN1 | JSPF_WAKEON_FACEUP
} JsPinetimeFlags;
volatile JsPinetimeFlags pinetimeFlags = JSPF_NONE;


typedef enum {
  JSPT_NONE,
  JSPT_RESET        = 1 << 0, ///< reset the watch and reload code from flash
  JSPT_LCD_ON       = 1 << 1, ///< LCD controller
  JSPT_LCD_OFF      = 1 << 2,
  JSPT_ACCEL_TAPPED = 1 << 3, ///< tap event detected
  JSPT_GESTURE_DATA = 1 << 4, ///< we have data from a gesture
  JSPT_HRM_DATA     = 1 << 5, ///< Heart rate data is ready for analysis
  JSPT_CHARGE_EVENT = 1 << 6, ///< we need to fire a charging event
  JSPT_STEP_EVENT   = 1 << 7, ///< we've detected a step via the pedometer
  JSPT_STILL_EVENT  = 1 << 8, ///< we've detected still
  JSPT_RUN_EVENT    = 1 << 9, ///< we've detected run
  JSPT_FACE_UP      = 1 << 10, ///< Watch was turned face up/down (faceUp holds the actual state)
  JSPT_HEALTH       = 1 << 11, ///< New 'health' event
  JSPT_MIDNIGHT     = 1 << 12, ///< Fired at midnight each day - for housekeeping tasks
} JsPinetimeTasks;
JsPinetimeTasks pinetimeTasks;

void jswrap_pinetime40_setLCDPowerBacklight(bool isOn);

APP_TIMER_DEF(m_peripheral_poll_timer_id);
volatile uint16_t pollInterval; // in ms

/// LCD Brightness - 255=full
uint8_t lcdBrightness;

/// Actual LCD brightness (if we fade to a new brightness level)
uint8_t realLcdBrightness;
bool lcdFadeHandlerActive;

void jswrap_pinetime40_beep_callback();
void jswrap_pinetime40_buzz_callback();

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
  return !jshPinGetValue(BAT_PIN_CHARGING);
}



/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "battVoltage",
    "generate" : "jswrap_pinetime40_battVoltage",
    "return" : ["float","The battery voltage."],
    "ifdef" : "PINETIME40"
}
*/

// 3.2V ADC range and 14-bit ADC resolution = 3288mV/16384
#define VBAT_MV_PER_LSB   (0.20068359375F)

// 1M + 1M voltage divider on VBAT = (1M / (1M + 1M))
#define VBAT_DIVIDER      (0.5F)

// Compensation factor for the VBAT divider
#define VBAT_DIVIDER_COMP (2.10F)

#define REAL_VBAT_MV_PER_LSB (VBAT_DIVIDER_COMP * VBAT_MV_PER_LSB)


JsVarFloat jswrap_pinetime40_battVoltage() {

  JsVarFloat v = jshPinAnalog(BAT_PIN_VOLTAGE) * 16384.0;

  //int pc = v * 100;
  return (v * REAL_VBAT_MV_PER_LSB) / 1000;

}

typedef struct {
  float voltage;
  int percentage;
} VoltageToPercentageEntry;

/*
Voltage (V)	Approximate Charge (%)
4.20	100%
4.12	90%
4.04	80%
3.96	70%
3.88	60%
3.80	50%
3.75	45%
3.70	40%
3.65	35%
3.60	30%
3.55	25%
3.50	20%
3.45	15%
3.40	10%
3.32	0% (Considered Empty)
*/

VoltageToPercentageEntry lookupTable[] = {    
    {4.10, 100.0},
    {4.04,	90.0},
    {3.96,	80.0},
    {3.88,	70.0},
    {3.80,	60.0},
    {3.75,	50.0},
    {3.70,	40.0},
    {3.65,	35.0},
    {3.60,	30.0},
    {3.55,	25.0},
    {3.50,	20.0},
    {3.45,	15.0},
    {3.40,	10.0},
    {3.30,	0.0}
};

#define TABLE_SIZE (sizeof(lookupTable) / sizeof(lookupTable[0]))

int voltageToPercentage(float voltage) {
  if (voltage >= lookupTable[0].voltage) {
    return lookupTable[0].percentage;
  }
  if (voltage <= lookupTable[TABLE_SIZE - 1].voltage) {
    return lookupTable[TABLE_SIZE - 1].percentage;
  }

  for (int i = 1; i < TABLE_SIZE; ++i) {
    if (voltage >= lookupTable[i].voltage) {
      VoltageToPercentageEntry prev = lookupTable[i - 1];
      VoltageToPercentageEntry current = lookupTable[i];
      return prev.percentage + (int)((voltage - prev.voltage) / (current.voltage - prev.voltage) * (current.percentage - prev.percentage));
    }
  }

  return 0; // Shouldn't reach here
}

/// get battery percentage
JsVarInt jswrap_pinetime40_getBattery() {

  JsVarFloat v = jswrap_pinetime40_battVoltage();

  int pc = voltageToPercentage(v);
  if (pc > 100) pc = 100;
  if (pc < 0) pc = 0;
  return pc;

}

// -------------------------------------------------------------------------------------------------------

void btnHandlerCommon(int button, bool state, IOEventFlags flags) {
  // wake up IF LCD power or Lock has a timeout (so will turn off automatically)
  if (lcdPowerTimeout) {
    if ((pinetimeFlags & JSPF_WAKEON_BTN1) && (button == 1)) {
      // if a 'hard' button, turn LCD on      
      inactivityTimer = 0;
      if (state) {
        bool ignoreBtnUp = false;
        if (lcdPowerTimeout && !(pinetimeFlags & JSPF_LCD_ON) && state) {
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
    }
    else {
      // on touchscreen, keep LCD on if it was in previously
      if (pinetimeFlags & JSPF_LCD_ON)
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
    }
    else {
      /* if the next event is a 'down', > 100ms after the last event, we propogate it
       and subsequent events */
      lcdWakeButton = 0;
      lcdWakeButtonTime = 0;
    }
  }
  // if not off, add to the event queue for normal processing for watches
  if (!(pinetimeFlags & JSPF_LCD_ON))
    jshPushIOEvent(flags | (state ? EV_EXTI_IS_HIGH : 0), t);
}


/// Clear the given health state back to defaults
static void healthStateClear(HealthState *health) {
  memset(health, 0, sizeof(HealthState));
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
    }
    else
      homeBtnInterruptTimer = 0;
  }
  else {
    homeBtnTimer = 0;
    homeBtnInterruptTimer = 0;
  }

  if (lcdPowerTimeout && (pinetimeFlags & JSPF_LCD_ON) && inactivityTimer >= lcdPowerTimeout) {
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


  // Health tracking + midnight event
  // Did we enter a new 10 minute interval?
  JsVarFloat msecs = jshGetMillisecondsFromTime(time);
  uint8_t healthIndex = (uint8_t)(msecs/HEALTH_INTERVAL);

  if (healthIndex != healthCurrent.index) {
    // we did - fire 'Bangle.health' event
    healthLast = healthCurrent;
    healthStateClear(&healthCurrent);
    healthCurrent.index = healthIndex;
    pinetimeTasks |= JSPT_HEALTH;
    jshHadEvent();
    // What if we've changed day?
    TimeInDay td = getTimeFromMilliSeconds(msecs, false/*forceGMT*/);
    uint8_t dayIndex = (uint8_t)td.daysSinceEpoch;
    if (dayIndex != healthDaily.index) {
      pinetimeTasks |= JSPT_MIDNIGHT;
      healthStateClear(&healthDaily);
      healthDaily.index = dayIndex;
    }
  }

}

void btn1Handler(bool state, IOEventFlags flags) {
  btnHandlerCommon(1, state, flags);
}

void jswrap_pinetime40_pwrBacklight(bool on) {
  jshPinOutput(LCD_BL, on);
}

static void jswrap_pinetime40_setLCDPowerController(bool isOn) {
    if (isOn) { // wake
      lcdCmd_SPINRF(0x11, 0, NULL); // SLPOUT
      jshDelayMicroseconds(20);
      lcdCmd_SPINRF(0x29, 0, NULL); // DISPON
    } else { // sleep
      lcdCmd_SPINRF(0x28, 0, NULL); // DISPOFF
      jshDelayMicroseconds(20);
      lcdCmd_SPINRF(0x10, 0, NULL); // SLPIN
    }
  #ifdef LCD_EN
    jshPinOutput(LCD_EN, isOn); // enable off
  #endif  
}


static void backlightFadeHandler() {
  int target = (pinetimeFlags&JSPF_LCD_ON) ? lcdBrightness : 0;
  int brightness = realLcdBrightness;
  int step = brightness>>3; // to make this more linear
  if (step<4) step=4;
  if (target > brightness) {
    brightness += step;
    if (brightness > target)
      brightness = target;
  } else if (target < brightness) {
    brightness -= step;
    if (brightness < target)
      brightness = target;
  }
  realLcdBrightness = brightness;
  if (brightness==0) jswrap_pinetime40_pwrBacklight(0);
  else if (realLcdBrightness==255) jswrap_pinetime40_pwrBacklight(1);
  else {
    jshPinAnalogOutput(LCD_BL, realLcdBrightness/256.0, 200, JSAOF_NONE);
  }
}

void jswrap_pinetime40_setLCDPowerBacklight(bool isOn) {

  /*jswrap_pinetime40_pwrBacklight(isOn && (lcdBrightness > 0));

  if (isOn && lcdBrightness > 0 && lcdBrightness < 255) {
    jshPinAnalogOutput(LCD_BL, lcdBrightness / 256.0, 200, JSAOF_NONE);
  }*/

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

  //jswrap_pinetime40_setLCDPowerController(isOn);
  //jswrap_pinetime40_setLCDPowerBacklight(isOn);

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
    "name" : "getLCDBrightness",
    "generate" : "jswrap_pinetime40_getLCDBrightness",
    "return" : ["float","The brightness of Pinetime's display - from 0(off) to 256(on full)"],
    "ifdef" : "PINETIME40"
}
*/
JsVarFloat jswrap_pinetime40_getLCDBrightness() {
  // don't work ????
  //JsVarFloat b = lcdBrightness / 256.0;
  //return (int)b * 100;
  return lcdBrightness;
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
    timeout = 0;
  else if (timeout < 0) timeout = 0;
  lcdPowerTimeout = timeout * 1000;
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
JsVar* _jswrap_pinetime40_setOptions(JsVar* options, bool createObject) {
  bool wakeOnBTN1 = pinetimeFlags & JSPF_WAKEON_BTN1;
  bool wakeOnFaceUp = pinetimeFlags & JSPF_WAKEON_FACEUP;
  bool wakeOnTouch = pinetimeFlags & JSPF_WAKEON_TOUCH;
  bool wakeOnTwist = false;//pinetimeFlags&JSPF_WAKEON_TWIST;
  bool powerSave = pinetimeFlags & JSPF_POWER_SAVE;
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
    pinetimeFlags = (pinetimeFlags & ~JSPF_WAKEON_BTN1) | (wakeOnBTN1 ? JSPF_WAKEON_BTN1 : 0);
    pinetimeFlags = (pinetimeFlags & ~JSPF_WAKEON_FACEUP) | (wakeOnFaceUp ? JSPF_WAKEON_FACEUP : 0);
    pinetimeFlags = (pinetimeFlags & ~JSPF_WAKEON_TOUCH) | (wakeOnTouch ? JSPF_WAKEON_TOUCH : 0);
    //pinetimeFlags = (pinetimeFlags&~JSPF_WAKEON_TWIST) | (wakeOnTwist?JSPF_WAKEON_TWIST:0);
    pinetimeFlags = (pinetimeFlags & ~JSPF_POWER_SAVE) | (powerSave ? JSPF_POWER_SAVE : 0);
    if (lcdPowerTimeout < 0) lcdPowerTimeout = 0;

  }
  return 0;
}

void jswrap_pinetime40_setOptions(JsVar* options) {
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
JsVar* jswrap_pinetime40_getOptions() {
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
  return (pinetimeFlags & JSPF_LCD_ON) != 0;
}

// ----------------------------------------------------------------------------------------------------------------
/* ----------------------------- LVGL --------------------------------- */

void disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p) {

  //if ((pinetimeFlags & JSPF_LCD_ON) == 0) return;

  uint32_t width = (area->x2 - area->x1) + 1;
  uint32_t height = (area->y2 - area->y1) + 1;

  lcdFlip_SPINRF(area->x1, area->y1, width, height, (uint8_t*)color_p);

  lv_disp_flush_ready(disp);         /* Indicate you are ready with the flushing*/
}

void touchpad_read(lv_indev_t* indev, lv_indev_data_t* data) {

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

  if (buf[1] == 1) {
    data->state = LV_INDEV_STATE_PRESSED;
    data->point.x = buf[3];
    data->point.y = buf[5];
  }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}


typedef struct _lvgl_file_header {
  uint32_t size;
  uint32_t addr;
  uint32_t pos;
} lvgl_file_header;

void* fs_open_cb(struct _lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode) {
  JsfFileName fn = jsfNameFromString(path);

  JsfFileHeader header;
  uint32_t addr = jsfFindFile(fn, &header);
  if (!addr) return NULL;
  int fileLen = (int)jsfGetFileSize(&header);

  lvgl_file_header* lv_file = (lvgl_file_header*)malloc(sizeof(lvgl_file_header));
  lv_file->size = fileLen;
  lv_file->addr = addr;
  lv_file->pos = 0;

  //jsiConsolePrintf("\n file open : (p)%s : (a)%x : (l)%x : (f)%x\n", path, addr, fileLen, lv_file);

  return lv_file;
}


lv_fs_res_t fs_close_cb(struct _lv_fs_drv_t* drv, void* file_p) {
  struct _lvgl_file_header* f = (lvgl_file_header*)file_p;
  //jsiConsolePrintf("\n file close : %x : (a)%x : (l)%x \n", f, f->addr, f->size);
  free(f);
  return LV_FS_RES_OK;
}

lv_fs_res_t fs_read_cb(struct _lv_fs_drv_t* drv, void* file_p, void* buf, uint32_t btr, uint32_t* br) {
  struct _lvgl_file_header* f = (lvgl_file_header*)file_p;
  //jsiConsolePrintf("\n file read : %x : (a)%x : (l)%x - %x \n", f, f->addr, f->size, btr);
  *br = btr;
  //buf = (unsigned char*) malloc(btr);
  jshFlashRead((unsigned char*)buf, f->addr + f->pos, btr);
  f->pos += btr;
  return LV_FS_RES_OK;
}

lv_fs_res_t fs_seek_cb(struct _lv_fs_drv_t* drv, void* file_p, uint32_t pos, lv_fs_whence_t whence) {
  struct _lvgl_file_header* f = (lvgl_file_header*)file_p;
  //jsiConsolePrintf("\n file seek : %x : (a)%x : (l)%x : (p)%x \n", f, f->addr, f->size, pos);
  f->pos = pos;
  return LV_FS_RES_OK;
}

void js_log_cb(const char* buf) {
  jsiConsolePrintf("LVGL : %s\n", buf);
}


void jswrap_pinetime40_lvglinit() {

  static lv_disp_drv_t disp_drv;        /*Descriptor of a display driver*/

  lv_init();

#if LV_USE_LOG
  lv_log_register_print_cb(js_log_cb);
#endif

  //Initialize the display
  lv_disp_draw_buf_init(&draw_buf, lvgl_buf1, NULL, LVGLBUf_SIZE);  /*Initialize the display buffer.*/

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
  lv_disp_t* dispp = lv_disp_get_default();
  lv_theme_t* theme = lv_theme_default_init(
    dispp,
    lv_palette_main(LV_PALETTE_BLUE),
    lv_palette_main(LV_PALETTE_RED),
    true,
    LV_FONT_DEFAULT);
  lv_disp_set_theme(dispp, theme);


}

/* ----------------------------- LVGL --------------------------------- */
// ----------------------------------------------------------------------------------------------------------------


// ----------------------------------------------------------------------------------------------------------------
/* ----------------------------- I2C --------------------------------- */
void _jswrap_pinetime40_i2cWr(JshI2CInfo *i2c, int i2cAddr, JsVarInt reg, JsVarInt data) {
  unsigned char buf[2];
  buf[0] = (unsigned char)reg;
  buf[1] = (unsigned char)data;
  //i2cBusy = true;
  jsi2cWrite(i2c, i2cAddr, 2, buf, true);
  //i2cBusy = false;
}

JsVar *_jswrap_pinetime40_i2cRd(JshI2CInfo *i2c, int i2cAddr, JsVarInt reg, JsVarInt cnt) {
  if (cnt<0) cnt=0;
  unsigned char buf[128];
  if (cnt>(int)sizeof(buf)) cnt=sizeof(buf);
  buf[0] = (unsigned char)reg;
  //i2cBusy = true;
  jsi2cWrite(i2c, i2cAddr, 1, buf, false);
  jsi2cRead(i2c, i2cAddr, (cnt==0)?1:cnt, buf, true);
  //i2cBusy = false;
  if (cnt) {
    JsVar *ab = jsvNewArrayBufferWithData(cnt, buf);
    JsVar *d = jswrap_typedarray_constructor(ARRAYBUFFERVIEW_UINT8, ab,0,0);
    jsvUnLock(ab);
    return d;
  } else return jsvNewFromInteger(buf[0]);
}
// ----------------------------------------------------------------------------------------------------------------


/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "accelWr",
    "generate" : "jswrap_pinetime40_accelWr",
    "params" : [
      ["reg","int",""],
      ["data","int",""]
    ],
    "ifdef" : "PINETIME40"
}
Writes a register on the accelerometer
*/
void jswrap_pinetime40_accelWr(JsVarInt reg, JsVarInt data) {
  _jswrap_pinetime40_i2cWr(ACCEL_I2C, ACCEL_ADDR, reg, data);
}

/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "accelRd",
    "generate" : "jswrap_pinetime40_accelRd",
    "params" : [
      ["reg","int",""],
      ["cnt","int","If specified, returns an array of the given length (max 128). If not (or 0) it returns a number"]
    ],
    "return" : ["JsVar",""],
    "ifdef" : "PINETIME40",
    "typescript" : [
      "accelRd(reg: number, cnt?: 0): number;",
      "accelRd(reg: number, cnt: number): number[];"
    ]
}
Reads a register from the accelerometer
*/


JsVar *jswrap_pinetime40_accelRd(JsVarInt reg, JsVarInt cnt) {
  return _jswrap_pinetime40_i2cRd(ACCEL_I2C, ACCEL_ADDR, reg, cnt);
}


/* ----------------------------- BMA400 --------------------------------- */


/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "getStepCount",
    "generate" : "jswrap_pinetime40_getStepCount",
    "return" : ["int","The number of steps recorded by the step counter"],
    "ifdef" : "PINETIME40"
}
Returns the current amount of steps recorded by the step counter
*/
int jswrap_pinetime40_getStepCount() {
  return healthDaily.stepCount;
}

/*! Read write length varies based on user requirement */
#define READ_WRITE_LENGTH  UINT8_C(46)

/*!
 * @brief I2C read function
 */
BMA400_INTF_RET_TYPE bma400_i2c_read(uint8_t reg_addr, uint8_t* reg_data, uint32_t len, void* intf_ptr) {
  uint8_t buf[1] = {reg_addr};
  jsi2cWrite(ACCEL_I2C, ACCEL_ADDR, 1, buf, false);
  jsi2cRead(ACCEL_I2C, ACCEL_ADDR, len, reg_data, true);
  //jsiConsolePrintf("read i2c %x %x %x\n", reg_addr, len, reg_data);
  return BMA400_OK;
}

/*!
 * @brief I2C write function
 */

static void i2c_wx(uint8_t reg, uint8_t *data, int cnt) {
  uint8_t buf[READ_WRITE_LENGTH+1];
  buf[0] = reg;
  memcpy(&buf[1], data, cnt);
  jsi2cWrite(ACCEL_I2C, ACCEL_ADDR, cnt+1, buf, true);
}

BMA400_INTF_RET_TYPE bma400_i2c_write(uint8_t reg_addr, const uint8_t* reg_data, uint32_t len, void* intf_ptr) {

  i2c_wx(reg_addr, reg_data, len);
  //jsiConsolePrintf("write i2c %x %x\n", reg_addr, len);
  return BMA400_OK;
}

/*!
 * @brief Delay function
 */
void bma400_delay_us(uint32_t period, void* intf_ptr) {
  jshDelayMicroseconds(period);
}

void bma400_check_rslt(const char api_name[], int8_t rslt) {


  switch (rslt) {
  case BMA400_OK:

    /* Do nothing */
    break;
  case BMA400_E_NULL_PTR:
    jsiConsolePrintf("Error [%d] : Null pointer (%s)\r\n", rslt, api_name);
    break;
  case BMA400_E_COM_FAIL:
    jsiConsolePrintf("Error [%d] : Communication failure (%s)\r\n", rslt, api_name);
    break;
  case BMA400_E_INVALID_CONFIG:
    jsiConsolePrintf("Error [%d] : Invalid configuration (%s)\r\n", rslt, api_name);
    break;
  case BMA400_E_DEV_NOT_FOUND:
    jsiConsolePrintf("Error [%d] : Device not found (%s)\r\n", rslt, api_name);
    break;
  case BMA400_W_SELF_TEST_FAIL:
    jsiConsolePrintf("Error [%d] : BMA400 Self-test fail!!!\r\n", rslt);
    break;
  default:
    jsiConsolePrintf("Error [%d] : Unknown error code (%s)\r\n", rslt, api_name);
    break;
  }
}

int8_t bma400_interface_init(struct bma400_dev* bma400, uint8_t intf) {
  int8_t rslt = BMA400_OK;

  if (bma400 != NULL) {
    bma400->read = bma400_i2c_read;
    bma400->write = bma400_i2c_write;
    bma400->intf = intf;
    bma400->intf_ptr = ACCEL_I2C;
    bma400->delay_us = bma400_delay_us;
    bma400->read_write_len = READ_WRITE_LENGTH;

  } else {
    rslt = BMA400_E_NULL_PTR;
  }

  return rslt;
}

void accelHandler(bool state, IOEventFlags flags) {

  if (state) return; // only interested in when low  

  int8_t rslt = 0;
  uint16_t int_status;
  uint32_t step_count = 0;
  uint8_t act_int;

  rslt = bma400_get_interrupt_status(&int_status, &bma_sensor);
  bma400_check_rslt("bma400_get_interrupt_status", rslt);

  if (rslt == BMA400_OK) {

    if (int_status & BMA400_ASSERTED_D_TAP_INT) {
      //jsiConsolePrintf("Double tap detected\n");    
      if (!jswrap_pinetime40_isLCDOn()) {
        pinetimeTasks |= JSPT_LCD_ON;
        inactivityTimer = 0;
      }      
    }

    //if ((pinetimeFlags & JSPF_LCD_ON) == 1) {

      if (int_status & /*BMA400_ASSERTED_STEP_INT*/ 0x0100) {
        rslt = bma400_get_steps_counted(&step_count, &act_int, &bma_sensor);
        bma400_check_rslt("bma400_get_steps_counted", rslt);

        //stepCounter = step_count;

        int newSteps = step_count - stepCounter;
        if (newSteps>0) {
          stepCounter = step_count;
          healthCurrent.stepCount += newSteps;
          healthDaily.stepCount += newSteps;        
        }

        switch (act_int)
        {
          case BMA400_STILL_ACT:
              //jsiConsolePrintf("Steps counted : %d\n", step_count);
              //jsiConsolePrintf("Still Activity detected\n");
              pinetimeTasks |= JSPT_STILL_EVENT;
              jshHadEvent();
              break;
          case BMA400_WALK_ACT:
              //jsiConsolePrintf("Steps counted : %d\n", step_count);
              //jsiConsolePrintf("Walking Activity detected\n");
              pinetimeTasks |= JSPT_STEP_EVENT;
              jshHadEvent();
              break;
          case BMA400_RUN_ACT:
              //jsiConsolePrintf("Steps counted : %d\n", step_count);
              //jsiConsolePrintf("Running Activity detected\n");
              pinetimeTasks |= JSPT_RUN_EVENT;
              jshHadEvent();
              break;
        }      

      }    

      /*if (int_status & BMA400_ASSERTED_ACT_CH_X | BMA400_ASSERTED_ACT_CH_Y | BMA400_ASSERTED_ACT_CH_Z) {
        struct bma400_sensor_data data;
        float x, y, z;

        rslt = bma400_get_accel_data(BMA400_DATA_ONLY, &data, &bma_sensor);
        bma400_check_rslt("bma400_get_accel_data", rslt);

        // 12-bit accelerometer at range 2G
        x = lsb_to_ms2(data.x, 2, 12);
        y = lsb_to_ms2(data.y, 2, 12);
        z = lsb_to_ms2(data.z, 2, 12);

        //jsiConsolePrintf("Gravity-x : %d,   Gravity-y : %d,  Gravity-z :  %d \r\n", x, y, z);

      }*/

    //}
    
  }
}

/* ----------------------------- BMA400 --------------------------------- */



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

  jshPinOutput(VIBRATE_PIN, 0);

  jshI2CInitInfo(&i2cInternal);
  i2cInternal.bitrate = 0x7FFFFFFF; // make it as fast as we can go
  i2cInternal.pinSDA = TOUCH_PIN_SDA; // all i2c in same pins
  i2cInternal.pinSCL = TOUCH_PIN_SCL;
  i2cInternal.clockStretch = false;
  jsi2cSetup(&i2cInternal);

  // Touch init
  jshPinOutput(TOUCH_PIN_RST, 1);
  jshDelayMicroseconds(1000);
  jshPinOutput(TOUCH_PIN_RST, 0);
  jshDelayMicroseconds(1000);
  jshPinOutput(TOUCH_PIN_RST, 1);

  unsigned char buf[2];
  // 0xEE - CST816_REG_NOR_SCAN_PER - 0x01
  buf[0] = 0xEE;
  buf[1] = 0x01;
  jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 2, buf, true);
  // 0xFA - CST816_REG_IRQ_CTL - 0x60
  buf[0] = 0xFA;
  buf[1] = 0x60;
  jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 2, buf, true);
  // 0xFB - CST816_REG_AUTO_RESET - 0x0
  buf[0] = 0xFB;
  buf[1] = 0x0;
  jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 2, buf, true);
  // 0xFC - CST816_REG_LONG_PRESS_TIME - 0x10
  buf[0] = 0xFC;
  buf[1] = 0x10;
  jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 2, buf, true);
  // 0xED - CST816_REG_IRQ_PLUSE_WIDTH - 0x02  
  buf[0] = 0xED;
  buf[1] = 0x02;
  jsi2cWrite(TOUCH_I2C, TOUCH_ADDR, 2, buf, true);
  // Touch init end ---

  // BMA400 Init

  jshPinSetState(ACCEL_PIN_INT, JSHPINSTATE_GPIO_IN);

  jshDelayMicroseconds(1000);

  stepCounter = 0;

  int8_t rslt = 0;

  struct bma400_sensor_conf accel_settin[4] = { { 0 } };
  struct bma400_int_enable int_en[3] = { { 0 } };
  struct bma400_device_conf dev_settings[1] = { { 0 } };
  
  rslt = bma400_interface_init(&bma_sensor, BMA400_I2C_INTF);
  bma400_check_rslt("bma400_interface_init", rslt);

  rslt = bma400_soft_reset(&bma_sensor);
  bma400_check_rslt("bma400_soft_reset 1", rslt);

  rslt = bma400_init(&bma_sensor);
  bma400_check_rslt("bma400_init", rslt);

  //rslt = bma400_set_power_mode(BMA400_MODE_SLEEP, &bma_sensor);
  rslt = bma400_set_power_mode(BMA400_MODE_NORMAL, &bma_sensor);
  bma400_check_rslt("bma400_set_power_mode", rslt);
  
  dev_settings[0].type = BMA400_INT_PIN_CONF;
  dev_settings[0].param.int_conf.int_chan = BMA400_INT_CHANNEL_1;
  dev_settings[0].param.int_conf.pin_conf = BMA400_INT_OPEN_DRIVE_ACTIVE_0;
  
  // Set the desired configurations to the sensor
  rslt = bma400_set_device_conf(dev_settings, 1, &bma_sensor);
  bma400_check_rslt("bma400_set_device_conf", rslt);

  accel_settin[0].type = BMA400_ACCEL;
  accel_settin[1].type = BMA400_TAP_INT;
  accel_settin[2].type = BMA400_ACTIVITY_CHANGE_INT;
  accel_settin[3].type = BMA400_STEP_COUNTER_INT;

  rslt = bma400_get_sensor_conf(accel_settin, 4, &bma_sensor);
  bma400_check_rslt("bma400_get_sensor_conf", rslt);

  accel_settin[0].param.accel.int_chan = BMA400_INT_CHANNEL_1;
  accel_settin[0].param.accel.odr = BMA400_ODR_200HZ;
  accel_settin[0].param.accel.range = BMA400_RANGE_2G;
  accel_settin[0].param.accel.data_src = BMA400_DATA_SRC_ACCEL_FILT_1;
  accel_settin[0].param.accel.filt1_bw = BMA400_ACCEL_FILT1_BW_1;

  accel_settin[1].param.tap.int_chan = BMA400_INT_CHANNEL_1;
  accel_settin[1].param.tap.axes_sel = BMA400_TAP_Z_AXIS_EN;
  accel_settin[1].param.tap.sensitivity = BMA400_TAP_SENSITIVITY_0;
  accel_settin[1].param.tap.tics_th = BMA400_TICS_TH_18_DATA_SAMPLES;
  accel_settin[1].param.tap.quiet = BMA400_QUIET_60_DATA_SAMPLES;
  accel_settin[1].param.tap.quiet_dt = BMA400_QUIET_DT_4_DATA_SAMPLES;

  accel_settin[2].param.act_ch.int_chan = BMA400_INT_CHANNEL_1;
  accel_settin[2].param.act_ch.axes_sel = BMA400_AXIS_XYZ_EN;
  accel_settin[2].param.act_ch.act_ch_ntps = BMA400_ACT_CH_SAMPLE_CNT_64;
  accel_settin[2].param.act_ch.data_source = BMA400_DATA_SRC_ACC_FILT1;
  accel_settin[2].param.act_ch.act_ch_thres = 10;

  accel_settin[3].param.step_cnt.int_chan = BMA400_INT_CHANNEL_1;

  // Set the desired configurations to the sensor
  rslt = bma400_set_sensor_conf(accel_settin, 4, &bma_sensor);
  bma400_check_rslt("bma400_set_sensor_conf", rslt);
  
  int_en[0].type = BMA400_DOUBLE_TAP_INT_EN;
  int_en[0].conf = BMA400_ENABLE;

  int_en[1].type = BMA400_ACTIVITY_CHANGE_INT_EN;
  int_en[1].conf = BMA400_ENABLE;

  int_en[2].type = BMA400_STEP_COUNTER_INT_EN;
  int_en[2].conf = BMA400_ENABLE;

  rslt = bma400_enable_interrupt(int_en, 3, &bma_sensor);
  bma400_check_rslt("bma400_enable_interrupt", rslt);


  //


  // HRS3300 Init

  //

  lcdInit_SPINRF();

  jswrap_pinetime40_lvglinit();

  jshPinSetState(BAT_PIN_CHARGING, JSHPINSTATE_GPIO_IN_PULLUP);

  jsiConsolePrintf("HWINIT DONE\n");
}

/*JSON{
  "type" : "init",
  "generate" : "jswrap_pinetime40_init"
}*/
NO_INLINE void jswrap_pinetime40_init() {

  IOEventFlags channel;

  bool firstRun = jsiStatus & JSIS_FIRST_BOOT; // is this the first time jswrap_pinetime40_init was called?

  /*JsVar *settingsFN = jsvNewFromString("setting.json");
  JsVar *settings = jswrap_storage_readJSON(settingsFN,true);
  jsvUnLock(settingsFN);

  jsvUnLock(settings);*/

  bool recoveryMode = false;

  if (firstRun) {
    pinetimeFlags |= JSPF_ENABLE_BUZZ;
    pinetimeFlags |= JSPF_ENABLE_BEEP;
    inactivityTimer = 0; // reset the LCD timeout timer
    btnLoadTimeout = DEFAULT_BTN_LOAD_TIMEOUT;
    lcdPowerTimeout = DEFAULT_LCD_POWER_TIMEOUT;
    
    realLcdBrightness = firstRun ? 0 : lcdBrightness;
    lcdFadeHandlerActive = false;

    healthStateClear(&healthCurrent);
    healthStateClear(&healthLast);
    healthStateClear(&healthDaily);

    pinetimeFlags = JSPF_DEFAULT | JSPF_LCD_ON; // includes pinetimeFlags
    lcdBrightness = 128;

    /*if (jshPinGetValue(HOME_BTN_PININDEX))
      recoveryMode = true;*/

  }

  // If the home button is still pressed when we're restarting, set up
  // lcdWakeButton so the event for button release is 'eaten'
  if (jshPinGetValue(HOME_BTN_PININDEX))
    lcdWakeButton = HOME_BTN;

  lcdWakeButton = 0;

  realLcdBrightness = firstRun ? 0 : lcdBrightness;
  lcdFadeHandlerActive = false;
  //jswrap_pinetime40_setLCDPowerBacklight(pinetimeFlags & JSPF_LCD_ON);

  buzzAmt = 0;
  beepFreq = 0;

  bool showSplashScreen = true;

  if (jsiStatus & JSIS_TODO_FLASH_LOAD) {
    showSplashScreen = false;

    if (!firstRun && !recoveryMode) {

      //jswrap_pinetime40_setLCDPower(1);

      lv_obj_clean(lv_scr_act());
      lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_t* label = lv_label_create(lv_scr_act());
      lv_label_set_text(label, "Loading...");
      lv_obj_center(label);

      /*lv_obj_t * spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
      lv_obj_set_size(spinner, 200, 200);
      lv_obj_center(spinner);*/
      lv_timer_handler();

    }
  }

  if (!(jsiStatus & JSIS_COMPLETELY_RESET))
    showSplashScreen = false;
  
  if (recoveryMode)
    showSplashScreen = false;
  
  if (showSplashScreen) {
    char addrStr[20];
    JsVar* addr = jswrap_ble_getAddress(); // Write MAC address in bottom right
    jsvGetString(addr, addrStr, sizeof(addrStr));
    jsvUnLock(addr);

    /* Create simple label */
    //lv_obj_clean(lv_scr_act());    
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000055), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t* label = lv_label_create(lv_scr_act());
    lv_label_set_text_fmt(label, "Pinetime 40 - LVGL\n\nEspruino %s\n%s\n\njoaquim.org", JS_VERSION, addrStr);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_center(label);
    //lv_obj_t *img1= lv_img_create(lv_scr_act());
    //lv_img_set_src(img1, "F:mario.bin");

    lv_timer_handler();

  }

  //if (firstRun) {

    pollInterval = DEFAULT_ACCEL_POLL_INTERVAL;

    uint32_t err_code = app_timer_create(&m_peripheral_poll_timer_id,
      APP_TIMER_MODE_REPEATED,
      peripheralPollHandler);
    jsble_check_error(err_code);
    app_timer_start(m_peripheral_poll_timer_id, APP_TIMER_TICKS(pollInterval), NULL);

  //}

  jshEnableWatchDog(5); // 5 second watchdog

  jshSetPinShouldStayWatched(BTN1_PININDEX, true);
  channel = jshPinWatch(BTN1_PININDEX, true, JSPW_NONE);
  if (channel != EV_NONE) jshSetEventCallback(channel, btn1Handler);

  jshSetPinShouldStayWatched(TOUCH_PIN_IRQ, true);
  channel = jshPinWatch(TOUCH_PIN_IRQ, true, JSPW_NONE);
  if (channel != EV_NONE) jshSetEventCallback(channel, touchHandler);

  jshSetPinShouldStayWatched(ACCEL_PIN_INT, true);
  channel = jshPinWatch(ACCEL_PIN_INT, true, JSPW_NONE);
  if (channel != EV_NONE) jshSetEventCallback(channel, accelHandler);

  jspEvaluate("setInterval(LVGL.timer_handler,10)", true);

}

/*JSON{
  "type" : "idle",
  "generate" : "jswrap_pinetime40_idle"
}*/
bool jswrap_pinetime40_idle() {
  JsVar* pinetime = jsvObjectGetChildIfExists(execInfo.root, "Pinetime");

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
      JsVar* charging = jsvNewFromBool(wasCharging);
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"charging", &charging, 1);
      jsvUnLock(charging);
    }

    if (pinetimeTasks & JSPT_STEP_EVENT) {
      JsVar *steps = jsvNewFromInteger(healthDaily.stepCount);
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"step", &steps, 1);
      jsvUnLock(steps);
    }

    if (pinetimeTasks & JSPT_STILL_EVENT) {
      JsVar *steps = jsvNewFromInteger(healthDaily.stepCount);
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"still", &steps, 1);
      jsvUnLock(steps);
    }

    if (pinetimeTasks & JSPT_RUN_EVENT) {
      JsVar *steps = jsvNewFromInteger(healthDaily.stepCount);
      jsiQueueObjectCallbacks(pinetime, JS_EVENT_PREFIX"run", &steps, 1);
      jsvUnLock(steps);
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

  app_timer_stop(m_peripheral_poll_timer_id);

  if (lcdFadeHandlerActive) {
    jstStopExecuteFn(backlightFadeHandler, NULL);
    lcdFadeHandlerActive = false;
  }

  // stop and unlock beep & buzz
  jsvUnLock(promiseBeep);
  promiseBeep = 0;
  jsvUnLock(promiseBuzz);
  promiseBuzz = 0;
  if (beepFreq) jswrap_pinetime40_beep_callback();
  if (buzzAmt) jswrap_pinetime40_buzz_callback();

}


/*******************************************************************/


static NO_INLINE void _jswrap_pinetime40_setVibration() {
  int beep = 0;
  if (pinetimeFlags & JSPF_BEEP_VIBRATE)
    beep = beepFreq;

  if (buzzAmt == 0 && beep == 0)
    jshPinOutput(VIBRATE_PIN, 0); // vibrate off
  else if (beep == 0) { // vibrate only
    jshPinAnalogOutput(VIBRATE_PIN, 0.4 + buzzAmt * 0.6 / 255, 1000, JSAOF_NONE);
  }
  else { // beep and vibrate
    jshPinAnalogOutput(VIBRATE_PIN, 0.2 + buzzAmt * 0.6 / 255, beep, JSAOF_NONE);
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

JsVar* jswrap_pinetime40_beep(int time, int freq) {
  if (freq <= 0) freq = 4000;
  if (freq > 60000) freq = 60000;
  if (time <= 0) time = 200;
  if (time > 5000) time = 5000;
  if (promiseBeep) {
    JsVar* fn = jsvNewNativeFunction((void (*)(void))jswrap_pinetime40_beep, JSWAT_JSVAR | (JSWAT_INT32 << JSWAT_BITS) | (JSWAT_INT32 << (JSWAT_BITS * 2)));
    JsVar* v;
    v = jsvNewFromInteger(time);jsvAddFunctionParameter(fn, 0, v);jsvUnLock(v); // bind param 1
    v = jsvNewFromInteger(freq);jsvAddFunctionParameter(fn, 0, v);jsvUnLock(v); // bind param 2
    JsVar* promise = jswrap_promise_then(promiseBeep, fn, NULL);
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

JsVar* jswrap_pinetime40_buzz(int time, JsVarFloat amt) {
  if (!isfinite(amt) || amt > 1) amt = 1;
  if (amt < 0) amt = 0;
  if (time <= 0) time = 200;
  if (time > 5000) time = 5000;
  if (promiseBuzz) {
    JsVar* fn = jsvNewNativeFunction((void (*)(void))jswrap_pinetime40_buzz, JSWAT_JSVAR | (JSWAT_INT32 << JSWAT_BITS) | (JSWAT_JSVARFLOAT << (JSWAT_BITS * 2)));
    JsVar* v;
    v = jsvNewFromInteger(time);jsvAddFunctionParameter(fn, 0, v);jsvUnLock(v); // bind param 1
    v = jsvNewFromFloat(amt);jsvAddFunctionParameter(fn, 0, v);jsvUnLock(v); // bind param 2
    JsVar* promise = jswrap_promise_then(promiseBuzz, fn, NULL);
    jsvUnLock(fn);
    return promise;
  }
  promiseBuzz = jspromise_create();
  if (!promiseBuzz) return 0;

  buzzAmt = (unsigned char)(amt * 255);
  if (jstExecuteFn(jswrap_pinetime40_buzz_callback, NULL, jshGetTimeFromMilliseconds(time), 0, NULL)) {
    // task schedule succeeded - start buzz
    if (pinetimeFlags & JSPF_ENABLE_BUZZ) {
      _jswrap_pinetime40_setVibration();
    }
  }
  else
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
bool jswrap_pinetime40_setHRMPower(bool isOn, JsVar* appId) {

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
  "name" : "setBootCode",
  "generate" : "jswrap_pinetime40_setBootCode",
  "params" : [
    ["code","JsVar","The code to execute (as a string)"],
    ["alwaysExec","bool","Whether to always execute the code (even after a reset)"]
  ],
  "typescript" : "setBootCode(code: string, alwaysExec?: boolean): void;"
}
This writes JavaScript code into Pinetime's flash memory, to be executed on
startup. It differs from `save()` in that `save()` saves the whole state of the
interpreter, whereas this just saves JS code that is executed at boot.

Code will be executed before `onInit()` and `E.on('init', ...)`.

If `alwaysExec` is `true`, the code will be executed even after a call to
`reset()`. This is useful if you're making something that you want to program,
but you want some code that is always built in (for instance setting up a
display or keyboard).

To remove boot code that has been saved previously, use `E.setBootCode("")`

**Note:** this removes any code that was previously saved with `save()`
*/
void jswrap_pinetime40_setBootCode(JsVar *code, bool alwaysExec) {
  if (jsvIsString(code)) code = jsvLockAgain(code);
  else code = jsvNewFromEmptyString();
  jsfSaveBootCodeToFlash(code, alwaysExec);
  jsvUnLock(code);
}