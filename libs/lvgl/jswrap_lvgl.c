

#include "jswrap_lvgl.h"
#include "jswrapper.h"
#include "jsutils.h"
#include "jsinteractive.h"

#include "lvgl.h"



/*JSON{
  "type" : "library",
  "class" : "lv",
  "typescript" : "lv"
}
This library provides GUI operations using LVGL.

*/

/*********************************************************************************/

/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_DIR_LEFT",    "generate_full" : "LV_DIR_LEFT",    "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_DIR_RIGHT",   "generate_full" : "LV_DIR_RIGHT",   "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_DIR_TOP",     "generate_full" : "LV_DIR_TOP",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_DIR_BOTTOM",  "generate_full" : "LV_DIR_BOTTOM",  "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_DIR_HOR",     "generate_full" : "LV_DIR_HOR",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_DIR_VER",     "generate_full" : "LV_DIR_VER",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_DIR_ALL",     "generate_full" : "LV_DIR_ALL",     "ifdef" : "LVGL", "return" : ["int",""]
}*/


/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_DEFAULT",     "generate_full" : "LV_ALIGN_DEFAULT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_TOP_LEFT",    "generate_full" : "LV_ALIGN_TOP_LEFT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_TOP_MID",     "generate_full" : "LV_ALIGN_TOP_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_TOP_RIGHT",   "generate_full" : "LV_ALIGN_TOP_RIGHT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_BOTTOM_LEFT", "generate_full" : "LV_ALIGN_BOTTOM_LEFT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_BOTTOM_MID",  "generate_full" : "LV_ALIGN_BOTTOM_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_BOTTOM_RIGHT","generate_full" : "LV_ALIGN_BOTTOM_RIGHT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_LEFT_MID",    "generate_full" : "LV_ALIGN_LEFT_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_RIGHT_MID",   "generate_full" : "LV_ALIGN_RIGHT_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_CENTER",      "generate_full" : "LV_ALIGN_CENTER",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_TOP_LEFT","generate_full" : "LV_ALIGN_OUT_TOP_LEFT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_TOP_MID", "generate_full" : "LV_ALIGN_OUT_TOP_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_TOP_RIGHT", "generate_full" : "LV_ALIGN_OUT_TOP_RIGHT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_BOTTOM_LEFT", "generate_full" : "LV_ALIGN_OUT_BOTTOM_LEFT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_BOTTOM_MID",  "generate_full" : "LV_ALIGN_OUT_BOTTOM_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_BOTTOM_RIGHT","generate_full" : "LV_ALIGN_OUT_BOTTOM_RIGHT",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_LEFT_TOP",    "generate_full" : "LV_ALIGN_OUT_LEFT_TOP",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_LEFT_MID",    "generate_full" : "LV_ALIGN_OUT_LEFT_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_LEFT_BOTTOM", "generate_full" : "LV_ALIGN_OUT_LEFT_BOTTOM",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_RIGHT_TOP",   "generate_full" : "LV_ALIGN_OUT_RIGHT_TOP",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_RIGHT_MID",   "generate_full" : "LV_ALIGN_OUT_RIGHT_MID",     "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_ALIGN_OUT_RIGHT_BOTTOM","generate_full" : "LV_ALIGN_OUT_RIGHT_BOTTOM",     "ifdef" : "LVGL", "return" : ["int",""]
}*/


/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_ALL", "generate_full" : "LV_EVENT_ALL", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_PRESSED", "generate_full" : "LV_EVENT_PRESSED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_PRESSING", "generate_full" : "LV_EVENT_PRESSING", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_PRESS_LOST", "generate_full" : "LV_EVENT_PRESS_LOST", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_SHORT_CLICKED", "generate_full" : "LV_EVENT_SHORT_CLICKED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_LONG_PRESSED", "generate_full" : "LV_EVENT_LONG_PRESSED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_LONG_PRESSED_REPEAT", "generate_full" : "LV_EVENT_LONG_PRESSED_REPEAT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_CLICKED", "generate_full" : "LV_EVENT_CLICKED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_RELEASED", "generate_full" : "LV_EVENT_RELEASED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_SCROLL_BEGIN", "generate_full" : "LV_EVENT_SCROLL_BEGIN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_SCROLL_END", "generate_full" : "LV_EVENT_SCROLL_END", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_SCROLL", "generate_full" : "LV_EVENT_SCROLL", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_GESTURE", "generate_full" : "LV_EVENT_GESTURE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_KEY", "generate_full" : "LV_EVENT_KEY", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_FOCUSED", "generate_full" : "LV_EVENT_FOCUSED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_DEFOCUSED", "generate_full" : "LV_EVENT_DEFOCUSED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_LEAVE", "generate_full" : "LV_EVENT_LEAVE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_HIT_TEST", "generate_full" : "LV_EVENT_HIT_TEST", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_COVER_CHECK", "generate_full" : "LV_EVENT_COVER_CHECK", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_REFR_EXT_DRAW_SIZE", "generate_full" : "LV_EVENT_REFR_EXT_DRAW_SIZE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_DRAW_MAIN_BEGIN", "generate_full" : "LV_EVENT_DRAW_MAIN_BEGIN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_DRAW_MAIN", "generate_full" : "LV_EVENT_DRAW_MAIN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_DRAW_MAIN_END", "generate_full" : "LV_EVENT_DRAW_MAIN_END", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_DRAW_POST_BEGIN", "generate_full" : "LV_EVENT_DRAW_POST_BEGIN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_DRAW_POST", "generate_full" : "LV_EVENT_DRAW_POST", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_DRAW_POST_END", "generate_full" : "LV_EVENT_DRAW_POST_END", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_DRAW_PART_BEGIN", "generate_full" : "LV_EVENT_DRAW_PART_BEGIN", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_DRAW_PART_END", "generate_full" : "LV_EVENT_DRAW_PART_END", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_VALUE_CHANGED", "generate_full" : "LV_EVENT_VALUE_CHANGED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_INSERT", "generate_full" : "LV_EVENT_INSERT", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_REFRESH", "generate_full" : "LV_EVENT_REFRESH", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_READY", "generate_full" : "LV_EVENT_READY", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_CANCEL", "generate_full" : "LV_EVENT_CANCEL", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_DELETE", "generate_full" : "LV_EVENT_DELETE", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_CHILD_CHANGED", "generate_full" : "LV_EVENT_CHILD_CHANGED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_CHILD_CREATED", "generate_full" : "LV_EVENT_CHILD_CREATED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_CHILD_DELETED", "generate_full" : "LV_EVENT_CHILD_DELETED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_SCREEN_UNLOAD_START", "generate_full" : "LV_EVENT_SCREEN_UNLOAD_START", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_SCREEN_LOAD_START", "generate_full" : "LV_EVENT_SCREEN_LOAD_START", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_SCREEN_LOADED", "generate_full" : "LV_EVENT_SCREEN_LOADED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_SCREEN_UNLOADED", "generate_full" : "LV_EVENT_SCREEN_UNLOADED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_SIZE_CHANGED", "generate_full" : "LV_EVENT_SIZE_CHANGED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_STYLE_CHANGED", "generate_full" : "LV_EVENT_STYLE_CHANGED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_LAYOUT_CHANGED", "generate_full" : "LV_EVENT_LAYOUT_CHANGED", "ifdef" : "LVGL", "return" : ["int",""]
}*/
/*JSON{"type" : "staticproperty", "class" : "lv", "name" : "LV_EVENT_GET_SELF_SIZE", "generate_full" : "LV_EVENT_GET_SELF_SIZE", "ifdef" : "LVGL", "return" : ["int",""]
}*/


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

/*********************************************************************************/



/*JSON{
  "type" : "init",
  "generate" : "jswrap_lvgl_init",
  "sortorder" : -100
}*/

void jswrap_lvgl_init() {
  jsiConsolePrintf("\n lvgl init \n");
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
  "type" : "staticmethod",
  "class" : "lv",
  "name" : "timerHandler",
  "generate_full" : "jswrap_lvgl_timerHandler()"
}*/

void jswrap_lvgl_timerHandler() {
  lv_timer_handler();
}


/*JSON{
  "type" : "staticmethod",
  "class" : "lv",
  "name" : "lv_scr_act",
  "generate" : "jswrap_lv_scr_act",
  "return" : ["JsVar","lv_obj_t"]
}*/

JsVar *jswrap_lv_scr_act() {
  struct _lv_obj_t * _res = (struct _lv_obj_t *)lv_scr_act();
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}

/*JSON{
  "type" : "staticmethod",
  "class" : "lv",
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
  "type" : "staticmethod",
  "class" : "lv",
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
  "type" : "staticmethod",
  "class" : "lv",
  "name" : "lv_label_create",
  "generate" : "jswrap_lv_label_create",
  "params" : [
    ["type","JsVar","lv_obj_t"]
  ],
  "return" : ["JsVar","lv_obj_t"]
}*/

JsVar *jswrap_lv_label_create(JsVar *jsvar) {
  return js_lv_obj_create(jsvar, lv_label_create);
}

/*JSON{
  "type" : "staticmethod",
  "class" : "lv",
  "name" : "lv_btn_create",
  "generate" : "jswrap_lv_btn_create",
  "params" : [
    ["type","JsVar","lv_obj_t"]
  ],
  "return" : ["JsVar","lv_obj_t"]
}*/

JsVar *jswrap_lv_btn_create(JsVar *jsvar) {
  return js_lv_obj_create(jsvar, lv_btn_create);
}

/*JSON{
  "type" : "staticmethod",
  "class" : "lv",
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
  "type" : "staticmethod",
  "class" : "lv",
  "name" : "lv_obj_center",
  "generate" : "jswrap_lv_obj_center",
  "params" : [
    ["type","JsVar","lv_obj_t"]
  ]
}*/

void jswrap_lv_obj_center(JsVar *jsvar) {
  js_lv_obj_center(jsvar, lv_obj_center);
}

/*JSON{
  "type" : "staticmethod",
  "class" : "lv",
  "name" : "lv_tileview_create",
  "generate" : "jswrap_lv_tileview_create",
  "params" : [
    ["type","JsVar","lv_obj_t"]
  ],
  "return" : ["JsVar","lv_obj_t"]
}*/

JsVar *jswrap_lv_tileview_create(JsVar *jsvar) {
  return js_lv_obj_create(jsvar, lv_tileview_create);
}

/*JSON{
  "type" : "staticmethod",
  "class" : "lv",
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
  struct _lv_obj_t * _res = (struct _lv_obj_t *)lv_tileview_add_tile(obj, col_id, row_id, (lv_dir_t)dir);
  return jsvNewNativeFunction((void*)_res, JSWAT_VOID);
}


/*JSON{
  "type" : "staticmethod",
  "class" : "lv",
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
  "type" : "staticmethod",
  "class" : "lv",
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

    //if(code == LV_EVENT_CLICKED) {
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
    args[1] = js_user_data;
    jspeFunctionCall(js_event_cb_h, jsvNewFromString("js_event_handler"), 0, false, 2, args);
    //}
}

void jswrap_lv_obj_add_event_cb(JsVar *jsvar, JsVar *event_cb, int filter, JsVar *user_data) {

  if (!jsvIsUndefined(event_cb) && !jsvIsFunction(event_cb)) {
    jsError("Expecting Callback Function, got %t", event_cb);
    return;
  }
 
  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);  
  obj->user_data = (uintptr_t)event_cb;
  //jsiConsolePrintf("\n func %x \n", obj->user_data);
  //jsiConsolePrintf("\n 1 - func %x, %x \n", event_cb, jsvIsFunction(event_cb));

  lv_obj_add_event_cb(obj, js_event_handler, filter, (uintptr_t)user_data);
}

