#include "../src/core/types.h"
#include "../src/hal/registers.h"
#include "../src/hal/gpio.h"
#include "../src/hal/uart.h"
#include "../src/drivers/led.h"
#include "../src/kernel/scheduler.h"
#include "../src/kernel/interrupt.h"
#include "../include/config.h"

// Forward declarations
extern "C" {
    void __vector_default(void) __attribute__((weak, interrupt));
    void reset_handler(void) __attribute__((naked, section(".init0")));
    void __vector_16(void) __attribute__((signal, used));  // Timer0 overflow vector
}

// Default interrupt handler
void __vector_default(void) {
    while (1);
}

// Task functions
static void led_task(void) {
    led_toggle(LED_PIN);
}

static void uart_task(void) {
    uart_println("System running...");
}

// Vector table
__attribute__((section(".vectors")))
void (* const vector_table[])(void) = {
    reset_handler,                // Reset vector
    __vector_default,            // External Interrupt 0
    __vector_default,            // External Interrupt 1
    __vector_default,            // External Interrupt 2
    __vector_default,            // External Interrupt 3
    __vector_default,            // External Interrupt 4
    __vector_default,            // External Interrupt 5
    __vector_default,            // External Interrupt 6
    __vector_default,            // External Interrupt 7
    __vector_default,            // Pin Change Interrupt 0
    __vector_default,            // Pin Change Interrupt 1
    __vector_default,            // Pin Change Interrupt 2
    __vector_default,            // Watchdog Timeout
    __vector_default,            // Timer/Counter2 Compare A
    __vector_default,            // Timer/Counter2 Compare B
    __vector_default,            // Timer/Counter2 Overflow
    __vector_16,                 // Timer/Counter0 Overflow
};

// Reset handler
void reset_handler(void) {
    // Initialize stack pointer
    asm volatile (
        "ldi r16, 0x21"    "\n\t"
        "out 0x3E, r16"    "\n\t"
        "ldi r16, 0xFF"    "\n\t"
        "out 0x3D, r16"    "\n\t"
        :::"r16"
    );
    
    // Initialize hardware
    init_hardware();
    
    // Initialize LED
    led_init(LED_PIN);
    
    // Initialize UART
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD,
        .data_bits = 8,
        .stop_bits = 1,
        .parity_enabled = FALSE
    };
    uart_init(&uart_config);
    
    // Initialize scheduler
    scheduler_init();
    
    // Add tasks
    scheduler_add_task(led_task, 1000, "LED_Blink");    // LED blink every 1000ms
    scheduler_add_task(uart_task, 5000, "UART_Status"); // UART message every 5000ms
    
    // Start scheduler
    scheduler_start();
    
    // Enable interrupts
    sei();
    
    uart_println("ArduinOS Started!");

    // Main loop
    while(1) {
        asm("nop");
    }
}

// Timer interrupt handler
void __vector_16(void) {
    scheduler_tick();
}