#pragma once
#include "../core/types.h"

// Timer modes
typedef enum {
    TIMER_MODE_NORMAL = 0,
    TIMER_MODE_CTC = 1,
    TIMER_MODE_PWM = 2
} timer_mode_t;

// Timer prescaler values
typedef enum {
    TIMER_PRESCALER_0 = 0,         // Timer stopped
    TIMER_PRESCALER_1 = 1,         // No prescaling
    TIMER_PRESCALER_8 = 2,         // 8 prescaling
    TIMER_PRESCALER_64 = 3,        // 64 prescaling
    TIMER_PRESCALER_256 = 4,       // 256 prescaling
    TIMER_PRESCALER_1024 = 5       // 1024 prescaling
} timer_prescaler_t;

// Timer control functions
void timer0_init(timer_mode_t mode, timer_prescaler_t prescaler);
void timer0_set_compare(u8 value);
void timer0_enable_interrupt(void);
void timer0_disable_interrupt(void);
