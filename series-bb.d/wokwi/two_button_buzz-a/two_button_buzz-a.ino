// progressing - 23:16:50z

// progressing - 19:27:51z
// closer to correct behavior.

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

bool button_1_pressed = 0;
bool button_2_pressed = 0;

#define hyst 73999

void hysteresis(void) {
    for (volatile uint64_t slower = hyst;
    slower > 0; slower--);
}

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

void evaluate_booleans(void) {
    act_on_button_1();
    act_on_button_2();
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

void condx_cpls(void) {
    if (button_1_pressed) { cpl(led_1); }
    if (button_2_pressed) { cpl(led_2); }
}

void reading(void) {
    while(!read_inputs());
    hysteresis();
}

void testing_aa(void) {
    // neither LED lights at all
    digitalWrite(led_1, 1);
    digitalWrite(led_2, 1);
    while(-1);
}

void testing_bb(void) {
    cpl(led_1); // make 'em alternate
    for (int index = 8; index > 0; index--) {
        cpl(led_2);
        cpl(led_1); delay(600);
    }
}

void setup() {
    pins_setup();
    // testing_aa();
    // testing_bb();
}

void loop() {
    reading();
    evaluate_booleans();
}

// END.
