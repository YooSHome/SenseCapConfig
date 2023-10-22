#ifndef UI_SCREEN_HA_AUTO_H
#define UI_SCREEN_HA_AUTO_H

#include "ha_config.h"
#include "lvgl/lvgl.h"
#include "ui_helpers.h"

typedef struct screen
{
    lv_obj_t *page_obj;
    lv_obj_t *ha_wifi_btn;
    lv_obj_t *ha_wifi_st;
    lv_obj_t *ha_time;
    lv_obj_t *label;
} screen_t;

//  sensor struct
typedef struct
{
    lv_obj_t *btn;   // main item
    lv_obj_t *logo;  // icon for sensor
    lv_obj_t *label; // label for sensor
    lv_obj_t *data;  // data label for sensor
    lv_obj_t *unit;  // unit label for sensor
    char *ha_key;    // ha key
} ha_sensor_t;

//  switch struct
typedef struct
{
    lv_obj_t *btn;        // main item
    lv_obj_t *img;        // icon for button switch
    lv_obj_t *label;      // label for switch
    lv_obj_t *unit;       // unit label for slider
    lv_obj_t *data_label; // data label for arc and slider
    lv_obj_t *data;       // toogle button or arc_data or slider
    int type;             // 0 - button, 1 - toggle, 2 - slider, 3 - arc
    lv_obj_t *page;       // parent
    char ha_key[100];     // ha key
} ha_switch_t;

// screen_t **screens;
extern screen_t *screens;
extern int screen_count;

// global array of sensors
extern ha_sensor_t *all_sensors;
extern int all_sensors_count;

// global array of switches
extern ha_switch_t *all_switches;
extern int all_switches_count;

// Function to init pages based on the config
void ui_ha_init(void);

extern char buffer[128];

#endif