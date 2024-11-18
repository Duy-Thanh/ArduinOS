#pragma once

// System Configuration
#define OS_VERSION             "1.0.0"
#define F_CPU                  16000000UL

// Memory Configuration
#define STACK_SIZE             0x0400      // 1KB stack
#define HEAP_SIZE              0x0800      // 2KB heap
#define RAM_START              0x0100      // Start of RAM
#define RAM_END                0x21FF      // End of RAM (8KB)

// Task Configuration
#define MAX_TASKS              16
#define MAX_PRIORITY_LEVELS    4
#define TASK_STACK_SIZE        128

// Hardware Configuration
#define LED_PIN                13          // Built-in LED pin (Digital 13)
#define UART_BAUD              115200