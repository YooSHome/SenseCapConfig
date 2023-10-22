#include "cJSON.h"
#include "indicator_ha.h"
#include "nvs.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "lwip/dns.h"
#include "lwip/err.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"

#include "ha_config.h"
#include "mqtt_client.h"

#include "indicator_ha_config.h"

static const char *TAG = "sensor-model";
#define DEBUG_SENSOR 0

// Declare global variable for configuration
ha_config_t __g_ha_config;

// flag: Config file readyness
int config_flag = CONF_NONE;

// JSON String
char *config_json = NULL;

// function to process json string and store results in __g_ha_config
void config_read()
{
    // ESP_LOGI(TAG, "%s", config_json);

    esp_err_t err;
    cJSON *config = NULL;
    config = cJSON_Parse(config_json);

    if (config)
    {
        // Read the URL
        cJSON *cjson_item = cJSON_GetObjectItem(config, "url");
        if (cjson_item != NULL && cjson_item->valuestring != NULL)
        {
            // allocate mem for URL
            __g_ha_config.url = malloc(strlen(cjson_item->valuestring) + 1);
            strcpy(__g_ha_config.url, cjson_item->valuestring);
        }

        // Read username
        cjson_item = cJSON_GetObjectItem(config, "username");
        if (cjson_item != NULL && cjson_item->valuestring != NULL)
        {
            // allocate mem for username
            __g_ha_config.username = malloc(strlen(cjson_item->valuestring) + 1);
            strcpy(__g_ha_config.username, cjson_item->valuestring);
        }

        // Read password
        cjson_item = cJSON_GetObjectItem(config, "password");
        if (cjson_item != NULL && cjson_item->valuestring != NULL)
        {
            // allocate mem for password
            __g_ha_config.password = malloc(strlen(cjson_item->valuestring) + 1);
            strcpy(__g_ha_config.password, cjson_item->valuestring);
        }

        // Parse pages in Json
        cJSON *cjson_pages = cJSON_GetObjectItem(config, "pages");
        if (cjson_pages != NULL && cjson_pages->child != NULL)
        {
            // allocate mem for pages
            __g_ha_config.pages = malloc(sizeof(ha_config_page_t) * cJSON_GetArraySize(cjson_pages));
            __g_ha_config.page_count = cJSON_GetArraySize(cjson_pages);

            int i = 0;
            const cJSON *cjson_page = NULL;
            ha_config_page_t *page = NULL;
            cJSON_ArrayForEach(cjson_page, cjson_pages)
            {
                page = &__g_ha_config.pages[i++];
                page->sensor_count = 0;
                page->switch_count = 0;

                cjson_item = cJSON_GetObjectItem(cjson_page, "name");
                if (cjson_item != NULL && cjson_item->valuestring != NULL)
                {
                    strcpy(page->name, cjson_item->valuestring);
                }
                cjson_item = cJSON_GetObjectItem(cjson_page, "label");
                if (cjson_item != NULL && cjson_item->valuestring != NULL)
                {
                    strcpy(page->label, cjson_item->valuestring);
                }
                // Convert type from string to enum value (1x1, 2x1, etc)
                cJSON *cjson_item_type = cJSON_GetObjectItem(cjson_page, "type");
                if (cjson_item_type != NULL && cjson_item_type->valuestring != NULL)
                {
                    if (strcmp(cjson_item_type->valuestring, "1x1") == 0)
                    {
                        page->type = IHAC_PAGE_TYPE_1x1;
                    }
                    else if (strcmp(cjson_item_type->valuestring, "1x2") == 0)
                    {
                        page->type = IHAC_PAGE_TYPE_1x2;
                    }
                    else if (strcmp(cjson_item_type->valuestring, "1x3") == 0)
                    {
                        page->type = IHAC_PAGE_TYPE_1x3;
                    }
                    else if (strcmp(cjson_item_type->valuestring, "1x4") == 0)
                    {
                        page->type = IHAC_PAGE_TYPE_1x4;
                    }
                    else if (strcmp(cjson_item_type->valuestring, "2x1") == 0)
                    {
                        page->type = IHAC_PAGE_TYPE_2x1;
                    }
                    else if (strcmp(cjson_item_type->valuestring, "2x2") == 0)
                    {
                        page->type = IHAC_PAGE_TYPE_2x2;
                    }
                    else if (strcmp(cjson_item_type->valuestring, "2x3") == 0)
                    {
                        page->type = IHAC_PAGE_TYPE_2x3;
                    }
                    else if (strcmp(cjson_item_type->valuestring, "2x4") == 0)
                    {
                        page->type = IHAC_PAGE_TYPE_2x4;
                    }
                }

                // Parse Sensors in Json
                cJSON *cjson_item_sensors = cJSON_GetObjectItem(cjson_page, "sensors");
                if (cjson_item_sensors != NULL && cjson_item_sensors->child != NULL)
                {
                    int j = 0;
                    const cJSON *cjson_item_sensor = NULL;
                    ha_config_page_sensor_t *sensor = NULL;
                    cJSON_ArrayForEach(cjson_item_sensor, cjson_item_sensors)
                    {
                        sensor = &page->sensors[j++];
                        cjson_item = cJSON_GetObjectItem(cjson_item_sensor, "name");
                        if (cjson_item != NULL && cjson_item->valuestring != NULL)
                        {
                            strcpy(sensor->name, cjson_item->valuestring);
                        }
                        cjson_item = cJSON_GetObjectItem(cjson_item_sensor, "label");
                        if (cjson_item != NULL && cjson_item->valuestring != NULL)
                        {
                            strcpy(sensor->label, cjson_item->valuestring);
                        }
                        cjson_item = cJSON_GetObjectItem(cjson_item_sensor, "unit");
                        if (cjson_item != NULL && cjson_item->valuestring != NULL)
                        {
                            strcpy(sensor->unit, cjson_item->valuestring);
                        }
                        cjson_item = cJSON_GetObjectItem(cjson_item_sensor, "key");
                        if (cjson_item != NULL && cjson_item->valuestring != NULL)
                        {
                            strcpy(sensor->ha_key, cjson_item->valuestring);
                        }

                        // get sensor x and y values. Convert string to int
                        cJSON *cjson_x = cJSON_GetObjectItem(cjson_item_sensor, "x");
                        cJSON *cjson_y = cJSON_GetObjectItem(cjson_item_sensor, "y");
                        if (cjson_x != NULL && cjson_x->valuestring != NULL)
                        {
                            sensor->x = atoi(cjson_x->valuestring);
                        }
                        if (cjson_y != NULL && cjson_y->valuestring != NULL)
                        {
                            sensor->y = atoi(cjson_y->valuestring);
                        }

                        cjson_item = cJSON_GetObjectItem(cjson_item_sensor, "icon");
                        if (cjson_item != NULL && cjson_item->valuestring != NULL)
                        {
                            strcpy(sensor->icon, cjson_item->valuestring);
                        }

                        // Convert size from string to enum value (large, medium, small)
                        cJSON *cjson_item_size = cJSON_GetObjectItem(cjson_item_sensor, "size");
                        if (cjson_item_size != NULL && cjson_item_size->valuestring != NULL)
                        {
                            if (strcmp(cjson_item_size->valuestring, "large") == 0)
                            {
                                sensor->size = IHAC_ITEM_SIZE_LARGE;
                            }
                            else if (strcmp(cjson_item_size->valuestring, "medium") == 0)
                            {
                                sensor->size = IHAC_ITEM_SIZE_MEDIUM;
                            }
                            else if (strcmp(cjson_item_size->valuestring, "small") == 0)
                            {
                                sensor->size = IHAC_ITEM_SIZE_SMALL;
                            }
                        }
                    }

                    // store number of sensors in page
                    page->sensor_count = j;
#if DEBUG_SENSOR
                    ESP_LOGI(TAG, "sensor count: %d", page->sensor_count);
#endif
                }

                // Parse Switches in Json
                cJSON *cjson_item_switches = cJSON_GetObjectItem(cjson_page, "switches");
                if (cjson_item_switches != NULL && cjson_item_switches->child != NULL)
                {
                    int j = 0;
                    const cJSON *cjson_item_switch = NULL;
                    ha_config_page_switch_t *switchItem = NULL;
                    cJSON_ArrayForEach(cjson_item_switch, cjson_item_switches)
                    {
                        switchItem = &page->switches[j++];

                        cjson_item = cJSON_GetObjectItem(cjson_item_switch, "name");
                        if (cjson_item != NULL && cjson_item->valuestring != NULL)
                        {
                            strcpy(switchItem->name, cjson_item->valuestring);
                        }
                        cjson_item = cJSON_GetObjectItem(cjson_item_switch, "label");
                        if (cjson_item != NULL && cjson_item->valuestring != NULL)
                        {
                            strcpy(switchItem->label, cjson_item->valuestring);
                        }
                        cjson_item = cJSON_GetObjectItem(cjson_item_switch, "unit");
                        if (cjson_item != NULL && cjson_item->valuestring != NULL)
                        {
                            strcpy(switchItem->unit, cjson_item->valuestring);
                        }
                        
                        // Convert type from string to enum value (toggle, slider, button, dimmer)
                        cJSON *cjson_item_type = cJSON_GetObjectItem(cjson_item_switch, "type");
                        if (cjson_item_type != NULL && cjson_item_type->valuestring != NULL)
                        {
                            if (strcmp(cjson_item_type->valuestring, "toggle") == 0)
                            {
                                switchItem->type = IHAC_SWITCH_TYPE_TOGGLE;
                            }
                            else if (strcmp(cjson_item_type->valuestring, "slider") == 0)
                            {
                                switchItem->type = IHAC_SWITCH_TYPE_SLIDER;
                            }
                            else if (strcmp(cjson_item_type->valuestring, "button") == 0)
                            {
                                switchItem->type = IHAC_SWITCH_TYPE_BUTTON;
                            }
                            else if (strcmp(cjson_item_type->valuestring, "arc") == 0)
                            {
                                switchItem->type = IHAC_SWITCH_TYPE_ARC;
                            }
                        }

                        cjson_item = cJSON_GetObjectItem(cjson_item_switch, "key");
                        if (cjson_item != NULL && cjson_item->valuestring != NULL)
                        {
                            strcpy(switchItem->ha_key, cjson_item->valuestring);
                        }
                        // get switch x and y values. Convert string to int
                        cJSON *cjson_x = cJSON_GetObjectItem(cjson_item_switch, "x");
                        cJSON *cjson_y = cJSON_GetObjectItem(cjson_item_switch, "y");
                        if (cjson_x != NULL && cjson_x->valuestring != NULL)
                        {
                            switchItem->x = atoi(cjson_x->valuestring);
                        }
                        if (cjson_y != NULL && cjson_y->valuestring != NULL)
                        {
                            switchItem->y = atoi(cjson_y->valuestring);
                        }
                        
                        cjson_item = cJSON_GetObjectItem(cjson_item_switch, "icon");
                        if (cjson_item != NULL && cjson_item->valuestring != NULL)
                        {
                            strcpy(switchItem->icon, cjson_item->valuestring);
                        }

                        // Convert size from string to enum value (large, medium, small)
                        cJSON *cjson_item_size = cJSON_GetObjectItem(cjson_item_switch, "size");
                        if (cjson_item_size != NULL && cjson_item_size->valuestring != NULL)
                        {
                            if (strcmp(cjson_item_size->valuestring, "large") == 0)
                            {
                                switchItem->size = IHAC_ITEM_SIZE_LARGE;
                            }
                            else if (strcmp(cjson_item_size->valuestring, "medium") == 0)
                            {
                                switchItem->size = IHAC_ITEM_SIZE_MEDIUM;
                            }
                            else if (strcmp(cjson_item_size->valuestring, "small") == 0)
                            {
                                switchItem->size = IHAC_ITEM_SIZE_SMALL;
                            }
                        }
                    }

                    // store number of switches in page
                    page->switch_count = j;
#if DEBUG_SENSOR
                    ESP_LOGI(TAG, "switch count: %d", page->switch_count);
#endif
                }
            }
        }

        // tag flag as true
        config_flag = CONF_READY;
    }

    // free memory
    cJSON_Delete(config);

    // free config_json memory
    free(config_json);
}

// Function to store configuration to json string
void store_config(char *json)
{
    // allocate memory for 'json' string size
    config_json = malloc(strlen(json) + 1);

    // copy 'json' string to 'config_json'
    strcpy(config_json, json);
}

// function to concat string to config
void concat_config(char *json, int len)
{
    // check if 'config_json' is NULL
    if (config_json == NULL)
    {
        // allocate memory for 'config_json' string size
        config_json = malloc(len + 1);

        // copy 'json' string to 'config_json'
        strcpy(config_json, json);
    }
    else // Already exist
    {
        // allocate memory for 'config_json' string size
        config_json = realloc(config_json, strlen(config_json) + len + 1);

        // concat 'json' string to 'config_json'
        strcat(config_json, json);
    }
}

// Function to free memory allocated for 'config_json'
void free_config()
{
    free(config_json);
}