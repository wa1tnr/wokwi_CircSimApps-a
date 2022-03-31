// Wed 30 Mar 10:21:14 UTC 2022 - ONLINE edit

// rp2040.cpp

// #include <Arduino.h>


#include "pico/stdlib.h"




#include "program.h"

// Forth code words

#define BLINK_TIME 80
#define DELTA_TIME 700

void quickly(void) {
sleep_ms(50);
#if 0
    int elapsed=millis();
    do {
        for (volatile int slow = 3; slow > 0; slow--) { }
    } while ((millis() - elapsed) < BLINK_TIME);
#endif
}

void slowly(void) {
sleep_ms(250);
#if 0
    int elapsed=millis();
    do {
        for (volatile int slow = 3; slow > 0; slow--) { }
    } while ((millis() - elapsed) < (BLINK_TIME + DELTA_TIME));
#endif
}

void _reflashing(void) {
    // reflash_firmware();
}

void _blink_led(void) {
    // digitalWrite(LED_BUILTIN, 1);
    quickly();
    // digitalWrite(LED_BUILTIN, 0);
    slowly();
}
