// Tue 15 Mar 16:02:45 UTC 2022

//   RE-EDIT  16:12:54z

// n_sketch_t-c-b.cpp

// https://github.com/wa1tnr/wokwi_CircSimApps-a/tree/dvlp-aa/series-gg.d/timer-counter-b

// SUCCESS:

// https://wokwi.com/projects/326213297742283348


#include <Arduino.h>

const byte BUZZER = 2;  // Timer 3 "B" output: OC3B

const long frequency = 50000L;  // Hz

const byte n =   233 ; // UNUSED

void setup_timer(void) {
  pinMode (BUZZER, OUTPUT);
  // tone(2, 500); while(-1); // test wiring

  // Arduino MEGA  2560 MCU:
  TCCR3A = bit (COM3B1)
      | bit (WGM31)
      | bit (WGM30)
  ; 

  TCCR3B = bit (WGM32)
  //  | bit (CS32)
      | bit (CS31)
      | bit (CS30)
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
