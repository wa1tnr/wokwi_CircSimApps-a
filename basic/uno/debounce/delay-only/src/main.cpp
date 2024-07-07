#include <Arduino.h>

const uint8_t LED_LOCAL = 11;
uint8_t value = 0;
uint16_t countPress = 0;
uint8_t ledState = 0;

void toggleLED() {
    ledState = !ledState;
    digitalWrite(LED_LOCAL, ledState);
}

uint8_t pbSwitchHandler() {
    if (value) {
        value = 0;
        toggleLED();
        countPress++;
        return 1;
    }
    return 0;
}

uint16_t responseDamping = 12; // milliseconds

void scanPbSwitch() {
    value = digitalRead(9);
    delay(responseDamping);
}

uint8_t scanning() {
    uint8_t result = 0;
    for (int scans = 3; scans > 0; scans--) {
        scanPbSwitch();
        result = pbSwitchHandler();
        return result;
    }
    return result;
}

void report() {
    Serial.print("   BUTTON_ACTIVE   ");
    Serial.print(countPress);
#if 0
  if (countPress - 1) {
    Serial.println(" times.");
  }
#endif

    if (countPress == 1) {
        Serial.println(" time.");
    } else {
        Serial.println(" times.");
    }
}

void setupSerial() {
    Serial.begin(9600);
    Serial.println("Sun  7 Jul 00:36:23 UTC 2024");
    Serial.println("");
}

void setup() {
    delay(800);
    setupSerial();
    pinMode(9, INPUT);
    pinMode(LED_LOCAL, OUTPUT);
}

void loop() {
    uint8_t result = scanning();
    // value = 0;
    if (result) {
        report();
        delay(430); // inhibit additional reports of same press
    }
}

// Sat  6 Jul 23:04:50 UTC 2024
// Sun  7 Jul 00:36:23 UTC 2024

// end
