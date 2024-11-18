#pragma once
#include "../core/types.h"

// Interrupt vectors
#define TIMER0_OVF_vect __vector_16
#define TIMER0_COMP_vect __vector_17
#define UART_RX_vect __vector_18
#define UART_TX_vect __vector_19

// Interrupt attributes
#define ISR(vector) \
    void vector(void) __attribute__((signal, used, externally_visible)); \
    void vector(void)

// Interrupt control
#define cli() __asm__ __volatile__("cli" ::: "memory")
#define sei() __asm__ __volatile__("sei" ::: "memory")

// Interrupt handler registeration
typedef void (*isr_handler_t)(void);
void interrupt_register_handler(u8 vector, isr_handler_t handler);
