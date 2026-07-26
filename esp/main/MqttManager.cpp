#include "MqttManager.h"

MqttManager *MqttManager::_instance = nullptr;

MqttManager::MqttManager(const char *server, uint16_t port,
                         const char *user, const char *password,
                         const char *topicCommand, const char *topicStatus,
                         uint8_t reconnectAttempts,
                         uint32_t beforeReconnectMs,
                         uint32_t statusIntervalMs,
                         LedController &led, uint32_t ledFlashMs,
                         const char *macAddr,
                         uint32_t beforeRebootMs)
    : _server(server), _port(port),
      _user(user), _password(password),
      _topicCommand(topicCommand), _topicStatus(topicStatus),
      _reconnectAttempts(reconnectAttempts),
      _beforeReconnectMs(beforeReconnectMs),
      _statusIntervalMs(statusIntervalMs),
      _led(led), _ledFlashMs(ledFlashMs),
      _macAddr(macAddr),
      _beforeRebootMs(beforeRebootMs),
      _mqttClient(_wifiClient), _wol(_udp)
{
    _instance = this;
}

void MqttManager::init()
{
    _mqttClient.setServer(_server, _port);
    _mqttClient.setCallback(staticCallback);
    reconnect();
}

void MqttManager::loop()
{
    static uint32_t _startLedTime = -1;

    if (!_mqttClient.connected())
        reconnect();
    _mqttClient.loop();

    if (millis() - _lastStatusTime > _statusIntervalMs)
    {
        _lastStatusTime = millis();
        _startLedTime = millis();
        _led.green();
        publishStatus();
    }
    if (millis() - _startLedTime > _ledFlashMs)
    {
        _startLedTime = -1;
        _led.off();
    }
}

void MqttManager::reboot()
{
    _led.red();
    Serial.println("Rebooting...");
    WiFi.disconnect(true);
    delay(_beforeRebootMs);
    ESP.restart();
}

void MqttManager::reconnect()
{
    _led.blue();
    uint8_t attempts = 0;
    while (!_mqttClient.connected())
    {
        if (++attempts > _reconnectAttempts)
        {
            Serial.println("MQTT reconnect failed!");
            reboot();
        }
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("WiFi disconnected while MQTT reconnecting!");
            reboot();
        }
        Serial.println("MQTT connecting...");
        if (_mqttClient.connect(WiFi.macAddress().c_str(), _user, _password))
        {
            _mqttClient.subscribe(_topicCommand);
            publishStatus("Online!");
        }
        else
        {
            _led.red();
            Serial.print("MQTT error code: ");
            Serial.println(_mqttClient.state());
            delay(_beforeReconnectMs);
            _led.blue();
        }
    }
    _led.off();
}

void MqttManager::publishStatus(const char *msg)
{
    String payload;
    if (strlen(msg) == 0)
        payload = "Uptime: " + String(millis() / 1000) + "s RSSI: " + String(WiFi.RSSI()) + " Serial: " + String(Serial) + "!";
    else
        payload = msg;
    Serial.print("statusMsg: ");
    Serial.println(payload);
    while (!_mqttClient.publish(_topicStatus, payload.c_str()))
    {
        Serial.println("Publish error!");
        reconnect();
    }
}

void MqttManager::staticCallback(char *topic, byte *payload, uint16_t length)
{
    if (_instance)
        _instance->handleCallback(topic, payload, length);
}

void MqttManager::handleCallback(char *topic, byte *payload, uint16_t length)
{
    Serial.print("Topic: ");
    Serial.print(topic);

    String message;
    for (uint16_t i = 0; i < length; ++i)
        message += (char)payload[i];
    Serial.print(" Message: ");
    Serial.println(message);

    if (String(topic) == _topicCommand)
    {
        if (message == "WOL")
        {
            if (_wol.sendMagicPacket(_macAddr))
                publishStatus("Sent!");
            else
                publishStatus("Failed!");
        }
        else if (message == "STATUS")
        {
            publishStatus();
        }
        else if (message == "REBOOT")
        {
            publishStatus("Rebooting...");
            reboot();
        }
        else
            publishStatus("Unknown! Command list: WOL, STATUS, REBOOT.");
    }
}