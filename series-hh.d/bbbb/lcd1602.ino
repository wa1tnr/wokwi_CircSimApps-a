// LCD1602 to Arduino Uno connection example

#include <LiquidCrystal.h>

#define START_MS 0

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() {
  Serial.begin(9600);
  Serial.write(' ');
  lcd.begin(16, 2);
  lcd.print("Hello World!");
}

uint32_t raw_ms = millis();
uint32_t prev_ms = START_MS;

#define DEBUG_AL
#undef DEBUG_AL

uint16_t clock = 0;

void loop() {

  raw_ms = millis();

  uint32_t result = raw_ms - prev_ms;

#ifdef DEBUG_AL
  Serial.print(result); Serial.print(" ");
#endif

  if (result > 249) { // print seconds every n milliseconds

    clock = clock + result;

// modulo 60 seconds:
    if (clock > 59999) { clock = 0; }

    uint8_t scaled_clock = clock / 1000;
    prev_ms = raw_ms;

    if (scaled_clock < 10) { Serial.print("0");}
    if (scaled_clock < 100)  { Serial.print("0");}

    Serial.print(scaled_clock);
    // Serial.write('z');
    Serial.write(' ');
  }
}
// 06:37:54z
// END.