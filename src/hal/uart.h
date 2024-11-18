#pragma once
#include "../core/types.h"

// UART configuration structure
typedef struct {
    u32 baud_rate;
    u8 data_bits;
    u8 stop_bits;
    bool_t parity_enabled;
} uart_config_t;

// UART functions
void uart_init(uart_config_t* config);
bool_t uart_data_ready(void);
void uart_send_byte(u8 data);
u8 uart_receive_byte(void);
void uart_print(const char* str);
void uart_println(const char* str);
void uart_print_hex(u32 num);