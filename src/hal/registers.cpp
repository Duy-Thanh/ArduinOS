#include "registers.h"
#include "../core/bits.h"

void init_hardware(void) {
    // Disable watchdog
    REG_8(0x60) = 0x00;  // WDTCSR register

    // Configure clock
    REG_8(0x61) = 0x80;  // CLKPR register - enable change
    REG_8(0x61) = 0x00;  // CLKPR register - set prescaler to 1

    // Initialize ports to known state
    REG_8(DDRB_BASE) = 0x00;   // Set all PORTB pins as inputs initially
    REG_8(DDRD_BASE) = 0x00;   // Set all PORTD pins as inputs initially
    REG_8(DDRC_BASE) = 0x00;   // Set all PORTC pins as inputs initially

    // Disable all pull-ups initially
    REG_8(PORTB_BASE) = 0x00;
    REG_8(PORTD_BASE) = 0x00;
    REG_8(PORTC_BASE) = 0x00;
    
    // Small delay after initialization
    for(volatile u32 i = 0; i < 1000; i++) {
        asm("nop");
    }
}