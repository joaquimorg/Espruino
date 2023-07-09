
#include "jsvar.h"
#include "jsvariterator.h"

#include "lvgl.h"

typedef struct JsLvgl {
    lv_obj_t *js_obj_t;    
} JsLvgl;


void jswrap_lvgl_init();
bool jswrap_lvgl_idle();

void jswrap_lvgl_timerHandler();
JsVar *jswrap_lv_scr_act();
void jswrap_lv_obj_clean(JsVar *jsvar);
void jswrap_lv_obj_del(JsVar *jsvar);

JsVar *jswrap_lv_label_create(JsVar *jsvar);
void jswrap_lv_label_set_text(JsVar *jsvar, JsVar *txt);
void jswrap_lv_obj_center(JsVar *jsvar);
