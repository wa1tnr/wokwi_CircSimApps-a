// n_sketch_clock_lcd.cpp
// Fri 22 Jul 22:02:19 UTC 2022 - +mega +space_aliens offline edit

#include <Arduino.h> // if empty .INO then this is required
#include <LiquidCrystal.h>

#undef AVR_UNO_SELECTED
#if defined(ARDUINO_AVR_UNO)
    #define AVR_UNO_SELECTED  // local flag specific to this very program ;)

#elif defined(__AVR_ATmega2560__)
    #define MEGA_2560_SELECTED
#else
    #error Unsupported board selection.
#endif

#define START_MS 0

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

#ifdef MEGA_2560_SELECTED
    extern void setup_old_timer_mega_2560();
#endif

void setup_lcd() {
  lcd.begin(16, 2);
  lcd.print("Hello World!");
}

void setup() {
  setup_old_timer_mega_2560();
  Serial.write(' ');
  setup_lcd();
}

uint32_t raw_ms = millis();
uint32_t prev_ms = START_MS;

#define DEBUG_AL
#undef DEBUG_AL

uint16_t clock = 0;

#ifdef MEGA_2560_SELECTED
    extern void loop_old_timer_mega_2560();
#endif

void loop() {
  loop_old_timer_mega_2560(); // zero effort to check this


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
