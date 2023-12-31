// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: medium

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_ha_sensors
void ui_ha_sensors_screen_init(void);
lv_obj_t *ui_ha_sensors;
lv_obj_t *ui_ha_sensors_label;
lv_obj_t *ui_sensor1_btn;
lv_obj_t *ui_sensor1_logo;
lv_obj_t *ui_sensor1_label;
lv_obj_t *ui_sensor1_data;
lv_obj_t *ui_sensor1_unit;
lv_obj_t *ui_sensor2_btn;
lv_obj_t *ui_sensor2_logo;
lv_obj_t *ui_sensor2_label;
lv_obj_t *ui_sensor2_data;
lv_obj_t *ui_sensor2_unit;
lv_obj_t *ui_sensor3_btn;
lv_obj_t *ui_sensor3_logo;
lv_obj_t *ui_sensor3_label;
lv_obj_t *ui_sensor3_data;
lv_obj_t *ui_sensor3_unit;
lv_obj_t *ui_sensor4_btn;
lv_obj_t *ui_sensor4_logo;
lv_obj_t *ui_sensor4_label;
lv_obj_t *ui_sensor4_data;
lv_obj_t *ui_sensor4_unit;
lv_obj_t *ui_logo;


// SCREEN: ui_ha_switches
void ui_ha_switches_screen_init(void);
lv_obj_t *ui_ha_switches;
lv_obj_t *ui_ha_switches_label;
lv_obj_t *ui_Button;
lv_obj_t *ui_button_logo;
lv_obj_t *ui_button_label;
lv_obj_t *ui_toggle;
lv_obj_t *ui_toggle_label;
lv_obj_t *ui_toggle_btn;
lv_obj_t *ui_slider;
lv_obj_t *ui_slider_label;
lv_obj_t *ui_slider_data;
lv_obj_t *ui_slider_unit;
void ui_event_slider_btn( lv_event_t * e);
lv_obj_t *ui_slider_btn;
lv_obj_t *ui_arc;
void ui_event_arc_btn( lv_event_t * e);
lv_obj_t *ui_arc_btn;
lv_obj_t *ui_arc_label;
lv_obj_t *ui_arc_data;
lv_obj_t *ui_dropdown;
lv_obj_t *ui_dropdown_label;
lv_obj_t *ui_dropdown_btn;


// SCREEN: ui_ha_switches2
void ui_ha_switches2_screen_init(void);
lv_obj_t *ui_ha_switches2;
lv_obj_t *ui_ha_switches2_label;
lv_obj_t *ui____initial_actions0;
const lv_img_dsc_t *ui_imgset_wifi_[3] = {&ui_img_wifi_1_png, &ui_img_wifi_2_png, &ui_img_wifi_3_png};
const lv_img_dsc_t *ui_imgset_ic_co[1] = {&ui_img_ic_co2_png};
const lv_img_dsc_t *ui_imgset_location[1] = {&ui_img_location2_png};
const lv_img_dsc_t *ui_imgset_co[1] = {&ui_img_co2_png};
const lv_img_dsc_t *ui_imgset_humidity_[2] = {&ui_img_humidity_1_png, &ui_img_humidity_2_png};
const lv_img_dsc_t *ui_imgset_temp_[2] = {&ui_img_temp_1_png, &ui_img_temp_2_png};
const lv_img_dsc_t *ui_imgset_ha_logo[1] = {&ui_img_ha_logo32_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_slider_btn( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      _ui_slider_set_text_value( ui_slider_data, target, "", "");
}
}
void ui_event_arc_btn( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      _ui_slider_set_text_value( ui_arc_data, target, "", " °C");
}
}

///////////////////// SCREENS ////////////////////

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_ha_sensors_screen_init();
ui_ha_switches_screen_init();
ui_ha_switches2_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_ha_sensors);
}
