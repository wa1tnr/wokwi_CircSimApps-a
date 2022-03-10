// Thu 10 Mar 20:54:58 UTC 2022 cd lmno OFFLINE datestamped edit
// bit of a mess now. ;)

#define ID_IN_SERIAL_MON(x) Serial.println("yj724b-ii")

// 13:17z - factored 'every_n_ms()'

// factored one function 'cls()'

// n_sketch_morse.cpp ORIG: MorsecodeToLedstrip.ino

// 9 March 2022, Version 1, by Koepel, Public Domain

#include <Arduino.h>
#include <FastLED.h>
#include "sketch_morse.h"

CRGB leds[NUM_LEDS];

const int potPin = A0;

byte buffer[80];

// very first factored function to clear the display:
void cls(void) {
  for ( int i = 0; i < NUM_LEDS + 0; i++) {
    leds[i] = CRGB::AntiqueWhite; // BACKGROUND_COLOR;
  }
  FastLED.show();
}

unsigned long counter = 0;

// second factored function to do something every n milliseconds
void every_n_ms(bool calling) {
  EVERY_N_MILLISECONDS( 200) { // from the FastLED library
    counter++;
    // TRAP:
    if (counter > 999999) {
      while (-1);
    }
    // void bump_leds(void) {
    for ( int i = NUM_LEDS - 1; i > 0; i--) {
      leds[i] = leds[i - 1];
    }
    // }

    leds[0] = LEAD_OR_TRAIL; // BACKGROUND_COLOR;

    bool not_trunc = false;
    bool nospace = false;
    int n = strlen(buffer);

    if (n > 0) {
      not_trunc = true;  // not_truncated
    }
    if (buffer[0] != ' ') {
      nospace = true;
    }
    if (not_trunc & nospace) {
      leds[0] = FOREGROUND_COLOR;
    }
    if (not_trunc & !nospace) {
      leds[0] = CRGB::Turquoise;
    }

    for ( int i = 0; i < n; i++) {
      buffer[i] = buffer[i + 1];
    }
    FastLED.show(); // make the leds[] data visible
  }
}

void interchar_sp(void) {
  strcat( buffer, "     "); // spacing between characters
}

void setup(void) {
  Serial.begin(115200); Serial.write(' ');
  buffer[0] = '\0';
  ID_IN_SERIAL_MON();
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  cls();
}

void loop(void) {
  bool call = false;
  every_n_ms(call);

  if (strlen( buffer) == 0) { // ready to accept new data ?
    int available_chars = Serial.available();
    if ( available_chars > 0) {
      byte serialChar = Serial.read();
      serialChar = toupper( serialChar); // no lower case in the morse code
      if (available_chars == 1) {
        call = true;
      }
      if (call) {
        interchar_sp();
      }

      // search for character in the table
      bool marker = false; // a test for '#' marker
      bool found = false;
      int index;
      byte morseChar;

      for ( index = 0; index < strlen_P(morseTable); index++) {
        byte morseChar = pgm_read_byte_near( morseTable + index);

        if ( marker) { // was previous character the marker ?
          if ( serialChar == morseChar) { // found the ASCII character ?
            found = true;
            break;
          }
        }

        if ( morseChar = '#') // found marker ?
          marker = true;
        else
          marker = false;
      }

      if ( found) {
        // Convert the character into morse code and put it in the buffer
        // This is the hard part
        // For now, just use a fixed pattern
        index++; // point to data after the ASCII character
        do {
          morseChar = pgm_read_byte_near( morseTable + index);
          if ( morseChar == '#') { // marker for new character ?
            break;
          } else {
            if ( morseChar == '.')
              strcat( buffer, "X ");
            else if ( morseChar == '-')
              strcat( buffer, "XXX ");
            else if ( morseChar == ' ')
              strcat( buffer, " ");
          }
          index++;
        } while (morseChar != '\0');
        interchar_sp();
      } else {
        Serial.print("Character not found in morse table: ");
        if (isprint( serialChar)) {
          Serial.print( (char) serialChar);
        } else {
          Serial.print( "0x");
          if ( serialChar < 0x10)
            Serial.print( "0");
          Serial.print( serialChar, HEX);
        }
        Serial.println();
      }
    }
  }
}
// END.
