#include "timer.h"
#include "registers.h"
#include "../core/bits.h"

void timer0_init(timer_mode_t mode, timer_prescaler_t prescaler) {
    // Stop timer first
    REG_8(TCCR0B_BASE) = 0;
    REG_8(TCNT0_BASE) = 0;
    
    // Clear any pending interrupts
    REG_8(TIFR0_BASE) = 0xFF;
    
    // Set mode
    switch (mode) {
        case TIMER_MODE_NORMAL:
            REG_8(TCCR0A_BASE) = 0;
            break;
        case TIMER_MODE_CTC:
            REG_8(TCCR0A_BASE) = BIT(1);
            break;
        case TIMER_MODE_PWM:
            REG_8(TCCR0A_BASE) = BIT(0) | BIT(1);
            break;
    }
    
    // Set prescaler (starts timer)
    if (prescaler != TIMER_PRESCALER_0) {
        REG_8(TCCR0B_BASE) = prescaler;
    }
}

void timer0_set_compare(u8 value) {
    REG_8(0x47) = value;
}

void timer0_enable_interrupt(void) {
    SET_BIT(REG_8(TIMSK0_BASE), 0); // TOIE0 bit
}

void timer0_disable_interrupt(void) {
    CLEAR_BIT(REG_8(TIMSK0_BASE), 0); // TOIE0 bit
}
