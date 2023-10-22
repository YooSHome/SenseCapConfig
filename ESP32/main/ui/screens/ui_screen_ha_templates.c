#include "ui_screen_ha_templates.h"
#include "esp_log.h"

typedef struct user_data
{
    lv_obj_t *data_label;
    char prefix[10];
    char postfix[10];
} user_data_t;


template_t ui_templates[3];

static const char *TAG = "HA_TEMPLATE";

void init_templates()
{
    // Small type
    ui_templates[BT_SMALL].type = BT_SMALL;
    ui_templates[BT_SMALL].sensor_ui.height = 78;
    ui_templates[BT_SMALL].sensor_ui.width = 214;
    ui_templates[BT_SMALL].sensor_ui.logo_width = 45;
    ui_templates[BT_SMALL].sensor_ui.logo_height = 45;
    ui_templates[BT_SMALL].sensor_ui.logo_x = 0;
    ui_templates[BT_SMALL].sensor_ui.logo_y = 0;
    ui_templates[BT_SMALL].sensor_ui.label_x = 0;
    ui_templates[BT_SMALL].sensor_ui.label_y = 0;
    ui_templates[BT_SMALL].sensor_ui.data_x = 58;
    ui_templates[BT_SMALL].sensor_ui.data_y = 24;
    ui_templates[BT_SMALL].sensor_ui.data_width = 71;
    ui_templates[BT_SMALL].sensor_ui.unit_x = 142;
    ui_templates[BT_SMALL].sensor_ui.unit_y = 27;
    ui_templates[BT_SMALL].sensor_ui.font_size = 20;

    // Large type
    ui_templates[BT_LARGE].type = BT_LARGE;
    ui_templates[BT_LARGE].sensor_ui.height = 164;
    ui_templates[BT_LARGE].sensor_ui.width = 214;
    ui_templates[BT_LARGE].sensor_ui.logo_width = 45;
    ui_templates[BT_LARGE].sensor_ui.logo_height = 45;
    ui_templates[BT_LARGE].sensor_ui.logo_x = 69;
    ui_templates[BT_LARGE].sensor_ui.logo_y = 22;
    ui_templates[BT_LARGE].sensor_ui.label_x = 0;
    ui_templates[BT_LARGE].sensor_ui.label_y = -5;
    ui_templates[BT_LARGE].sensor_ui.data_x = 11;
    ui_templates[BT_LARGE].sensor_ui.data_y = 79;
    ui_templates[BT_LARGE].sensor_ui.data_width = 71;
    ui_templates[BT_LARGE].sensor_ui.unit_x = 125;
    ui_templates[BT_LARGE].sensor_ui.unit_y = 82;
    ui_templates[BT_LARGE].sensor_ui.font_size = 20;

    // large switches
    ui_templates[BT_LARGE].switch_ui.width = 214;
    ui_templates[BT_LARGE].switch_ui.height = 164;

    // Button
    ui_templates[BT_LARGE].switch_ui.b_icon_x = 0;
    ui_templates[BT_LARGE].switch_ui.b_icon_y = -10;

    // toggle
    ui_templates[BT_LARGE].switch_ui.t_label_x = 0;
    ui_templates[BT_LARGE].switch_ui.t_label_y = -5;
    ui_templates[BT_LARGE].switch_ui.t_toggle_x = 0;
    ui_templates[BT_LARGE].switch_ui.t_toggle_y = -7;
    ui_templates[BT_LARGE].switch_ui.t_toggle_width = 120;
    ui_templates[BT_LARGE].switch_ui.t_toggle_height = 60;

    // slider
    ui_templates[BT_LARGE].switch_ui.s_data_label_x = 25;
    ui_templates[BT_LARGE].switch_ui.s_data_label_y = 21;

    // arc
    ui_templates[BT_LARGE].switch_ui.a_data_width = 130;
    ui_templates[BT_LARGE].switch_ui.a_data_height = 125;
    ui_templates[BT_LARGE].switch_ui.a_data_label_x = 0;
    ui_templates[BT_LARGE].switch_ui.a_data_label_y = -50;
}

void create_sensor_button(int size, lv_obj_t *parent, ha_sensor_t *sensor, int bt_x, int bt_y, int text_color, char *name, char *label, char *unit, char *icon)
{
    // ESP_LOGI(TAG, "create_sensor_button: name %s", name);
    // ESP_LOGI(TAG, "create_sensor_button: label %s", label);
    // ESP_LOGI(TAG, "create_sensor_button: unit %s", unit);
    // ESP_LOGI(TAG, "create_sensor_button: icon %s", icon);
    // ESP_LOGI(TAG, "create_sensor_button: size %d", size);
    // ESP_LOGI(TAG, "create_sensor_button: x, y %d, %d", bt_x, bt_y);

    lv_img_dsc_t *icon_img;

    if (strcmp(icon, 'temperature') == 0)
    {
        icon_img = &ui_img_ic_temp_png;
    }
    else if (strcmp(icon, "humidity") == 0)
    {
        icon_img = &ui_img_ic_hum_png;
    }
    else if (strcmp(icon, "co2") == 0)
    {
        icon_img = &ui_img_ic_co2_png;
    }
    else if (strcmp(icon, "tvoc") == 0)
    {
        icon_img = &ui_img_ic_tvoc_png;
    }
    else
    {
        icon_img = &ui_img_ic_temp_png; // default icon
    }

    sensor->btn = lv_btn_create(parent);
    lv_obj_set_width(sensor->btn, ui_templates[size].sensor_ui.width);
    lv_obj_set_height(sensor->btn, ui_templates[size].sensor_ui.height);
    lv_obj_set_x(sensor->btn, bt_x);
    lv_obj_set_y(sensor->btn, bt_y);
    lv_obj_add_flag(sensor->btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(sensor->btn, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(sensor->btn, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(sensor->btn, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(sensor->btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    sensor->logo = lv_img_create(sensor->btn);
    lv_img_set_src(sensor->logo, icon_img);
    lv_obj_set_width(sensor->logo, LV_SIZE_CONTENT);  /// 45
    lv_obj_set_height(sensor->logo, LV_SIZE_CONTENT); /// 45
    lv_obj_set_x(sensor->logo, ui_templates[size].sensor_ui.logo_x);
    lv_obj_set_y(sensor->logo, ui_templates[size].sensor_ui.logo_y);
    lv_obj_add_flag(sensor->logo, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(sensor->logo, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    sensor->label = lv_label_create(sensor->btn);
    lv_obj_set_width(sensor->label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(sensor->label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(sensor->label, ui_templates[size].sensor_ui.label_x);
    lv_obj_set_y(sensor->label, ui_templates[size].sensor_ui.label_y);
    lv_obj_set_align(sensor->label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(sensor->label, label);
    lv_obj_set_style_text_color(sensor->label, lv_color_hex(0x9E9E9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(sensor->label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(sensor->label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    sensor->data = lv_label_create(sensor->btn);
    lv_obj_set_width(sensor->data, 100);
    lv_obj_set_height(sensor->data, LV_SIZE_CONTENT); /// 2
    lv_obj_set_x(sensor->data, ui_templates[size].sensor_ui.data_x);
    lv_obj_set_y(sensor->data, ui_templates[size].sensor_ui.data_y);
    lv_label_set_text(sensor->data, "n/a");
    lv_obj_set_style_text_color(sensor->data, lv_color_hex(text_color), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(sensor->data, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(sensor->data, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(sensor->data, &ui_font_font2, LV_PART_MAIN | LV_STATE_DEFAULT);

    sensor->unit = lv_label_create(sensor->btn);
    lv_obj_set_width(sensor->unit, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(sensor->unit, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(sensor->unit, ui_templates[size].sensor_ui.unit_x);
    lv_obj_set_y(sensor->unit, ui_templates[size].sensor_ui.unit_y);
    lv_label_set_text(sensor->unit, unit);
    lv_obj_set_style_text_color(sensor->unit, lv_color_hex(text_color), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(sensor->unit, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(sensor->unit, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void create_switch_button(int size, lv_obj_t *parent, ha_switch_t *switch_, int bt_x, int bt_y, char *label)
{
    // ESP_LOGI(TAG, "create_switch_button: label %s", label);
    // ESP_LOGI(TAG, "create_switch_button: size %d", size);
    // ESP_LOGI(TAG, "create_switch_button: x, y %d, %d", bt_x, bt_y);
    // ESP_LOGI(TAG, "create_switch_button: parent %p", parent);
    // ESP_LOGI(TAG, "create_switch_button: switch_ %p", switch_);

    switch_->btn = lv_btn_create(parent);
    lv_obj_set_width(switch_->btn, ui_templates[size].switch_ui.width);
    lv_obj_set_height(switch_->btn, ui_templates[size].switch_ui.height);
    lv_obj_set_x(switch_->btn, bt_x);
    lv_obj_set_y(switch_->btn, bt_y);
    lv_obj_add_flag(switch_->btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(switch_->btn, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(switch_->btn, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(switch_->btn, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(switch_->btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    switch_->img = lv_img_create(switch_->btn);
    lv_img_set_src(switch_->img, &ui_img_ic_switch2_off_png);
    lv_obj_set_width(switch_->img, LV_SIZE_CONTENT);  /// 45
    lv_obj_set_height(switch_->img, LV_SIZE_CONTENT); /// 45
    lv_obj_set_x(switch_->img, ui_templates[size].switch_ui.b_icon_x);
    lv_obj_set_y(switch_->img, ui_templates[size].switch_ui.b_icon_y);
    lv_obj_set_align(switch_->img, LV_ALIGN_CENTER);
    lv_obj_add_flag(switch_->img, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(switch_->img, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    switch_->label = lv_label_create(switch_->btn);
    lv_obj_set_width(switch_->label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(switch_->label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(switch_->label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(switch_->label, label);
    lv_obj_set_style_text_color(switch_->label, lv_color_hex(0x9E9E9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(switch_->label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(switch_->label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void create_switch_toggle(int size, lv_obj_t *parent, ha_switch_t *switch_, int bt_x, int bt_y, char *label)
{
    // ESP_LOGI(TAG, "create_switch_toggle: label %s", label);
    // ESP_LOGI(TAG, "create_switch_toggle: size %d", size);
    // ESP_LOGI(TAG, "create_switch_toggle: x, y %d, %d", bt_x, bt_y);
    // ESP_LOGI(TAG, "create_switch_toggle: parent %p", parent);
    // ESP_LOGI(TAG, "create_switch_toggle: switch_ %p", switch_);

    switch_->btn = lv_obj_create(parent);
    lv_obj_set_width(switch_->btn, ui_templates[size].switch_ui.width);
    lv_obj_set_height(switch_->btn, ui_templates[size].switch_ui.height);
    lv_obj_set_x(switch_->btn, bt_x);
    lv_obj_set_y(switch_->btn, bt_y);
    lv_obj_clear_flag(switch_->btn, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(switch_->btn, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(switch_->btn, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(switch_->btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(switch_->btn, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(switch_->btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(switch_->btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    switch_->label = lv_label_create(switch_->btn);
    lv_obj_set_width(switch_->label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(switch_->label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(switch_->label, ui_templates[size].switch_ui.t_label_x);
    lv_obj_set_y(switch_->label, ui_templates[size].switch_ui.t_label_y);
    lv_obj_set_align(switch_->label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(switch_->label, label);
    lv_obj_set_style_text_color(switch_->label, lv_color_hex(0x9E9E9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(switch_->label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(switch_->label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    switch_->data = lv_switch_create(switch_->btn);
    lv_obj_set_width(switch_->data, ui_templates[size].switch_ui.t_toggle_width);
    lv_obj_set_height(switch_->data, ui_templates[size].switch_ui.t_toggle_height);
    lv_obj_set_x(switch_->data, ui_templates[size].switch_ui.t_toggle_x);
    lv_obj_set_y(switch_->data, ui_templates[size].switch_ui.t_toggle_y);
    lv_obj_set_align(switch_->data, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(switch_->data, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(switch_->data, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(switch_->data, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(switch_->data, 40, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(switch_->data, lv_color_hex(0x4F4F4F), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(switch_->data, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(switch_->data, lv_color_hex(0x529D53), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(switch_->data, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
}

void ui_event_btn(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    user_data_t *data = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        _ui_slider_set_text_value(data->data_label, target, data->prefix, data->postfix);
    }

    // free user data
    // free(data);
}

void create_switch_arc(int size, lv_obj_t *parent, ha_switch_t *switch_, int bt_x, int bt_y, char *label, char *unit)
{
    // ESP_LOGI(TAG, "create_switch_arc: label %s", label);
    // ESP_LOGI(TAG, "create_switch_arc: size %d", size);
    // ESP_LOGI(TAG, "create_switch_arc: x, y %d, %d", bt_x, bt_y);
    // ESP_LOGI(TAG, "create_switch_arc: parent %p", parent);
    // ESP_LOGI(TAG, "create_switch_arc: switch_ %p", switch_);
    // ESP_LOGI(TAG, "create_switch_arc: unit %s", unit);

    switch_->btn = lv_obj_create(parent);
    lv_obj_set_width(switch_->btn, ui_templates[size].switch_ui.width);
    lv_obj_set_height(switch_->btn, ui_templates[size].switch_ui.height);
    lv_obj_set_x(switch_->btn, bt_x);
    lv_obj_set_y(switch_->btn, bt_y);
    lv_obj_clear_flag(switch_->btn, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(switch_->btn, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(switch_->btn, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(switch_->btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(switch_->btn, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(switch_->btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(switch_->btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    switch_->data = lv_arc_create(switch_->btn);
    lv_obj_set_width(switch_->data, ui_templates[size].switch_ui.a_data_width);
    lv_obj_set_height(switch_->data, ui_templates[size].switch_ui.a_data_height);
    lv_obj_set_align(switch_->data, LV_ALIGN_CENTER);
    lv_arc_set_value(switch_->data, 0);
    lv_arc_set_bg_angles(switch_->data, 140, 40);
    lv_obj_set_style_arc_color(switch_->data, lv_color_hex(0x1C1C1C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(switch_->data, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(switch_->data, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(switch_->data, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(switch_->data, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(switch_->data, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(switch_->data, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(switch_->data, lv_color_hex(0x529D53), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(switch_->data, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(switch_->data, 8, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(switch_->data, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(switch_->data, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(switch_->data, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    switch_->label = lv_label_create(switch_->btn);
    lv_obj_set_width(switch_->label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(switch_->label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(switch_->label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(switch_->label, label);
    lv_obj_set_style_text_color(switch_->label, lv_color_hex(0x9E9E9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(switch_->label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(switch_->label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    switch_->data_label = lv_label_create(switch_->btn);
    lv_obj_set_width(switch_->data_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(switch_->data_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(switch_->data_label, ui_templates[size].switch_ui.s_data_label_x);
    lv_obj_set_y(switch_->data_label, ui_templates[size].switch_ui.s_data_label_y);
    lv_obj_set_align(switch_->data_label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(switch_->data_label, "n/a");
    lv_obj_set_style_text_color(switch_->data_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(switch_->data_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(switch_->data_label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    user_data_t *data = malloc(sizeof(user_data_t));
    data->data_label = switch_->data_label;
    strcpy(data->prefix, "");
    strcpy(data->postfix, unit);

    lv_obj_add_event_cb(switch_->data, ui_event_btn, LV_EVENT_ALL, data);
}

void create_switch_slider(int size, lv_obj_t *parent, ha_switch_t *switch_, int bt_x, int bt_y, char *label, char *unit)
{
    // ESP_LOGI(TAG, "create_switch_slider: label %s", label);
    // ESP_LOGI(TAG, "create_switch_slider: size %d", size);
    // ESP_LOGI(TAG, "create_switch_slider: x, y %d, %d", bt_x, bt_y);
    // ESP_LOGI(TAG, "create_switch_slider: parent %p", parent);
    // ESP_LOGI(TAG, "create_switch_slider: switch_ %p", switch_);
    // ESP_LOGI(TAG, "create_switch_slider: unit %s", unit);

    switch_->btn = lv_obj_create(parent);
    lv_obj_set_width(switch_->btn, ui_templates[size].switch_ui.width);
    lv_obj_set_height(switch_->btn, ui_templates[size].switch_ui.height);
    lv_obj_set_x(switch_->btn, bt_x);
    lv_obj_set_y(switch_->btn, bt_y);
    lv_obj_clear_flag(switch_->btn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(switch_->btn, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(switch_->btn, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(switch_->btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(switch_->btn, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(switch_->btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(switch_->btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    switch_->label = lv_label_create(switch_->btn);
    lv_obj_set_width(switch_->label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(switch_->label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(switch_->label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(switch_->label, label);
    lv_obj_set_style_text_color(switch_->label, lv_color_hex(0x9E9E9E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(switch_->label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(switch_->label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    switch_->data_label = lv_label_create(switch_->btn);
    lv_obj_set_width(switch_->data_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(switch_->data_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(switch_->data_label, ui_templates[size].switch_ui.s_data_label_x);
    lv_obj_set_y(switch_->data_label, ui_templates[size].switch_ui.s_data_label_y);
    lv_obj_set_align(switch_->data_label, LV_ALIGN_LEFT_MID);
    lv_label_set_text(switch_->data_label, "n/a");
    lv_obj_set_style_text_color(switch_->data_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(switch_->data_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(switch_->data_label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    switch_->unit = lv_label_create(switch_->btn);
    lv_obj_set_width(switch_->unit, 66);
    lv_obj_set_height(switch_->unit, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(switch_->unit, 104);
    lv_obj_set_y(switch_->unit, 23);
    lv_obj_set_align(switch_->unit, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(switch_->unit, LV_LABEL_LONG_DOT);
    lv_label_set_text(switch_->unit, unit);
    lv_obj_set_style_text_color(switch_->unit, lv_color_hex(0xECBF41), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(switch_->unit, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(switch_->unit, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(switch_->unit, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    switch_->data = lv_slider_create(switch_->btn);
    lv_slider_set_value(switch_->data, 40, LV_ANIM_OFF);
    if(lv_slider_get_mode(switch_->data) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(switch_->data, 0, LV_ANIM_OFF);
    lv_obj_set_width(switch_->data, 151);
    lv_obj_set_height(switch_->data, 37);
    lv_obj_set_x(switch_->data, -2);
    lv_obj_set_y(switch_->data, -28);
    lv_obj_set_align(switch_->data, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(switch_->data, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(switch_->data, lv_color_hex(0x1C1C1C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(switch_->data, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(switch_->data, lv_color_hex(0x529D53), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(switch_->data, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(switch_->data, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(switch_->data, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    user_data_t *data = malloc(sizeof(user_data_t));
    data->data_label = switch_->data_label;
    strcpy(data->prefix, "");
    strcpy(data->postfix, "");

    lv_obj_add_event_cb(switch_->data, ui_event_btn, LV_EVENT_ALL, data);
}

