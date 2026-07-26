# ESP32-S3 WoL Controller

A lightweight Wake-on-LAN controller built on the ESP32-S3. Send magic packets to wake up remote PC over MQTT with visual feedback via the built-in WS2812 LED.

## Features

- **Wake-on-LAN** — send WoL magic packets via MQTT commands
- **Status monitoring** — uptime, signal strength (RSSI), and Serial port activity
- **LED indicators** — built-in WS2812 LED shows connection and operation status:
  - White — booting
  - Blue — connecting to WiFi/MQTT
  - Green — status published
  - Red — error
- **Auto-reconnect** — WiFi and MQTT reconnection with configurable timeouts
- **Auto-reboot** — automatic restart every 24 hours
- **Python console client** — simple CLI tool for sending commands from a PC

## Hardware

- ESP32-S3 board with integrated WS2812 LED (GPIO 48)
- Any PC with WoL enabled on the LAN

## Dependencies

### Firmware (Arduino IDE)

| Library | Install |
|---|---|
| [WiFi](https://github.com/espressif/arduino-esp32) | Built-in with ESP32 board package |
| [PubSubClient](https://github.com/knolleary/pubsubclient) | Arduino Library Manager |
| [WakeOnLan](https://github.com/a7a8/WakeOnLan) | Arduino Library Manager |
| [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) | Arduino Library Manager |

### Server

```
pip install paho-mqtt
```

## Configuration

1. Copy `esp/main/config.example.h` to `esp/main/config.h`
2. Fill in your credentials:

```cpp
const char *WIFI_SSID = "YourSSID";
const char *WIFI_PASSWORD = "YourPassword";

const char *MQTT_SERVER = "192.168.1.100";
const char *MQTT_USER = "mqtt_user";
const char *MQTT_PASSWORD = "mqtt_password";

const char *MAC_ADDR = "AA:BB:CC:DD:EE:FF";
```

> `config.h` is gitignored to prevent accidental credential leaks.

### MQTT Topics

| Topic | Direction | Description |
|---|---|---|
| `esp32/command` | Subscribe | Commands sent to the ESP32 |
| `esp32/status` | Publish | Status messages from the ESP32 |

### MQTT Commands

| Command | Description |
|---|---|
| `WOL` | Send a WoL magic packet |
| `STATUS` | Return current status |
| `REBOOT` | Restart the ESP32 |

## Usage

### Firmware

1. Open `esp/main/main.ino` in Arduino IDE
2. Select board: **ESP32S3 Dev Module**
3. Switch **USB CDC On Boot** to **Enabled**
4. Configure and upload
