#include "LedController.h"
#include "WiFiManager.h"
#include "MqttManager.h"
#include "config.h"

LedController led(LED_PIN, LED_BRIGHTNESS);
WiFiManager wifi(WIFI_SSID, WIFI_PASSWORD,
				 WIFI_CONNECT_TIMEOUT_MS,
				 WIFI_BEFORE_RECONNECT_MS,
				 led, LED_FLASH_MS);
MqttManager mqtt(MQTT_SERVER, MQTT_PORT,
				 MQTT_USER, MQTT_PASSWORD,
				 MQTT_TOPIC_COMMAND, MQTT_TOPIC_STATUS,
				 MQTT_RECONNECT_ATTEMPTS,
				 MQTT_BEFORE_RECONNECT_MS,
				 MQTT_STATUS_INTERVAL_MS,
				 led, LED_FLASH_MS,
				 MAC_ADDR,
				 BEFORE_REBOOT_MS);

void setup()
{
	led.init();
	Serial.begin(SERIAL_BAUD_RATE);

	led.white();
	delay(BEFORE_START_MS);

	wifi.init();
	mqtt.init();
}

void loop()
{
	mqtt.loop();
	if (millis() >= AUTO_REBOOT_MS)
	{
		Serial.print("Auto rebooting...");
		ESP.restart();
	}
}