#include "bsp_board.h"
#include "esp_event.h"
#include "esp_event_base.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lv_port.h"

#include "./model/indicator_ha_config.h"
#include "indicator_model.h"
#include "indicator_view.h"
// #include "indicator_controller.h"

static const char *TAG = "app_main";

#define VERSION "Yoo-v2.0.0"

#define SENSECAP "\n\
   _____                      _________    ____         \n\
  / ___/___  ____  ________  / ____/   |  / __ \\       \n\
  \\__ \\/ _ \\/ __ \\/ ___/ _ \\/ /   / /| | / /_/ /   \n\
 ___/ /  __/ / / (__  )  __/ /___/ ___ |/ ____/         \n\
/____/\\___/_/ /_/____/\\___/\\____/_/  |_/_/           \n\
--------------------------------------------------------\n\
 Version: %s %s %s\n\
--------------------------------------------------------\n\
"

ESP_EVENT_DEFINE_BASE(VIEW_EVENT_BASE);
esp_event_loop_handle_t view_event_handle;

char buffer[128]; /* Make sure buffer is enough for `sprintf` */

void app_main(void)
{
    ESP_LOGI("", SENSECAP, VERSION, __DATE__, __TIME__);

    ESP_ERROR_CHECK(bsp_board_init());
    lv_port_init();

    esp_event_loop_args_t view_event_task_args = {
        .queue_size = 10,
        .task_name = "view_event_task",
        .task_priority = uxTaskPriorityGet(NULL),
        .task_stack_size = 10240,
        .task_core_id = tskNO_AFFINITY};

    ESP_ERROR_CHECK(esp_event_loop_create(&view_event_task_args, &view_event_handle));

    // sprintf(buffer, "   Biggest /     Free /    Total\n"
    //                 "\t  DRAM : [%8d / %8d / %8d]\n"
    //                 "\t PSRAM : [%8d / %8d / %8d]",
    //         heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_total_size(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM),
    //         heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
    //         heap_caps_get_total_size(MALLOC_CAP_SPIRAM));
    // ESP_LOGI("MEM-01", "%s", buffer);

    indicator_storage_init();
    // Start the communication with the RP2040
    indicator_sensor_init();

    // sprintf(buffer, "   Biggest /     Free /    Total\n"
    //                 "\t  DRAM : [%8d / %8d / %8d]\n"
    //                 "\t PSRAM : [%8d / %8d / %8d]",
    //         heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_total_size(MALLOC_CAP_INTERNAL),
    //         heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM),
    //         heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
    //         heap_caps_get_total_size(MALLOC_CAP_SPIRAM));
    // ESP_LOGI("MEM-02", "%s", buffer);

    bool UI_init_flag = false;
    
    while (1)
    {
        // chek if the configiguration is ready
        if (UI_init_flag == false && config_flag == CONF_READY)
        {
            ESP_LOGI("app_main", "conf ready, we can init UI");
            lv_port_sem_take();
            indicator_view_init();
            lv_port_sem_give();
            // Init MQTT
            // indicator_ha_init();
            indicator_model_init();

            indicator_controller_init();

            UI_init_flag = true;
        }

        // sprintf(buffer, "   Biggest /     Free /    Total\n"
        //                 "\t  DRAM : [%8d / %8d / %8d]\n"
        //                 "\t PSRAM : [%8d / %8d / %8d]",
        //         heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL),
        //         heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
        //         heap_caps_get_total_size(MALLOC_CAP_INTERNAL),
        //         heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM),
        //         heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
        //         heap_caps_get_total_size(MALLOC_CAP_SPIRAM));
        // ESP_LOGI("MEM", "%s", buffer);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
