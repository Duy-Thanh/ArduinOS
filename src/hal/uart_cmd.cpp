#include "uart_cmd.h"
#include "uart.h"
#include "../drivers/led.h"
#include "../kernel/scheduler.h"
#include "../../include/config.h"
#include "../core/string.h"

#define CMD_BUFFER_SIZE 32

static char cmd_buffer[CMD_BUFFER_SIZE];
static u8 cmd_index = 0;
static bool_t led_blink_enabled = FALSE;

// Forward declarations of command handlers
static void cmd_help(void);
static void cmd_led_on(void);
static void cmd_led_off(void);
static void cmd_led_blink(void);
static void cmd_status(void);

// Command table
typedef struct {
    const char *cmd;
    void (*handler)(void);
    const char *help;
} cmd_entry_t;

static const cmd_entry_t commands[] = {
    {"help", cmd_help, "Show this help"},
    {"on", cmd_led_on, "Turn on the LED"},
    {"off", cmd_led_off, "Turn off the LED"},
    {"blink", cmd_led_blink, "Toggle LED blinking"},
    {"status", cmd_status, "Show system status"}
};

#define NUM_COMMANDS (sizeof(commands) / sizeof(cmd_entry_t))

// Command handler implementations
static void cmd_help(void) {
    uart_println("\r\nAvailable commands:");
    for(u8 i = 0; i < NUM_COMMANDS; i++) {
        uart_print("  ");
        uart_print(commands[i].cmd);
        uart_print(" - ");
        uart_println(commands[i].help);
    }
}

static void cmd_led_on(void) {
    led_on(LED_PIN);
    uart_println("LED turned on");
}

static void cmd_led_off(void) {
    led_off(LED_PIN);
    uart_println("LED turned off");
}

static void cmd_led_blink(void) {
    led_blink_enabled = (led_blink_enabled == TRUE) ? FALSE : TRUE;
    uart_print("LED blinking ");
    uart_println(led_blink_enabled == TRUE ? "enabled" : "disabled");
}

static void cmd_status(void) {
    uart_println("\r\nSystem Status:");
    uart_print("LED: ");
    uart_println(gpio_read(LED_PIN) == PIN_HIGH ? "ON" : "OFF");
    uart_print("Blinking: ");
    uart_println(led_blink_enabled == TRUE ? "YES" : "NO");
}

static void execute_command(void) {
    // Null terminate the command
    cmd_buffer[cmd_index] = '\0';
    
    // Skip empty commands
    if(cmd_index == 0) {
        uart_print("> ");
        return;
    }
    
    // Search for command
    bool_t found = FALSE;
    for(u8 i = 0; i < NUM_COMMANDS; i++) {
        if(str_compare(cmd_buffer, commands[i].cmd) == 0) {
            commands[i].handler();
            found = TRUE;
            break;
        }
    }
    
    if(!found) {
        uart_print("Unknown command: ");
        uart_println(cmd_buffer);
        cmd_help();
    }
    
    // Reset buffer and show prompt
    cmd_index = 0;
    uart_print("> ");
}

void cmd_init(void) {
    cmd_index = 0;
    uart_println("\r\nArduinOS Command Interface");
    uart_println("Type 'help' for available commands");
    uart_print("> ");
}

void cmd_process(void) {
    while(uart_data_ready()) {
        u8 c = uart_receive_byte();
        
        // Handle backspace
        if(c == '\b' || c == 0x7F) {
            if(cmd_index > 0) {
                cmd_index--;
                uart_print("\b \b");
            }
        }
        // Handle enter (only process CR)
        else if(c == '\r') {
            uart_println("");
            execute_command();
            break;  // Exit after processing one command
        }
        // Ignore LF
        else if(c == '\n') {
            continue;
        }
        // Add to buffer
        else if(cmd_index < CMD_BUFFER_SIZE - 1) {
            cmd_buffer[cmd_index++] = (char)c;
            uart_send_byte(c);
        }
    }
}