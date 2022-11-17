// Thu 17 Nov 01:24:14 UTC 2022
// https://wokwi.com/projects/348532661122237011

void setup() {
    Serial.begin(9600);
    Serial.write(' '); // opens the terminal
}

char ch, junk;
uint16_t junk_count;

void echo_char() {
    Serial.print(
        (char) (ch + 0)
    );
}

bool reading() {
    int available = Serial.available();
    bool waiting = available > 1;
    if (!waiting) {
        return waiting;
    }
    Serial.print("  SERIAL seen  ");
    ch = Serial.read(); // read the keystroke
    if (Serial.available() == 1) {
        junk = Serial.read();
        if (junk == 10) {
            junk_count++; // placeholder for ASCII 10 detect
        }
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
