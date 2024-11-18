#include "src/core/types.h"
#include "src/hal/registers.h"
#include "src/hal/gpio.h"
#include "src/hal/uart.h"
#include "src/hal/uart_cmd.h"
#include "src/drivers/led.h"
#include "src/kernel/scheduler.h"
#include "src/kernel/interrupt.h"
#include "include/config.h"

// Task functions
static void led_task(void) {
    static bool_t led_state = FALSE;
    if (led_state) {
        led_off(LED_PIN);
        led_state = FALSE;
    } else {
        led_on(LED_PIN);
        led_state = TRUE;
    }
}

// Use a static flag in .noinit section to maintain state across resets
static volatile bool_t __attribute__((section(".noinit"))) first_boot;

// Initialization function
static void os_init(void) {
    static bool_t initialized = FALSE;
    
    if (initialized) return;
    initialized = TRUE;

    // Initialize hardware
    init_hardware();
    
    // Initialize LED
    led_init(LED_PIN);
    
    // Initialize UART with delay
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD,
        .data_bits = 8,
        .stop_bits = 1,
        .parity_enabled = FALSE
    };
    uart_init(&uart_config);
    
    // Small delay after UART init
    for(volatile u32 i = 0; i < 10000; i++) {
        asm volatile("nop");
    }
    
    // Initialize scheduler
    scheduler_init();
    
    // Add tasks
    scheduler_add_task(led_task, 1000, "LED_Blink");
    
    // Start scheduler
    scheduler_start();
    
    // Enable interrupts
    sei();

    uart_println("ArduinOS Started!");
    
    if (first_boot) {
        first_boot = FALSE;
    }
    
    // Initialize command interface last
    cmd_init();
}

// Override Arduino's weak setup/loop
extern "C" {
    void setup(void) __attribute__((weak));
    void loop(void) __attribute__((weak));
}

void setup() {
    os_init();
}

void loop() {
    static bool_t in_loop = FALSE;
    
    if (!in_loop) {
        in_loop = TRUE;
        cmd_process();
    }
}

// Our main function
int main(void) {
    setup();
    while(1) {
        loop();
        asm volatile("nop");
    }
    return 0;
}

// Timer interrupt handler
ISR(TIMER0_OVF_vect) {
    scheduler_tick();
}