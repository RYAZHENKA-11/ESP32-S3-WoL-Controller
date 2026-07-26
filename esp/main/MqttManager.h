#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <WakeOnLan.h>
#include "LedController.h"

class MqttManager
{
public:
	MqttManager(const char *_server, uint16_t _port,
				const char *_user, const char *_password,
				const char *_topicCommand, const char *_topicStatus,
				uint8_t _reconnectAttempts,
				uint32_t _beforeReconnectMs,
				uint32_t _statusIntervalMs,
				LedController &led, uint32_t _ledFlashMs,
				const char *macAddr,
				uint32_t _beforeRebootMs);
	void init();
	void loop();

private:
	const char *_server;
	const uint16_t _port;
	const char *_user;
	const char *_password;
	const char *_topicCommand;
	const char *_topicStatus;
	const uint8_t _reconnectAttempts;
	const uint32_t _beforeReconnectMs;
	const uint32_t _statusIntervalMs;
	LedController &_led;
	const uint32_t _ledFlashMs;
	const char *_macAddr;
	const uint32_t _beforeRebootMs;
	static MqttManager *_instance;
	WiFiClient _wifiClient;
	PubSubClient _mqttClient;
	WiFiUDP _udp;
	WakeOnLan _wol;
	uint32_t _lastStatusTime = 0;

	void reboot();
	void reconnect();
	void publishStatus(const char *msg = "");
	static void staticCallback(char *topic, byte *payload, uint16_t length);
	void handleCallback(char *topic, byte *payload, uint16_t length);
};

#endif