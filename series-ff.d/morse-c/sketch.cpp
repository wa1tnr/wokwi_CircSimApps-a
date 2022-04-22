// Wed 20 Apr 20:19:45 UTC 2022 indent rvim offline edit

#define ID_IN_SERIAL_MON(x) Serial.println("yj331e-bb")
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PINLED 13
#define BOTTONOUT 3
#define BOTTONIN 4
#define BRIGHTNESS 254 // 100

int Botton;
int State = 1; // trial 18:18 UTC Wed 20 Apr

#define LED_COUNT 32
#define RGB_STRIP_PIN 5

Adafruit_NeoPixel pixels (LED_COUNT, RGB_STRIP_PIN, NEO_GRBW + NEO_KHZ800);

void colorWipe (uint32_t color, int wait) {
    for (int i = 0; i < pixels.numPixels (); i++) {
        pixels.setPixelColor (i, color);
        pixels.show ();
        delay (wait);
    }
}

#define DURA_A 100
#define DURA_B 600
#define BLINKS 4

// ENiD,

void blink_pinled () {
    for (int blinked = BLINKS; blinked > 0; blinked--) {
        digitalWrite (PINLED, 1);
        delay (DURA_A);
        digitalWrite (PINLED, 0);
        delay (DURA_B);
    }
}

void setup () {
    Serial.begin (9600);
    delay (400);
    Serial.write ('.');
    Serial.println ("");
    ID_IN_SERIAL_MON (x);

    pinMode (BOTTONOUT, OUTPUT);
    digitalWrite (BOTTONOUT, LOW);
    pinMode (BOTTONIN, INPUT_PULLUP);
    pinMode (PINLED, OUTPUT);

    blink_pinled ();
    pixels.begin ();
    for (int i = 0; i < 33; i++) {
        pixels.setPixelColor (i, pixels.Color (0, 0, 0, 0));
    }
    pixels.show (); // Turn OFF all pixels ASAP
    pixels.setBrightness (BRIGHTNESS); // Set BRIGHTNESS (max = 255)
}

#define HYSTERESIS 350
uint16_t bpressed = 0;

void single_shot () {
    Serial.println ("singleShot() reached.");
    for (int outer = 4; outer > 0; outer--) {
        for (int a = 0; a < 8; a = a + 1) {
            pixels.setPixelColor ((a * outer), pixels.Color (199, 21, 21));
        }
        pixels.show ();
        Serial.write ('j');
    }
}

void do_max_state () {
    Serial.println ("MAX_STATE reached.");
    for (int outer = 4; outer > 0; outer--) {
        for (int a = 0; a < 8; a = a + 1) {
            pixels.setPixelColor ((a * outer), pixels.Color (21, 199, 21));
        }
        pixels.show ();
        Serial.write ('x');
    }
}

#define MAX_STATE 8
#define OVER_FLOW_A 0

bool single_shot_b = true;
bool idle = true;
bool pressed_note = true; //  tell operator about something
                          //  on very first button press

void loop () {
    uint32_t time_stamp = millis ();
    Botton = digitalRead (BOTTONIN);
    if (Botton == LOW) {
        idle = false; // allow one event
        Serial.println (" button LOW ");
        bool expired_timer = false;
        Serial.write ('r');
        do {
            uint32_t local_time = millis ();
            uint32_t time_difference = (local_time - time_stamp);
            expired_timer = (time_difference > HYSTERESIS);

            if (expired_timer) {
                time_stamp = millis (); // highwater
                Serial.write ('p');
                bpressed++; // how many button presses ever
            }
            // Serial.write('q');
        } while (!expired_timer);

        Serial.print ("  timer has expired.  Button presses: ");
        Serial.print ((bpressed + 1));

        State++;

        if (State) {
            Serial.print ("  State: ");
            Serial.println (State);
        }

        if (pressed_note) {
            pressed_note = false;
            Serial.print ("\n   NOTE: count of button presses starts with '2'.");
            Serial.print ("\n         The machine begins in State 1,");
            Serial.print ("\n         without a button-press, on a cold reset.\n\n");
        }
    }

    switch (State) {

    case 0:
        digitalWrite (PINLED, LOW);
        break;

    case 1:
        if (!idle) {
            idle = true;
            Serial.print ("   IDLE SOON  ");
            for (int a = 0; a < 31; a = a + 1) {
                pixels.setPixelColor (a, pixels.Color (0, 0, 0));
            }
            pixels.show ();
        } // not idle
        break;

    case 2:
        if (!idle) {
            idle = true;
            Serial.print ("   IDLE SOON  ");
            for (int a = 0; a < 31; a = a + 1) {
                pixels.setPixelColor (a, pixels.Color (183, 21, 184));
            }
            pixels.show ();
        } // not idle
        break;

    case 3:
        if (!idle) {
            idle = true;
            Serial.print ("   IDLE SOON  ");
            Serial.println (" idle-guarded in the current slot ");
            for (int a = 0; a < 31; a = a + 1) {
                pixels.setPixelColor (a, pixels.Color (250, 0, 250));
            }
            pixels.show ();
        } // not idle
        break;

    case 4:
        if (!idle) {
            idle = true;
            Serial.print ("   IDLE SOON  ");
            for (int a = 0; a < 8; a = a + 1) {
                pixels.setPixelColor (a, pixels.Color (199, 21, 21));
            }
            pixels.show ();
        } // not idle
        Serial.println (" it idles in the current slot ");
        break;

    case 5:
        if (!idle) {
            idle = true;
            Serial.print ("   IDLE SOON  ");
            if (single_shot_b) {
                single_shot_b = false;
                single_shot ();
                break;
            }
        } // not idle
        break;

    case 6:
        if (!idle) {
            idle = true;
            colorWipe (0xc0ffee, 3);
            Serial.print ("   IDLE SOON  ");
        } // not idle
        break;

    case 7:
        if (!idle) {
            idle = true;
            colorWipe (0xffc0ee, 3);
            Serial.print ("   IDLE SOON  ");
        } // not idle
        break;

    case (MAX_STATE + OVER_FLOW_A):
        State = 0;
        do_max_state ();
        break;

    default:
        Serial.println ("DEFAULT seen");
        if (State > (MAX_STATE - 1)) {
            State = 0;
        }
        break;
    }
}

// https://github.com/wa1tnr/wokwi_CircSimApps-a/blob/dvlp-aa/series-ff.d/morse-c/sketch.cpp

// END.
