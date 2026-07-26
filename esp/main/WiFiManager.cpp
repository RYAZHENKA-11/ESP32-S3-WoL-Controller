#include "WiFiManager.h"

WiFiManager::WiFiManager(const char *ssid, const char *password,
                         uint32_t connectTimeoutMs,
                         uint32_t beforeReconnectMs,
                         LedController &led, uint32_t ledFlashMs)
    : _ssid(ssid), _password(password),
      _connectTimeoutMs(connectTimeoutMs),
      _beforeReconnectMs(beforeReconnectMs),
      _led(led), _ledFlashMs(ledFlashMs) {}

void WiFiManager::init()
{
    Serial.print("Wi-Fi connecting");
    WiFi.begin(_ssid, _password);
    uint32_t start_ms = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        if (millis() - start_ms > _connectTimeoutMs)
        {
            _led.red();
            Serial.println("\nTimeout!");
            WiFi.disconnect(true);
            delay(_beforeReconnectMs);
            ESP.restart();
        }
        _led.blue();
        delay(_ledFlashMs);
        _led.off();
        delay(_ledFlashMs);
        Serial.print(".");
    }
    Serial.println("\nConnected!");
}