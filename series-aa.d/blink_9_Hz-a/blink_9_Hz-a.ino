// Sun  5 Dec 12:54:47 UTC 2021

#define i9_Hz 55 // milliseconds

void pulse_once(int interval) { }

void pulse_at_9_Hz(void) {
        pulse_once(i9_Hz);
}

void pulse(void) { // alias
    pulse_at_9_Hz();
}

void setup_gpio(void) { }

void setup_serial(void) { }

void bring_stuff_up(void) {
    setup_gpio();
    setup_serial();
}

void blinking(void) {
    pulse();
}

void setup(void) {
    bring_stuff_up();
    blinking();
}

void loop(void) {
    while(-1); // endless
}

// END.
