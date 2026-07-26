#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Adafruit_NeoPixel.h>

class LedController
{
public:
	LedController(uint16_t pin, uint8_t brightness);
	void init();
	void setColor(uint8_t r, uint8_t g, uint8_t b);
	void off();
	void red();
	void green();
	void blue();
	void white();

private:
	Adafruit_NeoPixel _led;
	uint8_t _brightness;
};

#endif