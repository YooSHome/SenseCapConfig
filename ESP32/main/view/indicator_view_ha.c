#include "indicator_view_ha.h"
#include "ui.h"

#include "../model/indicator_ha_config.h"
#include "../ui/screens/ui_screen_ha_templates.h"

static const char *TAG = "view-ha";

static void __view_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data)
{
    lv_port_sem_take();
    switch (id)
    {
    case VIEW_EVENT_HA_SENSOR:
    {
        ESP_LOGI(TAG, "event: VIEW_EVENT_HA_SENSOR");
        struct view_data_ha_sensor_data *p_data = (struct view_data_ha_sensor_data *)event_data;

        lv_label_set_text(all_sensors[p_data->index].data, p_data->value);
        break;
    }

    case VIEW_EVENT_HA_SWITCH_SET:
    {
        ESP_LOGI(TAG, "event: VIEW_EVENT_HA_SWITCH_SET");
        struct view_data_ha_switch_data *p_data = (struct view_data_ha_switch_data *)event_data;

        ESP_LOGI(TAG, "set switch %d: %d", (p_data->index) + 1, p_data->value);

        switch (all_switches[p_data->index].type)
        {
        case IHAC_SWITCH_TYPE_TOGGLE:
            if (p_data->value)
            {
                // lv_obj_add_state(all_switches[p_data->index].btn, LV_STATE_CHECKED);
                lv_obj_add_state(all_switches[p_data->index].data, LV_STATE_CHECKED);
            }
            else
            {
                // lv_obj_clear_state(all_switches[p_data->index].btn, LV_STATE_CHECKED);
                lv_obj_clear_state(all_switches[p_data->index].data, LV_STATE_CHECKED);
            }
            lv_event_send((lv_obj_t *)all_switches[p_data->index].btn, LV_EVENT_CLICKED, NULL);
            break;

        case IHAC_SWITCH_TYPE_SLIDER:
            lv_slider_set_value(all_switches[p_data->index].data, p_data->value, true); // todo check value
            lv_event_send((lv_obj_t *)all_switches[p_data->index].data, LV_EVENT_VALUE_CHANGED, NULL);
            break;

        case IHAC_SWITCH_TYPE_BUTTON:
            if (p_data->value)
            {
                lv_obj_add_state(all_switches[p_data->index].btn, LV_STATE_CHECKED);
            }
            else
            {
                lv_obj_clear_state(all_switches[p_data->index].btn, LV_STATE_CHECKED);
            }
            lv_event_send((lv_obj_t *)all_switches[p_data->index].btn, LV_EVENT_CLICKED, NULL);
            break;

        case IHAC_SWITCH_TYPE_ARC:
            lv_arc_set_value(all_switches[p_data->index].data, p_data->value); // todo check value
            lv_event_send((lv_obj_t *)all_switches[p_data->index].data, LV_EVENT_VALUE_CHANGED, NULL);
            break;

        default:
            break;
        }
        break;
    }
    default:
        break;
    }
    lv_port_sem_give();
}

int indicator_view_ha_init(void)
{
    ESP_ERROR_CHECK(esp_event_handler_instance_register_with(view_event_handle,
                                                             VIEW_EVENT_BASE, VIEW_EVENT_HA_SENSOR,
                                                             __view_event_handler, NULL, NULL));

    ESP_ERROR_CHECK(esp_event_handler_instance_register_with(view_event_handle,
                                                             VIEW_EVENT_BASE, VIEW_EVENT_HA_SWITCH_SET,
                                                             __view_event_handler, NULL, NULL));
}