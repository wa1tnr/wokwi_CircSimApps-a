// Thu 10 Mar 11:58:18 UTC 2022
// ORIG: MorsecodeToLedstrip.ino

// For: https://forum.arduino.cc/t/making-a-long-memory-led-chase-sequence/967584/

// 9 March 2022, Version 1, by Koepel, Public Domain
//   Working a little, not checked, not a good sketch, it is bad in some parts.

//   By using a buffer between the conversion table and the ledstrip,
//   it is easier to translate the (compact) conversion table and shift
//   the pattern to the ledstrip.
//   That buffer also makes it easy to add color information.

#include <FastLED.h>

#define LED_PIN  5
#define NUM_LEDS 240     // 240 leds could be possible with an Arduino Uno

CRGB leds[NUM_LEDS];     // leds[0] is the first led on the left

#define BACKGROUND_COLOR CRGB::Blue       // the background color for the ledstrip
#define FOREGROUND_COLOR CRGB::Red        // the morse code foreground color

const int potPin = A0;

byte buffer[40];  // a buffer that holds the morse code to be shifted into the ledstrip

#define MORSE_DOT '.'
#define MORSE_DASH '-'
#define MORSE_INTERCODE ' '
#define MORSE_INTERCHAR '#'

#define MORSE_DOT_LENGTH 1
#define MORSE_DASH_LENGTH 3
#define MORSE_INTERCODE_LENGTH 3
#define MORSE_INTERCHAR_LENGTH 8

// The conversion text for the morse code is made for:
//   - showing the morse code in readable format.
//   - compact
//   - code that needs time to search is okay
const byte morseTable[] PROGMEM =
  "#  "            // something special, a space, that is a gap between words
  "#A.-"           // ASCII character is 'A' code is ".-" no spaces in code
  "#B-..."
  "#C-.-."
  "#D-.."
  "#E."
  "#F..-."
  "#G--."
  "#H...."
  "#I.."
  "#J.---"
  "#K-.-"
  "#L.-.."
  "#M--"
  "#N-."
  "#O---"
  "#P.--."
  "#Q--.-"
  "#R.-."
  "#S..."
  "#T-"
  "#U..-"
  "#V...-"
  "#W.--"
  "#X-..-"
  "#Y-.--"
  "#Z--.."
  "#1.----"
  "#2..---"
  "#3...--"
  "#4....-"
  "#5....."
  "#6-...."
  "#7--..."
  "#8---.."
  "#9----."
  "#0-----"
  "#..-.-.-"
  "#;-.-.-."
  "#\--..--"
  "#?..--.."
  "#/-..-."
  "#\r  "                 // end of line, should be a larger gap
  "#\n  "                 // end of line, should be a larger gap
  "#";                    // end of list



void setup() 
{
  Serial.begin(115200);
  Serial.print( "The size of the morse code table is: ");
  Serial.print( sizeof( morseTable));
  Serial.println( " bytes");
  Serial.println("Enter the text");

  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);

  // pre-fill with background.
  for( int i=0; i<NUM_LEDS; i++)
  {
    leds[i] = BACKGROUND_COLOR;
  }
  FastLED.show();
}


void loop() 
{
  EVERY_N_MILLISECONDS( 100)           // from the FastLED library
  {
    // Move the pixels one pixel to the right.
    // If there is no morse data, then there is nothing to shift,
    // but it is shifted anyway.
    for( int i=NUM_LEDS-1; i>0; i--)
    {
      leds[i] = leds[i-1];
    }

    leds[0] = BACKGROUND_COLOR;            // background color as default

    // The buffer contains the new data to be entered into the ledstrip.
    int n = strlen( buffer);
    if( n > 0)
    {
      if( buffer[0] != ' ')
      {
        leds[0] = FOREGROUND_COLOR;
      }

      // Move buffer to the left.
      // The zero-terminator is also copied
      for( int i=0; i<n; i++)
      {
        buffer[i] = buffer[i+1];
      }
    }
    FastLED.show();                // make the leds[] data visible
  }

  if( strlen( buffer) == 0)        // ready to accept new data ?
  {
    if( Serial.available() > 0)
    {
      byte serialChar = Serial.read();
      serialChar = toupper( serialChar);          // no lower case in the morse code

      // search for character in the table
      bool marker = false;         // a test for '#' marker
      bool found = false;
      int index;
      byte morseChar;

      for( index=0; index<strlen_P(morseTable); index++)
      {       
        byte morseChar = pgm_read_byte_near( morseTable + index);
   
        if( marker)                  // was previous character the marker ?
        {
          if( serialChar == morseChar)   // found the ASCII character ?
          {
            found = true;
            break;
          }
        }

        if( morseChar = '#')         // found marker ?
          marker = true;
        else
          marker = false;
      }

      if( found)
      {
        // Convert the character into morse code and put it in the buffer
        // This is the hard part
        // For now, just use a fixed pattern
        index++;           // point to data after the ASCII character
        do
        {
          morseChar = pgm_read_byte_near( morseTable + index);

          if( morseChar == '#')   // marker for new character ?
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
        strcat( buffer, "   ");         // spacing between characters
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
