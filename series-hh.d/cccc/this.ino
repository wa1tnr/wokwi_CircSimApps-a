// Thu 17 Nov 00:55:29 UTC 2022
// https://wokwi.com/projects/348532661122237011

void setup() {
    Serial.begin(9600);
    Serial.write(' '); // opens the terminal
}

char ch, junk;
uint16_t junk_count;

void scan_loop() {
    int available = Serial.available();
    bool waiting = available > 1;
    if (!waiting) {
        return;
    }
    Serial.print("  SERIAL seen  ");
    ch = Serial.read(); // read the keystroke
    if (Serial.available() == 1) {
        junk = Serial.read();
        if (junk == 10) {
            junk_count++; // placeholder for ASCII 10 detect
        }
    }
    Serial.print((char) (ch + 1));
}

void action() {
    // if (ch == 'b') {
    if (ch == 98) {
        ch = '\0'; // null
        Serial.print("  SAW 'b'  ");
    }
}

void loop() {
    scan_loop();
    action();
}

// END.
