#include "../../model/indicator_ha_config.h"
#include "../ui.h"
#include "ui_helpers.h"
#include "ui_screen_ha_templates.h"

#define DEBUG_UI 0
static const char *TAG = "HA_UI_AUTO";

// screen_t **screens;
screen_t *screens;
int screen_count = 0;

// global array of sensors
ha_sensor_t *all_sensors;
int all_sensors_count = 0;

// global array of switches
ha_switch_t *all_switches;
int all_switches_count = 0;

// Function to init pages based on the config
void ui_ha_init(void)
{
    // sprintf(buffer, "   Biggest /     Free /    Total\n"
    //                 "\t  DRAM : [%8d / %8d / %8d]\n"
    //                 "\t PSRAM : [%8d / %8d / %8d]",
    //         heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_total_size(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT),
    //         heap_caps_get_free_size(MALLOC_CAP_DEFAULT),
    //         heap_caps_get_total_size(MALLOC_CAP_DEFAULT));
    // ESP_LOGI("MEM-3", "%s", buffer);
    init_templates();
    // sprintf(buffer, "   Biggest /     Free /    Total\n"
    //                 "\t  DRAM : [%8d / %8d / %8d]\n"
    //                 "\t PSRAM : [%8d / %8d / %8d]",
    //         heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_total_size(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT),
    //         heap_caps_get_free_size(MALLOC_CAP_DEFAULT),
    //         heap_caps_get_total_size(MALLOC_CAP_DEFAULT));
    // ESP_LOGI("MEM-31", "%s", buffer);
#if DEBUG_UI
    ESP_LOGI(TAG, "ui init: Start (count: %d)", __g_ha_config.page_count);
#endif
    // allocate screens based on number of pages
    screens = malloc(__g_ha_config.page_count * sizeof(screen_t));

    // calculate the number of sensors
    int sensor_count = 0;
    int switch_count = 0;
    for (int i = 0; i < __g_ha_config.page_count; i++)
    {
#if DEBUG_UI
        ESP_LOGI(TAG,
                 "ui init: Page id: %d - sensors: %d - switches: %d",
                 i,
                 __g_ha_config.pages[i].sensor_count,
                 __g_ha_config.pages[i].switch_count);
#endif
        sensor_count += __g_ha_config.pages[i].sensor_count;
        switch_count += __g_ha_config.pages[i].switch_count;
    }

    // allocate memory for sensors
    all_sensors = malloc(sensor_count * sizeof(ha_sensor_t));
    // allocate memory for switches
    all_switches = malloc(switch_count * sizeof(ha_switch_t));

    // sprintf(buffer, "   Biggest /     Free /    Total\n"
    //                 "\t  DRAM : [%8d / %8d / %8d]\n"
    //                 "\t PSRAM : [%8d / %8d / %8d]",
    //         heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_total_size(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT),
    //         heap_caps_get_free_size(MALLOC_CAP_DEFAULT),
    //         heap_caps_get_total_size(MALLOC_CAP_DEFAULT));
    // ESP_LOGI("MEM-32", "%s", buffer);

#if DEBUG_UI
    ESP_LOGI(TAG, "ui init: Screen count: %d", __g_ha_config.page_count);
    ESP_LOGI(TAG, "ui init: Sensor count: %d", sensor_count);
    ESP_LOGI(TAG, "ui init: Switch count: %d", switch_count);
#endif

    // Loop through all pages
    for (int i = 0; i < __g_ha_config.page_count; i++)
    {
        // Get page
        ha_config_page_t page = __g_ha_config.pages[i];

#if DEBUG_UI
        ESP_LOGI(TAG, "ui init: Create page name: %s", page.name);
        ESP_LOGI(TAG, "ui init: Create page label: %s", page.label);
        ESP_LOGI(TAG, "ui init: Create page type: %d", page.type);
        ESP_LOGI(TAG, "ui init: Create page sensor count: %d", page.sensor_count);
        ESP_LOGI(TAG, "ui init: Create page switch count: %d", page.switch_count);
#endif
        // sprintf(buffer, "   Biggest /     Free /    Total\n"
        //                 "\t  DRAM : [%8d / %8d / %8d]\n"
        //                 "\tDefault: [%8d / %8d / %8d]",
        //         heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL),
        //         heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
        //         heap_caps_get_total_size(MALLOC_CAP_INTERNAL),
        //         heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT),
        //         heap_caps_get_free_size(MALLOC_CAP_DEFAULT),
        //         heap_caps_get_total_size(MALLOC_CAP_DEFAULT));
        // ESP_LOGI("MEM-33", "%s", buffer);
        // Create Page
        page_create(i, page.name, page.label);

        // Loop through all sensors in the page
        for (int j = 0; j < page.sensor_count; j++)
        {
            // Get sensor
            ha_config_page_sensor_t *sensor = &(page.sensors[j]);

#if DEBUG_UI
            ESP_LOGI(TAG, "ui init: Create sensor name: %s", sensor->name);
            ESP_LOGI(TAG, "ui init: Create sensor label: %s", sensor->label);
            ESP_LOGI(TAG, "ui init: Create sensor unit: %s", sensor->unit);
            ESP_LOGI(TAG, "ui init: Create sensor icon: %s", sensor->icon);
            ESP_LOGI(TAG, "ui init: Create sensor size: %d", sensor->size);
            ESP_LOGI(TAG, "ui init: Create sensor key: %s", sensor->ha_key);
#endif

            int x = 0;
            int y = 0;
            // Call function to get the x, y based on page type
            getXYfromPageType(page.type, sensor->x - 1, sensor->y - 1, &x, &y);

            // Create sensor
            sensor_create(screens[i].page_obj, sensor->name, sensor->label, sensor->unit, sensor->icon, sensor->ha_key, sensor->size, x, y);
        }

        // Loop through all switches in the page
        for (int j = 0; j < page.switch_count; j++)
        {
            // Get switch
            ha_config_page_switch_t *switch_ = &(page.switches[j]);
#if DEBUG_UI
            ESP_LOGI(TAG, "ui init: Create switch name: %s", switch_->name);
#endif
            int x = 0;
            int y = 0;
            // Call function to get the x, y based on page type
            getXYfromPageType(page.type, switch_->x - 1, switch_->y - 1, &x, &y);

            // Create switch
            switch_create(screens[i].page_obj, switch_->name, switch_->label, switch_->icon, switch_->size, switch_->ha_key, switch_->unit, switch_->type, x, y);
        }

        if (screens[i].page_obj == NULL)
        {
            ESP_LOGE(TAG, "ui init: Screen is null");
        }
        else
        {
#if DEBUG_UI
            ESP_LOGI(TAG, "creat_scrolldots: %d\n", screens[i].page_obj);
#endif
            creat_scrolldots(screens[i].page_obj, i + 2, __g_ha_config.page_count + 3); // first dynamic page is 2, first one is clock page
        }
    }
}

// Function to get x, y based on page type
void getXYfromPageType(int type, int sensorx, int sensory, int *x, int *y)
{
    switch (type)
    {
    case IHAC_PAGE_TYPE_1x1:
        *x = 27;
        *y = 96;
        break;
    case IHAC_PAGE_TYPE_1x2:
        *x = 27;
        *y = 96 + (sensory * 164) + (sensory * 8);
        break;
    case IHAC_PAGE_TYPE_1x3:
        *x = 27;
        *y = 96 + (sensory * 105) + (sensory * 8);
        break;
    case IHAC_PAGE_TYPE_1x4:
        *x = 27;
        *y = 96 + (sensory * 78) + (sensory * 8);
        break;
    case IHAC_PAGE_TYPE_2x1:
        *x = 27 + (sensorx * 214) + (sensorx * 8);
        *y = 96;
        break;
    case IHAC_PAGE_TYPE_2x2:
        *x = 27 + (sensorx * 214) + (sensorx * 8);
        *y = 96 + (sensory * 164) + (sensory * 8);
        break;
    case IHAC_PAGE_TYPE_2x3:
        *x = 27 + (sensorx * 214) + (sensorx * 8);
        *y = 96 + (sensory * 105) + (sensory * 8);
        break;
    case IHAC_PAGE_TYPE_2x4:
        *x = 27 + (sensorx * 214) + (sensorx * 8);
        *y = 96 + (sensory * 78) + (sensory * 8);
        break;
    }

#if DEBUG_UI
    ESP_LOGI(TAG, "ui init: sensor x y : %d, %d", sensorx, sensory);
    ESP_LOGI(TAG, "ui init: case, x, y : %d, %d, %d", type, *x, *y);
#endif
}

// Function to create a page
void page_create(int index, char *name, char *label)
{
    // increment screen counter
    screen_count++;

    screens[index].page_obj = lv_obj_create(NULL);
    ESP_LOGI(TAG, "page_create: %d (index : %d)", screens[index].page_obj, index);

    lv_obj_clear_flag(screens[index].page_obj, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(screens[index].page_obj, lv_color_hex(0x1C1C1C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(screens[index].page_obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    screens[index].ha_wifi_btn = lv_btn_create(screens[index].page_obj);
    // screens[index].ha_wifi_btn = lv_btn_create(screens[index].page_obj);
    lv_obj_set_width(screens[index].ha_wifi_btn, 60);
    lv_obj_set_height(screens[index].ha_wifi_btn, 60);
    lv_obj_set_x(screens[index].ha_wifi_btn, -10);
    lv_obj_set_y(screens[index].ha_wifi_btn, 10);
    lv_obj_set_align(screens[index].ha_wifi_btn, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(screens[index].ha_wifi_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(screens[index].ha_wifi_btn, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(screens[index].ha_wifi_btn, lv_color_hex(0x1C1C1C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(screens[index].ha_wifi_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(screens[index].ha_wifi_btn, lv_color_hex(0x1C1C1C), LV_PART_MAIN | LV_STATE_DEFAULT);

    screens[index].ha_wifi_st = lv_img_create(screens[index].ha_wifi_btn);
    // ui_ha_wifi_st = lv_img_create(screens[index].ha_wifi_btn);
    lv_img_set_src(screens[index].ha_wifi_st, &ui_img_wifi_disconet_png);
    lv_obj_set_width(screens[index].ha_wifi_st, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(screens[index].ha_wifi_st, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(screens[index].ha_wifi_st, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(screens[index].ha_wifi_st, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(screens[index].ha_wifi_st, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    screens[index].ha_time = lv_label_create(screens[index].page_obj);
    // screens[index].ha_time = lv_label_create(screens[index].page_obj);
    lv_obj_set_width(screens[index].ha_time, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(screens[index].ha_time, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(screens[index].ha_time, 30);
    lv_obj_set_y(screens[index].ha_time, 20);
    lv_label_set_text(screens[index].ha_time, "21:20");
    lv_obj_set_style_text_font(screens[index].ha_time, &ui_font_font1, LV_PART_MAIN | LV_STATE_DEFAULT);

    screens[index].label = lv_label_create(screens[index].page_obj);
    // screens[index].label = lv_label_create(screens[index].page_obj);
    lv_obj_set_width(screens[index].label, 316);
    lv_obj_set_height(screens[index].label, 38);
    lv_obj_set_x(screens[index].label, 82);
    lv_obj_set_y(screens[index].label, 58);
    lv_label_set_text(screens[index].label, label);
    lv_obj_set_style_text_color(screens[index].label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(screens[index].label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screens[index].label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(screens[index].label, &ui_font_font0, LV_PART_MAIN | LV_STATE_DEFAULT);
}

// Function to create a sensor
void sensor_create(lv_obj_t *parent, char *name, char *label, char *unit, char *icon, char *key, int size, int x, int y)
{
    // sensor counter
    int i = all_sensors_count;

    // increment sensor counter
    all_sensors_count++;

    // allocate memory for the ha key
    all_sensors[i].ha_key = malloc(strlen(key) + 1);
    // copy the ha key
    strcpy(all_sensors[i].ha_key, key);

    ESP_LOGI(TAG, "sensor_create: %s - %s", key, all_sensors[i].ha_key);
    ESP_LOGI(TAG, "sensor_create: size: %d", size);
    ESP_LOGI(TAG, "sensor_create: x: %d", x);
    ESP_LOGI(TAG, "sensor_create: y: %d", y);
    ESP_LOGI(TAG, "sensor_create: name: %s", name);
    ESP_LOGI(TAG, "sensor_create: label: %s", label);
    ESP_LOGI(TAG, "sensor_create: unit: %s", unit);
    ESP_LOGI(TAG, "sensor_create: icon: %s", icon);

    create_sensor_button(size, parent, &all_sensors[i], x, y, 0xECBF41, name, label, unit, icon);
}

// function to create a switch
void switch_create(lv_obj_t *parent, char *name, char *label, char *icon, int size, char *ha_key, char *unit, int type, int x, int y)
{
    // switch counter
    int i = all_switches_count;

    // increment switch counter
    all_switches_count++;

    // store the page in the switch struct
    all_switches[i].page = parent;
    // store the ha key
    strcpy(all_switches[i].ha_key, ha_key);

    ESP_LOGI(TAG, "switch_create: %s - %s", ha_key, all_switches[i].ha_key);
    ESP_LOGI(TAG, "switch_create: type: %d", type);

    // create switch based on type
    switch (type)
    {
    case IHAC_SWITCH_TYPE_BUTTON:
        ESP_LOGI(TAG, "switch_create: create_switch_button");
        create_switch_button(size, parent, &all_switches[i], x, y, label);
        break;
    case IHAC_SWITCH_TYPE_TOGGLE:
        ESP_LOGI(TAG, "switch_create: create_switch_toggle");
        create_switch_toggle(size, parent, &all_switches[i], x, y, label);
        break;
    case IHAC_SWITCH_TYPE_SLIDER:
        ESP_LOGI(TAG, "switch_create: create_switch_slider");
        create_switch_slider(size, parent, &all_switches[i], x, y, label, unit);
        break;
    case IHAC_SWITCH_TYPE_ARC:
        ESP_LOGI(TAG, "switch_create: create_switch_arc");
        create_switch_arc(size, parent, &all_switches[i], x, y, label, unit);
        break;
    default:
        break;
    }
}
