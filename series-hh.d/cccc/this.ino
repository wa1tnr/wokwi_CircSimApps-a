// Thu 17 Nov 01:27:03 UTC 2022
// https://wokwi.com/projects/348532661122237011

void setup() {
    Serial.begin(9600);
    Serial.write(' '); // opens the terminal
}

char ch, junk;

void echo_char() {
    Serial.print((char) (ch + 0)); // non-zero proves math
}

bool reading() {
    int available = Serial.available();
    bool waiting = available > 1;
    if (!waiting) {
        return waiting;
    }
    // DEBUG: Serial.print("  SERIAL seen  ");
    ch = Serial.read(); // read the keystroke
    if (Serial.available() == 1) {
        junk = Serial.read();
        // if (junk == 10) { }
    }
    echo_char();
    return waiting;
}

void action() {
    if (ch == 98) { // if (ch == 'b')
        ch = '\0'; // null
        Serial.print("  SAW 'b'  ");
    }
}

void loop() {
    bool was_waiting = reading();
    if (was_waiting) {
        action();
    }
}

// END.
