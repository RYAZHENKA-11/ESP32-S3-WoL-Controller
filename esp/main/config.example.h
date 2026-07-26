#ifndef CONFIG_H
#define CONFIG_H

const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";
const uint32_t WIFI_CONNECT_TIMEOUT_MS = 60000;
const uint32_t WIFI_BEFORE_RECONNECT_MS = 60000;

const char *MQTT_SERVER = "";
const uint16_t MQTT_PORT = 1883;
const char *MQTT_USER = "";
const char *MQTT_PASSWORD = "";
const char *MQTT_TOPIC_COMMAND = "esp32/command";
const char *MQTT_TOPIC_STATUS = "esp32/status";
const uint8_t MQTT_RECONNECT_ATTEMPTS = 5;
const uint32_t MQTT_BEFORE_RECONNECT_MS = 10000;
const uint32_t MQTT_STATUS_INTERVAL_MS = 30000;

const char *MAC_ADDR = "";

const uint8_t LED_PIN = 48;
const uint8_t LED_BRIGHTNESS = 128;
const uint32_t LED_FLASH_MS = 250;

const uint32_t AUTO_REBOOT_MS = 24 * 60 * 60 * 1000;
const uint32_t BEFORE_START_MS = 5000;
const uint32_t BEFORE_REBOOT_MS = 1000;

const uint32_t SERIAL_BAUD_RATE = 115200;

#endif
