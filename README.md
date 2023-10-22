# Indicator Home Assistant with Configuration File

<div align="center"><img width={480} src="https://files.seeedstudio.com/wiki/SenseCAP/SenseCAP_Indicator/SenseCAP_Indicator_1.png"/></div>

This project is based on the example project for SenseCap Indicator with added Home Assistant functions.

The main difference is the feature to load Indicator screens (sensor, switch, etc.) based on a configuration file. The configuration file is stored in the SDCard and can be modified by the user. The configuration file is in JSON format. The configuration file is loaded at startup.

Initial example look and feel used.
<figure class="third">
    <img src="./docs/Home Assistant Data.png" width="480"/>
    <img src="./docs/Home Assistant.png" width="480"/>
    <img src="./docs/Home Assistant Control(ON).png" width="480"/>
    <img src="./docs/Home Assistant Control(OFF).png" width="480"/>
</figure>



## Global Functions
- [x] Time display.
- [x] CO2, tVOC, Temperature and Humidity data real-time display.
- [x] CO2, tVOC, Temperature and Humidity history data display.
- [x] Wifi config.
- [x] Display config.
- [x] time config.
- [x] Home Assistant data.
- [x] Home Assistant control.

## Additional Features

In addition to the initial example, I added the possiblity to load screens with sensors and switches based on a configuration file. This JSON file contain as well the HA connection information (url, username, password). So there is no need to recompile the firmware to add new items. 

### Screens types

Different type of pages are support defined as grid:
- 1x1 (1 coluum of 1 Xlarge UI item)
- 1x2 (1 coloum of 2 large UI items)
- 1x3 (1 coloum of 3 medium UI items)
- 1x4 (1 coloum of 4 small UI items)
- 2x1 (2 coloums of 1 Xlarge UI item)
- 2x2 (2 coloums of 2 large UI items)
- 2x3 (2 coloums of 3 medium UI items)
- 2x4 (2 coloums of 4 small UI items)

### Type of UI items

1. Sensor : Display sensor data and select one of the 4 icons
2. Switch button : Display a switch button (Switch type in mqtt)
2. Switch toggle : Display a switch toggle (Switch type in mqtt)
3. Switch slider : Display a switch slider (Number type in mqtt)
4. Switch arc : Display a switch arc (Number type in mqtt)
5. Switch dropdown : Display a switch dropdown (Selec type in mqtt)

## How to modify the UI templates

The UI templates are based on squareline (see /squareline/ sub folder with projects) with different UI elements. 
You can find few projects for large, medium and small screens. You can modify the UI elements, generate the code and modify the `./main/ui/screens/ui_sreen_ha_templates` files.

## How to use this version

Please first read the [User Guide](https://wiki.seeedstudio.com/SenseCAP_Indicator_Get_Started) of the SenseCAP Indicator Board to learn about its software and hardware information.

### Configuration file JSON

The configuration file is stored in the SDCard and load by the RP2040. The ESP32 MCU will request the configuration file from the RP2040 and generate screens, sensors and swtiches.

Structure of the config file : 

```json
{
    "url": "mqtt://<url>",
    "username": "<username>",
    "password": "<password>",
    "pages": [
        {
            "name": "<PAGE_NAME>",
            "label": "<PAGE_LABEL>",
            "type": "<PAGE_TYPE>",
            "sensors": [
                {
                    "name": "<SENSOR_NAME>",
                    "label": "<SENSOR_LABEL>",
                    "unit": "<SENSOR_UNIT>",
                    "key": "<SENSOR_HA_KEY>",
                    "x": "<SENSOR_X>",
                    "y": "<SENSOR_Y>",
                    "icon": "<SENSOR_ICON>",
                    "size": "<SENSOR_SIZE>"
                },
            ],
            "switches": [
                {
                    "name": "<SWITCH_NAME>",
                    "label": "<SWITCH_LABEL>",
                    "key": "<SWITCH_HA_KEY>",
                    "x": "<SWITCH_X>",
                    "y": "<SWITCH_Y>",
                    "type": "<SWITCH_TYPE>",
                    "size": "<SWITCH_SIZE>",                 
                    "unit": "<SWITCH_UNIT>"   
                },
            ]
        }
    ]
}
```

### Home Assistant Configuration (mqtt.yaml)

You need to configure Home assistant to receive and send data from/to the Indicator device. The following is an example of the mqtt.yaml file.

```yaml
sensor:
  # SenseCAP Sensors
  - unique_id: SC_temperature
    name: "SC Temperature"
    state_topic: "indicator/sensor"
    #suggested_display_precision: 1
    unit_of_measurement: "°C"
    value_template: "{{ value_json.temp }}"
  - unique_id: SC_humidity
    name: "SC Humidity"
    state_topic: "indicator/sensor"
    unit_of_measurement: "%"
    value_template: "{{ value_json.humidity }}"
  - unique_id: SC_co2
    name: "SC CO2"
    state_topic: "indicator/sensor"
    unit_of_measurement: "ppm"
    value_template: "{{ value_json.co2 }}"
  - unique_id: SC_tvoc
    name: "SC tVOC"
    state_topic: "indicator/sensor"
    unit_of_measurement: ""
    value_template: "{{ value_json.tvoc }}"
  # Additonal Sensors
  - unique_id: <SENSOR_ID>
    name: "<SENSOR_NAME>"
    state_topic: "indicator/sensor"
    unit_of_measurement: "<SENSOR_UNIT>"
    value_template: "{{ value_json.<SENSOR_HA_KEY> }}"
switch:
  - unique_id: <SWITCH_ID>
    name: "<SWITCH_NAME>"
    state_topic: "indicator/switch/state"
    command_topic: "indicator/switch/set"
    value_template: "{{ value_json.<SWITCH_HA_KEY> }}"
    payload_on: '{"<SWITCH_HA_KEY>":1}'
    payload_off: '{"<SWITCH_HA_KEY>":0}'
    state_on: 1
    state_off: 0
number:
  - unique_id: <SWITCH_ID>
    name: "<SWITCH_NAME>"
    state_topic: "indicator/switch/state"
    command_topic: "indicator/switch/set"
    command_template: '{"<SWITCH_HA_KEY>": {{ value }} }'
    value_template: "{{ value_json.<SWITCH_HA_KEY> }}"
```

### Home Assistant Automation for senors data publishing

If you want to display any information from HA on SenseCap Indicator screens (like temp, humidity of other sensors, rooms), you need to create an automation to publish the data to the Indicator device.

*Example of the automation*
Publish a temperature and humidity sensor data on MQTT every minute (time_pattern)

```yaml
alias: MQTT - <Automation Name>
description: ""
trigger:
  - platform: time_pattern
    minutes: "*"
    hours: "*"
condition: []
action:
  - service: mqtt.publish
    data:
      qos: "0"
      retain: false
      topic: indicator/sensor
      payload: >-
        {"<SENSOR_HA_KEY>" : "{{states('sensor.<HA_SENSOR_NAME>')
        }}"}
  - service: mqtt.publish
    data:
      qos: "0"
      retain: false
      topic: indicator/sensor
      payload: "{\"<SENSOR_HA_KEY>\" : \"{{states('sensor.<HA_SENSOR_NAME>') }}\"}"
mode: single
```

### Build and Flash (RP2040)

The RP2030 is an aduino project. You can use the Arduino IDE to build and flash the project.

Step 1: Install Arduino IDE
Step 2: Add the Raspberry Pi Pico Board
Step 3: Add the Libraries
-  LIBRARIES FOR REFERENCE
-  Sensirion Core: Sensirion Arduino Core library
-  PacketSerial : Serial communication protoco
-  Sensirion I2C SGP40 : SGP40 TVOC sensor library
-  Sensirion I2C SCD4x : SCD41 CO2 sensor library
-  Sensirion Gas Index Algorithm : Transfer index library
-  Seeed_Arduino_AHT20 : AHT20 temperature and humidity sensor library

Step 4: Select the board and port
Search "Indicator" and select Seeed INDICATOR RP2040 board and select the usbmodem Serial Port.

For more information : https://wiki.seeedstudio.com/SenseCAP_Indicator_How_To_Flash_The_Default_Firmware/#for-rp2040


### Build and Flash (ESP32)

1. The project configure PSRAM with Octal 120M by default. please see [here](../../tools/patch/README.md#idf-patch) to enable `PSRAM Octal 120M` feature.
2. Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

For more information : https://wiki.seeedstudio.com/SenseCAP_Indicator_How_To_Flash_The_Default_Firmware/#for-esp32-s3