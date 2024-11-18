#include "led.h"

void led_init(u8 pin) {
    gpio_set_direction(pin, PIN_OUTPUT);
    gpio_write(pin, PIN_LOW);  // Start with LED off
}

void led_on(u8 pin) {
    gpio_write(pin, PIN_HIGH);
}

void led_off(u8 pin) {
    gpio_write(pin, PIN_LOW);
}

void led_toggle(u8 pin) {
    // Get current pin state and toggle it
    pin_state_t current_state = gpio_read(pin);
    gpio_write(pin, current_state == PIN_LOW ? PIN_HIGH : PIN_LOW);
}