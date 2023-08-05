

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

/*JSON{
  "type" : "init",
  "generate" : "jswrap_lvgl_init",
  "sortorder" : -100
}*/

void jswrap_lvgl_init() {
}

/*JSON{
  "type" : "idle",
  "generate" : "jswrap_lvgl_idle"
}*/

bool jswrap_lvgl_idle() {
  return false;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
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

// lv_anim_enable_t
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ANIM_OFF", "generate_full" : "LV_ANIM_OFF", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_ANIM_ON", "generate_full" : "LV_ANIM_ON", "ifdef" : "LVGL", "return" : ["int",""]
}*/


// lv_text_decor_t
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_TEXT_DECOR_NONE", "generate_full" : "LV_TEXT_DECOR_NONE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_TEXT_DECOR_UNDERLINE", "generate_full" : "LV_TEXT_DECOR_UNDERLINE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_TEXT_DECOR_STRIKETHROUGH", "generate_full" : "LV_TEXT_DECOR_STRIKETHROUGH", "ifdef" : "LVGL", "return" : ["int",""]
}*/

//lv_border_side_t
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_BORDER_SIDE_NONE", "generate_full" : "LV_BORDER_SIDE_NONE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_BORDER_SIDE_BOTTOM", "generate_full" : "LV_BORDER_SIDE_BOTTOM", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_BORDER_SIDE_TOP", "generate_full" : "LV_BORDER_SIDE_TOP", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_BORDER_SIDE_LEFT", "generate_full" : "LV_BORDER_SIDE_LEFT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_BORDER_SIDE_RIGHT", "generate_full" : "LV_BORDER_SIDE_RIGHT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_BORDER_SIDE_FULL", "generate_full" : "LV_BORDER_SIDE_FULL", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_BORDER_SIDE_INTERNAL", "generate_full" : "LV_BORDER_SIDE_INTERNAL", "ifdef" : "LVGL", "return" : ["int",""]
}*/

//lv_scr_load_anim_t
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_NONE", "generate_full" : "LV_SCR_LOAD_ANIM_NONE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_OVER_LEFT", "generate_full" : "LV_SCR_LOAD_ANIM_OVER_LEFT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_OVER_RIGHT", "generate_full" : "LV_SCR_LOAD_ANIM_OVER_RIGHT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_OVER_TOP", "generate_full" : "LV_SCR_LOAD_ANIM_OVER_TOP", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_OVER_BOTTOM", "generate_full" : "LV_SCR_LOAD_ANIM_OVER_BOTTOM", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_MOVE_LEFT", "generate_full" : "LV_SCR_LOAD_ANIM_MOVE_LEFT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_MOVE_RIGHT", "generate_full" : "LV_SCR_LOAD_ANIM_MOVE_RIGHT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_MOVE_TOP", "generate_full" : "LV_SCR_LOAD_ANIM_MOVE_TOP", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_MOVE_BOTTOM", "generate_full" : "LV_SCR_LOAD_ANIM_MOVE_BOTTOM", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_FADE_IN", "generate_full" : "LV_SCR_LOAD_ANIM_FADE_IN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_FADE_ON", "generate_full" : "LV_SCR_LOAD_ANIM_FADE_IN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_FADE_OUT", "generate_full" : "LV_SCR_LOAD_ANIM_FADE_OUT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_OUT_LEFT", "generate_full" : "LV_SCR_LOAD_ANIM_OUT_LEFT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_OUT_RIGHT", "generate_full" : "LV_SCR_LOAD_ANIM_OUT_RIGHT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_OUT_TOP", "generate_full" : "LV_SCR_LOAD_ANIM_OUT_TOP", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "LVGL", "name" : "LV_SCR_LOAD_ANIM_OUT_BOTTOM", "generate_full" : "LV_SCR_LOAD_ANIM_OUT_BOTTOM", "ifdef" : "LVGL", "return" : ["int",""]
}*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
// FONT

/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_font_BigNumbers",
  "generate" : "jswrap_lv_font_BigNumbers",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_BigNumbers() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_BigNumbers;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_font_Icons32",
  "generate" : "jswrap_lv_font_Icons32",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_Icons32() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_Icons32;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_font_Numbers42",
  "generate" : "jswrap_lv_font_Numbers42",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_Numbers42() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_Numbers42;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_font_Numbers64",
  "generate" : "jswrap_lv_font_Numbers64",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_Numbers64() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_Numbers64;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_font_OpenSans22",
  "generate" : "jswrap_lv_font_OpenSans22",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_OpenSans22() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_OpenSans22;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_font_OpenSans22Bold",
  "generate" : "jswrap_lv_font_OpenSans22Bold",
  "return" : ["JsVar","lv_font_t"]
}*/
JsVar *jswrap_lv_font_OpenSans22Bold() {
  struct lv_font_t * _font = (struct lv_font_t *)&ui_font_OpenSans22Bold;
  return jsvNewNativeFunction((void*)_font, JSWAT_VOID);
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "timer_handler",
  "generate_full" : "lv_timer_handler()"
}*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
// Call back function

/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
// Generic functions

/*
 * inline static void lv_obj_center(struct _lv_obj_t *obj) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_center )
 */
void jswrap_lv_obj_center(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *))lv_func_ptr)(obj);
}


/*
 * inline static lv_coord_t lv_obj_dpx(const lv_obj_t *obj, lv_coord_t n) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_dpx )
 */
int jswrap_lv_obj_dpx(JsVar *jsobj, lv_coord_t n, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  lv_coord_t _res = ((lv_coord_t (*)(const lv_obj_t *, lv_coord_t))lv_func_ptr)(obj, n);
  return _res;
}


/*
 * inline static void lv_obj_move_foreground(lv_obj_t *obj) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_move_foreground )
 */
void jswrap_lv_obj_move_foreground(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *))lv_func_ptr)(obj);
}


/*
 * void lv_obj_set_pos(struct _lv_obj_t *obj, lv_coord_t x, lv_coord_t y) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_pos )
 */
void jswrap_lv_obj_set_pos(JsVar *jsobj, lv_coord_t x, lv_coord_t y, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_coord_t, lv_coord_t))lv_func_ptr)(obj, x, y);
}


/*
 * void lv_obj_set_x(struct _lv_obj_t *obj, lv_coord_t x) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_x )
 */
void jswrap_lv_obj_set_x(JsVar *jsobj, lv_coord_t x, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_coord_t))lv_func_ptr)(obj, x);
}


/*
 * void lv_obj_set_layout(struct _lv_obj_t *obj, uint32_t layout) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_layout )
 */
void jswrap_lv_obj_set_layout(JsVar *jsobj, uint32_t layout, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, uint32_t))lv_func_ptr)(obj, layout);
}


/*
 * void lv_obj_update_layout(const struct _lv_obj_t *obj) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_update_layout )
 */
void jswrap_lv_obj_update_layout(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(const struct _lv_obj_t *))lv_func_ptr)(obj);
}


/*
 * void lv_obj_set_align(struct _lv_obj_t *obj, lv_align_t align) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_align )
 */
void jswrap_lv_obj_set_align(JsVar *jsobj, lv_align_t align, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_align_t))lv_func_ptr)(obj, align);
}


/*
 * void lv_obj_align(struct _lv_obj_t *obj, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_align )
 */
void jswrap_lv_obj_align(JsVar *jsobj, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_align_t, lv_coord_t, lv_coord_t))lv_func_ptr)(obj, align, x_ofs, y_ofs);
}


/*
 * void lv_obj_align_to(struct _lv_obj_t *obj, const struct _lv_obj_t *base, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_align_to )
 */
void jswrap_lv_obj_align_to(JsVar *jsobj, JsVar *base, JsVar *args, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  struct _lv_obj_t *objbase = jsvGetNativeFunctionPtr(base);

  lv_align_t align = jsvGetInteger(jsvGetArrayItem(args, 0)); 
  lv_coord_t x_ofs = jsvGetInteger(jsvGetArrayItem(args, 1));
  lv_coord_t y_ofs = jsvGetInteger(jsvGetArrayItem(args, 2));

  ((void (*)(struct _lv_obj_t *, const struct _lv_obj_t *, lv_align_t, lv_coord_t, lv_coord_t))lv_func_ptr)(obj, objbase, align, x_ofs, y_ofs);
}

/*
 * lv_coord_t lv_obj_get_x(const struct _lv_obj_t *obj) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_get_x )
 */
int jswrap_lv_obj_get_x(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  lv_coord_t _res = ((lv_coord_t (*)(const struct _lv_obj_t *))lv_func_ptr)(obj);
  return _res;
}


/*
 * struct _lv_obj_t *lv_obj_get_screen(const struct _lv_obj_t *obj) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_get_screen )
 */
JsVar *jswrap_lv_obj_get_screen(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  struct _lv_obj_t * _res = ((struct _lv_obj_t *(*)(const struct _lv_obj_t *))lv_func_ptr)(obj);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/*
 * struct _lv_obj_t *lv_obj_get_child(const struct _lv_obj_t *obj, int32_t id) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_get_child )
 */
JsVar *jswrap_lv_obj_get_child(JsVar *jsobj, int32_t id, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  struct _lv_obj_t * _res = ((struct _lv_obj_t *(*)(const struct _lv_obj_t *, int32_t))lv_func_ptr)(obj, id);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/*
 * void lv_obj_set_scrollbar_mode(struct _lv_obj_t *obj, lv_scrollbar_mode_t mode) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_scrollbar_mode )
 */
void jswrap_lv_obj_set_scrollbar_mode(JsVar *jsobj, lv_scrollbar_mode_t mode, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_scrollbar_mode_t))lv_func_ptr)(obj, mode);
}


/*
 * void lv_obj_set_scroll_dir(struct _lv_obj_t *obj, lv_dir_t dir) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_scroll_dir )
 */
void jswrap_lv_obj_set_scroll_dir(JsVar *jsobj, lv_dir_t dir, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_dir_t))lv_func_ptr)(obj, dir);
}


/*
 * void lv_obj_set_scroll_snap_x(struct _lv_obj_t *obj, lv_scroll_snap_t align) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_scroll_snap_x )
 */
void jswrap_lv_obj_set_scroll_snap_x(JsVar *jsobj, lv_scroll_snap_t align, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_scroll_snap_t))lv_func_ptr)(obj, align);
}


/*
 * void lv_obj_scroll_by(struct _lv_obj_t *obj, lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_scroll_by )
 */
void jswrap_lv_obj_scroll_by(JsVar *jsobj, lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_coord_t, lv_coord_t, lv_anim_enable_t))lv_func_ptr)(obj, x, y, anim_en);
}


/*
 * void lv_obj_scroll_to_x(struct _lv_obj_t *obj, lv_coord_t x, lv_anim_enable_t anim_en) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_scroll_to_x )
 */
void jswrap_lv_obj_scroll_to_x(JsVar *jsobj, lv_coord_t x, lv_anim_enable_t anim_en, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_coord_t, lv_anim_enable_t))lv_func_ptr)(obj, x, anim_en);
}


/*
 * void lv_obj_scroll_to_view(struct _lv_obj_t *obj, lv_anim_enable_t anim_en) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_scroll_to_view )
 */
void jswrap_lv_obj_scroll_to_view(JsVar *jsobj, lv_anim_enable_t anim_en, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_anim_enable_t))lv_func_ptr)(obj, anim_en);
}


/*
 * void lv_obj_add_style(struct _lv_obj_t *obj, lv_style_t *style, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_add_style )
 */
void jswrap_lv_obj_add_style(JsVar *jsobj, JsVar *style, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  struct lv_style_t *objstyle = jsvGetNativeFunctionPtr(style);
  ((void (*)(struct _lv_obj_t *, lv_style_t *, lv_style_selector_t))lv_func_ptr)(obj, objstyle, selector);
}


/*
 * lv_state_t lv_obj_style_get_selector_state(lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_style_get_selector_state )
 */
int jswrap_lv_obj_style_get_selector_state(lv_style_selector_t selector, void *lv_func_ptr) {
  lv_state_t _res = ((lv_state_t (*)(lv_style_selector_t))lv_func_ptr)(selector);
  return _res;
}


/*
 * lv_part_t lv_obj_style_get_selector_part(lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_style_get_selector_part )
 */
int jswrap_lv_obj_style_get_selector_part(lv_style_selector_t selector, void *lv_func_ptr) {
  lv_part_t _res = ((lv_part_t (*)(lv_style_selector_t))lv_func_ptr)(selector);
  return _res;
}


/*
 * void lv_obj_set_style_align(struct _lv_obj_t *obj, lv_align_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_align )
 */
void jswrap_lv_obj_set_style_align(JsVar *jsobj, lv_align_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_align_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_bg_color(struct _lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_color )
 */
void jswrap_lv_obj_set_style_bg_color(JsVar *jsobj, JsVarInt *value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  lv_color_t value_c;
  value_c.full = (uint32_t)jsvGetInteger(value);
  ((void (*)(struct _lv_obj_t *, lv_color_t, lv_style_selector_t))lv_func_ptr)(obj, value_c, selector);
}


/*
 * void lv_obj_set_style_bg_opa(struct _lv_obj_t *obj, lv_opa_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_opa )
 */
void jswrap_lv_obj_set_style_bg_opa(JsVar *jsobj, lv_opa_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_opa_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_bg_grad_dir(struct _lv_obj_t *obj, lv_grad_dir_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_grad_dir )
 */
void jswrap_lv_obj_set_style_bg_grad_dir(JsVar *jsobj, lv_grad_dir_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_grad_dir_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_bg_grad(struct _lv_obj_t *obj, const lv_grad_dsc_t *value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_grad )
 */
void jswrap_lv_obj_set_style_bg_grad(JsVar *jsobj, JsVar *value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  struct _lv_grad_dsc_t *objvalue = jsvGetNativeFunctionPtr(value);
  ((void (*)(struct _lv_obj_t *, const lv_grad_dsc_t *, lv_style_selector_t))lv_func_ptr)(obj, objvalue, selector);
}


/*
 * void lv_obj_set_style_bg_dither_mode(struct _lv_obj_t *obj, lv_dither_mode_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_dither_mode )
 */
void jswrap_lv_obj_set_style_bg_dither_mode(JsVar *jsobj, lv_dither_mode_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_dither_mode_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_bg_img_src(struct _lv_obj_t *obj, const void *value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_img_src )
 */
void jswrap_lv_obj_set_style_bg_img_src(JsVar *jsobj, JsVar *value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, const void *, lv_style_selector_t))lv_func_ptr)(obj, jsvGetNativeFunctionPtr(value), selector);
}


/*
 * void lv_obj_set_style_bg_img_tiled(struct _lv_obj_t *obj, bool value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_img_tiled )
 */
void jswrap_lv_obj_set_style_bg_img_tiled(JsVar *jsobj, bool value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, bool, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_border_side(struct _lv_obj_t *obj, lv_border_side_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_border_side )
 */
void jswrap_lv_obj_set_style_border_side(JsVar *jsobj, lv_border_side_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_border_side_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_text_font(struct _lv_obj_t *obj, const lv_font_t *value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_text_font )
 */
void jswrap_lv_obj_set_style_text_font(JsVar *jsobj, JsVar *value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  const lv_font_t *value_f = (const lv_font_t *)jsvGetNativeFunctionPtr(value);
  ((void (*)(struct _lv_obj_t *, const lv_font_t *, lv_style_selector_t))lv_func_ptr)(obj, value_f, selector);
}


/*
 * void lv_obj_set_style_text_decor(struct _lv_obj_t *obj, lv_text_decor_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_text_decor )
 */
void jswrap_lv_obj_set_style_text_decor(JsVar *jsobj, lv_text_decor_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_text_decor_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_text_align(struct _lv_obj_t *obj, lv_text_align_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_text_align )
 */
void jswrap_lv_obj_set_style_text_align(JsVar *jsobj, lv_text_align_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_text_align_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_anim(struct _lv_obj_t *obj, const lv_anim_t *value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_anim )
 */
void jswrap_lv_obj_set_style_anim(JsVar *jsobj, JsVar *value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  const lv_anim_t *objvalue = (const lv_anim_t *)jsvGetNativeFunctionPtr(value);
  ((void (*)(struct _lv_obj_t *, const lv_anim_t *, lv_style_selector_t))lv_func_ptr)(obj, objvalue, selector);
}


/*
 * void lv_obj_set_style_anim_time(struct _lv_obj_t *obj, uint32_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_anim_time )
 */
void jswrap_lv_obj_set_style_anim_time(JsVar *jsobj, uint32_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, uint32_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_transition(struct _lv_obj_t *obj, const lv_style_transition_dsc_t *value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_transition )
 */
void jswrap_lv_obj_set_style_transition(JsVar *jsobj, JsVar *value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  const lv_style_transition_dsc_t *objvalue = (const lv_style_transition_dsc_t *)jsvGetNativeFunctionPtr(value);
  ((void (*)(struct _lv_obj_t *, const lv_style_transition_dsc_t *, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_blend_mode(struct _lv_obj_t *obj, lv_blend_mode_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_blend_mode )
 */
void jswrap_lv_obj_set_style_blend_mode(JsVar *jsobj, lv_blend_mode_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_blend_mode_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_layout(struct _lv_obj_t *obj, uint16_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_layout )
 */
void jswrap_lv_obj_set_style_layout(JsVar *jsobj, uint16_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, uint16_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_base_dir(struct _lv_obj_t *obj, lv_base_dir_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_base_dir )
 */
void jswrap_lv_obj_set_style_base_dir(JsVar *jsobj, lv_base_dir_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(struct _lv_obj_t *, lv_base_dir_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_add_flag(lv_obj_t *obj, lv_obj_flag_t f) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_add_flag )
 */
void jswrap_lv_obj_add_flag(JsVar *jsobj, lv_obj_flag_t f, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_obj_flag_t))lv_func_ptr)(obj, f);
}


/*
 * void lv_obj_add_state(lv_obj_t *obj, lv_state_t state) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_add_state )
 */
void jswrap_lv_obj_add_state(JsVar *jsobj, lv_state_t state, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_state_t))lv_func_ptr)(obj, state);
}


/*
 * bool lv_obj_has_flag(const lv_obj_t *obj, lv_obj_flag_t f) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_has_flag )
 */
bool jswrap_lv_obj_has_flag(JsVar *jsobj, lv_obj_flag_t f, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  bool _res = ((bool (*)(const lv_obj_t *, lv_obj_flag_t))lv_func_ptr)(obj, f);
  return _res;
}


/*
 * lv_state_t lv_obj_get_state(const lv_obj_t *obj) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_get_state )
 */
int jswrap_lv_obj_get_state(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  lv_state_t _res = ((lv_state_t (*)(const lv_obj_t *))lv_func_ptr)(obj);
  return _res;
}


/*
 * bool lv_obj_has_state(const lv_obj_t *obj, lv_state_t state) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_has_state )
 */
bool jswrap_lv_obj_has_state(JsVar *jsobj, lv_state_t state, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  bool _res = ((bool (*)(const lv_obj_t *, lv_state_t))lv_func_ptr)(obj, state);
  return _res;
}


/*
 * void lv_obj_set_flex_flow(lv_obj_t *obj, lv_flex_flow_t flow) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_flex_flow )
 */
void jswrap_lv_obj_set_flex_flow(JsVar *jsobj, lv_flex_flow_t flow, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_flex_flow_t))lv_func_ptr)(obj, flow);
}


/*
 * void lv_obj_set_flex_align(lv_obj_t *obj, lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_cross_place) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_flex_align )
 */
void jswrap_lv_obj_set_flex_align(JsVar *jsobj, lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_cross_place, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_flex_align_t, lv_flex_align_t, lv_flex_align_t))lv_func_ptr)(obj, main_place, cross_place, track_cross_place);
}


/*
 * void lv_obj_set_flex_grow(lv_obj_t *obj, uint8_t grow) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_flex_grow )
 */
void jswrap_lv_obj_set_flex_grow(JsVar *jsobj, uint8_t grow, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, uint8_t))lv_func_ptr)(obj, grow);
}


/*
 * void lv_obj_set_style_flex_flow(lv_obj_t *obj, lv_flex_flow_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_flex_flow )
 */
void jswrap_lv_obj_set_style_flex_flow(JsVar *jsobj, lv_flex_flow_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_flex_flow_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_flex_main_place(lv_obj_t *obj, lv_flex_align_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_flex_main_place )
 */
void jswrap_lv_obj_set_style_flex_main_place(JsVar *jsobj, lv_flex_align_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_flex_align_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_style_flex_grow(lv_obj_t *obj, uint8_t value, lv_style_selector_t selector) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_flex_grow )
 */
void jswrap_lv_obj_set_style_flex_grow(JsVar *jsobj, uint8_t value, lv_style_selector_t selector, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, uint8_t, lv_style_selector_t))lv_func_ptr)(obj, value, selector);
}


/*
 * void lv_obj_set_tile(lv_obj_t *tv, lv_obj_t *tile_obj, lv_anim_enable_t anim_en) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_tile )
 */
void jswrap_lv_obj_set_tile(JsVar *tv, JsVar *tile_obj, lv_anim_enable_t anim_en, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(tv);
  struct _lv_obj_t *tile = jsvGetNativeFunctionPtr(tile_obj);
  ((void (*)(lv_obj_t *, lv_obj_t *, lv_anim_enable_t))lv_func_ptr)(obj, tile, anim_en);
  
}


/*
 * void lv_obj_set_tile_id(lv_obj_t *tv, uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_tile_id )
 */
void jswrap_lv_obj_set_tile_id(JsVar *tv, uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(tv);
  ((void (*)(lv_obj_t *, uint32_t, uint32_t, lv_anim_enable_t))lv_func_ptr)(obj, col_id, row_id, anim_en);
}


/*
 * lv_obj_t *lv_obj_create(lv_obj_t *parent) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_obj_create )
 */
JsVar *jswrap_lv_obj_create(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  lv_obj_t * _res = ((lv_obj_t *(*)(lv_obj_t *))lv_func_ptr)(obj);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/*
 * void lv_arc_set_start_angle(lv_obj_t *obj, uint16_t start) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_start_angle )
 */
void jswrap_lv_arc_set_start_angle(JsVar *jsobj, uint16_t start, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, uint16_t))lv_func_ptr)(obj, start);
}


/*
 * void lv_arc_set_angles(lv_obj_t *obj, uint16_t start, uint16_t end) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_angles )
 */
void jswrap_lv_arc_set_angles(JsVar *jsobj, uint16_t start, uint16_t end, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, uint16_t, uint16_t))lv_func_ptr)(obj, start, end);
}


/*
 * void lv_arc_set_mode(lv_obj_t *obj, lv_arc_mode_t type) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_mode )
 */
void jswrap_lv_arc_set_mode(JsVar *jsobj, lv_arc_mode_t type, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_arc_mode_t))lv_func_ptr)(obj, type);
}


/*
 * void lv_arc_set_value(lv_obj_t *obj, int16_t value) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_value )
 */
void jswrap_lv_arc_set_value(JsVar *jsobj, int16_t value, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, int16_t))lv_func_ptr)(obj, value);
}


/*
 * void lv_arc_set_range(lv_obj_t *obj, int16_t min, int16_t max) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_range )
 */
void jswrap_lv_arc_set_range(JsVar *jsobj, int16_t min, int16_t max, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, int16_t, int16_t))lv_func_ptr)(obj, min, max);
}

/*
 * int16_t lv_arc_get_value(const lv_obj_t *obj) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_arc_get_value )
 */
int jswrap_lv_arc_get_value(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  int16_t _res = ((int16_t (*)(const lv_obj_t *))lv_func_ptr)(obj);
  return _res;
}


/*
 * void lv_arc_align_obj_to_angle(const lv_obj_t *obj, lv_obj_t *obj_to_align, lv_coord_t r_offset) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_arc_align_obj_to_angle )
 */
void jswrap_lv_arc_align_obj_to_angle(JsVar *jsobj, JsVar *obj_to_align, lv_coord_t r_offset, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  struct _lv_obj_t *objta = jsvGetNativeFunctionPtr(obj_to_align);
  ((void (*)(const lv_obj_t *, lv_obj_t *, lv_coord_t))lv_func_ptr)(obj, objta, r_offset);
  
}


/*
 * void lv_img_cache_invalidate_src(const void *src) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_img_cache_invalidate_src )
 */
void jswrap_lv_img_cache_invalidate_src(JsVar *src, void *lv_func_ptr) {
  ((void (*)(const void *))lv_func_ptr)(jsvGetNativeFunctionPtr(src));
}


/*
 * void lv_img_set_src(lv_obj_t *obj, const void *src) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_img_set_src )
 */
void jswrap_lv_img_set_src(JsVar *jsobj, JsVar *src, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  char buf[30]; // fix size ??
  jsvGetString(src, buf, sizeof(buf));
  ((void (*)(lv_obj_t *, const void *))lv_func_ptr)(obj, buf);
}


/*
 * void lv_img_set_offset_x(lv_obj_t *obj, lv_coord_t x) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_img_set_offset_x )
 */
void jswrap_lv_img_set_offset_x(JsVar *jsobj, lv_coord_t x, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_coord_t))lv_func_ptr)(obj, x);
}


/*
 * void lv_img_set_pivot(lv_obj_t *obj, lv_coord_t x, lv_coord_t y) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_img_set_pivot )
 */
void jswrap_lv_img_set_pivot(JsVar *jsobj, lv_coord_t x, lv_coord_t y, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_coord_t, lv_coord_t))lv_func_ptr)(obj, x, y);
}


/*
 * void lv_img_set_antialias(lv_obj_t *obj, bool antialias) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_img_set_antialias )
 */
void jswrap_lv_img_set_antialias(JsVar *jsobj, bool antialias, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, bool))lv_func_ptr)(obj, antialias);
}


/*
 * void lv_img_set_size_mode(lv_obj_t *obj, lv_img_size_mode_t mode) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_img_set_size_mode )
 */
void jswrap_lv_img_set_size_mode(JsVar *jsobj, lv_img_size_mode_t mode, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_img_size_mode_t))lv_func_ptr)(obj, mode);
}


/*
 * lv_coord_t lv_img_get_offset_x(lv_obj_t *obj) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_img_get_offset_x )
 */
int jswrap_lv_img_get_offset_x(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  lv_coord_t _res = ((lv_coord_t (*)(lv_obj_t *))lv_func_ptr)(obj);
  return _res;
}


/*
 * void lv_label_set_text(lv_obj_t *obj, const char *text) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_label_set_text )
 */
void jswrap_lv_label_set_text(JsVar *jsobj, JsVar *text, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  JSV_GET_AS_CHAR_ARRAY(messagePtr, messageLen, text);
  ((void (*)(lv_obj_t *, const char *))lv_func_ptr)(obj, messagePtr);
}


/*
 * void lv_label_set_long_mode(lv_obj_t *obj, lv_label_long_mode_t long_mode) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_label_set_long_mode )
 */
void jswrap_lv_label_set_long_mode(JsVar *jsobj, lv_label_long_mode_t long_mode, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_label_long_mode_t))lv_func_ptr)(obj, long_mode);
}


/*
 * void lv_line_set_points(lv_obj_t *obj, const lv_point_t points[], uint16_t point_num) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_line_set_points )
 */
void jswrap_lv_line_set_points(JsVar *jsobj, JsVar *points, uint16_t point_num, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  // TODO : convert from array....
  ((void (*)(lv_obj_t *, const lv_point_t [], uint16_t))lv_func_ptr)(obj, points, point_num);
}


/*
 * const char *lv_checkbox_get_text(const lv_obj_t *obj) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_checkbox_get_text )
 */
JsVar *jswrap_lv_checkbox_get_text(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  const char * _res = ((const char *(*)(const lv_obj_t *))lv_func_ptr)(obj);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/*
 * void lv_bar_set_value(lv_obj_t *obj, int32_t value, lv_anim_enable_t anim) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_bar_set_value )
 */
void jswrap_lv_bar_set_value(JsVar *jsobj, int32_t value, lv_anim_enable_t anim, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, int32_t, lv_anim_enable_t))lv_func_ptr)(obj, value, anim);
}


/*
 * void lv_bar_set_range(lv_obj_t *obj, int32_t min, int32_t max) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_bar_set_range )
 */
void jswrap_lv_bar_set_range(JsVar *jsobj, int32_t min, int32_t max, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, int32_t, int32_t))lv_func_ptr)(obj, min, max);
}


/*
 * void lv_bar_set_mode(lv_obj_t *obj, lv_bar_mode_t mode) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_bar_set_mode )
 */
void jswrap_lv_bar_set_mode(JsVar *jsobj, lv_bar_mode_t mode, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_bar_mode_t))lv_func_ptr)(obj, mode);
}


/*
 * int32_t lv_bar_get_value(const lv_obj_t *obj) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_bar_get_value )
 */
int jswrap_lv_bar_get_value(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  int32_t _res = ((int32_t (*)(const lv_obj_t *))lv_func_ptr)(obj);
  return _res;
}


/*
 * inline static void lv_slider_set_mode(lv_obj_t *obj, lv_slider_mode_t mode) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_slider_set_mode )
 */
void jswrap_lv_slider_set_mode(JsVar *jsobj, lv_slider_mode_t mode, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_slider_mode_t))lv_func_ptr)(obj, mode);
  
}

/*
 * void lv_roller_set_options(lv_obj_t *obj, const char *options, lv_roller_mode_t mode) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_roller_set_options )
 */
void jswrap_lv_roller_set_options(JsVar *jsobj, JsVar *options, lv_roller_mode_t mode, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  JSV_GET_AS_CHAR_ARRAY(messagePtr, messageLen, options);
  ((void (*)(lv_obj_t *, const char *, lv_roller_mode_t))lv_func_ptr)(obj, messagePtr, mode);
}


/*
 * void lv_roller_set_selected(lv_obj_t *obj, uint16_t sel_opt, lv_anim_enable_t anim) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_roller_set_selected )
 */
void jswrap_lv_roller_set_selected(JsVar *jsobj, uint16_t sel_opt, lv_anim_enable_t anim, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, uint16_t, lv_anim_enable_t))lv_func_ptr)(obj, sel_opt, anim);
}


/*
 * uint16_t lv_roller_get_selected(const lv_obj_t *obj) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_roller_get_selected )
 */
int jswrap_lv_roller_get_selected(JsVar *jsobj, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  uint16_t _res = ((uint16_t (*)(const lv_obj_t *))lv_func_ptr)(obj);
  return _res;
}


/*
 * void lv_animimg_set_src(lv_obj_t *img, const void *dsc[], uint8_t num) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_animimg_set_src )
 */
void jswrap_lv_animimg_set_src(JsVar *jsobj, JsVar *dsc, uint8_t num, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  char buf[30]; // fix size ??
  jsvGetString(dsc, buf, sizeof(buf));
  ((void (*)(lv_obj_t *, const void *[], uint8_t))lv_func_ptr)(obj, buf, num);
}


/*
 * lv_obj_t *lv_spinner_create(lv_obj_t *parent, uint32_t time, uint32_t arc_length) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_spinner_create )
 */
JsVar *jswrap_lv_spinner_create(JsVar *jsobj, uint32_t time, uint32_t arc_length, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  lv_obj_t * _res = ((lv_obj_t *(*)(lv_obj_t *, uint32_t, uint32_t))lv_func_ptr)(obj, time, arc_length);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/*
 * lv_obj_t *lv_tileview_add_tile(lv_obj_t *tv, uint8_t col_id, uint8_t row_id, lv_dir_t dir) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_tileview_add_tile )
 */
JsVar *jswrap_lv_tileview_add_tile(JsVar *tv, uint8_t col_id, uint8_t row_id, lv_dir_t dir, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(tv);
  lv_obj_t * _res = ((lv_obj_t *(*)(lv_obj_t *, uint8_t, uint8_t, lv_dir_t))lv_func_ptr)(obj, col_id, row_id, dir);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/*
 * inline static uint8_t lv_color_to1(lv_color_t color) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_color_to1 )
 */
int jswrap_lv_color_to1(JsVar * color, void *lv_func_ptr) {
  lv_color_t value_c;
  value_c.full = (uint32_t)jsvGetInteger(color);
  uint8_t _res = ((uint8_t (*)(lv_color_t))lv_func_ptr)(value_c);
  return _res;
}


/*
 * inline static uint16_t lv_color_to16(lv_color_t color) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_color_to16 )
 */
int jswrap_lv_color_to16(JsVar * color, void *lv_func_ptr) {
  lv_color_t value_c;
  value_c.full = (uint32_t)jsvGetInteger(color);
  uint16_t _res = ((uint16_t (*)(lv_color_t))lv_func_ptr)(value_c);
  return _res;
}


/*
 * inline static uint32_t lv_color_to32(lv_color_t color) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_color_to32 )
 */
int jswrap_lv_color_to32(JsVar * color, void *lv_func_ptr) {
  lv_color_t value_c;
  value_c.full = (uint32_t)jsvGetInteger(color);
  uint32_t _res = ((uint32_t (*)(lv_color_t))lv_func_ptr)(value_c);
  return _res;
}


/*
 * inline static lv_color_t lv_color_mix(lv_color_t c1, lv_color_t c2, uint8_t mix) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_color_mix )
 */
JsVar *jswrap_lv_color_mix(JsVar * c1, JsVar * c2, uint8_t mix, void *lv_func_ptr) {
  lv_color_t value_c1;
  value_c1.full = (uint32_t)jsvGetInteger(c1);
  lv_color_t value_c2;
  value_c2.full = (uint32_t)jsvGetInteger(c2);
  lv_color_t _res = ((lv_color_t (*)(lv_color_t, lv_color_t, uint8_t))lv_func_ptr)(value_c1, value_c2, mix);
  return jsvNewFromInteger(_res.full);
}


/*
 * lv_color_t lv_color_lighten(lv_color_t c, lv_opa_t lvl) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_color_lighten )
 */
JsVar *jswrap_lv_color_lighten(JsVar * c, lv_opa_t lvl, void *lv_func_ptr) {
  lv_color_t value_c;
  value_c.full = (uint32_t)jsvGetInteger(c);
  lv_color_t _res = ((lv_color_t (*)(lv_color_t, lv_opa_t))lv_func_ptr)(value_c, lvl);
  return jsvNewFromInteger(_res.full);
}


/*
 * inline static lv_coord_t lv_font_get_line_height(const lv_font_t *font_p) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_font_get_line_height )
 */
int jswrap_lv_font_get_line_height(JsVar *font_p, void *lv_func_ptr) {
  const lv_font_t *value_f = (const lv_font_t *)jsvGetNativeFunctionPtr(font_p);
  lv_coord_t _res = ((lv_coord_t (*)(const lv_font_t *))lv_func_ptr)(value_f);
  return _res;
}


/*
 * void lv_font_free(lv_font_t *font) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_font_free )
 */
void jswrap_lv_font_free(lv_font_t *font, void *lv_func_ptr) {
  const lv_font_t *value_f = (const lv_font_t *)jsvGetNativeFunctionPtr(font);
  ((void (*)(lv_font_t *))lv_func_ptr)(value_f);
}


/*
 * inline static void lv_anim_set_var(lv_anim_t *a, void *var) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_set_var )
 */
void jswrap_lv_anim_set_var(JsVar *a, void *var, void *lv_func_ptr) {
  struct _lv_anim_t *aobj = jsvGetNativeFunctionPtr(a);
  ((void (*)(lv_anim_t *, void *))lv_func_ptr)(aobj, jsvGetNativeFunctionPtr(var));
}


/*
 * inline static void lv_anim_set_time(lv_anim_t *a, uint32_t duration) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_set_time )
 */
void jswrap_lv_anim_set_time(JsVar *a, uint32_t duration, void *lv_func_ptr) {
  struct _lv_anim_t *aobj = jsvGetNativeFunctionPtr(a);
  ((void (*)(lv_anim_t *, uint32_t))lv_func_ptr)(aobj, duration);
}


/*
 * inline static void lv_anim_set_values(lv_anim_t *a, int32_t start, int32_t end) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_set_values )
 */
void jswrap_lv_anim_set_values(JsVar *a, int32_t start, int32_t end, void *lv_func_ptr) {
  struct _lv_anim_t *aobj = jsvGetNativeFunctionPtr(a);
  ((void (*)(lv_anim_t *, int32_t, int32_t))lv_func_ptr)(aobj, start, end);
}


/*
 * inline static void lv_anim_set_repeat_count(lv_anim_t *a, uint16_t cnt) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_set_repeat_count )
 */
void jswrap_lv_anim_set_repeat_count(JsVar *a, uint16_t cnt, void *lv_func_ptr) {
  struct _lv_anim_t *aobj = jsvGetNativeFunctionPtr(a);
  ((void (*)(lv_anim_t *, uint16_t))lv_func_ptr)(aobj, cnt);
}


/*
 * inline static void lv_anim_set_early_apply(lv_anim_t *a, bool en) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_set_early_apply )
 */
void jswrap_lv_anim_set_early_apply(JsVar *a, bool en, void *lv_func_ptr) {
  struct _lv_anim_t *aobj = jsvGetNativeFunctionPtr(a);
  ((void (*)(lv_anim_t *, bool))lv_func_ptr)(aobj, en);
}


/*
 * inline static uint32_t lv_anim_get_delay(lv_anim_t *a) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_get_delay )
 */
int jswrap_lv_anim_get_delay(JsVar *a, void *lv_func_ptr) {
  struct _lv_anim_t *aobj = jsvGetNativeFunctionPtr(a);
  uint32_t _res = ((uint32_t (*)(lv_anim_t *))lv_func_ptr)(aobj);
  return _res;
}


/*
 * lv_anim_t *lv_anim_start(const lv_anim_t *a) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_start )
 */
JsVar *jswrap_lv_anim_start(JsVar *a, void *lv_func_ptr) {
  struct _lv_anim_t *aobj = jsvGetNativeFunctionPtr(a);
  lv_anim_t * _res = ((lv_anim_t *(*)(const lv_anim_t *))lv_func_ptr)(aobj);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/*
 * int32_t lv_anim_path_linear(const lv_anim_t *a) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_path_linear )
 */
int jswrap_lv_anim_path_linear(JsVar *a, void *lv_func_ptr) {
  struct _lv_anim_t *aobj = jsvGetNativeFunctionPtr(a);
  int32_t _res = ((int32_t (*)(const lv_anim_t *))lv_func_ptr)(aobj);
  return _res;
}



/*
 * void lv_anim_timeline_del(lv_anim_timeline_t *at) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_del )
 */
void jswrap_lv_anim_timeline_del(JsVar *at, void *lv_func_ptr) {
  struct _lv_anim_timeline_t *atobj = jsvGetNativeFunctionPtr(at);
  ((void (*)(lv_anim_timeline_t *))lv_func_ptr)(atobj);
}


/*
 * void lv_anim_timeline_add(lv_anim_timeline_t *at, uint32_t start_time, lv_anim_t *a) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_add )
 */
void jswrap_lv_anim_timeline_add(JsVar *at, uint32_t start_time, JsVar *a, void *lv_func_ptr) {
  struct _lv_anim_timeline_t *atobj = jsvGetNativeFunctionPtr(at);
  ((void (*)(lv_anim_timeline_t *, uint32_t, lv_anim_t *))lv_func_ptr)(atobj, start_time, a);
}


/*
 * uint32_t lv_anim_timeline_start(lv_anim_timeline_t *at) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_start )
 */
int jswrap_lv_anim_timeline_start(JsVar *at, void *lv_func_ptr) {
  struct _lv_anim_timeline_t *atobj = jsvGetNativeFunctionPtr(at);
  uint32_t _res = ((uint32_t (*)(lv_anim_timeline_t *))lv_func_ptr)(atobj);
  return _res;
}


/*
 * void lv_anim_timeline_set_reverse(lv_anim_timeline_t *at, bool reverse) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_set_reverse )
 */
void jswrap_lv_anim_timeline_set_reverse(JsVar *at, bool reverse, void *lv_func_ptr) {
  struct _lv_anim_timeline_t *atobj = jsvGetNativeFunctionPtr(at);
  ((void (*)(lv_anim_timeline_t *, bool))lv_func_ptr)(atobj, reverse);
}


/*
 * void lv_anim_timeline_set_progress(lv_anim_timeline_t *at, uint16_t progress) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_set_progress )
 */
void jswrap_lv_anim_timeline_set_progress(JsVar *at, uint16_t progress, void *lv_func_ptr) {
  struct _lv_anim_timeline_t *atobj = jsvGetNativeFunctionPtr(at);
  ((void (*)(lv_anim_timeline_t *, uint16_t))lv_func_ptr)(atobj, progress);
}


/*
 * bool lv_anim_timeline_get_reverse(lv_anim_timeline_t *at) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_get_reverse )
 */
bool jswrap_lv_anim_timeline_get_reverse(JsVar *at, void *lv_func_ptr) {
  struct _lv_anim_timeline_t *atobj = jsvGetNativeFunctionPtr(at);
  bool _res = ((bool (*)(lv_anim_timeline_t *))lv_func_ptr)(atobj);
  return _res;
}


/*
 * inline static lv_color_t lv_color_make(uint8_t r, uint8_t g, uint8_t b) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_color_make )
 */
JsVar *jswrap_lv_color_make(uint8_t r, uint8_t g, uint8_t b, void *lv_func_ptr) {
  lv_color_t _res = ((lv_color_t (*)(uint8_t, uint8_t, uint8_t))lv_func_ptr)(r, g, b);
  return jsvNewFromInteger(_res.full);
}


/*
 * inline static lv_color_t lv_color_hex(uint32_t c) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_color_hex )
 */
JsVar *jswrap_lv_color_hex(uint32_t c, void *lv_func_ptr) {
  //jsiConsolePrintf("\n color : %x \n", c);      
  lv_color_t _res = ((lv_color_t (*)(uint32_t))lv_func_ptr)(c);
  return jsvNewFromInteger(_res.full);
}


/*
 * inline static lv_color_t lv_color_chroma_key(void) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_color_chroma_key )
 */
JsVar *jswrap_lv_color_chroma_key(void *lv_func_ptr) {
  lv_color_t _res = ((lv_color_t (*)(void))lv_func_ptr)();
  return jsvNewFromInteger(_res.full);
}


/*
 * inline static bool lv_style_prop_has_flag(lv_style_prop_t prop, uint8_t flag) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_style_prop_has_flag )
 */
bool jswrap_lv_style_prop_has_flag(lv_style_prop_t prop, uint8_t flag, void *lv_func_ptr) {
  bool _res = ((bool (*)(lv_style_prop_t, uint8_t))lv_func_ptr)(prop, flag);
  return _res;
}


/*
 * inline static lv_obj_t *lv_scr_act(void) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_scr_act )
 */
JsVar *jswrap_lv_scr_act(void *lv_func_ptr) {  
  lv_obj_t * _res = ((lv_obj_t *(*)(void))lv_func_ptr)();
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/*
 * bool lv_anim_del(void *var, lv_anim_exec_xcb_t exec_cb) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_del )
 */
bool jswrap_lv_anim_del(void *var, lv_anim_exec_xcb_t exec_cb, void *lv_func_ptr) {
  bool _res = ((bool (*)(void *, lv_anim_exec_xcb_t))lv_func_ptr)(jsvGetNativeFunctionPtr(var), (void *)(uintptr_t)exec_cb);
  return _res;
}


/*
 * lv_anim_t *lv_anim_get(void *var, lv_anim_exec_xcb_t exec_cb) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_get )
 */
JsVar *jswrap_lv_anim_get(void *var, lv_anim_exec_xcb_t exec_cb, void *lv_func_ptr) {
  lv_anim_t * _res = ((lv_anim_t *(*)(void *, lv_anim_exec_xcb_t))lv_func_ptr)(var, (void *)(uintptr_t)exec_cb);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/*
 * struct _lv_timer_t *lv_anim_get_timer(void) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_get_timer )
 */
JsVar *jswrap_lv_anim_get_timer(void *lv_func_ptr) {
  struct _lv_timer_t * _res = ((struct _lv_timer_t *(*)(void))lv_func_ptr)();
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/*
 * uint16_t lv_anim_count_running(void) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_count_running )
 */
int jswrap_lv_anim_count_running(void *lv_func_ptr) {
  uint16_t _res = ((uint16_t (*)(void))lv_func_ptr)();
  return _res;
}


/*
 * uint32_t lv_anim_speed_to_time(uint32_t speed, int32_t start, int32_t end) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_speed_to_time )
 */
int jswrap_lv_anim_speed_to_time(uint32_t speed, int32_t start, int32_t end, void *lv_func_ptr) {
  uint32_t _res = ((uint32_t (*)(uint32_t, int32_t, int32_t))lv_func_ptr)(speed, start, end);
  return _res;
}


/*
 * lv_anim_timeline_t *lv_anim_timeline_create(void) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_create )
 */
JsVar *jswrap_lv_anim_timeline_create(void *lv_func_ptr) {
  lv_anim_timeline_t * _res = ((lv_anim_timeline_t *(*)(void))lv_func_ptr)();
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}

/*
 * void lv_scr_load_anim(lv_obj_t *scr, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_scr_load_anim )
 */
void jswrap_lv_scr_load_anim(JsVar *jsobj, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del, void *lv_func_ptr) {
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsobj);
  ((void (*)(lv_obj_t *, lv_scr_load_anim_t, uint32_t, uint32_t, bool))lv_func_ptr)(obj, anim_type, time, delay, auto_del);
}


/*
 * lv_font_t *lv_font_load(const char *fontName) 
 * ( https://docs.lvgl.io/8.3/search.html?q=lv_font_load )
 */
JsVar *jswrap_lv_font_load(JsVar *fontName, void *lv_func_ptr) {
  char buf[30]; // fix size ??
  jsvGetString(fontName, buf, sizeof(buf));
  lv_font_t * _res = ((lv_font_t *(*)(const char *))lv_func_ptr)(buf);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// -----------------------------------------------
// JS wrap 


// lv_obj_center
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_center",
  "generate_full" : "jswrap_lv_obj_center(jsobj, lv_obj_center)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_center
*/
    
// lv_obj_remove_style_all
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_remove_style_all",
  "generate_full" : "jswrap_lv_obj_center(jsobj, lv_obj_remove_style_all)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_remove_style_all
*/
    
    
// lv_obj_set_pos
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_pos",
  "generate_full" : "jswrap_lv_obj_set_pos(jsobj, x, y, lv_obj_set_pos)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"],
    ["y","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_pos
*/
    
// lv_obj_set_x
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_x",
  "generate_full" : "jswrap_lv_obj_set_x(jsobj, x, lv_obj_set_x)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_x
*/
    
// lv_obj_set_y
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_y",
  "generate_full" : "jswrap_lv_obj_set_x(jsobj, x, lv_obj_set_y)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_y
*/
    
// lv_obj_set_size
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_size",
  "generate_full" : "jswrap_lv_obj_set_pos(jsobj, x, y, lv_obj_set_size)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"],
    ["y","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_size
*/
    
// lv_obj_set_width
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_width",
  "generate_full" : "jswrap_lv_obj_set_x(jsobj, x, lv_obj_set_width)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_width
*/
    
// lv_obj_set_height
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_height",
  "generate_full" : "jswrap_lv_obj_set_x(jsobj, x, lv_obj_set_height)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_height
*/
    
// lv_obj_set_content_width
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_content_width",
  "generate_full" : "jswrap_lv_obj_set_x(jsobj, x, lv_obj_set_content_width)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_content_width
*/
    
// lv_obj_set_content_height
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_content_height",
  "generate_full" : "jswrap_lv_obj_set_x(jsobj, x, lv_obj_set_content_height)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_content_height
*/
    
// lv_obj_set_layout
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_layout",
  "generate_full" : "jswrap_lv_obj_set_layout(jsobj, layout, lv_obj_set_layout)",
  "params" : [
    ["jsobj","JsVar"],
    ["layout","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_layout
*/
    
// lv_obj_mark_layout_as_dirty
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_mark_layout_as_dirty",
  "generate_full" : "jswrap_lv_obj_center(jsobj, lv_obj_mark_layout_as_dirty)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_mark_layout_as_dirty
*/
    
// lv_obj_update_layout
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_update_layout",
  "generate_full" : "jswrap_lv_obj_update_layout(jsobj, lv_obj_update_layout)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_update_layout
*/
    
// lv_obj_set_align
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_align",
  "generate_full" : "jswrap_lv_obj_set_align(jsobj, align, lv_obj_set_align)",
  "params" : [
    ["jsobj","JsVar"],
    ["align","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_align
*/
    
// lv_obj_align
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_align",
  "generate_full" : "jswrap_lv_obj_align(jsobj, align, x_ofs, y_ofs, lv_obj_align)",
  "params" : [
    ["jsobj","JsVar"],
    ["align","int"],
    ["x_ofs","int"],
    ["y_ofs","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_align
*/

    
// lv_obj_refr_pos
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_refr_pos",
  "generate_full" : "jswrap_lv_obj_center(jsobj, lv_obj_refr_pos)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_refr_pos
*/
    
// lv_obj_move_to
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_move_to",
  "generate_full" : "jswrap_lv_obj_set_pos(jsobj, x, y, lv_obj_move_to)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"],
    ["y","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_move_to
*/
    
// lv_obj_invalidate
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_invalidate",
  "generate_full" : "jswrap_lv_obj_update_layout(jsobj, lv_obj_invalidate)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_invalidate
*/
    
// lv_obj_set_ext_click_area
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_ext_click_area",
  "generate_full" : "jswrap_lv_obj_set_x(jsobj, x, lv_obj_set_ext_click_area)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_ext_click_area
*/
    
// lv_obj_del
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_del",
  "generate_full" : "jswrap_lv_obj_center(jsobj, lv_obj_del)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_del
*/
    
// lv_obj_clean
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_clean",
  "generate_full" : "jswrap_lv_obj_center(jsobj, lv_obj_clean)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_clean
*/
    
// lv_obj_del_delayed
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_del_delayed",
  "generate_full" : "jswrap_lv_obj_set_layout(jsobj, layout, lv_obj_del_delayed)",
  "params" : [
    ["jsobj","JsVar"],
    ["layout","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_del_delayed
*/
    
// lv_obj_del_async
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_del_async",
  "generate_full" : "jswrap_lv_obj_center(jsobj, lv_obj_del_async)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_del_async
*/
    
// lv_obj_get_screen
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_get_screen",
  "generate_full" : "jswrap_lv_obj_get_screen(jsobj, lv_obj_get_screen)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","struct _lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_get_screen
*/
    
// lv_obj_set_scrollbar_mode
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_scrollbar_mode",
  "generate_full" : "jswrap_lv_obj_set_scrollbar_mode(jsobj, mode, lv_obj_set_scrollbar_mode)",
  "params" : [
    ["jsobj","JsVar"],
    ["mode","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_scrollbar_mode
*/
    
// lv_obj_set_scroll_dir
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_scroll_dir",
  "generate_full" : "jswrap_lv_obj_set_scroll_dir(jsobj, dir, lv_obj_set_scroll_dir)",
  "params" : [
    ["jsobj","JsVar"],
    ["dir","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_scroll_dir
*/
    
// lv_obj_set_scroll_snap_x
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_scroll_snap_x",
  "generate_full" : "jswrap_lv_obj_set_scroll_snap_x(jsobj, align, lv_obj_set_scroll_snap_x)",
  "params" : [
    ["jsobj","JsVar"],
    ["align","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_scroll_snap_x
*/
    
// lv_obj_set_scroll_snap_y
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_scroll_snap_y",
  "generate_full" : "jswrap_lv_obj_set_scroll_snap_x(jsobj, align, lv_obj_set_scroll_snap_y)",
  "params" : [
    ["jsobj","JsVar"],
    ["align","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_scroll_snap_y
*/
    
    
// lv_obj_scroll_by
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_scroll_by",
  "generate_full" : "jswrap_lv_obj_scroll_by(jsobj, x, y, anim_en, lv_obj_scroll_by)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"],
    ["y","int"],
    ["anim_en","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_scroll_by
*/
    
// lv_obj_scroll_by_bounded
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_scroll_by_bounded",
  "generate_full" : "jswrap_lv_obj_scroll_by(jsobj, x, y, anim_en, lv_obj_scroll_by_bounded)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"],
    ["y","int"],
    ["anim_en","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_scroll_by_bounded
*/
    
// lv_obj_scroll_to
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_scroll_to",
  "generate_full" : "jswrap_lv_obj_scroll_by(jsobj, x, y, anim_en, lv_obj_scroll_to)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"],
    ["y","int"],
    ["anim_en","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_scroll_to
*/
    
// lv_obj_scroll_to_x
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_scroll_to_x",
  "generate_full" : "jswrap_lv_obj_scroll_to_x(jsobj, x, anim_en, lv_obj_scroll_to_x)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"],
    ["anim_en","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_scroll_to_x
*/
    
// lv_obj_scroll_to_y
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_scroll_to_y",
  "generate_full" : "jswrap_lv_obj_scroll_to_x(jsobj, x, anim_en, lv_obj_scroll_to_y)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"],
    ["anim_en","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_scroll_to_y
*/
    
// lv_obj_scroll_to_view
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_scroll_to_view",
  "generate_full" : "jswrap_lv_obj_scroll_to_view(jsobj, anim_en, lv_obj_scroll_to_view)",
  "params" : [
    ["jsobj","JsVar"],
    ["anim_en","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_scroll_to_view
*/
    
// lv_obj_scroll_to_view_recursive
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_scroll_to_view_recursive",
  "generate_full" : "jswrap_lv_obj_scroll_to_view(jsobj, anim_en, lv_obj_scroll_to_view_recursive)",
  "params" : [
    ["jsobj","JsVar"],
    ["anim_en","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_scroll_to_view_recursive
*/
    
// lv_obj_update_snap
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_update_snap",
  "generate_full" : "jswrap_lv_obj_scroll_to_view(jsobj, anim_en, lv_obj_update_snap)",
  "params" : [
    ["jsobj","JsVar"],
    ["anim_en","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_update_snap
*/
    
// lv_obj_scrollbar_invalidate
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_scrollbar_invalidate",
  "generate_full" : "jswrap_lv_obj_center(jsobj, lv_obj_scrollbar_invalidate)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_scrollbar_invalidate
*/
    
// lv_obj_readjust_scroll
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_readjust_scroll",
  "generate_full" : "jswrap_lv_obj_scroll_to_view(jsobj, anim_en, lv_obj_readjust_scroll)",
  "params" : [
    ["jsobj","JsVar"],
    ["anim_en","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_readjust_scroll
*/
    
// lv_obj_add_style
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_add_style",
  "generate_full" : "jswrap_lv_obj_add_style(jsobj, style, selector, lv_obj_add_style)",
  "params" : [
    ["jsobj","JsVar"],
    ["style","JsVar"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_add_style
*/
    
// lv_obj_remove_style
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_remove_style",
  "generate_full" : "jswrap_lv_obj_add_style(jsobj, style, selector, lv_obj_remove_style)",
  "params" : [
    ["jsobj","JsVar"],
    ["style","JsVar"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_remove_style
*/
  
    
// lv_obj_set_style_align
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_align",
  "generate_full" : "jswrap_lv_obj_set_style_align(jsobj, value, selector, lv_obj_set_style_align)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_align
*/
    
// lv_obj_set_style_bg_color
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_bg_color",
  "generate_full" : "jswrap_lv_obj_set_style_bg_color(jsobj, value, selector, lv_obj_set_style_bg_color)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_color
*/
    
// lv_obj_set_style_bg_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_bg_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_bg_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_opa
*/
    
// lv_obj_set_style_bg_grad_color
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_bg_grad_color",
  "generate_full" : "jswrap_lv_obj_set_style_bg_color(jsobj, value, selector, lv_obj_set_style_bg_grad_color)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_grad_color
*/
    
// lv_obj_set_style_bg_grad_dir
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_bg_grad_dir",
  "generate_full" : "jswrap_lv_obj_set_style_bg_grad_dir(jsobj, value, selector, lv_obj_set_style_bg_grad_dir)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_grad_dir
*/
    
// lv_obj_set_style_bg_grad
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_bg_grad",
  "generate_full" : "jswrap_lv_obj_set_style_bg_grad(jsobj, value, selector, lv_obj_set_style_bg_grad)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","JsVar"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_grad
*/
    
// lv_obj_set_style_bg_dither_mode
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_bg_dither_mode",
  "generate_full" : "jswrap_lv_obj_set_style_bg_dither_mode(jsobj, value, selector, lv_obj_set_style_bg_dither_mode)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_dither_mode
*/
    
// lv_obj_set_style_bg_img_src
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_bg_img_src",
  "generate_full" : "jswrap_lv_obj_set_style_bg_img_src(jsobj, value, selector, lv_obj_set_style_bg_img_src)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","JsVar"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_img_src
*/
    
// lv_obj_set_style_bg_img_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_bg_img_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_bg_img_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_img_opa
*/
    
// lv_obj_set_style_bg_img_recolor
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_bg_img_recolor",
  "generate_full" : "jswrap_lv_obj_set_style_bg_color(jsobj, value, selector, lv_obj_set_style_bg_img_recolor)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_img_recolor
*/
    
// lv_obj_set_style_bg_img_recolor_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_bg_img_recolor_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_bg_img_recolor_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_img_recolor_opa
*/
    
// lv_obj_set_style_bg_img_tiled
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_bg_img_tiled",
  "generate_full" : "jswrap_lv_obj_set_style_bg_img_tiled(jsobj, value, selector, lv_obj_set_style_bg_img_tiled)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","bool"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_bg_img_tiled
*/
    
// lv_obj_set_style_border_color
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_border_color",
  "generate_full" : "jswrap_lv_obj_set_style_bg_color(jsobj, value, selector, lv_obj_set_style_border_color)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_border_color
*/
    
// lv_obj_set_style_border_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_border_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_border_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_border_opa
*/
    
// lv_obj_set_style_border_side
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_border_side",
  "generate_full" : "jswrap_lv_obj_set_style_border_side(jsobj, value, selector, lv_obj_set_style_border_side)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_border_side
*/
    
// lv_obj_set_style_border_post
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_border_post",
  "generate_full" : "jswrap_lv_obj_set_style_bg_img_tiled(jsobj, value, selector, lv_obj_set_style_border_post)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","bool"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_border_post
*/
    
// lv_obj_set_style_outline_color
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_outline_color",
  "generate_full" : "jswrap_lv_obj_set_style_bg_color(jsobj, value, selector, lv_obj_set_style_outline_color)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_outline_color
*/
    
// lv_obj_set_style_outline_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_outline_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_outline_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_outline_opa
*/
    
// lv_obj_set_style_shadow_color
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_shadow_color",
  "generate_full" : "jswrap_lv_obj_set_style_bg_color(jsobj, value, selector, lv_obj_set_style_shadow_color)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_shadow_color
*/
    
// lv_obj_set_style_shadow_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_shadow_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_shadow_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_shadow_opa
*/
    
// lv_obj_set_style_img_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_img_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_img_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_img_opa
*/
    
// lv_obj_set_style_img_recolor
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_img_recolor",
  "generate_full" : "jswrap_lv_obj_set_style_bg_color(jsobj, value, selector, lv_obj_set_style_img_recolor)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_img_recolor
*/
    
// lv_obj_set_style_img_recolor_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_img_recolor_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_img_recolor_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_img_recolor_opa
*/
    
// lv_obj_set_style_line_rounded
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_line_rounded",
  "generate_full" : "jswrap_lv_obj_set_style_bg_img_tiled(jsobj, value, selector, lv_obj_set_style_line_rounded)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","bool"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_line_rounded
*/
    
// lv_obj_set_style_line_color
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_line_color",
  "generate_full" : "jswrap_lv_obj_set_style_bg_color(jsobj, value, selector, lv_obj_set_style_line_color)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_line_color
*/
    
// lv_obj_set_style_line_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_line_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_line_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_line_opa
*/
    
// lv_obj_set_style_arc_rounded
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_arc_rounded",
  "generate_full" : "jswrap_lv_obj_set_style_bg_img_tiled(jsobj, value, selector, lv_obj_set_style_arc_rounded)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","bool"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_arc_rounded
*/
    
// lv_obj_set_style_arc_color
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_arc_color",
  "generate_full" : "jswrap_lv_obj_set_style_bg_color(jsobj, value, selector, lv_obj_set_style_arc_color)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_arc_color
*/
    
// lv_obj_set_style_arc_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_arc_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_arc_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_arc_opa
*/
    
// lv_obj_set_style_arc_img_src
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_arc_img_src",
  "generate_full" : "jswrap_lv_obj_set_style_bg_img_src(jsobj, value, selector, lv_obj_set_style_arc_img_src)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","JsVar"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_arc_img_src
*/
    
// lv_obj_set_style_text_color
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_text_color",
  "generate_full" : "jswrap_lv_obj_set_style_bg_color(jsobj, value, selector, lv_obj_set_style_text_color)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_text_color
*/
    
// lv_obj_set_style_text_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_text_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_text_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_text_opa
*/
    
// lv_obj_set_style_text_font
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_text_font",
  "generate_full" : "jswrap_lv_obj_set_style_text_font(jsobj, value, selector, lv_obj_set_style_text_font)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","JsVar"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_text_font
*/
    
// lv_obj_set_style_text_decor
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_text_decor",
  "generate_full" : "jswrap_lv_obj_set_style_text_decor(jsobj, value, selector, lv_obj_set_style_text_decor)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_text_decor
*/
    
// lv_obj_set_style_text_align
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_text_align",
  "generate_full" : "jswrap_lv_obj_set_style_text_align(jsobj, value, selector, lv_obj_set_style_text_align)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_text_align
*/
    
// lv_obj_set_style_clip_corner
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_clip_corner",
  "generate_full" : "jswrap_lv_obj_set_style_bg_img_tiled(jsobj, value, selector, lv_obj_set_style_clip_corner)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","bool"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_clip_corner
*/
    
// lv_obj_set_style_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_opa
*/
    
// lv_obj_set_style_color_filter_opa
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_color_filter_opa",
  "generate_full" : "jswrap_lv_obj_set_style_bg_opa(jsobj, value, selector, lv_obj_set_style_color_filter_opa)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_color_filter_opa
*/
    
// lv_obj_set_style_anim
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_anim",
  "generate_full" : "jswrap_lv_obj_set_style_anim(jsobj, value, selector, lv_obj_set_style_anim)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","JsVar"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_anim
*/
    
// lv_obj_set_style_anim_time
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_anim_time",
  "generate_full" : "jswrap_lv_obj_set_style_anim_time(jsobj, value, selector, lv_obj_set_style_anim_time)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_anim_time
*/
    
// lv_obj_set_style_anim_speed
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_anim_speed",
  "generate_full" : "jswrap_lv_obj_set_style_anim_time(jsobj, value, selector, lv_obj_set_style_anim_speed)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_anim_speed
*/
    
// lv_obj_set_style_transition
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_transition",
  "generate_full" : "jswrap_lv_obj_set_style_transition(jsobj, value, selector, lv_obj_set_style_transition)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","JsVar"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_transition
*/
    
// lv_obj_set_style_blend_mode
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_blend_mode",
  "generate_full" : "jswrap_lv_obj_set_style_blend_mode(jsobj, value, selector, lv_obj_set_style_blend_mode)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_blend_mode
*/
    
// lv_obj_set_style_layout
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_layout",
  "generate_full" : "jswrap_lv_obj_set_style_layout(jsobj, value, selector, lv_obj_set_style_layout)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_layout
*/
    
    
// lv_obj_refresh_ext_draw_size
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_refresh_ext_draw_size",
  "generate_full" : "jswrap_lv_obj_center(jsobj, lv_obj_refresh_ext_draw_size)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_refresh_ext_draw_size
*/
    
// lv_obj_class_init_obj
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_class_init_obj",
  "generate_full" : "jswrap_lv_obj_center(jsobj, lv_obj_class_init_obj)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_class_init_obj
*/
    
// lv_obj_add_flag
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_add_flag",
  "generate_full" : "jswrap_lv_obj_add_flag(jsobj, f, lv_obj_add_flag)",
  "params" : [
    ["jsobj","JsVar"],
    ["f","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_add_flag
*/
    
// lv_obj_clear_flag
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_clear_flag",
  "generate_full" : "jswrap_lv_obj_add_flag(jsobj, f, lv_obj_clear_flag)",
  "params" : [
    ["jsobj","JsVar"],
    ["f","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_clear_flag
*/
    
// lv_obj_add_state
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_add_state",
  "generate_full" : "jswrap_lv_obj_add_state(jsobj, state, lv_obj_add_state)",
  "params" : [
    ["jsobj","JsVar"],
    ["state","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_add_state
*/
    
// lv_obj_clear_state
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_clear_state",
  "generate_full" : "jswrap_lv_obj_add_state(jsobj, state, lv_obj_clear_state)",
  "params" : [
    ["jsobj","JsVar"],
    ["state","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_clear_state
*/
    
// lv_obj_has_flag
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_has_flag",
  "generate_full" : "jswrap_lv_obj_has_flag(jsobj, f, lv_obj_has_flag)",
  "params" : [
    ["jsobj","JsVar"],
    ["f","int"]
  ],
  "return" : ["bool","bool"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_has_flag
*/
    
// lv_obj_has_flag_any
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_has_flag_any",
  "generate_full" : "jswrap_lv_obj_has_flag(jsobj, f, lv_obj_has_flag_any)",
  "params" : [
    ["jsobj","JsVar"],
    ["f","int"]
  ],
  "return" : ["bool","bool"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_has_flag_any
*/
    
// lv_obj_get_state
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_get_state",
  "generate_full" : "jswrap_lv_obj_get_state(jsobj, lv_obj_get_state)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["int","lv_state_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_get_state
*/
    
// lv_obj_has_state
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_has_state",
  "generate_full" : "jswrap_lv_obj_has_state(jsobj, state, lv_obj_has_state)",
  "params" : [
    ["jsobj","JsVar"],
    ["state","int"]
  ],
  "return" : ["bool","bool"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_has_state
*/
    
// lv_obj_allocate_spec_attr
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_allocate_spec_attr",
  "generate_full" : "jswrap_lv_obj_move_foreground(jsobj, lv_obj_allocate_spec_attr)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_allocate_spec_attr
*/
    
// lv_obj_set_flex_flow
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_flex_flow",
  "generate_full" : "jswrap_lv_obj_set_flex_flow(jsobj, flow, lv_obj_set_flex_flow)",
  "params" : [
    ["jsobj","JsVar"],
    ["flow","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_flex_flow
*/
    
// lv_obj_set_flex_align
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_flex_align",
  "generate_full" : "jswrap_lv_obj_set_flex_align(jsobj, main_place, cross_place, track_cross_place, lv_obj_set_flex_align)",
  "params" : [
    ["jsobj","JsVar"],
    ["main_place","int"],
    ["cross_place","int"],
    ["track_cross_place","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_flex_align
*/
    
// lv_obj_set_flex_grow
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_flex_grow",
  "generate_full" : "jswrap_lv_obj_set_flex_grow(jsobj, grow, lv_obj_set_flex_grow)",
  "params" : [
    ["jsobj","JsVar"],
    ["grow","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_flex_grow
*/
    
// lv_obj_set_style_flex_flow
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_flex_flow",
  "generate_full" : "jswrap_lv_obj_set_style_flex_flow(jsobj, value, selector, lv_obj_set_style_flex_flow)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_flex_flow
*/
    
// lv_obj_set_style_flex_main_place
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_flex_main_place",
  "generate_full" : "jswrap_lv_obj_set_style_flex_main_place(jsobj, value, selector, lv_obj_set_style_flex_main_place)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_flex_main_place
*/
    
// lv_obj_set_style_flex_cross_place
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_flex_cross_place",
  "generate_full" : "jswrap_lv_obj_set_style_flex_main_place(jsobj, value, selector, lv_obj_set_style_flex_cross_place)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_flex_cross_place
*/
    
// lv_obj_set_style_flex_track_place
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_flex_track_place",
  "generate_full" : "jswrap_lv_obj_set_style_flex_main_place(jsobj, value, selector, lv_obj_set_style_flex_track_place)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_flex_track_place
*/
    
// lv_obj_set_style_flex_grow
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_style_flex_grow",
  "generate_full" : "jswrap_lv_obj_set_style_flex_grow(jsobj, value, selector, lv_obj_set_style_flex_grow)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["selector","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_flex_grow
*/
    
// lv_obj_set_tile
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_tile",
  "generate_full" : "jswrap_lv_obj_set_tile(tv, tile_jsobj, anim_en, lv_obj_set_tile)",
  "params" : [
    ["tv","JsVar"],
    ["tile_jsobj","JsVar"],
    ["anim_en","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_tile
*/
    
// lv_obj_set_tile_id
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_set_tile_id",
  "generate_full" : "jswrap_lv_obj_set_tile_id(tv, col_id, row_id, anim_en, lv_obj_set_tile_id)",
  "params" : [
    ["tv","JsVar"],
    ["col_id","int"],
    ["row_id","int"],
    ["anim_en","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_tile_id
*/
    
// lv_obj_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_obj_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_create
*/
    
// lv_arc_set_start_angle
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_set_start_angle",
  "generate_full" : "jswrap_lv_arc_set_start_angle(jsobj, start, lv_arc_set_start_angle)",
  "params" : [
    ["jsobj","JsVar"],
    ["start","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_start_angle
*/
    
// lv_arc_set_end_angle
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_set_end_angle",
  "generate_full" : "jswrap_lv_arc_set_start_angle(jsobj, start, lv_arc_set_end_angle)",
  "params" : [
    ["jsobj","JsVar"],
    ["start","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_end_angle
*/
    
// lv_arc_set_angles
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_set_angles",
  "generate_full" : "jswrap_lv_arc_set_angles(jsobj, start, end, lv_arc_set_angles)",
  "params" : [
    ["jsobj","JsVar"],
    ["start","int"],
    ["end","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_angles
*/
    
// lv_arc_set_bg_start_angle
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_set_bg_start_angle",
  "generate_full" : "jswrap_lv_arc_set_start_angle(jsobj, start, lv_arc_set_bg_start_angle)",
  "params" : [
    ["jsobj","JsVar"],
    ["start","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_bg_start_angle
*/
    
// lv_arc_set_bg_end_angle
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_set_bg_end_angle",
  "generate_full" : "jswrap_lv_arc_set_start_angle(jsobj, start, lv_arc_set_bg_end_angle)",
  "params" : [
    ["jsobj","JsVar"],
    ["start","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_bg_end_angle
*/
    
// lv_arc_set_bg_angles
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_set_bg_angles",
  "generate_full" : "jswrap_lv_arc_set_angles(jsobj, start, end, lv_arc_set_bg_angles)",
  "params" : [
    ["jsobj","JsVar"],
    ["start","int"],
    ["end","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_bg_angles
*/
    
// lv_arc_set_rotation
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_set_rotation",
  "generate_full" : "jswrap_lv_arc_set_start_angle(jsobj, start, lv_arc_set_rotation)",
  "params" : [
    ["jsobj","JsVar"],
    ["start","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_rotation
*/
    
// lv_arc_set_mode
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_set_mode",
  "generate_full" : "jswrap_lv_arc_set_mode(jsobj, type, lv_arc_set_mode)",
  "params" : [
    ["jsobj","JsVar"],
    ["type","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_mode
*/
    
// lv_arc_set_value
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_set_value",
  "generate_full" : "jswrap_lv_arc_set_value(jsobj, value, lv_arc_set_value)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_value
*/
    
// lv_arc_set_range
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_set_range",
  "generate_full" : "jswrap_lv_arc_set_range(jsobj, min, max, lv_arc_set_range)",
  "params" : [
    ["jsobj","JsVar"],
    ["min","int"],
    ["max","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_range
*/
    
// lv_arc_set_change_rate
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_set_change_rate",
  "generate_full" : "jswrap_lv_arc_set_start_angle(jsobj, start, lv_arc_set_change_rate)",
  "params" : [
    ["jsobj","JsVar"],
    ["start","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_set_change_rate
*/
    
 
// lv_arc_get_value
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_get_value",
  "generate_full" : "jswrap_lv_arc_get_value(jsobj, lv_arc_get_value)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["int","int16_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_get_value
*/
    
// lv_arc_align_obj_to_angle
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_align_obj_to_angle",
  "generate_full" : "jswrap_lv_arc_align_obj_to_angle(jsobj, jsobj_to_align, r_offset, lv_arc_align_obj_to_angle)",
  "params" : [
    ["jsobj","JsVar"],
    ["jsobj_to_align","JsVar"],
    ["r_offset","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_align_obj_to_angle
*/
    
// lv_arc_rotate_obj_to_angle
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_rotate_obj_to_angle",
  "generate_full" : "jswrap_lv_arc_align_obj_to_angle(jsobj, jsobj_to_align, r_offset, lv_arc_rotate_obj_to_angle)",
  "params" : [
    ["jsobj","JsVar"],
    ["jsobj_to_align","JsVar"],
    ["r_offset","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_rotate_obj_to_angle
*/
    
// lv_arc_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_arc_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_arc_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_arc_create
*/
    
// lv_btn_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_btn_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_btn_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_btn_create
*/
    
// lv_img_cache_invalidate_src
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_img_cache_invalidate_src",
  "generate_full" : "jswrap_lv_img_cache_invalidate_src(src, lv_img_cache_invalidate_src)",
  "params" : [
    ["src","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_img_cache_invalidate_src
*/
    
// lv_img_set_src
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_img_set_src",
  "generate_full" : "jswrap_lv_img_set_src(jsobj, src, lv_img_set_src)",
  "params" : [
    ["jsobj","JsVar"],
    ["src","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_img_set_src
*/
    
// lv_img_set_offset_x
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_img_set_offset_x",
  "generate_full" : "jswrap_lv_img_set_offset_x(jsobj, x, lv_img_set_offset_x)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_img_set_offset_x
*/
    
// lv_img_set_offset_y
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_img_set_offset_y",
  "generate_full" : "jswrap_lv_img_set_offset_x(jsobj, x, lv_img_set_offset_y)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_img_set_offset_y
*/
    
// lv_img_set_angle
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_img_set_angle",
  "generate_full" : "jswrap_lv_arc_set_value(jsobj, value, lv_img_set_angle)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_img_set_angle
*/
    
// lv_img_set_pivot
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_img_set_pivot",
  "generate_full" : "jswrap_lv_img_set_pivot(jsobj, x, y, lv_img_set_pivot)",
  "params" : [
    ["jsobj","JsVar"],
    ["x","int"],
    ["y","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_img_set_pivot
*/
    
// lv_img_set_zoom
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_img_set_zoom",
  "generate_full" : "jswrap_lv_arc_set_start_angle(jsobj, start, lv_img_set_zoom)",
  "params" : [
    ["jsobj","JsVar"],
    ["start","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_img_set_zoom
*/
    
// lv_img_set_antialias
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_img_set_antialias",
  "generate_full" : "jswrap_lv_img_set_antialias(jsobj, antialias, lv_img_set_antialias)",
  "params" : [
    ["jsobj","JsVar"],
    ["antialias","bool"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_img_set_antialias
*/
    
// lv_img_set_size_mode
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_img_set_size_mode",
  "generate_full" : "jswrap_lv_img_set_size_mode(jsobj, mode, lv_img_set_size_mode)",
  "params" : [
    ["jsobj","JsVar"],
    ["mode","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_img_set_size_mode
*/

    
// lv_img_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_img_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_img_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_img_create
*/
    
// lv_label_set_text
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_label_set_text",
  "generate_full" : "jswrap_lv_label_set_text(jsobj, text, lv_label_set_text)",
  "params" : [
    ["jsobj","JsVar"],
    ["text","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_label_set_text
*/

    
// lv_label_set_long_mode
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_label_set_long_mode",
  "generate_full" : "jswrap_lv_label_set_long_mode(jsobj, long_mode, lv_label_set_long_mode)",
  "params" : [
    ["jsobj","JsVar"],
    ["long_mode","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_label_set_long_mode
*/
    
// lv_label_set_recolor
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_label_set_recolor",
  "generate_full" : "jswrap_lv_img_set_antialias(jsobj, antialias, lv_label_set_recolor)",
  "params" : [
    ["jsobj","JsVar"],
    ["antialias","bool"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_label_set_recolor
*/
    
// lv_label_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_label_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_label_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_label_create
*/
    
// lv_line_set_points
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_line_set_points",
  "generate_full" : "jswrap_lv_line_set_points(jsobj, points, point_num, lv_line_set_points)",
  "params" : [
    ["jsobj","JsVar"],
    ["points","JsVar"],
    ["point_num","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_line_set_points
*/
    
// lv_line_set_y_invert
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_line_set_y_invert",
  "generate_full" : "jswrap_lv_img_set_antialias(jsobj, antialias, lv_line_set_y_invert)",
  "params" : [
    ["jsobj","JsVar"],
    ["antialias","bool"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_line_set_y_invert
*/
    
// lv_line_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_line_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_line_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_line_create
*/
    
// lv_checkbox_set_text
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_checkbox_set_text",
  "generate_full" : "jswrap_lv_label_set_text(jsobj, text, lv_checkbox_set_text)",
  "params" : [
    ["jsobj","JsVar"],
    ["text","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_checkbox_set_text
*/
    
// lv_checkbox_set_text_static
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_checkbox_set_text_static",
  "generate_full" : "jswrap_lv_label_set_text(jsobj, text, lv_checkbox_set_text_static)",
  "params" : [
    ["jsobj","JsVar"],
    ["text","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_checkbox_set_text_static
*/
  
    
// lv_checkbox_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_checkbox_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_checkbox_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_checkbox_create
*/
    
// lv_bar_set_value
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_bar_set_value",
  "generate_full" : "jswrap_lv_bar_set_value(jsobj, value, anim, lv_bar_set_value)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["anim","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_bar_set_value
*/
    
// lv_bar_set_start_value
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_bar_set_start_value",
  "generate_full" : "jswrap_lv_bar_set_value(jsobj, value, anim, lv_bar_set_start_value)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["anim","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_bar_set_start_value
*/
    
// lv_bar_set_range
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_bar_set_range",
  "generate_full" : "jswrap_lv_bar_set_range(jsobj, min, max, lv_bar_set_range)",
  "params" : [
    ["jsobj","JsVar"],
    ["min","int"],
    ["max","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_bar_set_range
*/
    
// lv_bar_set_mode
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_bar_set_mode",
  "generate_full" : "jswrap_lv_bar_set_mode(jsobj, mode, lv_bar_set_mode)",
  "params" : [
    ["jsobj","JsVar"],
    ["mode","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_bar_set_mode
*/
    
// lv_bar_get_value
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_bar_get_value",
  "generate_full" : "jswrap_lv_bar_get_value(jsobj, lv_bar_get_value)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["int","int32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_bar_get_value
*/

    
// lv_bar_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_bar_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_bar_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_bar_create
*/
    
// lv_slider_set_value
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_slider_set_value",
  "generate_full" : "jswrap_lv_bar_set_value(jsobj, value, anim, lv_slider_set_value)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["anim","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_slider_set_value
*/
    
// lv_slider_set_left_value
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_slider_set_left_value",
  "generate_full" : "jswrap_lv_bar_set_value(jsobj, value, anim, lv_slider_set_left_value)",
  "params" : [
    ["jsobj","JsVar"],
    ["value","int"],
    ["anim","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_slider_set_left_value
*/
    
// lv_slider_set_range
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_slider_set_range",
  "generate_full" : "jswrap_lv_bar_set_range(jsobj, min, max, lv_slider_set_range)",
  "params" : [
    ["jsobj","JsVar"],
    ["min","int"],
    ["max","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_slider_set_range
*/
    
// lv_slider_set_mode
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_slider_set_mode",
  "generate_full" : "jswrap_lv_slider_set_mode(jsobj, mode, lv_slider_set_mode)",
  "params" : [
    ["jsobj","JsVar"],
    ["mode","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_slider_set_mode
*/
    
// lv_slider_get_value
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_slider_get_value",
  "generate_full" : "jswrap_lv_bar_get_value(jsobj, lv_slider_get_value)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["int","int32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_slider_get_value
*/
    
// lv_slider_get_left_value
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_slider_get_left_value",
  "generate_full" : "jswrap_lv_bar_get_value(jsobj, lv_slider_get_left_value)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["int","int32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_slider_get_left_value
*/
    
    
// lv_slider_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_slider_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_slider_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_slider_create
*/
    
// lv_roller_set_options
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_roller_set_options",
  "generate_full" : "jswrap_lv_roller_set_options(jsobj, options, mode, lv_roller_set_options)",
  "params" : [
    ["jsobj","JsVar"],
    ["options","JsVar"],
    ["mode","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_roller_set_options
*/
    
// lv_roller_set_selected
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_roller_set_selected",
  "generate_full" : "jswrap_lv_roller_set_selected(jsobj, sel_opt, anim, lv_roller_set_selected)",
  "params" : [
    ["jsobj","JsVar"],
    ["sel_opt","int"],
    ["anim","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_roller_set_selected
*/
    
// lv_roller_set_visible_row_count
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_roller_set_visible_row_count",
  "generate_full" : "jswrap_lv_obj_set_flex_grow(jsobj, grow, lv_roller_set_visible_row_count)",
  "params" : [
    ["jsobj","JsVar"],
    ["grow","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_roller_set_visible_row_count
*/
    
// lv_roller_get_selected
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_roller_get_selected",
  "generate_full" : "jswrap_lv_roller_get_selected(jsobj, lv_roller_get_selected)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["int","uint16_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_roller_get_selected
*/
    
// lv_roller_get_options
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_roller_get_options",
  "generate_full" : "jswrap_lv_checkbox_get_text(jsobj, lv_roller_get_options)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","const char *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_roller_get_options
*/
    
// lv_roller_get_option_cnt
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_roller_get_option_cnt",
  "generate_full" : "jswrap_lv_roller_get_selected(jsobj, lv_roller_get_option_cnt)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["int","uint16_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_roller_get_option_cnt
*/
    
// lv_roller_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_roller_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_roller_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_roller_create
*/
    
// lv_switch_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_switch_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_switch_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_switch_create
*/
    
// lv_animimg_set_src
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_animimg_set_src",
  "generate_full" : "jswrap_lv_animimg_set_src(jsobj, dsc, num, lv_animimg_set_src)",
  "params" : [
    ["jsobj","JsVar"],
    ["dsc","JsVar"],
    ["num","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_animimg_set_src
*/
    
// lv_animimg_start
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_animimg_start",
  "generate_full" : "jswrap_lv_obj_move_foreground(jsobj, lv_animimg_start)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_animimg_start
*/
    
// lv_animimg_set_repeat_count
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_animimg_set_repeat_count",
  "generate_full" : "jswrap_lv_arc_set_start_angle(jsobj, start, lv_animimg_set_repeat_count)",
  "params" : [
    ["jsobj","JsVar"],
    ["start","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_animimg_set_repeat_count
*/
    
// lv_animimg_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_animimg_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_animimg_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_animimg_create
*/
    
// lv_spinner_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_spinner_create",
  "generate_full" : "jswrap_lv_spinner_create(jsobj, time, arc_length, lv_spinner_create)",
  "params" : [
    ["jsobj","JsVar"],
    ["time","int"],
    ["arc_length","int"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_spinner_create
*/
    
// lv_tileview_add_tile
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_tileview_add_tile",
  "generate_full" : "jswrap_lv_tileview_add_tile(tv, col_id, row_id, dir, lv_tileview_add_tile)",
  "params" : [
    ["tv","JsVar"],
    ["col_id","int"],
    ["row_id","int"],
    ["dir","int"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_tileview_add_tile
*/
    
// lv_tileview_get_tile_act
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_tileview_get_tile_act",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_tileview_get_tile_act)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_tileview_get_tile_act
*/
    
// lv_tileview_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_tileview_create",
  "generate_full" : "jswrap_lv_obj_create(jsobj, lv_tileview_create)",
  "params" : [
    ["jsobj","JsVar"]
  ],
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_tileview_create
*/
    
// lv_color_to1
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_to1",
  "generate_full" : "jswrap_lv_color_to1(color, lv_color_to1)",
  "params" : [
    ["color","int"]
  ],
  "return" : ["int","uint8_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_to1
*/
    
// lv_color_to8
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_to8",
  "generate_full" : "jswrap_lv_color_to1(color, lv_color_to8)",
  "params" : [
    ["color","int"]
  ],
  "return" : ["int","uint8_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_to8
*/
    
// lv_color_to16
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_to16",
  "generate_full" : "jswrap_lv_color_to16(color, lv_color_to16)",
  "params" : [
    ["color","int"]
  ],
  "return" : ["int","uint16_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_to16
*/
    
// lv_color_to32
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_to32",
  "generate_full" : "jswrap_lv_color_to32(color, lv_color_to32)",
  "params" : [
    ["color","int"]
  ],
  "return" : ["int","uint32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_to32
*/
    
// lv_color_mix
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_mix",
  "generate_full" : "jswrap_lv_color_mix(c1, c2, mix, lv_color_mix)",
  "params" : [
    ["c1","int"],
    ["c2","int"],
    ["mix","int"]
  ],
  "return" : ["int","lv_color_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_mix
*/
    
// lv_color_brightness
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_brightness",
  "generate_full" : "jswrap_lv_color_to1(color, lv_color_brightness)",
  "params" : [
    ["color","int"]
  ],
  "return" : ["int","uint8_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_brightness
*/
    
// lv_color_lighten
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_lighten",
  "generate_full" : "jswrap_lv_color_lighten(c, lvl, lv_color_lighten)",
  "params" : [
    ["c","int"],
    ["lvl","int"]
  ],
  "return" : ["int","lv_color_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_lighten
*/
    
// lv_color_darken
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_darken",
  "generate_full" : "jswrap_lv_color_lighten(c, lvl, lv_color_darken)",
  "params" : [
    ["c","int"],
    ["lvl","int"]
  ],
  "return" : ["int","lv_color_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_darken
*/
    
// lv_color_change_lightness
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_change_lightness",
  "generate_full" : "jswrap_lv_color_lighten(c, lvl, lv_color_change_lightness)",
  "params" : [
    ["c","int"],
    ["lvl","int"]
  ],
  "return" : ["int","lv_color_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_change_lightness
*/
    
// lv_font_free
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_font_free",
  "generate_full" : "jswrap_lv_font_free(font, lv_font_free)",
  "params" : [
    ["font","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_font_free
*/
    
// lv_anim_set_var
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_set_var",
  "generate_full" : "jswrap_lv_anim_set_var(a, var, lv_anim_set_var)",
  "params" : [
    ["a","JsVar"],
    ["var","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_set_var
*/
    
// lv_anim_set_time
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_set_time",
  "generate_full" : "jswrap_lv_anim_set_time(a, duration, lv_anim_set_time)",
  "params" : [
    ["a","JsVar"],
    ["duration","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_set_time
*/
    
// lv_anim_set_delay
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_set_delay",
  "generate_full" : "jswrap_lv_anim_set_time(a, duration, lv_anim_set_delay)",
  "params" : [
    ["a","JsVar"],
    ["duration","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_set_delay
*/
    
// lv_anim_set_values
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_set_values",
  "generate_full" : "jswrap_lv_anim_set_values(a, start, end, lv_anim_set_values)",
  "params" : [
    ["a","JsVar"],
    ["start","int"],
    ["end","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_set_values
*/
    
// lv_anim_set_playback_time
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_set_playback_time",
  "generate_full" : "jswrap_lv_anim_set_time(a, duration, lv_anim_set_playback_time)",
  "params" : [
    ["a","JsVar"],
    ["duration","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_set_playback_time
*/
    
// lv_anim_set_playback_delay
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_set_playback_delay",
  "generate_full" : "jswrap_lv_anim_set_time(a, duration, lv_anim_set_playback_delay)",
  "params" : [
    ["a","JsVar"],
    ["duration","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_set_playback_delay
*/

 
// lv_anim_start
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_start",
  "generate_full" : "jswrap_lv_anim_start(a, lv_anim_start)",
  "params" : [
    ["a","JsVar"]
  ],
  "return" : ["JsVar","lv_anim_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_start
*/
     
// lv_anim_path_linear
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_path_linear",
  "generate_full" : "jswrap_lv_anim_path_linear(a, lv_anim_path_linear)",
  "params" : [
    ["a","JsVar"]
  ],
  "return" : ["int","int32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_path_linear
*/
    
// lv_anim_path_ease_in
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_path_ease_in",
  "generate_full" : "jswrap_lv_anim_path_linear(a, lv_anim_path_ease_in)",
  "params" : [
    ["a","JsVar"]
  ],
  "return" : ["int","int32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_path_ease_in
*/
    
// lv_anim_path_ease_out
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_path_ease_out",
  "generate_full" : "jswrap_lv_anim_path_linear(a, lv_anim_path_ease_out)",
  "params" : [
    ["a","JsVar"]
  ],
  "return" : ["int","int32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_path_ease_out
*/
    
// lv_anim_path_ease_in_out
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_path_ease_in_out",
  "generate_full" : "jswrap_lv_anim_path_linear(a, lv_anim_path_ease_in_out)",
  "params" : [
    ["a","JsVar"]
  ],
  "return" : ["int","int32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_path_ease_in_out
*/
    
// lv_anim_path_overshoot
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_path_overshoot",
  "generate_full" : "jswrap_lv_anim_path_linear(a, lv_anim_path_overshoot)",
  "params" : [
    ["a","JsVar"]
  ],
  "return" : ["int","int32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_path_overshoot
*/
    
// lv_anim_path_bounce
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_path_bounce",
  "generate_full" : "jswrap_lv_anim_path_linear(a, lv_anim_path_bounce)",
  "params" : [
    ["a","JsVar"]
  ],
  "return" : ["int","int32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_path_bounce
*/
    
// lv_anim_path_step
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_path_step",
  "generate_full" : "jswrap_lv_anim_path_linear(a, lv_anim_path_step)",
  "params" : [
    ["a","JsVar"]
  ],
  "return" : ["int","int32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_path_step
*/
    
// lv_anim_timeline_del
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_timeline_del",
  "generate_full" : "jswrap_lv_anim_timeline_del(at, lv_anim_timeline_del)",
  "params" : [
    ["at","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_del
*/
    
// lv_anim_timeline_add
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_timeline_add",
  "generate_full" : "jswrap_lv_anim_timeline_add(at, start_time, a, lv_anim_timeline_add)",
  "params" : [
    ["at","JsVar"],
    ["start_time","int"],
    ["a","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_add
*/
    
// lv_anim_timeline_start
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_timeline_start",
  "generate_full" : "jswrap_lv_anim_timeline_start(at, lv_anim_timeline_start)",
  "params" : [
    ["at","JsVar"]
  ],
  "return" : ["int","uint32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_start
*/
    
// lv_anim_timeline_stop
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_timeline_stop",
  "generate_full" : "jswrap_lv_anim_timeline_del(at, lv_anim_timeline_stop)",
  "params" : [
    ["at","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_stop
*/
    
// lv_anim_timeline_set_reverse
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_timeline_set_reverse",
  "generate_full" : "jswrap_lv_anim_timeline_set_reverse(at, reverse, lv_anim_timeline_set_reverse)",
  "params" : [
    ["at","JsVar"],
    ["reverse","bool"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_set_reverse
*/
    
// lv_anim_timeline_set_progress
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_timeline_set_progress",
  "generate_full" : "jswrap_lv_anim_timeline_set_progress(at, progress, lv_anim_timeline_set_progress)",
  "params" : [
    ["at","JsVar"],
    ["progress","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_set_progress
*/
    
// lv_anim_timeline_get_playtime
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_timeline_get_playtime",
  "generate_full" : "jswrap_lv_anim_timeline_start(at, lv_anim_timeline_get_playtime)",
  "params" : [
    ["at","JsVar"]
  ],
  "return" : ["int","uint32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_get_playtime
*/
    
// lv_anim_timeline_get_reverse
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_timeline_get_reverse",
  "generate_full" : "jswrap_lv_anim_timeline_get_reverse(at, lv_anim_timeline_get_reverse)",
  "params" : [
    ["at","JsVar"]
  ],
  "return" : ["bool","bool"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_get_reverse
*/
    
// lv_color_make
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_make",
  "generate_full" : "jswrap_lv_color_make(r, g, b, lv_color_make)",
  "params" : [
    ["r","int"],
    ["g","int"],
    ["b","int"]
  ],
  "return" : ["int","lv_color_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_make
*/
    
// lv_color_hex
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_hex",
  "generate_full" : "jswrap_lv_color_hex(c, lv_color_hex)",
  "params" : [
    ["c","int"]
  ],
  "return" : ["int","lv_color_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_hex
*/
    
// lv_color_hex3
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_color_hex3",
  "generate_full" : "jswrap_lv_color_hex(c, lv_color_hex3)",
  "params" : [
    ["c","int"]
  ],
  "return" : ["int","lv_color_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_color_hex3
*/

    
// lv_style_prop_has_flag
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_style_prop_has_flag",
  "generate_full" : "jswrap_lv_style_prop_has_flag(prop, flag, lv_style_prop_has_flag)",
  "params" : [
    ["prop","int"],
    ["flag","int"]
  ],
  "return" : ["bool","bool"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_style_prop_has_flag
*/
    
// lv_scr_act
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_scr_act",
  "generate_full" : "jswrap_lv_scr_act(lv_scr_act)",
  "return" : ["JsVar","lv_obj_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_scr_act
*/
  
    
// lv_scr_load
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_scr_load",
  "generate_full" : "jswrap_lv_obj_move_foreground(jsobj, lv_scr_load)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_scr_load
*/
    
// lv_anim_del
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_del",
  "generate_full" : "jswrap_lv_anim_del(var, exec_cb, lv_anim_del)",
  "params" : [
    ["var","JsVar"],
    ["exec_cb","JsVar"]
  ],
  "return" : ["bool","bool"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_del
*/
    
// lv_anim_get
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_get",
  "generate_full" : "jswrap_lv_anim_get(var, exec_cb, lv_anim_get)",
  "params" : [
    ["var","JsVar"],
    ["exec_cb","JsVar"]
  ],
  "return" : ["int","lv_anim_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_get
*/
    
// lv_anim_count_running
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_count_running",
  "generate_full" : "jswrap_lv_anim_count_running(lv_anim_count_running)",
  "params" : [

  ],
  "return" : ["int","uint16_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_count_running
*/
    
// lv_anim_speed_to_time
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_speed_to_time",
  "generate_full" : "jswrap_lv_anim_speed_to_time(speed, start, end, lv_anim_speed_to_time)",
  "params" : [
    ["speed","int"],
    ["start","int"],
    ["end","int"]
  ],
  "return" : ["int","uint32_t"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_speed_to_time
*/
    
// lv_anim_timeline_create
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_anim_timeline_create",
  "generate_full" : "jswrap_lv_anim_timeline_create(lv_anim_timeline_create)",
  "params" : [

  ],
  "return" : ["int","lv_anim_timeline_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_timeline_create
*/ 
    
// lv_disp_load_scr
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_disp_load_scr",
  "generate_full" : "jswrap_lv_obj_move_foreground(jsobj, lv_disp_load_scr)",
  "params" : [
    ["jsobj","JsVar"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_disp_load_scr
*/
    
// lv_scr_load_anim
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_scr_load_anim",
  "generate_full" : "jswrap_lv_scr_load_anim(jsobj, anim_type, time, delay, false, lv_scr_load_anim)",
  "params" : [
    ["jsobj","JsVar"],
    ["anim_type","int"],
    ["time","int"],
    ["delay","int"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_scr_load_anim
*/

// lv_font_load
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_font_load",
  "generate_full" : "jswrap_lv_font_load(fontName, lv_font_load)",
  "params" : [
    ["fontName","JsVar"]
  ],
  "return" : ["int","lv_font_t *"]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_font_load
*/

// lv_obj_align_to
/*JSON{
  "type" : "staticmethod", "class" : "LVGL", "ifdef" : "LVGL",
  "name" : "lv_obj_align_to",
  "generate_full" : "jswrap_lv_obj_align_to(jsobj, base, args, lv_obj_align_to)",
  "params" : [
    ["jsobj","JsVar"],
    ["base","JsVar"],
    ["args","JsVarArray","{align, x_ofs, y_ofs}"]
  ]
}
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_align_to
*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
