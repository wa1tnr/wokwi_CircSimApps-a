// Fri 22 Jul 22:02:19 UTC 2022

// was: series gg, n_sketch_t-c-b.cpp

// https://github.com/wa1tnr/wokwi_CircSimApps-a/tree/dvlp-aa/series-gg.d/timer-counter-b

// RTTYVARG:

// https://wokwi.com/projects/326239532234048084

// AND_THEN (here):
// https://wokwi.com/projects/326235653444469332


// SUCCESS:

// https://wokwi.com/projects/326213297742283348


#include <Arduino.h>

const byte TONE = 88;  // not used much

const byte BUZZER = 2;  // Timer 3 "B" output: OC3B

void setup_timer(void) {
  pinMode (BUZZER, OUTPUT);
  // tone(2, 500); while(-1); // test wiring

  // Arduino MEGA  2560 MCU:
  TCCR3A = 
        bit (COM3B1)
      | bit (WGM31)
      | bit (WGM30)
  ;
  // MODE 15 WGM33 32 31 and 30 all set
  TCCR3B = 
        bit (WGM33)
     |  bit (WGM32)
     |  bit (CS32)
  // |  bit (CS31)
  // |  bit (CS30)
  ;
  OCR3A = TONE;
}

// can't see it so using piezo instead of LED

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

void setup_old_timer_mega_2560() {
  setup_serial();
  setup_gpio();
  setup_timer();
}

#define SLOWNESS ((1*400)+177) // was ((1*100)+177) before  Fri 22 Jul 19:55:12 UTC 2022
#define UPNESS   38  // RTTY MARK
#define DOWNNESS 54  // RTTY SPACE

void sweeping(void) {
  for (int i=DOWNNESS; i >=UPNESS; i--) {
    OCR3A = i;
    for (volatile long int slower = SLOWNESS; slower > 0; slower--) ;
  }

  for (int i=UPNESS; i <=DOWNNESS; i++) {
    OCR3A = i;
    for (volatile long int slower = SLOWNESS; slower > 0; slower--) ;
    // delay(15);
  }
}

void loop_old_timer_mega_2560() {
  // put your main code here, to run repeatedly:
  // blink(LED_pin);
  sweeping();
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
