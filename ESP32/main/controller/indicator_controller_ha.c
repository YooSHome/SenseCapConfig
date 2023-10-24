#include "indicator_controller_ha.h"
#include "lvgl.h"
#include "ui.h"

#include "../model/indicator_ha_config.h"
#include "../ui/screens/ui_screen_ha_auto.h"
#include "../ui/screens/ui_screen_ha_templates.h"

#include "indicator_view.h"

#include "ui_helpers.h"
#include <sys/time.h>
#include <time.h>

/* The above code is written in the C programming language. It declares a static constant character
pointer variable named "TAG" and initializes it with the value "controller-ha". The purpose of this
code is not clear without any additional context. */
static const char *TAG = "controller-ha";

/**
 * The function `ui_event_screen_ha` handles gesture events and changes the screen accordingly.
 *
 * @param e The parameter "e" is a pointer to an lv_event_t structure, which contains information about
 * the event that occurred.
 */
void ui_event_screen_ha(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);

    if (event_code == LV_EVENT_GESTURE)
    {
        int *index = e->user_data;

        ESP_LOGI(TAG, "ui_event_screen_ha: index %p", index);

        if (index == NULL)
        {
            // ESP_LOGE(TAG, "ui_event_screen_ha: index is NULL");
            return;
        }
        int screen_index = *index;
        // ESP_LOGI(TAG, "ui_event_screen_ha: screen_index %d", screen_index);

        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) // next screen
        {

            if (screen_index == screen_count - 1)
            {
                // go to settings
                _ui_screen_change(ui_screen_setting, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0);
            }
            else
            {
                // next screen from the dynamic screens
                _ui_screen_change(screens[screen_index + 1].page_obj, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0);
            }
        }
        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) // Previous
        {
            if (screen_index == 0)
            {
                // go to sensor
                _ui_screen_change(ui_screen_sensor, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0);
            }
            else
            {
                // previous screen from the dynamic screens
                _ui_screen_change(screens[screen_index - 1].page_obj, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0);
            }
        }
        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP)
        {
            _ui_screen_change(ui_screen_time, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0);
        }
    }
}

/**
 * The function `ui_event_switch_slider` handles the event when a switch slider is changed and posts an
 * event with the switch index and value.
 *
 * @param e The parameter `e` is a pointer to an `lv_event_t` structure, which represents the event
 * that occurred.
 *
 * @return The function does not return any value.
 */
void ui_event_switch_slider(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t *cur_screen = lv_scr_act();
    int *index = e->user_data;

    if (event_code == LV_EVENT_VALUE_CHANGED && cur_screen == all_switches[*index].page)
    {
        ESP_LOGI(TAG, "ui_event_switch_slider: index %p", index);
        ESP_LOGI(TAG, "ui_event_switch_slider: index %d", *index);
        ESP_LOGI(TAG, "ui_event_switch_slider: event_code %d", event_code);

        int32_t value = lv_slider_get_value(all_switches[*index].data);
        struct view_data_ha_switch_data switch_data;
        switch_data.index = *index;
        // switch_data.key = all_switches[*index].ha_key;
        switch_data.value = value;
        esp_event_post_to(view_event_handle, VIEW_EVENT_BASE, VIEW_EVENT_HA_SWITCH_ST, &switch_data, sizeof(switch_data), portMAX_DELAY);
    }
}

/**
 * The function `ui_event_switch` handles events related to switches in a user interface.
 *
 * @param e The parameter `e` is a pointer to an `lv_event_t` structure, which represents an event in
 * the LittlevGL library.
 *
 * @return The function does not return any value.
 */
void ui_event_switch_button(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t *cur_screen = lv_scr_act();
    int *index = e->user_data;

    if (event_code == LV_EVENT_CLICKED && cur_screen == all_switches[*index].page)
    {
        ESP_LOGI(TAG, "ui_event_switch: index %p", index);
        ESP_LOGI(TAG, "ui_event_switch: index %d", *index);
        ESP_LOGI(TAG, "ui_event_switch: event_code %d", event_code);

        struct view_data_ha_switch_data switch_data;
        switch_data.index = *index;
        // switch_data.key = all_switches[*index].ha_key;
        if (lv_obj_has_state(all_switches[*index].btn, LV_STATE_CHECKED))
        {
            switch_data.value = 1;
            lv_img_set_src(all_switches[*index].img, &ui_img_ic_switch2_on_png); // TODO: work on the image size based on switch size
        }
        else
        {
            switch_data.value = 0;
            lv_img_set_src(all_switches[*index].img, &ui_img_ic_switch2_off_png); // TODO: work on the image size based on switch size
        }
        ESP_LOGI(TAG, " switch %d: %d", switch_data.index, switch_data.value);
        esp_event_post_to(view_event_handle, VIEW_EVENT_BASE, VIEW_EVENT_HA_SWITCH_ST, &switch_data, sizeof(switch_data), portMAX_DELAY);
    }
}

/**
 * The function `ui_event_switch_arc` handles the LV_EVENT_VALUE_CHANGED event for a specific arc
 * object, updates a label with the new value, and posts an event with the new value to a view event
 * handle.
 *
 * @param e The parameter "e" is a pointer to an lv_event_t structure, which contains information about
 * the event that occurred.
 */
void ui_event_switch_arc(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t *cur_screen = lv_scr_act();
    int *index = e->user_data;

    if (event_code == LV_EVENT_VALUE_CHANGED && cur_screen == all_switches[*index].page)
    {
        ESP_LOGI(TAG, "ui_event_switch_arc: index %p", index);
        ESP_LOGI(TAG, "ui_event_switch_arc: index %d", *index);
        ESP_LOGI(TAG, "ui_event_switch_arc: event_code %d", event_code);

        int32_t value = lv_arc_get_value(all_switches[*index].data);
        char buf[16];
        sprintf(buf, "%d", value);
        lv_label_set_text(all_switches[*index].data, buf);

        struct view_data_ha_switch_data switch_data;
        switch_data.index = *index;
        // switch_data.key = all_switches[*index].ha_key;
        switch_data.value = value;
        esp_event_post_to(view_event_handle, VIEW_EVENT_BASE, VIEW_EVENT_HA_SWITCH_ST, &switch_data, sizeof(switch_data), portMAX_DELAY);
    }
}

/**
 * The function `ui_event_switch7` handles a UI event for a switch widget and posts an event with the
 * switch data.
 *
 * @param e The parameter "e" is a pointer to an lv_event_t structure, which contains information about
 * the event that occurred.
 */
void ui_event_switch_toggle(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t *cur_screen = lv_scr_act();
    int *index = e->user_data;

    if (event_code == LV_EVENT_CLICKED && cur_screen == all_switches[*index].page)
    {
        struct view_data_ha_switch_data switch_data;
        switch_data.index = *index;
        // switch_data.key = all_switches[*index].ha_key;

        if (lv_obj_has_state(target, LV_STATE_CHECKED))
        {
            switch_data.value = 1;
            lv_obj_add_state(all_switches[*index].data, LV_STATE_CHECKED);
            lv_obj_add_state(all_switches[*index].btn, LV_STATE_CHECKED);
        }
        else
        {
            switch_data.value = 0;
            lv_obj_clear_state(all_switches[*index].data, LV_STATE_CHECKED);
            lv_obj_clear_state(all_switches[*index].btn, LV_STATE_CHECKED);
        }
        esp_event_post_to(view_event_handle, VIEW_EVENT_BASE, VIEW_EVENT_HA_SWITCH_ST, &switch_data, sizeof(switch_data), portMAX_DELAY);
    }
}

/**
 * The function `ui_event_ha_wifi_btn` handles the LV_EVENT_CLICKED event for a button in a user
 * interface, and changes the screen to the wifi screen.
 *
 * @param e The parameter "e" is a pointer to an lv_event_t structure, which represents the event that
 * occurred. It contains information about the event, such as the event code and the target object that
 * triggered the event.
 */
void ui_event_ha_wifi_btn(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);

    // find the screen index
    int screen_index = -1;
    int i;
    for (i = 0; i < screen_count; i++)
    {
        if (target == screens[i].page_obj)
        {
            screen_index = i;
            break;
        }
    }

    if (screen_index == -1)
    {
        ESP_LOGE(TAG, "Screen not found");
        return;
    }

    if (event_code == LV_EVENT_CLICKED)
    {
        ui_screen_last = screens[screen_index].page_obj;
        _ui_screen_change(ui_screen_wifi, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 200, 0);
    }
}

/**
 * The function `ui_event_ha_init` initializes event callbacks for various UI elements.
 */
void ui_event_ha_init(void)
{
    // create handle for all dynamic screens
    for (int i = 0; i < screen_count; i++)
    {
        int *index = malloc(sizeof(int));
        *index = i;
        ESP_LOGI(TAG, "ui_event_ha_init: i %d ,index %p", i, index);

        lv_obj_add_event_cb(screens[i].page_obj, ui_event_screen_ha, LV_EVENT_ALL, index);
    }

    // replace by generic fucntion by type of switch
    // loop switches in config __g_ha_config
    for (int i = 0; i < all_switches_count; i++)
    {
        ESP_LOGI(TAG, "ui_event_ha_init: i %d", i);
        ESP_LOGI(TAG, "ui_event_ha_init: type %d", all_switches[i].type);

        switch (all_switches[i].type)
        {
        case IHAC_SWITCH_TYPE_TOGGLE:
        {
            int *index = malloc(sizeof(int));
            *index = i;
            lv_obj_add_event_cb(all_switches[i].data, ui_event_switch_toggle, LV_EVENT_ALL, index);
            break;
        }
        case IHAC_SWITCH_TYPE_SLIDER:
        {
            int *index = malloc(sizeof(int));
            *index = i;
            lv_obj_add_event_cb(all_switches[i].data, ui_event_switch_slider, LV_EVENT_VALUE_CHANGED, index);
            break;
        }
        case IHAC_SWITCH_TYPE_ARC:
        {
            int *index = malloc(sizeof(int));
            *index = i;
            lv_obj_add_event_cb(all_switches[i].data, ui_event_switch_arc, LV_EVENT_ALL, index);
            break;
        }
        case IHAC_SWITCH_TYPE_BUTTON:
        {
            int *index = malloc(sizeof(int));
            *index = i;
            lv_obj_add_event_cb(all_switches[i].btn, ui_event_switch_button, LV_EVENT_ALL, index);
            break;
        }
        default:
            break;
        }
    }

    // wifi button for each page in screens array
    for (int i = 0; i < screen_count; i++)
    {
        // lv_obj_add_event_cb(screens[i].wifi_btn, ui_event_ha_wifi_btn, LV_EVENT_ALL, NULL);
        // TODO: create the handler function
    }

    // lv_obj_add_event_cb(ui_ha_data_wifi_btn, ui_event_ha_data_wifi_btn, LV_EVENT_ALL, NULL);
    // lv_obj_add_event_cb(ui_ha_wifi_btn, ui_event_ha_wifi_btn, LV_EVENT_ALL, NULL);
    // lv_obj_add_event_cb(ui_ha_ctrl_wifi_btn, ui_event_ha_ctrl_wifi_btn, LV_EVENT_ALL, NULL);
}

/**
 * The function initializes the indicator controller by calling the ui_event_ha_init() function.
 *
 * @return 0.
 */
int indicator_controller_ha_init(void)
{
    ui_event_ha_init();
    return 0;
}