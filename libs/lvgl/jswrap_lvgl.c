

#include "jswrap_lvgl.h"
#include "jswrapper.h"
#include "jsutils.h"
#include "jsinteractive.h"

#include "lvgl.h"



/*********************************************************************************/

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
  lv_timer_handler();
  return false;
}


/*JSON{
  "type" : "library",
  "class" : "lv",
  "typescript" : "lv"
}
This library provides GUI operations using LVGL.

*/


/*JSON{
  "type" : "staticmethod",
  "class" : "lv",
  "name" : "timerHandler",
  "generate_full" : "jswrap_lvgl_timerHandler()"
}

*/
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

  /*jsiConsolePrintf("\n");
  jsiConsolePrintf("_lv_obj_t : %x\n", _res);
  jsiConsolePrintf("parent : %x\n", parent);
  jsiConsolePrintf("data : %x\n", data);*/

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

  /*jsiConsolePrintf("\n");
  jsiConsolePrintf("parent : %x\n", parent);
  jsiConsolePrintf("jsvar : %x\n", jsvar);
  jsiConsolePrintf("_lv_obj_t : %x\n", obj);*/
  
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
  "return" : ["JsVar","pointer to the active screen"],
  "return_object" : "JsVar"
}*/

JsVar *jswrap_lv_label_create(JsVar *jsvar) {
  return js_lv_obj_create(jsvar, lv_label_create);
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