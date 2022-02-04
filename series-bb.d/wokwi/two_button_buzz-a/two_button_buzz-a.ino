// progressing - 23:41:41z
// quite good heuristics

// design target is:
// https://wokwi.com/arduino/new?template=arduino-uno

// only one LED and only one pushbutton have
// been accounted for, though both pairs are
// present and the second instance is probably
// correct, electrically. 19:27 UTC Fri 4 Feb 2022

#define button_1 12
#define button_2 11
#define bz        3
#define led_1    10
#define led_2     9

void pins_setup(void) {
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  pinMode(bz, OUTPUT); // push-pull
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
}

bool button_1_pressed, button_2_pressed = 0;

void cpl(int pin) {
    bool state = digitalRead(pin);
    state = !state ;
    digitalWrite(pin, state);
}

void act_on_button_1(void) {
    if (button_1_pressed) {
        button_1_pressed = 0;
        cpl(led_1);
    }
}

void act_on_button_2(void) {
    if (button_2_pressed) {
        button_2_pressed = 0;
        cpl(led_2);
    }
}

#define hyst 98999  // 73999

void hysteresis(void) {
    for (volatile uint64_t slower = hyst;
    slower > 0; slower--);
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

// END.
