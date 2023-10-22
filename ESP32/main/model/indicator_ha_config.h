#ifndef INDICATOR_HA_CONF_H
#define INDICATOR_HA_CONF_H

#include "config.h"
#include "view_data.h"

// Define struct for sensors in a page
typedef struct ha_config_page_sensor
{
    char name[32];
    char label[32];
    char unit[32];
    char icon[32];
    char ha_key[100];
    int size; // enum ha_config_page_item_size
    int x;
    int y;
} ha_config_page_sensor_t;

// Define struct for switches in a page
typedef struct ha_config_page_switch
{
    char name[32];
    char label[32];
    char icon[32];
    char unit[32];
    char ha_key[100];
    int size; // enum ha_config_page_item_size
    int type; // enum ha_config_page_switch_type
    int x;
    int y;
} ha_config_page_switch_t;

// Enum for item size
enum ha_config_page_item_size
{
    IHAC_ITEM_SIZE_SMALL,
    IHAC_ITEM_SIZE_MEDIUM,
    IHAC_ITEM_SIZE_LARGE
};

// Enum for switch type
enum ha_config_page_switch_type
{
    IHAC_SWITCH_TYPE_TOGGLE,
    IHAC_SWITCH_TYPE_SLIDER,
    IHAC_SWITCH_TYPE_BUTTON,
    IHAC_SWITCH_TYPE_ARC
};

// Define enum for the page type
enum ha_config_page_type
{
    IHAC_PAGE_TYPE_1x1,
    IHAC_PAGE_TYPE_1x2,
    IHAC_PAGE_TYPE_1x3,
    IHAC_PAGE_TYPE_1x4,
    IHAC_PAGE_TYPE_2x1,
    IHAC_PAGE_TYPE_2x2,
    IHAC_PAGE_TYPE_2x3,
    IHAC_PAGE_TYPE_2x4,
};

// Config file status (RP2040 -> ESP32)
enum config_file_status
{
    CONF_NONE = 0,
    CONF_STARTED,
    CONF_COMPLETED,
    CONF_READY
};

typedef struct ha_config_page
{
    char name[32];
    char label[32];
    int type; // enum ha_config_page_type

    ha_config_page_sensor_t sensors[16]; // Max 16 sensors per page
    int sensor_count;

    ha_config_page_switch_t switches[16]; // Max 16 switches per page
    int switch_count;

} ha_config_page_t;

typedef struct ha_config
{
    char *url;
    char *username;
    char *password;

    ha_config_page_t *pages;
    int page_count;

} ha_config_t;

// Extern global variable
extern ha_config_t __g_ha_config;
extern int config_flag;

void ha_config_read(const char *filename);
void store_config(char *json);
void concat_config(char *json, int len);
void config_read();

#endif
