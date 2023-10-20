#include <jswrap_pinetime.h>

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
#include "jswrap_bluetooth.h"
#include "jswrap_graphics.h"
#include "jsflash.h"
#include "app_timer.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_soc.h"
#include "nrf_saadc.h"
#include "nrf5x_utils.h"

#include "jsi2c.h" // accelerometer/etc

//#if defined(LCD_CONTROLLER_ST7789V)
//#include "lcd_spi_unbuf.h"
//#include "lcd_spilcd.h"
#include "lcd_st7789v.h"
//#endif

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
    "ifdef" : "PINETIME"
}
Class containing utility functions for
[Pinetime.js](https://www.pine64.org/pinetime/)
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
  "ifdef" : "PINETIME",
  "return" : ["pin",""]
}
The Pinetime's vibration motor.
*/

/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "step",
  "params" : [["up","int","The number of steps since Pinetime was last reset"]],
  "ifdef" : "PINETIME"
}
Called whenever a step is detected by Pinetime's pedometer.
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "charging",
  "params" : [["charging","bool","`true` if charging"]],
  "ifdef" : "PINETIME"
}
Is the battery charging or not?
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "lcdPower",
  "params" : [["on","bool","`true` if screen is on"]],
  "ifdef" : "PINETIME"
}
Has the screen been turned on or off? Can be used to stop tasks that are no
longer useful if nothing is displayed. Also see `Pinetime.isLCDOn()`
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "gesture",
  "params" : [["xyz","JsVar","An Int8Array of XYZXYZXYZ data"]],
  "ifdef" : "PINETIME",
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
  "ifdef" : "PINETIME",
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
  "ifdef" : "PINETIME",
  "typescript" : "on(event: \"touch\", callback: TouchCallback): void;"
}
Emitted when the touchscreen is pressed
*/
/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "midnight",
  "ifdef" : "PINETIME"
}
Emitted at midnight (at the point the `day` health info is reset to 0).

Can be used for housekeeping tasks that don't want to be run during the day.
*/

/*JSON{
  "type" : "event",
  "class" : "Pinetime",
  "name" : "lock",
  "params" : [["on","bool","`true` if screen is locked, `false` if it is unlocked and touchscreen/buttons will work"]],
  "ifdef" : "PINETIME"
}
Has the screen been locked? Also see `Pinetime.isLocked()`
*/


void graphicsInternalFlip() {
  //lcdFlip_SPILCD(&graphicsInternal);
  lcdST7789_flip();
  //jswrap_lcd_spi_unbuf_idle();
}

/// Flip buffer contents with the screen.
void lcd_flip(JsVar* parent, bool all) {
  graphicsInternalFlip();
}


/*JSON{
  "type" : "hwinit",
  "generate" : "jswrap_pinetime_hwinit"
}*/
NO_INLINE void jswrap_pinetime_hwinit() {
  // BT1 Enable
  jshPinOutput(15, false);
  NRF_GPIO_PIN_CNF(BTN1_PININDEX,0x0000000c);     // BTN1 input (with pullup)  
  NRF_GPIO_PIN_CNF(BAT_PIN_CHARGING,0x0000000c);     // Charge input (with pullup)

  jswrap_ble_setTxPower(4);

  // LCD pin init
  /*jshPinOutput(LCD_PIN_CS, 1);
  jshPinOutput(LCD_PIN_DC, 1);
  jshPinOutput(LCD_PIN_SCK, 1);*/

  //
  graphicsStructInit(&graphicsInternal, LCD_WIDTH, LCD_HEIGHT, LCD_BPP);
  graphicsInternal.data.type = JSGRAPHICSTYPE_ST7789;
  graphicsInternal.data.flags = 0;
  graphicsInternal.data.fontSize = JSGRAPHICS_FONTSIZE_6X8 + 2; // 4x6 size is default

  //lcdInit_SPILCD(&graphicsInternal);

  lcdST7789_init(&graphicsInternal);
  //lcdST7789_setMode( LCDST7789_MODE_UNBUFFERED );
  //lcdST7789_setCallbacks(&graphicsInternal);

  graphicsSetCallbacks(&graphicsInternal);

  graphicsFillRect(&graphicsInternal, 0,0,LCD_WIDTH-1,LCD_HEIGHT-1, GRAPHICS_COL_RGB_TO_16(0,0,255));
}

/*JSON{
  "type" : "init",
  "generate" : "jswrap_pinetime_init"
}*/
NO_INLINE void jswrap_pinetime_init() {


  
  // Reset global graphics instance
  graphicsStructResetState(&graphicsInternal);

  // Create backing graphics object for LCD
  JsVar *graphics = jspNewObject(0, "Graphics");
  // if there's nothing in the Graphics object, we assume it's for the built-in graphics
  if (!graphics) return; // low memory
  // add it as a global var
  jsvObjectSetChild(execInfo.root, "g", graphics);
  jsvObjectSetChild(execInfo.hiddenRoot, JS_GRAPHICS_VAR, graphics);
  graphicsInternal.graphicsVar = graphics;

  // Create 'flip' fn
  JsVar *fn = jsvNewNativeFunction((void (*)(void))lcd_flip, JSWAT_VOID|JSWAT_THIS_ARG|(JSWAT_BOOL << (JSWAT_BITS*1)));
  jsvObjectSetChildAndUnLock(graphics,"flip",fn);



}

/*JSON{
  "type" : "kill",
  "generate" : "jswrap_pinetime_kill"
}*/
void jswrap_pinetime_kill() {

}

/*JSON{
  "type" : "idle",
  "generate" : "jswrap_pinetime_idle"
}*/
bool jswrap_pinetime_idle() {

}

void jswrap_pinetime_kickPollWatchdog() {

}

JsVarInt jswrap_pinetime_getBattery() {
  return 100;
}



/*JSON{
    "type" : "staticmethod",
    "class" : "Pinetime",
    "name" : "load",
    "generate_js" : "libs/js/pinetime/load.min.js",
    "params" : [
      ["file","JsVar","[optional] A string containing the file name for the app to be loaded"]
    ],
    "ifdef" : "PINETIME",
    "typescript": [
      "load(file: string): void;",
      "load(): void;"
    ]
}
*/







