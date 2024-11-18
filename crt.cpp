#include <avr/io.h>

// Forward declarations
extern "C" {
    int main(void);
}

// Reset vector and minimal vector table
void __attribute__((section(".vectors"))) __vectors(void) {
    asm volatile (
        "jmp __init"  "\n\t"    // Reset Vector
        ".skip 100"   "\n\t"    // Skip space for other vectors
    );
}

// Startup code
void __attribute__((naked, used, section(".init0"))) __init(void) {
    // Initialize stack pointer
    asm volatile (
        "ldi r16, 0x21"    "\n\t"
        "out 0x3E, r16"    "\n\t"
        "ldi r16, 0xFF"    "\n\t"
        "out 0x3D, r16"    "\n\t"
        :::"r16"
    );
    
    // Call main
    main();
    
    // If main returns, loop forever
    while(1);
}