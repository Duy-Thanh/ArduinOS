#pragma once
#include "../core/types.h"

// Task structure
typedef struct {
    void (*function)(void);    // Task function pointer
    u32 interval;              // Task interval in milliseconds
    u32 last_run;             // Last run timestamp
    bool_t enabled;            // Task enabled flag
    const char* name;          // Task name
} task_t;

// Scheduler functions
void scheduler_init(void);
void scheduler_start(void);
void scheduler_tick(void);
bool_t scheduler_add_task(void (*function)(void), u32 interval, const char* name);
void scheduler_remove_task(u8 task_id);
void scheduler_enable_task(u8 task_id);
void scheduler_disable_task(u8 task_id);