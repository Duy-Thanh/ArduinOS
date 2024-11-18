
#include "gpio.h"
#include "../core/bits.h"
#include "registers.h"

void gpio_set_direction(u8 pin, pin_direction_t direction) {
    u8 port_num = pin / 8;
    u8 pin_num = pin % 8;
    
    volatile u8* ddr;
    switch (port_num) {
        case 0: ddr = (volatile u8*)DDRD_BASE; break;  // pins 0-7
        case 1: ddr = (volatile u8*)DDRB_BASE; break;  // pins 8-13 (LED is on pin 13 = PB5)
        case 2: ddr = (volatile u8*)DDRC_BASE; break;  // pins 14-19
        default: return;
    }
    
    if (direction == PIN_OUTPUT) {
        *ddr |= (1 << pin_num);
    } else {
        *ddr &= ~(1 << pin_num);
    }
}

void gpio_write(u8 pin, pin_state_t state) {
    u8 port_num = pin / 8;
    u8 pin_num = pin % 8;
    
    volatile u8* port;
    switch (port_num) {
        case 0: port = (volatile u8*)PORTD_BASE; break;  // pins 0-7
        case 1: port = (volatile u8*)PORTB_BASE; break;  // pins 8-13 (LED is on pin 13 = PB5)
        case 2: port = (volatile u8*)PORTC_BASE; break;  // pins 14-19
        default: return;
    }
    
    if (state == PIN_HIGH) {
        *port |= (1 << pin_num);
    } else {
        *port &= ~(1 << pin_num);
    }
}

pin_state_t gpio_read(u8 pin) {
    u8 port_num = pin / 8;
    u8 pin_num = pin % 8;

    volatile u8* port;
    switch (port_num) {
        case 0: port = (volatile u8*)PINB_BASE; break;
        case 1: port = (volatile u8*)PIND_BASE; break;
        default: return PIN_LOW;
    }

    return GET_BIT(*port, pin_num) ? PIN_HIGH : PIN_LOW;
}
