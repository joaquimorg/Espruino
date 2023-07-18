
#include "jsvar.h"
#include "jsvariterator.h"

#include "lvgl.h"

typedef struct JsLvgl {
    lv_obj_t *js_obj_t;    
} JsLvgl;


void jswrap_lvgl_init();
bool jswrap_lvgl_idle();

JsVar *jswrap_lv_font_montserrat_18();
JsVar *jswrap_lv_font_montserrat_22();
JsVar *jswrap_lv_font_montserrat_34();
JsVar *jswrap_lv_font_montserrat_48();

void jswrap_lvgl_timerHandler();
JsVar *jswrap_lv_scr_act();

void jswrap_lv_obj_clean(JsVar *jsvar);
void jswrap_lv_obj_del(JsVar *jsvar);

JsVar *jswrap_lv_label_create(JsVar *jsvar);
void jswrap_lv_label_set_text(JsVar *jsvar, JsVar *txt);

JsVar *jswrap_lv_tileview_create(JsVar *jsvar);
JsVar *jswrap_lv_tileview_add_tile(JsVar *jsvar, int col_id, int row_id, int dir);

JsVar *jswrap_lv_btn_create(JsVar *jsvar);

void jswrap_lv_obj_center(JsVar *jsvar);
void jswrap_lv_obj_align(JsVar *jsvar, int align, int x_ofs, int y_ofs);

void jswrap_lv_scr_load(JsVar *jsvar);

void jswrap_lv_obj_add_event_cb(JsVar *jsvar, JsVar *event_cb, int filter, JsVar *user_data);

JsVar *jswrap_lv_color_hex(JsVar *jsvar);
void jswrap_lv_obj_set_style_bg_color(JsVar *jsvar, JsVar *jsvar_color, int selector);
void jswrap_lv_obj_set_style_text_align(JsVar *jsvar, int align, int selector);

void jswrap_lv_obj_set_style_text_font(JsVar *jsvar, JsVar *jsvar_font, int selector);


JsVar *jswrap_lv_img_create(JsVar *jsvar);
void jswrap_lv_img_set_src(JsVar *jsvar, JsVar *src);


