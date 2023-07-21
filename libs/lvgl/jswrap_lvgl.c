

#include "jswrap_lvgl.h"
#include "jswrapper.h"
#include "jsutils.h"
#include "jsinteractive.h"
#include "lvgl.h"

/*JSON{
  "type" : "class",
  "class" : "LVGL",
  "typescript" : "lv"
}
This class provides GUI operations using LVGL.
*/

/*********************************************************************************/
// lv_dir_t
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_DIR_LEFT",    "generate_full" : "LV_DIR_LEFT",    "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_DIR_RIGHT",   "generate_full" : "LV_DIR_RIGHT",   "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_DIR_TOP",     "generate_full" : "LV_DIR_TOP",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_DIR_BOTTOM",  "generate_full" : "LV_DIR_BOTTOM",  "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_DIR_HOR",     "generate_full" : "LV_DIR_HOR",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_DIR_VER",     "generate_full" : "LV_DIR_VER",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_DIR_ALL",     "generate_full" : "LV_DIR_ALL",     "ifdef" : "LVGL", "return" : ["int",""]
}*/

//lv_align_t
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_DEFAULT",     "generate_full" : "LV_ALIGN_DEFAULT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_TOP_LEFT",    "generate_full" : "LV_ALIGN_TOP_LEFT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_TOP_MID",     "generate_full" : "LV_ALIGN_TOP_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_TOP_RIGHT",   "generate_full" : "LV_ALIGN_TOP_RIGHT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_BOTTOM_LEFT", "generate_full" : "LV_ALIGN_BOTTOM_LEFT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_BOTTOM_MID",  "generate_full" : "LV_ALIGN_BOTTOM_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_BOTTOM_RIGHT","generate_full" : "LV_ALIGN_BOTTOM_RIGHT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_LEFT_MID",    "generate_full" : "LV_ALIGN_LEFT_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_RIGHT_MID",   "generate_full" : "LV_ALIGN_RIGHT_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_CENTER",      "generate_full" : "LV_ALIGN_CENTER",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_TOP_LEFT","generate_full" : "LV_ALIGN_OUT_TOP_LEFT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_TOP_MID", "generate_full" : "LV_ALIGN_OUT_TOP_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_TOP_RIGHT", "generate_full" : "LV_ALIGN_OUT_TOP_RIGHT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_BOTTOM_LEFT", "generate_full" : "LV_ALIGN_OUT_BOTTOM_LEFT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_BOTTOM_MID",  "generate_full" : "LV_ALIGN_OUT_BOTTOM_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_BOTTOM_RIGHT","generate_full" : "LV_ALIGN_OUT_BOTTOM_RIGHT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_LEFT_TOP",    "generate_full" : "LV_ALIGN_OUT_LEFT_TOP",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_LEFT_MID",    "generate_full" : "LV_ALIGN_OUT_LEFT_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_LEFT_BOTTOM", "generate_full" : "LV_ALIGN_OUT_LEFT_BOTTOM",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_RIGHT_TOP",   "generate_full" : "LV_ALIGN_OUT_RIGHT_TOP",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_RIGHT_MID",   "generate_full" : "LV_ALIGN_OUT_RIGHT_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ALIGN_OUT_RIGHT_BOTTOM","generate_full" : "LV_ALIGN_OUT_RIGHT_BOTTOM",     "ifdef" : "LVGL", "return" : ["int",""]
}*/

//lv_text_align_t
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_TEXT_ALIGN_AUTO","generate_full" : "LV_TEXT_ALIGN_AUTO", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_TEXT_ALIGN_LEFT","generate_full" : "LV_TEXT_ALIGN_LEFT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_TEXT_ALIGN_CENTER","generate_full" : "LV_TEXT_ALIGN_CENTER", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_TEXT_ALIGN_RIGHT","generate_full" : "LV_TEXT_ALIGN_RIGHT", "ifdef" : "LVGL", "return" : ["int",""]
}*/

//lv_event_code_t
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_ALL", "generate_full" : "LV_EVENT_ALL", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_PRESSED", "generate_full" : "LV_EVENT_PRESSED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_PRESSING", "generate_full" : "LV_EVENT_PRESSING", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_PRESS_LOST", "generate_full" : "LV_EVENT_PRESS_LOST", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_SHORT_CLICKED", "generate_full" : "LV_EVENT_SHORT_CLICKED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_LONG_PRESSED", "generate_full" : "LV_EVENT_LONG_PRESSED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_LONG_PRESSED_REPEAT", "generate_full" : "LV_EVENT_LONG_PRESSED_REPEAT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_CLICKED", "generate_full" : "LV_EVENT_CLICKED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_RELEASED", "generate_full" : "LV_EVENT_RELEASED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_SCROLL_BEGIN", "generate_full" : "LV_EVENT_SCROLL_BEGIN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_SCROLL_END", "generate_full" : "LV_EVENT_SCROLL_END", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_SCROLL", "generate_full" : "LV_EVENT_SCROLL", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_GESTURE", "generate_full" : "LV_EVENT_GESTURE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_KEY", "generate_full" : "LV_EVENT_KEY", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_FOCUSED", "generate_full" : "LV_EVENT_FOCUSED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_DEFOCUSED", "generate_full" : "LV_EVENT_DEFOCUSED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_LEAVE", "generate_full" : "LV_EVENT_LEAVE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_HIT_TEST", "generate_full" : "LV_EVENT_HIT_TEST", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_COVER_CHECK", "generate_full" : "LV_EVENT_COVER_CHECK", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_REFR_EXT_DRAW_SIZE", "generate_full" : "LV_EVENT_REFR_EXT_DRAW_SIZE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_DRAW_MAIN_BEGIN", "generate_full" : "LV_EVENT_DRAW_MAIN_BEGIN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_DRAW_MAIN", "generate_full" : "LV_EVENT_DRAW_MAIN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_DRAW_MAIN_END", "generate_full" : "LV_EVENT_DRAW_MAIN_END", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_DRAW_POST_BEGIN", "generate_full" : "LV_EVENT_DRAW_POST_BEGIN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_DRAW_POST", "generate_full" : "LV_EVENT_DRAW_POST", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_DRAW_POST_END", "generate_full" : "LV_EVENT_DRAW_POST_END", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_DRAW_PART_BEGIN", "generate_full" : "LV_EVENT_DRAW_PART_BEGIN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_DRAW_PART_END", "generate_full" : "LV_EVENT_DRAW_PART_END", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_VALUE_CHANGED", "generate_full" : "LV_EVENT_VALUE_CHANGED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_INSERT", "generate_full" : "LV_EVENT_INSERT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_REFRESH", "generate_full" : "LV_EVENT_REFRESH", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_READY", "generate_full" : "LV_EVENT_READY", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_CANCEL", "generate_full" : "LV_EVENT_CANCEL", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_DELETE", "generate_full" : "LV_EVENT_DELETE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_CHILD_CHANGED", "generate_full" : "LV_EVENT_CHILD_CHANGED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_CHILD_CREATED", "generate_full" : "LV_EVENT_CHILD_CREATED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_CHILD_DELETED", "generate_full" : "LV_EVENT_CHILD_DELETED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_SCREEN_UNLOAD_START", "generate_full" : "LV_EVENT_SCREEN_UNLOAD_START", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_SCREEN_LOAD_START", "generate_full" : "LV_EVENT_SCREEN_LOAD_START", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_SCREEN_LOADED", "generate_full" : "LV_EVENT_SCREEN_LOADED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_SCREEN_UNLOADED", "generate_full" : "LV_EVENT_SCREEN_UNLOADED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_SIZE_CHANGED", "generate_full" : "LV_EVENT_SIZE_CHANGED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_STYLE_CHANGED", "generate_full" : "LV_EVENT_STYLE_CHANGED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_LAYOUT_CHANGED", "generate_full" : "LV_EVENT_LAYOUT_CHANGED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_EVENT_GET_SELF_SIZE", "generate_full" : "LV_EVENT_GET_SELF_SIZE", "ifdef" : "LVGL", "return" : ["int",""]
}*/

//lv_state_t
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_DEFAULT", "generate_full" : "LV_STATE_DEFAULT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_CHECKED", "generate_full" : "LV_STATE_CHECKED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_FOCUSED", "generate_full" : "LV_STATE_FOCUSED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_FOCUS_KEY", "generate_full" : "LV_STATE_FOCUS_KEY", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_EDITED", "generate_full" : "LV_STATE_EDITED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_HOVERED", "generate_full" : "LV_STATE_HOVERED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_PRESSED", "generate_full" : "LV_STATE_PRESSED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_SCROLLED", "generate_full" : "LV_STATE_SCROLLED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_DISABLED", "generate_full" : "LV_STATE_DISABLED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_USER_1", "generate_full" : "LV_STATE_USER_1", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_USER_2", "generate_full" : "LV_STATE_USER_2", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_USER_3", "generate_full" : "LV_STATE_USER_3", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_USER_4", "generate_full" : "LV_STATE_USER_4", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_STATE_ANY", "generate_full" : "LV_STATE_ANY", "ifdef" : "LVGL", "return" : ["int",""]
}*/


//lv_part_t
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_PART_MAIN", "generate_full" : "LV_PART_MAIN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_PART_SCROLLBAR", "generate_full" : "LV_PART_SCROLLBAR", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_PART_INDICATOR", "generate_full" : "LV_PART_INDICATOR", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_PART_KNOB", "generate_full" : "LV_PART_KNOB", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_PART_SELECTED", "generate_full" : "LV_PART_SELECTED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_PART_ITEMS", "generate_full" : "LV_PART_ITEMS", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_PART_TICKS", "generate_full" : "LV_PART_TICKS", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_PART_CURSOR", "generate_full" : "LV_PART_CURSOR", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_PART_CUSTOM_FIRST", "generate_full" : "LV_PART_CUSTOM_FIRST", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_PART_ANY", "generate_full" : "LV_PART_ANY", "ifdef" : "LVGL", "return" : ["int",""]
}*/


/*******************************************************************************************/
// FONT

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_font_BigNumbers",
  "generate" : "jswrap_lv_font_BigNumbers",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_BigNumbers() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_BigNumbers;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_font_Icons32",
  "generate" : "jswrap_lv_font_Icons32",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_Icons32() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_Icons32;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_font_Numbers42",
  "generate" : "jswrap_lv_font_Numbers42",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_Numbers42() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_Numbers42;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_font_Numbers64",
  "generate" : "jswrap_lv_font_Numbers64",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_Numbers64() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_Numbers64;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_font_OpenSans22",
  "generate" : "jswrap_lv_font_OpenSans22",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_OpenSans22() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_OpenSans22;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_font_OpenSans22Bold",
  "generate" : "jswrap_lv_font_OpenSans22Bold",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_OpenSans22Bold() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_OpenSans22Bold;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}


/*******************************************************************************************/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "timer_handler",
  "generate_full" : "lv_timer_handler()"
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_set_style_img_recolor_opa",
  "generate_full" : "js_lv_obj_set_style_bg_opa(jsvar, value, selector, lv_obj_set_style_img_recolor_opa)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["value","int","lv_opa_t"],
    ["selector","int","lv_style_selector_t"]
  ]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_create",
  "generate_full" : "js_lv_obj_create(jsvar, lv_obj_create)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"]
  ],
  "return" : ["JsVar","lv_obj_t"]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_label_create",
  "generate_full" : "js_lv_obj_create(jsvar, lv_label_create)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"]
  ],
  "return" : ["JsVar","lv_obj_t"]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_btn_create",
  "generate_full" : "js_lv_obj_create(jsvar, lv_btn_create)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"]
  ],
  "return" : ["JsVar","lv_obj_t"]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_img_create",
  "generate_full" : "js_lv_obj_create(jsvar, lv_img_create)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"]
  ],
  "return" : ["JsVar","lv_obj_t"]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_center",
  "generate_full" : "js_lv_obj_center(jsvar, lv_obj_center)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"]
  ]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_scr_load",
  "generate_full" : "js_lv_obj_center(jsvar, lv_scr_load)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"]
  ]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_tileview_create",
  "generate_full" : "js_lv_obj_create(jsvar, lv_tileview_create)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"]
  ],
  "return" : ["JsVar","lv_obj_t"]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_color_hex",
  "generate_full" : "js_lv_color_hex(jsvar, lv_color_hex)",
  "params" : [
    ["jsvar","JsVar","hex color"]
  ],
  "return" : ["JsVar","lv_color_t"]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_set_style_bg_color",
  "generate_full" : "js_lv_obj_set_style_bg_color(jsvar, jsvar_color, selector, lv_obj_set_style_bg_color)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["jsvar_color","JsVar","lv_color_t"],
    ["selector","int","lv_style_selector_t"]
  ]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_set_style_text_align",
  "generate_full" : "js_lv_obj_set_style_text_align(jsvar, align, selector, lv_obj_set_style_text_align)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["align","int","lv_text_align_t"],
    ["selector","int","lv_style_selector_t"]
  ]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_set_style_text_font",
  "generate_full" : "js_lv_obj_set_style_text_font(jsvar, jsvar_font, selector, lv_obj_set_style_text_font)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["jsvar_font","JsVar","lv_font_t"],
    ["selector","int","lv_style_selector_t"]
  ]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_set_style_img_recolor",
  "generate_full" : "js_lv_obj_set_style_bg_color(jsvar, jsvar_color, selector, lv_obj_set_style_img_recolor)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["jsvar_color","JsVar","lv_color_t"],
    ["selector","int","lv_style_selector_t"]
  ]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_add_flag",
  "generate_full" : "js_lv_obj_add_flag(jsvar, flag, lv_obj_add_flag)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["flag","int","lv_obj_flag_t"]
  ]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_clear_flag",
  "generate_full" : "js_lv_obj_add_flag(jsvar, flag, lv_obj_add_flag)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["flag","int","lv_obj_flag_t"]
  ]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_add_state",
  "generate_full" : "js_lv_obj_add_state(jsvar, state, lv_obj_add_state)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["state","int","lv_state_t"]
  ]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_clear_state",
  "generate_full" : "js_lv_obj_add_state(jsvar, state, lv_obj_clear_state)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["state","int","lv_state_t"]
  ]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_has_flag",
  "generate_full" : "js_lv_obj_has_flag(jsvar, flag, lv_obj_has_flag)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["flag","int","lv_obj_flag_t"]
  ],
  "return" : ["bool",""]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_has_flag_any",
  "generate_full" : "js_lv_obj_has_flag(jsvar, flag, lv_obj_has_flag_any)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["flag","int","lv_obj_flag_t"]
  ],
  "return" : ["bool",""]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_get_state",
  "generate_full" : "js_lv_obj_get_state(jsvar, lv_obj_get_state)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"]
  ],
  "return" : ["int","lv_state_t"]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_has_state",
  "generate_full" : "js_lv_obj_has_state(jsvar, state, lv_obj_has_state)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"],
    ["state","int","lv_state_t"]
  ],
  "return" : ["bool",""]
}*/

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_arc_create",
  "generate_full" : "js_lv_obj_create(jsvar, lv_arc_create)",
  "params" : [
    ["jsvar","JsVar","lv_obj_t"]
  ],
  "return" : ["JsVar","lv_obj_t"]
}*/


/*******************************************************************************************/
// Generic functions

/*
 * lv_obj_t *lv_obj_create(lv_obj_t *parent)
 */
JsVar *js_lv_obj_create(JsVar *jsvar, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
  lv_obj_t * _res = ((lv_obj_t *(*)(lv_obj_t *))lv_func_ptr)(obj);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}

/*
 * inline static void lv_obj_center(struct _lv_obj_t *obj)
 */
void js_lv_obj_center(JsVar *jsvar, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
  ((void (*)(struct _lv_obj_t *))lv_func_ptr)(obj);
}

/*
 * void lv_label_set_text(lv_obj_t *obj, const char *text)
 */
void js_lv_label_set_text(JsVar *jsvar, const char* txt, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
  ((void (*)(lv_obj_t *, const char *))lv_func_ptr)(obj, txt);
  //jsiConsolePrintf("\n set_text : %s \n", txt);
}

/*
 * inline static lv_color_t lv_color_hex(uint32_t c)
 */
JsVar *js_lv_color_hex(JsVar *jsvar, void *lv_func_ptr) {
    uint32_t c = (uint32_t)jsvGetLongInteger(jsvar);
    //jsiConsolePrintf("\n color : %x \n", c);    
    lv_color_t _res = ((lv_color_t (*)(uint32_t))lv_func_ptr)(c);
    return jsvNewFromInteger(_res.full);
}

/*
 * void lv_obj_set_style_bg_color(struct _lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
 */
void js_lv_obj_set_style_bg_color(JsVar *jsvar, JsVar *jsvar_color, int selector, void *lv_func_ptr) {
    struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
    lv_color_t value;
    value.full = (uint32_t)jsvGetInteger(jsvar_color);
    ((void (*)(struct _lv_obj_t *, lv_color_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}

/*
 * void lv_obj_set_style_text_align(struct _lv_obj_t *obj, lv_text_align_t value, lv_style_selector_t selector)
 */
void js_lv_obj_set_style_text_align(JsVar *jsvar, int align, int selector, void *lv_func_ptr) {
    struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
    ((void (*)(struct _lv_obj_t *, lv_text_align_t, lv_style_selector_t))lv_func_ptr)(obj, align, selector);
}

/*
 * void lv_style_set_text_font(lv_style_t *style, const lv_font_t *value)
 */
void js_lv_style_set_text_font(JsVar *jsvar, JsVar *jsvar_font, void *lv_func_ptr) {
    lv_style_t *style = jsvGetNativeFunctionPtr(jsvar);
    const lv_font_t *value = (const lv_font_t *)jsvGetNativeFunctionPtr(jsvar_font);
    ((void (*)(lv_style_t *, const lv_font_t *))lv_func_ptr)(style, value);    
}

/*
 * void lv_obj_set_style_text_font(struct _lv_obj_t *obj, const lv_font_t *value, lv_style_selector_t selector)
 */
void js_lv_obj_set_style_text_font(JsVar *jsvar, JsVar *jsvar_font, int selector, void *lv_func_ptr) {
    struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
    const lv_font_t *value = (const lv_font_t *)jsvGetNativeFunctionPtr(jsvar_font);
    ((void (*)(struct _lv_obj_t *, const lv_font_t *, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}

/* 
 * void lv_img_set_src(lv_obj_t *obj, const void *src)
 */
void js_lv_img_set_src(JsVar *jsvar, const void* src, void *lv_func_ptr) {
    struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
    //jsiConsolePrintf("\n img : %s \n", src);
    ((void (*)(lv_obj_t *, const void *))lv_func_ptr)(obj, src);    
}

/*
 * void lv_obj_set_style_bg_opa(struct _lv_obj_t *obj, lv_opa_t value, lv_style_selector_t selector)
 */
void js_lv_obj_set_style_bg_opa(JsVar *jsvar, int value, int selector, void *lv_func_ptr) {
    struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
    ((void (*)(struct _lv_obj_t *, lv_opa_t, lv_style_selector_t))lv_func_ptr)(obj, (uint8_t)value, selector);    
}

/*
 * void lv_obj_add_flag(lv_obj_t *obj, lv_obj_flag_t f)
 */
void js_lv_obj_add_flag(JsVar *jsvar, int flag, void *lv_func_ptr) {
    struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
    ((void (*)(lv_obj_t *, lv_obj_flag_t))lv_func_ptr)(obj, flag);
}


/*
 * void lv_obj_add_state(lv_obj_t *obj, lv_state_t state)
 */
void js_lv_obj_add_state(JsVar *jsvar, int state, void *lv_func_ptr) {
    struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
    ((void (*)(lv_obj_t *, lv_state_t))lv_func_ptr)(obj, state);
}

/*
 * bool lv_obj_has_flag(const lv_obj_t *obj, lv_obj_flag_t f)
 */
bool js_lv_obj_has_flag(JsVar *jsvar, int flag, void *lv_func_ptr) {
    struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
    bool _res = ((bool (*)(const lv_obj_t *, lv_obj_flag_t))lv_func_ptr)(obj, flag);
    return _res;
}

/*
 * lv_state_t lv_obj_get_state(const lv_obj_t *obj)
 */
int js_lv_obj_get_state(JsVar *jsvar, void *lv_func_ptr) {
    struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
    lv_state_t _res = ((lv_state_t (*)(const lv_obj_t *))lv_func_ptr)(obj);
    return _res;
}


/* 
 * bool lv_obj_has_state(const lv_obj_t *obj, lv_state_t state)
 */
bool js_lv_obj_has_state(JsVar *jsvar, int state, void *lv_func_ptr) {
    struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
    bool _res = ((bool (*)(const lv_obj_t *, lv_state_t))lv_func_ptr)(obj, state);
    return _res;
}



/*********************************************************************************/



/*JSON{
  "type" : "init",
  "generate" : "jswrap_lvgl_init",
  "sortorder" : -100
}*/

void jswrap_lvgl_init() {
  //jsiConsolePrintf("\n lvgl init \n");
}

/*JSON{
  "type" : "idle",
  "generate" : "jswrap_lvgl_idle"
}*/

bool jswrap_lvgl_idle() {
  //lv_timer_handler();
  return false;
}


/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_scr_act",
  "generate" : "jswrap_lv_scr_act",
  "return" : ["JsVar","lv_obj_t"]
}*/
JsVar *jswrap_lv_scr_act() {
  struct _lv_obj_t * _res = (struct _lv_obj_t *)lv_scr_act();
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_clean",
  "generate" : "jswrap_lv_obj_clean",
  "params" : [
    ["type","JsVar","lv_obj_t"]
  ]
}*/
void jswrap_lv_obj_clean(JsVar *jsvar) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
  lv_obj_clean(obj);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_del",
  "generate" : "jswrap_lv_obj_del",
  "params" : [
    ["type","JsVar","lv_obj_t"]
  ]
}*/
void jswrap_lv_obj_del(JsVar *jsvar) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
  lv_obj_del(obj);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_label_set_text",
  "generate" : "jswrap_lv_label_set_text",
  "params" : [
    ["name","JsVar","lv_obj_t"],
    ["name","JsVar","Text"]
  ],
  "typescript" : "lv_label_set_text(obj: lv_obj_t, txt: string): void;"
}*/
void jswrap_lv_label_set_text(JsVar *jsvar, JsVar *txt) {
  JSV_GET_AS_CHAR_ARRAY(messagePtr, messageLen, txt);
  if (!messagePtr) return;
  js_lv_label_set_text(jsvar, messagePtr, lv_label_set_text);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_tileview_add_tile",
  "generate" : "jswrap_lv_tileview_add_tile",
  "params" : [
    ["type","JsVar","lv_obj_t"],
    ["type","int","col_id"],
    ["type","int","row_id"],
    ["type","int","lv_dir_t"]
  ],
  "return" : ["JsVar","lv_obj_t"]
}*/
JsVar *jswrap_lv_tileview_add_tile(JsVar *jsvar, int col_id, int row_id, int dir) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
  struct _lv_obj_t *_res = (struct _lv_obj_t *)lv_tileview_add_tile(obj, col_id, row_id, (lv_dir_t)dir);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_align",
  "generate" : "jswrap_lv_obj_align",
  "params" : [
    ["type","JsVar","lv_obj_t"],
    ["type","int","lv_align_t"],
    ["type","int","lv_coord_t"],
    ["type","int","lv_coord_t"]
  ]
}*/
void jswrap_lv_obj_align(JsVar *jsvar, int align, int x_ofs, int y_ofs) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);
  lv_obj_align(obj, align, x_ofs, y_ofs);
}


/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_obj_add_event_cb",
  "generate" : "jswrap_lv_obj_add_event_cb",
  "params" : [
    ["type","JsVar","lv_obj_t"],
    ["type","JsVar","event_cb"],
    ["type","int","lv_coord_t"],
    ["type","int","lv_coord_t"]
  ]
}*/
static void js_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);

    lv_obj_t* target = lv_event_get_target(e);
    JsVar *js_event_cb_h = target->user_data;

    //jsiConsolePrintf("\n Clicked \n");
    JsVar *js_user_data = lv_event_get_user_data(e);
    //jsiConsolePrintf("\n 2 - func %x, %x \n", js_event_cb_h, jsvIsFunction(js_event_cb_h));

    if (!jsvIsUndefined(js_event_cb_h) && !jsvIsFunction(js_event_cb_h)) {
      jsError("Callback Function error, got %t", js_event_cb_h);
      return;
    }
    JsVar *args[2];
    args[0] = jsvNewFromInteger(code);
    args[1] = NULL;

    jspeFunctionCall(js_event_cb_h, jsvNewFromString("js_event_handler"), 0, false, 2, args);
}

void jswrap_lv_obj_add_event_cb(JsVar *jsvar, JsVar *event_cb, int filter, JsVar *user_data) {

  if (!jsvIsUndefined(event_cb) && !jsvIsFunction(event_cb)) {
    jsError("Expecting Callback Function, got %t", event_cb);
    return;
  }
 
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);  
  obj->user_data = (void *)(uintptr_t)event_cb;

  lv_obj_add_event_cb(obj, js_event_handler, filter, (void *)(uintptr_t)user_data);
}


/*JSON{
  "type" : "staticmethod", "class" : "LVGL",
  "name" : "lv_img_set_src",
  "generate" : "jswrap_lv_img_set_src",
  "params" : [
    ["type","JsVar","lv_obj_t"],
    ["type","JsVar","src"]
  ]
}*/
void jswrap_lv_img_set_src(JsVar *jsvar, JsVar *src) {
  char buf[30];
  jsvGetString(src, buf, sizeof(buf));
  js_lv_img_set_src(jsvar, buf, lv_img_set_src);
}


