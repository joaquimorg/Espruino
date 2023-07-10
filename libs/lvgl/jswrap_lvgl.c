

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
  if (!messagePtr) return 0;
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

void jswrap_lv_obj_add_event_cb(JsVar *jsvar, JsVar *event_cb, int filter, int user_data) {

  if (!jsvIsUndefined(event_cb) && !jsvIsFunction(event_cb)) {
    jsError("Expecting Callback Function but got %t", event_cb);
    return;
  }
  //lv_event_code_t 

  struct _lv_obj_t *obj = jsvGetNativeFunctionPtr(jsvar);

  jspeFunctionCall(event_cb, 0, NULL, false, 0, NULL);

  //lv_obj_add_event_cb(obj, jsvGetNativeFunctionPtr(event_cb), filter, NULL);
}

