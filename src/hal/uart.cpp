#include "uart.h"
#include "../core/bits.h"
#include "registers.h"
#include "../kernel/interrupt.h"

void uart_init(uart_config_t* config) {
    // Disable interrupts during initialization
    cli();
    
    // Calculate baud rate register value
    u16 ubrr = (F_CPU / (16 * config->baud_rate)) - 1;
    
    // Set baud rate registers
    REG_8(UBRR0H_BASE) = (u8)(ubrr >> 8);
    REG_8(UBRR0L_BASE) = (u8)ubrr;
    
    // Enable receiver and transmitter
    REG_8(UCSR0B_BASE) = BIT(4) | BIT(3);  // RXEN0 and TXEN0
    
    // Set frame format: 8 data bits, 1 stop bit, no parity
    REG_8(UCSR0C_BASE) = BIT(2) | BIT(1);  // UCSZ01 and UCSZ00
    
    // Clear any pending interrupts
    REG_8(UCSR0A_BASE) = 0;
    
    // Flush receive buffer
    while(REG_8(UCSR0A_BASE) & BIT(7)) {
        volatile u8 dummy = REG_8(UDR0_BASE);
        (void)dummy;
    }
    
    // Re-enable interrupts
    sei();
}

bool_t uart_data_ready(void) {
    return (REG_8(UCSR0A_BASE) & BIT(7)) ? TRUE : FALSE;  // RXC0 bit
}

void uart_send_byte(u8 data) {
    // Wait for transmit buffer to be empty
    while(!(REG_8(UCSR0A_BASE) & BIT(5)));  // UDRE0 bit
    REG_8(UDR0_BASE) = data;
}

u8 uart_receive_byte(void) {
    // Wait for data
    while(!(REG_8(UCSR0A_BASE) & BIT(7)));  // RXC0 bit
    return REG_8(UDR0_BASE);
}

void uart_print(const char* str) {
    while(*str) {
        uart_send_byte((u8)*str++);
    }
}

void uart_println(const char* str) {
    uart_print(str);
    uart_print("\r\n");
}

void uart_print_hex(u32 num) {
    u8 i;
    u8 digit;
    bool_t leading_zero = TRUE;

    uart_print("0x");

    for(i = 0; i < 8; i++) {
        digit = (num >> (28 - i * 4)) & 0xF;
        
        if(digit != 0 || !leading_zero || i == 7) {
            leading_zero = FALSE;
            uart_send_byte((u8)(digit < 10 ? '0' + digit : 'A' + digit - 10));
        }
    }
}