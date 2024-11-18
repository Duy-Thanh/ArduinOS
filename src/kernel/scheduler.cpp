#include "scheduler.h"
#include "../hal/timer.h"
#include "../../include/config.h"

// Task array
static task_t tasks[MAX_TASKS];
static u8 task_count = 0;

void scheduler_init(void) {
    task_count = 0;
    for(u8 i = 0; i < MAX_TASKS; i++) {
        tasks[i].function = NULL_FUNC;  // Use NULL_FUNC instead of NULL
        tasks[i].interval = 0;
        tasks[i].last_run = 0;
        tasks[i].enabled = FALSE;
        tasks[i].name = NULL_STR;      // Use NULL_STR instead of NULL
    }
}

bool_t scheduler_add_task(void (*function)(void), u32 interval, const char* name) {
    if(task_count >= MAX_TASKS) return FALSE;
    
    tasks[task_count].function = function;
    tasks[task_count].interval = interval;
    tasks[task_count].last_run = 0;
    tasks[task_count].enabled = TRUE;
    tasks[task_count].name = name;
    
    task_count++;
    return TRUE;
}

void scheduler_remove_task(u8 task_id) {
    if(task_id >= task_count) return;
    
    // Shift remaining tasks
    for(u8 i = task_id; i < task_count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    
    task_count--;
}

void scheduler_enable_task(u8 task_id) {
    if(task_id < task_count) {
        tasks[task_id].enabled = TRUE;
    }
}

void scheduler_disable_task(u8 task_id) {
    if(task_id < task_count) {
        tasks[task_id].enabled = FALSE;
    }
}

void scheduler_tick(void) {
    static u32 tick_count = 0;
    tick_count++;
    
    for(u8 i = 0; i < task_count; i++) {
        if(!tasks[i].enabled || tasks[i].function == NULL_FUNC) continue;
        
        if(tasks[i].interval == 0) {
            tasks[i].function();  // Run immediately for interval 0
            continue;
        }
        
        if(tick_count % tasks[i].interval == 0) {
            tasks[i].last_run = tick_count;
            tasks[i].function();
        }
    }
}

void scheduler_start(void) {
    // Initialize Timer0 for 1ms ticks
    timer0_init(TIMER_MODE_NORMAL, TIMER_PRESCALER_64);
    timer0_enable_interrupt();
}