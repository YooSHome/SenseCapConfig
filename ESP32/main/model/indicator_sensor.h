#ifndef INDICATOR_SENSOR_H
#define INDICATOR_SENSOR_H

#include "config.h"
#include "view_data.h"
#include "driver/uart.h"


#ifdef __cplusplus
extern "C" {
#endif

enum pkt_type
{
    PKT_TYPE_CMD_COLLECT_INTERVAL = 0xA0, // uin32_t
    PKT_TYPE_CMD_BEEP_ON = 0xA1,          // uin32_t  ms: on time
    PKT_TYPE_CMD_BEEP_OFF = 0xA2,
    PKT_TYPE_CMD_SHUTDOWN = 0xA3, // uin32_t
    PKT_TYPE_CMD_POWER_ON = 0xA4,

    PKT_TYPE_SENSOR_SCD41_TEMP = 0xB0,     // float
    PKT_TYPE_SENSOR_SCD41_HUMIDITY = 0xB1, // float
    PKT_TYPE_SENSOR_SCD41_CO2 = 0xB2,      // float

    PKT_TYPE_SENSOR_SHT41_TEMP = 0xB3,     // float
    PKT_TYPE_SENSOR_SHT41_HUMIDITY = 0xB4, // float

    PKT_TYPE_SENSOR_TVOC_INDEX = 0xB5, // float

    // Yoo : 0xC0 ~ 0xCF for config file
    PKT_TYPE_CONFIG_FILE_GET = 0xC0,     // uint8_t[]
    PKT_TYPE_CONFIG_FILE_ACK = 0xC1, // uint8_t[]
    PKT_TYPE_CONFIG_FILE_COMPLETE = 0xC2, // uint8_t[]
    // todo
};

int indicator_sensor_init(void);
// static int __cmd_send(uint8_t cmd, void *p_data, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif
