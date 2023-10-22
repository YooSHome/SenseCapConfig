
#ifndef UI_SCREEN_HA_TEMPLATES_H
#define UI_SCREEN_HA_TEMPLATES_H

#include "../../model/indicator_ha_config.h"
#include "../ui.h"



// Define small sensor
typedef struct sensor_ui {
    int width;
    int height;
    int logo_width;
    int logo_height;
    int logo_x;
    int logo_y;
    int label_x;
    int label_y;
    int data_x;
    int data_y;
    int data_width;
    int unit_x;
    int unit_y;
    int font_size;
} sensor_ui_t;

typedef struct switch_ui {
    // Global
    int width;
    int height;

    // Button
    int b_icon_x;
    int b_icon_y;

    // toggle
    int t_label_x;
    int t_label_y;
    int t_toggle_x;
    int t_toggle_y;
    int t_toggle_width;
    int t_toggle_height;

    // slider
    int s_data_label_x;
    int s_data_label_y;

    // arc
    int a_data_width;
    int a_data_height;
    int a_data_label_x;
    int a_data_label_y;

} switch_ui_t;

// Global template
typedef struct template {
    sensor_ui_t sensor_ui;
    switch_ui_t switch_ui;
    int type;
} template_t;

enum template_type {
    BT_SMALL = 0,
    BT_MEDIUM = 1,
    BT_LARGE = 2
};

#define GLOBAL_LABEL_COLOR 0xECBF41
#define GLOBAL_DATA_COLOR 0xECBF41
#define GLOBAL_UNIT_COLOR 0xECBF41
#define GLOBAL_BTN_BG_COLOR 0x282828

// FUCNTIONS
void create_sensor_button(int type, lv_obj_t *parent, ha_sensor_t *sensor, int bt_x, int bt_y, int text_color, char *name, char *label, char *unit, char *icon);
void create_switch_button(int size, lv_obj_t *parent, ha_switch_t *switch_, int bt_x, int bt_y, char *label);
void create_switch_toggle(int size, lv_obj_t *parent, ha_switch_t *switch_, int bt_x, int bt_y, char *label);
void create_switch_arc(int size, lv_obj_t *parent, ha_switch_t *switch_, int bt_x, int bt_y, char *label, char *unit);
void create_switch_slider(int size, lv_obj_t *parent, ha_switch_t *switch_, int bt_x, int bt_y, char *label, char *unit);
void ui_event_btn(lv_event_t *e);

#endif