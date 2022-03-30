// Wed 30 Mar 10:21:14 UTC 2022

// warn 002: #warning seen compatibility.h

#undef  RP2040_VARIANT
#define RP2040_VARIANT

#ifdef RP2040_VARIANT
#define RP2040_PRESENT -1 // TRUE
#endif

#ifndef RP2040_VARIANT
#define RP2040_PRESENT -0 // FALSE
#endif
