#pragma once

// Bit manipulation macros
#define BIT(x)                      (1 << x)
#define SET_BIT(x, b)               ((x) |= BIT(b))
#define CLEAR_BIT(x, b)             ((x) &= ~BIT(b))
#define TOGGLE_BIT(x, b)            ((x) ^= BIT(b))
#define GET_BIT(x, b)               ((x) & BIT(b))

// Bit field manipulation
#define SET_BITS(x, mask)           ((x) |= (mask))
#define CLEAR_BITS(x, mask)         ((x) &= ~(mask))
#define TOGGLE_BITS(x, mask)        ((x) ^= (mask))
#define GET_BITS(x, mask)           ((x) & (mask))