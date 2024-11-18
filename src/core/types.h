#pragma once

// Unsigned integers
typedef unsigned char       u8;     // 8 bits
typedef unsigned short     u16;    // 16 bits
typedef unsigned long      u32;    // 32 bits
typedef unsigned long long u64;    // 64 bits

// Signed integers
typedef signed char        s8;     // 8 bits
typedef signed short      s16;    // 16 bits
typedef signed long       s32;    // 32 bits
typedef signed long long  s64;    // 64 bits

// Floating point
typedef float            f32;    // 32 bits
typedef double          f64;    // 64 bits

// Boolean type
typedef enum {
    FALSE = 0,
    TRUE = 1
} bool_t;

// Function pointer types
typedef void (*voidfunc_t)(void);
typedef void (*taskfunc_t)(void*);

// Size type for memory operations
typedef u16 size_t;

// Null pointer
#define NULL_FUNC ((voidfunc_t)0)
#define NULL_STR  ((const char*)0)
#define NULL_PTR  ((void*)0)

// Memory alignment
#define ALIGN(x) __attribute__((aligned(x)))

// Volatile for hardware registers
#define REG_8(addr)                  (*(volatile u8*)(addr))
#define REG_16(addr)                 (*(volatile u16*)(addr))
#define REG_32(addr)                 (*(volatile u32*)(addr))

namespace System {
    enum TaskPriority {
        CRITICAL = 0,
        HIGH = 1,
        NORMAL = 2,
        LOW = 3
    };

    struct Task {
        void (*function)();
        unsigned long interval;
        unsigned long lastRun;
        bool enabled;
        const char* name;
        bool isKernelTask;
        TaskPriority priority;
        unsigned int stackSize;
    };
}