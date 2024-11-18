#pragma once
#include "../core/types.h"

// Port B registers (Digital pins 13-8)
#define PORTB_BASE              0x25
#define DDRB_BASE               0x24
#define PINB_BASE               0x23

#define PORTC_BASE              0x28    // Port C Data Register
#define DDRC_BASE               0x27    // Port C Data Direction Register
#define PINC_BASE               0x26    // Port C Input Pins


// Port D registers (Digital pins 7-0)
#define PORTD_BASE              0x2B
#define DDRD_BASE               0x2A
#define PIND_BASE               0x29

// ADC registers
#define ADCL_BASE               0x78
#define ADCH_BASE               0x79
#define ADCSRA_BASE             0x7A
#define ADMUX_BASE              0x7C

// Timer registers
#define TCCR0A_BASE             0x44    // Timer/Counter Control Register A
#define TCCR0B_BASE             0x45    // Timer/Counter Control Register B
#define TCNT0_BASE              0x46    // Timer/Counter Register
#define OCR0A_BASE              0x47    // Output Compare Register A
#define OCR0B_BASE              0x48    // Output Compare Register B
#define TIMSK0_BASE             0x6E    // Timer/Counter Interrupt Mask Register
#define TIFR0_BASE              0x35    // Timer/Counter Interrupt Flag Register

// UART registers
#define UBRR0H_BASE             0xC5    // USART Baud Rate Register High
#define UBRR0L_BASE             0xC4    // USART Baud Rate Register Low
#define UCSR0A_BASE             0xC0    // USART Control and Status Register A
#define UCSR0B_BASE             0xC1    // USART Control and Status Register B
#define UCSR0C_BASE             0xC2    // USART Control and Status Register C
#define UDR0_BASE               0xC6    // USART I/O Data Register

// Direct register access
#define PORTB                   REG_8(PORTB_BASE)
#define DDRB                    REG_8(DDRB_BASE)
#define PINB                    REG_8(PINB_BASE)

// GPIO control
struct GPIO_t {
    u8 pin;
    u8 port;
    u8 ddr;
};

// Basic hardware initialization
void init_hardware(void);