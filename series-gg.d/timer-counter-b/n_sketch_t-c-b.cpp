// Tue 15 Mar 15:09:31 UTC 2022
// n_sketch_t-c-b.cpp

// successful code captured - correct buzzer pin used - can hear the audio nice.

// https://github.com/wa1tnr/wokwi_CircSimApps-a/tree/dvlp-aa/series-gg.d/timer-counter-b

// SUCCESS:
// wokwi URI here TODO 15:15z

// NEW:

// https://wokwi.com/projects/326154839088169556

// https://oscarliang.com/arduino-timer-and-interrupt-tutorial/

// OLD (Uno R3-based):
// https://wokwi.com/projects/326126843778302548


#include <Arduino.h>

const byte BUZZER = 2;  // Timer 3 "B" output: OC3B

const long frequency = 50000L;  // Hz

const byte n =   249 ; // fine adjustment of the tone

void setup_timer(void) {
  pinMode (BUZZER, OUTPUT);
  // tone(2, 500); while(-1); // test wiring
// anything 16.something was for 8-bit and is wrong here.

// Arduino MEGA  2560 MCU:
//  5 2 3  mapped to A B or C
// 17.11.2
  TCCR3A =
             bit (COM3B1) // table 17-5
    //     | 
    //         bit (COM3B0) // seems to make constant sound visually in wokwi
           |
          
          bit (WGM30) // Fast PWM, 8-bit table 17-what
  ; 

// IMPORTANT

// setup your tone here using the prescaler bits CS22-CS20:
// 17.11.6
  TCCR3B =
    //       bit (ICNC3)
    //     |
    //       bit (ICES3)
    //     |

   //     |
  //       bit (WGM32) // TCCR3B 17.11.6
  // comment out one or two of these three lines:
  //       | bit (CS32)
        bit (CS31) // very high pitch if singleton set-bit
          | 
         bit (CS30)
  ; // ends this utterance ;)
 // OC3A OC3B OC3C not to be conflated;
 // COM3A1 B1 C1 A0 B0 C0 may be the things.

  OCR3A = n;
  OCR3B = ((OCR3A + 1) / 2) - 1
  ;
}

// cant see it so using piezo instead of LED

void cpl(int PIN) {
  bool state = digitalRead(PIN);
  state = !state;
  digitalWrite(PIN, state);
}

#define ON_TIME 250
#define OFF_TIME 1700

void blink(int PIN) {
  cpl(PIN);
  delay(ON_TIME);
  cpl(PIN);
  delay(OFF_TIME);
}

void setup_serial(void) {
  Serial.begin(115200);
  delay(400);
  while(!Serial) { delay(10); }
  Serial.write(' ');
}

const int LED_pin = 5;

void setup_gpio(void) {
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, LOW);
}

void setup() {
  setup_serial();
  setup_gpio();
  setup_timer();
}

void loop() {
  // put your main code here, to run repeatedly:
  blink(LED_pin);
}

#if 0
Timers and counters

    https://www.gammon.com.au/timers

The Atmega328 (as on the Arduino Uno) has three
timers/counters on-board the chip.

Timer 0 is set up by the init() function (which is
automatically called by the code generated by the
IDE, before setup() is called).

This is used to count approximately every millisecond.

This provides you with the figure that the millis()
function returns.


example sketch from Nick Gammon follows.

const byte LED_timed = 3;  // Timer 2 "B" output: OC2B

const long frequency = 50000L;  // Hz

void setup_timer(void) {
  pinMode (LED_timed, OUTPUT);

  TCCR2A = bit (WGM20) | bit (WGM21) | bit (COM2B1); // fast PWM, clear OC2B on compare
  TCCR2B = bit (WGM22) | bit (CS21);         // fast PWM, prescaler of 8
  OCR2A =  ((F_CPU / 8) / frequency) - 1;    // zero relative  
  OCR2B = ((OCR2A + 1) / 2) - 1;             // 50% duty cycle
}

void loop()
  {
  // do other stuff here
  }

#endif
// END.
