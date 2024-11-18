#include "interrupt.h"

#define MAX_HANDLERS 32

static struct {
    u8 vector;
    isr_handler_t handler;
} interrupt_handlers[MAX_HANDLERS];

static u8 handler_count = 0;

void interrupt_register_handler(u8 vector, isr_handler_t handler) {
    if (handler_count >= MAX_HANDLERS) return;
    
    interrupt_handlers[handler_count].vector = vector;
    interrupt_handlers[handler_count].handler = handler;
    handler_count++;
}