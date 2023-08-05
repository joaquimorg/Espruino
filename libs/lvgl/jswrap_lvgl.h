
#include "jsvar.h"
#include "jsvariterator.h"

#include "lvgl.h"

typedef struct JsLvgl {
    JsVar *js_obj_t;    
} JsLvgl;


void jswrap_lvgl_init();
bool jswrap_lvgl_idle();

JsVar *jswrap_lv_font_BigNumbers();
JsVar *jswrap_lv_font_Icons32();
JsVar *jswrap_lv_font_Numbers42();
JsVar *jswrap_lv_font_Numbers64();
JsVar *jswrap_lv_font_OpenSans22();
JsVar *jswrap_lv_font_OpenSans22Bold();

void jswrap_lv_obj_add_event_cb(JsVar *jsvar, JsVar *event_cb, int filter, JsVar *user_data);


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void jswrap_lv_obj_center(JsVar *jsobj, void *lv_func_ptr);
int jswrap_lv_obj_dpx(JsVar *jsobj, lv_coord_t n, void *lv_func_ptr);
void jswrap_lv_obj_move_foreground(JsVar *jsobj, void *lv_func_ptr);
void jswrap_lv_obj_set_pos(JsVar *jsobj, lv_coord_t x, lv_coord_t y, void *lv_func_ptr);
void jswrap_lv_obj_set_x(JsVar *jsobj, lv_coord_t x, void *lv_func_ptr);
void jswrap_lv_obj_set_layout(JsVar *jsobj, uint32_t layout, void *lv_func_ptr);
void jswrap_lv_obj_update_layout(JsVar *jsobj, void *lv_func_ptr);
void jswrap_lv_obj_set_align(JsVar *jsobj, lv_align_t align, void *lv_func_ptr);
void jswrap_lv_obj_align(JsVar *jsobj, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs, void *lv_func_ptr);
void jswrap_lv_obj_align_to(JsVar *jsobj, JsVar *base, JsVar *args, void *lv_func_ptr);
void jswrap_lv_obj_get_coords(JsVar *jsobj, lv_area_t *coords, void *lv_func_ptr);
int jswrap_lv_obj_get_x(JsVar *jsobj, void *lv_func_ptr);
JsVar *jswrap_lv_obj_get_screen(JsVar *jsobj, void *lv_func_ptr);
JsVar *jswrap_lv_obj_get_child(JsVar *jsobj, int32_t id, void *lv_func_ptr);
void jswrap_lv_obj_set_scrollbar_mode(JsVar *jsobj, lv_scrollbar_mode_t mode, void *lv_func_ptr);
void jswrap_lv_obj_set_scroll_dir(JsVar *jsobj, lv_dir_t dir, void *lv_func_ptr);
void jswrap_lv_obj_set_scroll_snap_x(JsVar *jsobj, lv_scroll_snap_t align, void *lv_func_ptr);
void jswrap_lv_obj_scroll_by(JsVar *jsobj, lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en, void *lv_func_ptr);
void jswrap_lv_obj_scroll_to_x(JsVar *jsobj, lv_coord_t x, lv_anim_enable_t anim_en, void *lv_func_ptr);
void jswrap_lv_obj_scroll_to_view(JsVar *jsobj, lv_anim_enable_t anim_en, void *lv_func_ptr);
void jswrap_lv_obj_add_style(JsVar *jsobj, JsVar *style, lv_style_selector_t selector, void *lv_func_ptr);
int jswrap_lv_obj_style_get_selector_state(lv_style_selector_t selector, void *lv_func_ptr);
int jswrap_lv_obj_style_get_selector_part(lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_align(JsVar *jsobj, lv_align_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_bg_color(JsVar *jsobj, JsVarInt *value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_bg_opa(JsVar *jsobj, lv_opa_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_bg_grad_dir(JsVar *jsobj, lv_grad_dir_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_bg_grad(JsVar *jsobj, JsVar *value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_bg_dither_mode(JsVar *jsobj, lv_dither_mode_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_bg_img_src(JsVar *jsobj, JsVar *value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_bg_img_tiled(JsVar *jsobj, bool value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_border_side(JsVar *jsobj, lv_border_side_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_text_font(JsVar *jsobj, JsVar *value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_text_decor(JsVar *jsobj, lv_text_decor_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_text_align(JsVar *jsobj, lv_text_align_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_color_filter_dsc(JsVar *jsobj, JsVar *value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_anim(JsVar *jsobj, JsVar *value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_anim_time(JsVar *jsobj, uint32_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_transition(JsVar *jsobj, JsVar *value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_blend_mode(JsVar *jsobj, lv_blend_mode_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_layout(JsVar *jsobj, uint16_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_base_dir(JsVar *jsobj, lv_base_dir_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_add_flag(JsVar *jsobj, lv_obj_flag_t f, void *lv_func_ptr);
void jswrap_lv_obj_add_state(JsVar *jsobj, lv_state_t state, void *lv_func_ptr);
bool jswrap_lv_obj_has_flag(JsVar *jsobj, lv_obj_flag_t f, void *lv_func_ptr);
int jswrap_lv_obj_get_state(JsVar *jsobj, void *lv_func_ptr);
bool jswrap_lv_obj_has_state(JsVar *jsobj, lv_state_t state, void *lv_func_ptr);
void jswrap_lv_obj_set_flex_flow(JsVar *jsobj, lv_flex_flow_t flow, void *lv_func_ptr);
void jswrap_lv_obj_set_flex_align(JsVar *jsobj, lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_cross_place, void *lv_func_ptr);
void jswrap_lv_obj_set_flex_grow(JsVar *jsobj, uint8_t grow, void *lv_func_ptr);
void jswrap_lv_obj_set_style_flex_flow(JsVar *jsobj, lv_flex_flow_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_flex_main_place(JsVar *jsobj, lv_flex_align_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_style_flex_grow(JsVar *jsobj, uint8_t value, lv_style_selector_t selector, void *lv_func_ptr);
void jswrap_lv_obj_set_tile(JsVar *tv, JsVar *tile_obj, lv_anim_enable_t anim_en, void *lv_func_ptr);
void jswrap_lv_obj_set_tile_id(JsVar *tv, uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en, void *lv_func_ptr);
JsVar *jswrap_lv_obj_create(JsVar *jsobj, void *lv_func_ptr);
void jswrap_lv_arc_set_start_angle(JsVar *jsobj, uint16_t start, void *lv_func_ptr);
void jswrap_lv_arc_set_angles(JsVar *jsobj, uint16_t start, uint16_t end, void *lv_func_ptr);
void jswrap_lv_arc_set_mode(JsVar *jsobj, lv_arc_mode_t type, void *lv_func_ptr);
void jswrap_lv_arc_set_value(JsVar *jsobj, int16_t value, void *lv_func_ptr);
void jswrap_lv_arc_set_range(JsVar *jsobj, int16_t min, int16_t max, void *lv_func_ptr);
int jswrap_lv_arc_get_angle_start(JsVar *jsobj, void *lv_func_ptr);
int jswrap_lv_arc_get_value(JsVar *jsobj, void *lv_func_ptr);
int jswrap_lv_arc_get_mode(JsVar *jsobj, void *lv_func_ptr);
void jswrap_lv_arc_align_obj_to_angle(JsVar *jsobj, JsVar *jsobj_to_align, lv_coord_t r_offset, void *lv_func_ptr);
void jswrap_lv_img_cache_invalidate_src(JsVar *src, void *lv_func_ptr);
void jswrap_lv_img_set_src(JsVar *jsobj, JsVar *src, void *lv_func_ptr);
void jswrap_lv_img_set_offset_x(JsVar *jsobj, lv_coord_t x, void *lv_func_ptr);
void jswrap_lv_img_set_pivot(JsVar *jsobj, lv_coord_t x, lv_coord_t y, void *lv_func_ptr);
void jswrap_lv_img_set_antialias(JsVar *jsobj, bool antialias, void *lv_func_ptr);
void jswrap_lv_img_set_size_mode(JsVar *jsobj, lv_img_size_mode_t mode, void *lv_func_ptr);
int jswrap_lv_img_get_offset_x(JsVar *jsobj, void *lv_func_ptr);
void jswrap_lv_img_get_pivot(JsVar *jsobj, JsVar *pivot, void *lv_func_ptr);
bool jswrap_lv_img_get_antialias(JsVar *jsobj, void *lv_func_ptr);
int jswrap_lv_img_get_size_mode(JsVar *jsobj, void *lv_func_ptr);
void jswrap_lv_label_set_text(JsVar *jsobj, JsVar *text, void *lv_func_ptr);
void jswrap_lv_label_set_long_mode(JsVar *jsobj, lv_label_long_mode_t long_mode, void *lv_func_ptr);
void jswrap_lv_line_set_points(JsVar *jsobj, JsVar *points, uint16_t point_num, void *lv_func_ptr);
JsVar *jswrap_lv_checkbox_get_text(JsVar *jsobj, void *lv_func_ptr);
void jswrap_lv_bar_set_value(JsVar *jsobj, int32_t value, lv_anim_enable_t anim, void *lv_func_ptr);
void jswrap_lv_bar_set_range(JsVar *jsobj, int32_t min, int32_t max, void *lv_func_ptr);
void jswrap_lv_bar_set_mode(JsVar *jsobj, lv_bar_mode_t mode, void *lv_func_ptr);
int jswrap_lv_bar_get_value(JsVar *jsobj, void *lv_func_ptr);
int jswrap_lv_bar_get_mode(JsVar *jsobj, void *lv_func_ptr);
void jswrap_lv_slider_set_mode(JsVar *jsobj, lv_slider_mode_t mode, void *lv_func_ptr);
int jswrap_lv_slider_get_mode(JsVar *slider, void *lv_func_ptr);
void jswrap_lv_roller_set_options(JsVar *jsobj, JsVar *options, lv_roller_mode_t mode, void *lv_func_ptr);
void jswrap_lv_roller_set_selected(JsVar *jsobj, uint16_t sel_opt, lv_anim_enable_t anim, void *lv_func_ptr);
int jswrap_lv_roller_get_selected(JsVar *jsobj, void *lv_func_ptr);
void jswrap_lv_animimg_set_src(JsVar *jsobj, JsVar *dsc, uint8_t num, void *lv_func_ptr);
JsVar *jswrap_lv_spinner_create(JsVar *jsobj, uint32_t time, uint32_t arc_length, void *lv_func_ptr);
JsVar *jswrap_lv_tileview_add_tile(JsVar *tv, uint8_t col_id, uint8_t row_id, lv_dir_t dir, void *lv_func_ptr);
//void jswrap_lv_imgbtn_set_src(JsVar *jsobj, lv_imgbtn_state_t state, JsVar *src_left, JsVar *src_mid, JsVar *src_right, void *lv_func_ptr);
//void jswrap_lv_imgbtn_set_state(JsVar *jsobj, lv_imgbtn_state_t state, void *lv_func_ptr);
//JsVar *jswrap_lv_imgbtn_get_src_left(JsVar *jsobj, lv_imgbtn_state_t state, void *lv_func_ptr);
int jswrap_lv_color_to1(JsVar *color, void *lv_func_ptr);
int jswrap_lv_color_to16(JsVar *color, void *lv_func_ptr);
int jswrap_lv_color_to32(JsVar *olor, void *lv_func_ptr);
JsVar *jswrap_lv_color_mix(JsVar *c1, JsVar *c2, uint8_t mix, void *lv_func_ptr);
JsVar *jswrap_lv_color_lighten(JsVar *c, lv_opa_t lvl, void *lv_func_ptr);
JsVar *jswrap_lv_gradient_calculate(JsVar *dsc, lv_coord_t range, lv_coord_t frac, void *lv_func_ptr);
JsVar *jswrap_lv_gradient_get(JsVar *gradient, lv_coord_t w, lv_coord_t h, void *lv_func_ptr);
int jswrap_lv_font_get_line_height(JsVar *font_p, void *lv_func_ptr);
void jswrap_lv_font_free(lv_font_t *font, void *lv_func_ptr);
void jswrap_lv_anim_set_var(JsVar *a, void *var, void *lv_func_ptr);
void jswrap_lv_anim_set_time(JsVar *a, uint32_t duration, void *lv_func_ptr);
void jswrap_lv_anim_set_values(JsVar *a, int32_t start, int32_t end, void *lv_func_ptr);
void jswrap_lv_anim_set_repeat_count(JsVar *a, uint16_t cnt, void *lv_func_ptr);
void jswrap_lv_anim_set_early_apply(JsVar *a, bool en, void *lv_func_ptr);
int jswrap_lv_anim_get_delay(JsVar *a, void *lv_func_ptr);
bool jswrap_lv_anim_custom_del(JsVar *a, void *lv_func_ptr);
JsVar *jswrap_lv_anim_start(JsVar *a, void *lv_func_ptr);
int jswrap_lv_anim_path_linear(JsVar *a, void *lv_func_ptr);
bool jswrap_lv_style_remove_prop(JsVar *style, lv_style_prop_t prop, void *lv_func_ptr);
bool jswrap_lv_style_is_empty(JsVar *style, void *lv_func_ptr);
void jswrap_lv_anim_timeline_del(JsVar *at, void *lv_func_ptr);
void jswrap_lv_anim_timeline_add(JsVar *at, uint32_t start_time, JsVar *a, void *lv_func_ptr);
int jswrap_lv_anim_timeline_start(JsVar *at, void *lv_func_ptr);
void jswrap_lv_anim_timeline_set_reverse(JsVar *at, bool reverse, void *lv_func_ptr);
void jswrap_lv_anim_timeline_set_progress(JsVar *at, uint16_t progress, void *lv_func_ptr);
bool jswrap_lv_anim_timeline_get_reverse(JsVar *at, void *lv_func_ptr);
JsVar *jswrap_lv_color_make(uint8_t r, uint8_t g, uint8_t b, void *lv_func_ptr);
JsVar *jswrap_lv_color_hex(uint32_t c, void *lv_func_ptr);
JsVar *jswrap_lv_color_chroma_key(void *lv_func_ptr);
bool jswrap_lv_style_prop_has_flag(lv_style_prop_t prop, uint8_t flag, void *lv_func_ptr);
JsVar *jswrap_lv_scr_act(void *lv_func_ptr);
bool jswrap_lv_anim_del(void *var, lv_anim_exec_xcb_t exec_cb, void *lv_func_ptr);
JsVar *jswrap_lv_anim_get(void *var, lv_anim_exec_xcb_t exec_cb, void *lv_func_ptr);
JsVar *jswrap_lv_anim_get_timer(void *lv_func_ptr);
int jswrap_lv_anim_count_running(void *lv_func_ptr);
int jswrap_lv_anim_speed_to_time(uint32_t speed, int32_t start, int32_t end, void *lv_func_ptr);
JsVar *jswrap_lv_anim_timeline_create(void *lv_func_ptr);
void jswrap_lv_scr_load_anim(JsVar *jsobj, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del, void *lv_func_ptr);
JsVar *jswrap_lv_font_load(JsVar *fontName, void *lv_func_ptr);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

