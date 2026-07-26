#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include "LedController.h"

class WiFiManager
{
public:
	WiFiManager(const char *ssid, const char *password,
				uint32_t connectTimeoutMs,
				uint32_t beforeReconnectMs,
				LedController &led, uint32_t ledFlashMs);
	void init();

private:
	const char *_ssid;
	const char *_password;
	uint32_t _connectTimeoutMs;
	uint32_t _beforeReconnectMs;
	LedController &_led;
	uint32_t _ledFlashMs;
};

#endif