// Wed 20 Apr 18:11:41 UTC 2022
// Wed 20 Apr 17:56:19 UTC 2022 - online edit

#define ID_IN_SERIAL_MON(x) Serial.println("yj329c-ee")
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PINLED 13
#define BOTTONOUT 3
#define BOTTONIN 4
#define BRIGHTNESS 254 // 100

int Botton;
int State = 0;

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

#define MAX_STATE 6
#define OVER_FLOW_A 0

bool single_shot_b = true;
void loop () {
    // bool single_shot_b = true;
    uint32_t time_stamp = millis ();
    Botton = digitalRead (BOTTONIN);
    if (Botton == LOW) {
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
        Serial.print (bpressed);

        State++;

        if (State) {
            Serial.print ("  State: ");
            Serial.println (State);
        }
    }

    switch (State) {
    case 0:
        digitalWrite (PINLED, LOW);
        break;

    case 1:
        for (int a = 0; a < 31; a = a + 1) {
            pixels.setPixelColor (a, pixels.Color (0, 0, 0));
        }
        pixels.show ();
        break;

    case 2:
        for (int a = 0; a < 31; a = a + 1) {
            pixels.setPixelColor (a, pixels.Color (183, 21, 184));
        }
        pixels.show ();
        break;

    case 3:
        for (int a = 0; a < 31; a = a + 1) {
            pixels.setPixelColor (a, pixels.Color (250, 0, 250));
        }
        pixels.show ();
        break;

    case 4:
        for (int a = 0; a < 8; a = a + 1) {
            pixels.setPixelColor (a, pixels.Color (199, 21, 21));
        }
        pixels.show ();
        // Serial.println(" it idles in the current slot ");
        break;

    case 5:
        if (single_shot_b) {
            single_shot_b = false;
            single_shot ();
            // State = 0;
            break;
        }
        break;

    case (MAX_STATE + OVER_FLOW_A):
        State = 0;
        do_max_state ();
        break;

    default:
        // single_shot_b = false;
        Serial.println ("DEFAULT seen");
        if (State > (MAX_STATE - 1)) {
            State = 0;
        }
        break;
    }
}

// END.
