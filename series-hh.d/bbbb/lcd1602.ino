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
uint32_t curr_ms = START_MS;
uint32_t prev_ms = START_MS;

void loop() {

  raw_ms = millis();

  uint32_t result = raw_ms - prev_ms;
  Serial.print(result); Serial.print(" ");

  if (result > 4000) {
    prev_ms = curr_ms;
    curr_ms = raw_ms;
    Serial.write('z'); Serial.write(' ');
  }

}
// 04:39:22z
// END.