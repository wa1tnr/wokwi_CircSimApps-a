// two pushbuttons with buzzer
// Sat  5 Feb 11:27:51 UTC 2022

// quite good heuristics

// design target is:
// https://wokwi.com/arduino/new?template=arduino-uno

// tone:
// https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/

#define button_1 12
#define button_2 11
#define buzzer    3
#define led_1    10
#define led_2     9

void pins_setup(void) {
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  // pinMode(buzzer, OUTPUT); // push-pull
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
}

bool button_1_pressed, button_2_pressed = 0;

void cpl(int pin) {
    bool state = digitalRead(pin);
    state = !state ;
    digitalWrite(pin, state);
}

#define hyst 98999  // 73999

void hysteresis(void) {
    for (volatile uint64_t slower = hyst;
    slower > 0; slower--);
}

// ref:
// https://learn.adafruit.com/using-piezo-buzzers-with-circuitpython-arduino/arduino

void buzzing(int bz_pin, int pitch) {
    tone(bz_pin, pitch); // ON until 'notone'
    // tone(bz_pin, pitch, 800); // optional duration
    hysteresis(); // cheap delay
    noTone(bz_pin);
}

#define hertz 440

void act_on_button_1(void) {
    if (button_1_pressed) {
        button_1_pressed = 0;
        cpl(led_1);
        buzzing(buzzer, hertz);
    }
}

void act_on_button_2(void) {
    if (button_2_pressed) {
        button_2_pressed = 0;
        cpl(led_2);
    }
}

void evaluate_booleans(void) {
    act_on_button_1();
    act_on_button_2();
    hysteresis();
}

bool read_inputs(void) {
    button_1_pressed = !digitalRead(button_1);
    button_2_pressed = !digitalRead(button_2);
    if (!button_1_pressed &&
        !button_2_pressed) {
          return 0;
    }
    return -1;
}

void reading(void) {
    while(!read_inputs());
}

void setup() {
    pins_setup();
}

void loop() {
    reading();
    evaluate_booleans();
}

#if 0
{
  "version": 1,
  "author": "Anonymous maker",
  "editor": "wokwi",
  "parts": [
    { "type": "wokwi-arduino-uno", "id": "uno", "top": 0, "left": 0, "attrs": {} },
    {
      "type": "wokwi-buzzer",
      "id": "bz1",
      "top": 0,
      "left": 290,
      "rotate": 180,
      "attrs": { "volume": "0.1" }
    },
    { "type": "wokwi-resistor", "id": "r1", "top": 250, "left": 60, "attrs": {} },
    { "type": "wokwi-resistor", "id": "r2", "top": 250, "left": 200, "attrs": {} },
    {
      "type": "wokwi-pushbutton",
      "id": "btn1",
      "top": 260,
      "left": -40,
      "rotate": 90,
      "attrs": { "color": "green" }
    },
    {
      "type": "wokwi-pushbutton",
      "id": "btn2",
      "top": 260,
      "left": 300,
      "rotate": 270,
      "attrs": { "color": "green" }
    },
    { "type": "wokwi-led",
      "id": "led2",
      "top": -60,
      "left": 390, "attrs": { "color": "red" } },
    {
      "type": "wokwi-led",
      "id": "led1",
      "top": -60,
      "left": -113,
      "attrs": { "color": "red" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r3",
      "top": 80,
      "left": -130,
      "rotate": 90,
      "attrs": {}
    },
    {
      "type": "wokwi-resistor",
      "id": "r4",
      "top": 80,
      "left": 373.2,
      "rotate": 90,
      "attrs": {}
    }
  ],
  "connections": [
    [ "btn1:1.l", "r1:1", "red", [ "v-20", "h30", "v0" ] ],
    [ "btn1:1.r", "uno:12", "yellow", [ "v40", "h-140", "v-460", "h265" ] ],
    [ "btn1:2.l", "uno:GND.2", "black", [ "v-30", "h0" ] ],
    [ "btn1:2.r", "r3:2", "black", [ "v20", "h0" ] ],
    [ "btn2:1.l", "uno:11", "yellow", [ "v40", "h170", "v-460", "h0" ] ],
    [ "btn2:1.r", "r2:2", "red", [ "v-20", "h-30", "v0" ] ],
    [ "btn2:2.l", "r4:2", "black", [ "v20", "h20" ] ],
    [ "btn2:2.r", "uno:GND.3", "black", [ "v-30", "h0" ] ],
    [ "bz1:1", "uno:GND.1", "black", [ "v-30", "h0" ] ],
    [ "bz1:2", "uno:3", "red", [ "v-1", "h0", "v-20", "h0" ] ],
    [ "led2:A", "uno:9", "orange", [ "v20", "h50", "v-80", "h0" ] ],
    [ "led2:C", "r4:1", "black", [ "v0" ] ],
    [ "led1:A", "uno:10", "orange", [ "v20", "h50", "v-80", "h0" ] ],
    [ "led1:C", "r3:1", "black", [ "v0" ] ],
    [ "uno:5V", "r1:2", "red", [ "v0" ] ],
    [ "r1:2", "r2:1", "red", [ "v0" ] ]
  ]
}
#endif
// END.
