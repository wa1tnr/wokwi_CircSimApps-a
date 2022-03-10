// factored one function 'cls()'
// previous commit ran fine. ;)
// Thu 10 Mar 12:56:53 UTC 2022 bcd ONLINE edit
// n_sketch_morse.cpp ORIG: MorsecodeToLedstrip.ino

// 9 March 2022, Version 1, by Koepel, Public Domain

#include <Arduino.h>
#include <FastLED.h>
#include "sketch_morse.h"

CRGB leds[NUM_LEDS];

const int potPin = A0;

byte buffer[40];

// very first factored function to clear the display:
void cls(void) {
    for( int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB::AntiqueWhite; // BACKGROUND_COLOR;
    }
    FastLED.show();
}

void setup(void) {
    Serial.begin(115200); Serial.write(' ');
    Serial.println("yj724b-aa");

    FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
    cls(); // new function 12:50z
}


void loop(void) {
    EVERY_N_MILLISECONDS( 100) { // from the FastLED library
        for( int i=NUM_LEDS-1; i>0; i--) {
            leds[i] = leds[i-1];
        }
        leds[0] = BACKGROUND_COLOR; // background color as default
        int n = strlen( buffer);
        if( n > 0) {
            if( buffer[0] != ' ') { #warning NESTED IF LINE 43
                leds[0] = FOREGROUND_COLOR;
            }
        for( int i=0; i<n; i++) {
            buffer[i] = buffer[i+1];
        }
        } // end of nested IF
        FastLED.show(); // make the leds[] data visible
    } // end of every n millisec - good candidate for factoring

if( strlen( buffer) == 0) // ready to accept new data ?
{
if( Serial.available() > 0)
{
byte serialChar = Serial.read();
serialChar = toupper( serialChar); // no lower case in the morse code

// search for character in the table
bool marker = false; // a test for '#' marker
bool found = false;
int index;
byte morseChar;

for( index=0; index<strlen_P(morseTable); index++)
{ 
byte morseChar = pgm_read_byte_near( morseTable + index);

if( marker) // was previous character the marker ?
{
if( serialChar == morseChar) // found the ASCII character ?
{
found = true;
break;
}
}

if( morseChar = '#') // found marker ?
marker = true;
else
marker = false;
}

if( found)
{
// Convert the character into morse code and put it in the buffer
// This is the hard part
// For now, just use a fixed pattern
index++; // point to data after the ASCII character
do
{
morseChar = pgm_read_byte_near( morseTable + index);

if( morseChar == '#') // marker for new character ?
{
break;
}
else
{
if( morseChar == '.')
strcat( buffer, "X ");
else if( morseChar == '-')
strcat( buffer, "XXX ");
else if( morseChar == ' ')
strcat( buffer, " ");
}

index++;

} while( morseChar != '\0');
strcat( buffer, " "); // spacing between characters
}
else
{
Serial.print("Character not found in morse table: ");
// The isPrintable() is a Arduino function
// The isprint() is a 'C' function
if( isprint( serialChar)) 
{
Serial.print( (char) serialChar);
}
else
{
Serial.print( "0x");
if( serialChar < 0x10)
Serial.print( "0");
Serial.print( serialChar, HEX);
}
Serial.println();
}
} 
}
}
// END.
