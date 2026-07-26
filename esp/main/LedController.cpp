#include "LedController.h"

LedController::LedController(uint16_t pin, uint8_t brightness) : _led(1, pin, NEO_GRB + NEO_KHZ800), _brightness(brightness) {}

void LedController::init()
{
	_led.begin();
	_led.setBrightness(_brightness);
	_led.show();
}

void LedController::setColor(uint8_t r, uint8_t g, uint8_t b)
{
	_led.setPixelColor(0, r, g, b);
	_led.show();
}

void LedController::off()
{
	setColor(0, 0, 0);
}

void LedController::red()
{
	setColor(255, 0, 0);
}

void LedController::green()
{
	setColor(0, 255, 0);
}

void LedController::blue()
{
	setColor(0, 0, 255);
}

void LedController::white()
{
	setColor(255, 255, 255);
}