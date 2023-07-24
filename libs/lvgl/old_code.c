/******************************************************************************/

// Functions to convert.....

// lv_imgbtn_set_src
/*
    https://docs.lvgl.io/8.3/search.html?q=lv_imgbtn_set_src
*/


// lv_obj_align_to
/*
    https://docs.lvgl.io/8.3/search.html?q=lv_obj_align_to
*/


// lv_anim_custom_del
/*
    https://docs.lvgl.io/8.3/search.html?q=lv_anim_custom_del
*/

// lv_gradient_calculate
/*
    https://docs.lvgl.io/8.3/search.html?q=lv_gradient_calculate
*/
    
// lv_gradient_get
/*
    https://docs.lvgl.io/8.3/search.html?q=lv_gradient_get
*/

// lv_font_get_line_height
/*
    https://docs.lvgl.io/8.3/search.html?q=lv_font_get_line_height
*/

// lv_style_is_empty
/*
    https://docs.lvgl.io/8.3/search.html?q=lv_style_is_empty
*/

// lv_font_load
/*
   https://docs.lvgl.io/8.3/search.html?q=lv_font_load
*/

// lv_obj_set_style_color_filter_dsc
/*
   https://docs.lvgl.io/8.3/search.html?q=lv_obj_set_style_color_filter_dsc
*/



// lv_win_get_content
/*
    https://docs.lvgl.io/8.3/search.html?q=lv_win_get_content
*/

// lv_win_get_header
/*
    https://docs.lvgl.io/8.3/search.html?q=lv_win_get_header
*/

/******************************************************************************/

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
