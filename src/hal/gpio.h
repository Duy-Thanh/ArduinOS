#pragma once
#include "../core/types.h"

// Pin direction
typedef enum {
    PIN_INPUT = 0,
    PIN_OUTPUT = 1
} pin_direction_t;

// Pin state
typedef enum {
    PIN_LOW = 0,
    PIN_HIGH = 1
} pin_state_t;

// GPIO functions
void gpio_set_direction(u8 pin, pin_direction_t dir);
void gpio_write(u8 pin, pin_state_t state);
pin_state_t gpio_read(u8 pin);
