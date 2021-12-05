// Sun  5 Dec 12:54:47 UTC 2021

#define i9_Hz 55 // milliseconds

// target: almost any board will do, including the Uno R3

#define LED 13 // change for your target board

void pulse_once(int interval) { }

void pulse_at_9_Hz(void) {
        pulse_once(i9_Hz);
}

void pulse(void) { // alias
    pulse_at_9_Hz();
}

void setup_gpio(void) {
    pinMode(LED, 1);
    digitalWrite(LED, 0); // turn it off
}

void setup_serial(void) {
    Serial.begin(9600);
    while(!Serial); // hold for serial connection
    delay(100); // superstition
    Serial.println("Program is online now.");
}

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
