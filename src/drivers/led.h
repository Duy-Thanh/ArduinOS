#pragma once
#include "../core/types.h"
#include "../hal/gpio.h"

// LED control functions
void led_init(u8 pin);
void led_on(u8 pin);
void led_off(u8 pin);
void led_toggle(u8 pin);