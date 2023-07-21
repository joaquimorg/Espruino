
#include "jsvar.h"
#include "jsvariterator.h"

#include "lvgl.h"

typedef struct JsLvgl {
    lv_obj_t *js_obj_t;    
} JsLvgl;


void jswrap_lvgl_init();
bool jswrap_lvgl_idle();

JsVar *jswrap_lv_font_BigNumbers();
JsVar *jswrap_lv_font_Icons32();
JsVar *jswrap_lv_font_Numbers42();
JsVar *jswrap_lv_font_Numbers64();
JsVar *jswrap_lv_font_OpenSans22();
JsVar *jswrap_lv_font_OpenSans22Bold();


JsVar *jswrap_lv_scr_act();
void jswrap_lv_obj_clean(JsVar *jsvar);
void jswrap_lv_obj_del(JsVar *jsvar);
void jswrap_lv_label_set_text(JsVar *jsvar, JsVar *txt);
JsVar *jswrap_lv_tileview_add_tile(JsVar *jsvar, int col_id, int row_id, int dir);
void jswrap_lv_obj_align(JsVar *jsvar, int align, int x_ofs, int y_ofs);
void jswrap_lv_obj_add_event_cb(JsVar *jsvar, JsVar *event_cb, int filter, JsVar *user_data);
void jswrap_lv_img_set_src(JsVar *jsvar, JsVar *src);


JsVar *js_lv_obj_create(JsVar *jsvar, void *lv_func_ptr);
void js_lv_obj_center(JsVar *jsvar, void *lv_func_ptr);
void js_lv_label_set_text(JsVar *jsvar, const char* txt, void *lv_func_ptr);
JsVar *js_lv_color_hex(JsVar *jsvar, void *lv_func_ptr) ;
void js_lv_obj_set_style_bg_color(JsVar *jsvar, JsVar *jsvar_color, int selector, void *lv_func_ptr);
void js_lv_obj_set_style_text_align(JsVar *jsvar, int align, int selector, void *lv_func_ptr);
void js_lv_style_set_text_font(JsVar *jsvar, JsVar *jsvar_font, void *lv_func_ptr);
void js_lv_obj_set_style_text_font(JsVar *jsvar, JsVar *jsvar_font, int selector, void *lv_func_ptr);
void js_lv_img_set_src(JsVar *jsvar, const void* src, void *lv_func_ptr);
void js_lv_obj_set_style_bg_opa(JsVar *jsvar, int value, int selector, void *lv_func_ptr);
void js_lv_obj_add_flag(JsVar *jsvar, int flag, void *lv_func_ptr);
void js_lv_obj_add_state(JsVar *jsvar, int state, void *lv_func_ptr);
bool js_lv_obj_has_flag(JsVar *jsvar, int flag, void *lv_func_ptr);
int js_lv_obj_get_state(JsVar *jsvar, void *lv_func_ptr);
bool js_lv_obj_has_state(JsVar *jsvar, int state, void *lv_func_ptr);