// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.6
// Project name: Large

#include "../ui.h"

void ui_ha_switches_screen_init(void)
{
    ui_ha_switches = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ha_switches, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ha_switches, lv_color_hex(0x1C1C1C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ha_switches, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ha_switches_label = lv_label_create(ui_ha_switches);
    lv_obj_set_width(ui_ha_switches_label, 316);
    lv_obj_set_height(ui_ha_switches_label, 38);
    lv_obj_set_x(ui_ha_switches_label, 82);
    lv_obj_set_y(ui_ha_switches_label, 58);
    lv_label_set_text(ui_ha_switches_label, "Switches");
    lv_obj_set_style_text_color(ui_ha_switches_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ha_switches_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_ha_switches_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ha_switches_label, &ui_font_font0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button = lv_btn_create(ui_ha_switches);
    lv_obj_set_width(ui_Button, 214);
    lv_obj_set_height(ui_Button, 164);
    lv_obj_set_x(ui_Button, 22);
    lv_obj_set_y(ui_Button, 96);
    lv_obj_add_flag(ui_Button, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Button, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Button, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_Button, 12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_Button, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Button, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_button_logo = lv_img_create(ui_Button);
    lv_img_set_src(ui_button_logo, &ui_img_ic_switch2_off_png);
    lv_obj_set_width(ui_button_logo, LV_SIZE_CONTENT);   /// 45
    lv_obj_set_height(ui_button_logo, LV_SIZE_CONTENT);    /// 45
    lv_obj_set_x(ui_button_logo, 0);
    lv_obj_set_y(ui_button_logo, -10);
    lv_obj_set_align(ui_button_logo, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_button_logo, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_button_logo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_button_label = lv_label_create(ui_Button);
    lv_obj_set_width(ui_button_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_button_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_button_label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_button_label, "Button");
    lv_obj_set_style_text_color(ui_button_label, lv_color_hex(0x9E9E9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_button_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_button_label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_toggle = lv_obj_create(ui_ha_switches);
    lv_obj_set_width(ui_toggle, 214);
    lv_obj_set_height(ui_toggle, 164);
    lv_obj_set_x(ui_toggle, 244);
    lv_obj_set_y(ui_toggle, 268);
    lv_obj_clear_flag(ui_toggle, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_toggle, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_toggle, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_toggle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_toggle, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_toggle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_toggle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_toggle_label = lv_label_create(ui_toggle);
    lv_obj_set_width(ui_toggle_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_toggle_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_toggle_label, 0);
    lv_obj_set_y(ui_toggle_label, -5);
    lv_obj_set_align(ui_toggle_label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_toggle_label, "Toggle");
    lv_obj_set_style_text_color(ui_toggle_label, lv_color_hex(0x9E9E9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_toggle_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_toggle_label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_toggle_btn = lv_switch_create(ui_toggle);
    lv_obj_set_width(ui_toggle_btn, 120);
    lv_obj_set_height(ui_toggle_btn, 60);
    lv_obj_set_x(ui_toggle_btn, 0);
    lv_obj_set_y(ui_toggle_btn, -7);
    lv_obj_set_align(ui_toggle_btn, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_toggle_btn, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_toggle_btn, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_toggle_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_toggle_btn, 40, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_toggle_btn, lv_color_hex(0x4F4F4F), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_toggle_btn, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_toggle_btn, lv_color_hex(0x529D53), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_toggle_btn, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_slider = lv_obj_create(ui_ha_switches);
    lv_obj_set_width(ui_slider, 214);
    lv_obj_set_height(ui_slider, 164);
    lv_obj_set_x(ui_slider, 22);
    lv_obj_set_y(ui_slider, 268);
    lv_obj_clear_flag(ui_slider, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_slider, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_slider, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_slider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_slider, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_slider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_slider_label = lv_label_create(ui_slider);
    lv_obj_set_width(ui_slider_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_slider_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_slider_label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_slider_label, "Slider");
    lv_obj_set_style_text_color(ui_slider_label, lv_color_hex(0x9E9E9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_slider_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_slider_label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_slider_data = lv_label_create(ui_slider);
    lv_obj_set_width(ui_slider_data, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_slider_data, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_slider_data, 25);
    lv_obj_set_y(ui_slider_data, 21);
    lv_obj_set_align(ui_slider_data, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_slider_data, "24.5");
    lv_obj_set_style_text_color(ui_slider_data, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_slider_data, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_slider_data, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_slider_unit = lv_label_create(ui_slider);
    lv_obj_set_width(ui_slider_unit, 66);
    lv_obj_set_height(ui_slider_unit, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_slider_unit, 104);
    lv_obj_set_y(ui_slider_unit, 23);
    lv_obj_set_align(ui_slider_unit, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(ui_slider_unit, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_slider_unit, "%");
    lv_obj_set_style_text_color(ui_slider_unit, lv_color_hex(0xECBF41), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_slider_unit, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_slider_unit, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_slider_unit, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_slider_btn = lv_slider_create(ui_slider);
    lv_slider_set_value(ui_slider_btn, 40, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_slider_btn) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_slider_btn, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_slider_btn, 151);
    lv_obj_set_height(ui_slider_btn, 37);
    lv_obj_set_x(ui_slider_btn, -2);
    lv_obj_set_y(ui_slider_btn, -28);
    lv_obj_set_align(ui_slider_btn, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_slider_btn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_slider_btn, lv_color_hex(0x1C1C1C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_slider_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_slider_btn, lv_color_hex(0x529D53), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_slider_btn, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_slider_btn, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_slider_btn, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_arc = lv_obj_create(ui_ha_switches);
    lv_obj_set_width(ui_arc, 214);
    lv_obj_set_height(ui_arc, 164);
    lv_obj_set_x(ui_arc, 244);
    lv_obj_set_y(ui_arc, 96);
    lv_obj_clear_flag(ui_arc, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_arc, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_arc, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_arc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_arc, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_arc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_arc_btn = lv_arc_create(ui_arc);
    lv_obj_set_width(ui_arc_btn, 130);
    lv_obj_set_height(ui_arc_btn, 125);
    lv_obj_set_align(ui_arc_btn, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_arc_btn, 80);
    lv_arc_set_bg_angles(ui_arc_btn, 140, 40);
    lv_obj_set_style_arc_color(ui_arc_btn, lv_color_hex(0x1C1C1C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_arc_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_arc_btn, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(ui_arc_btn, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_arc_btn, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_arc_btn, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_arc_btn, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_arc_btn, lv_color_hex(0x529D53), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_arc_btn, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_arc_btn, 8, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_arc_btn, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_arc_btn, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_arc_btn, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_arc_label = lv_label_create(ui_arc);
    lv_obj_set_width(ui_arc_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_arc_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_arc_label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_arc_label, "Arc");
    lv_obj_set_style_text_color(ui_arc_label, lv_color_hex(0x9E9E9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_arc_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_arc_label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_arc_data = lv_label_create(ui_arc);
    lv_obj_set_width(ui_arc_data, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_arc_data, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_arc_data, -4);
    lv_obj_set_y(ui_arc_data, -54);
    lv_obj_set_align(ui_arc_data, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_arc_data, "24.5");
    lv_obj_set_style_text_color(ui_arc_data, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_arc_data, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_arc_data, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_arc_data, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_slider_btn, ui_event_slider_btn, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_arc_btn, ui_event_arc_btn, LV_EVENT_ALL, NULL);

}
