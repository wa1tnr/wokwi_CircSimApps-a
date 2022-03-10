// Thu 10 Mar 15:35:33 UTC 2022 cd
// sketch_morse.h

// 9 March 2022, Version 1, by Koepel, Public Domain

// #include <Arduino.h>
// #include <FastLED.h>

#define LED_PIN  5
#define NUM_LEDS 24 // 240

#define BACKGROUND_COLOR CRGB::Blue
#define FOREGROUND_COLOR CRGB::Red

#define MORSE_DOT '.'
#define MORSE_DASH '-'
#define MORSE_INTERCODE ' '
#define MORSE_INTERCHAR '#'

#define MORSE_DOT_LENGTH 1
#define MORSE_DASH_LENGTH 3
#define MORSE_INTERCODE_LENGTH 3
#define MORSE_INTERCHAR_LENGTH 8

const byte morseTable[] PROGMEM =
  "#  " // a space; a gap between words
  "#A.-" "#B-..." "#C-.-." "#D-.." "#E." "#F..-."
  "#G--." "#H...." "#I.." "#J.---" "#K-.-" "#L.-.."
  "#M--" "#N-." "#O---" "#P.--." "#Q--.-" "#R.-."
  "#S..." "#T-" "#U..-" "#V...-" "#W.--" "#X-..-"
  "#Y-.--" "#Z--.." "#1.----" "#2..---" "#3...--"
  "#4....-" "#5....." "#6-...." "#7--..." "#8---.."
  "#9----." "#0-----" "#..-.-.-" "#;-.-.-."
  "#\--..--" "#?..--.." "#/-..-."
  "#\r  " "#\n  "
  "#";

// END.
