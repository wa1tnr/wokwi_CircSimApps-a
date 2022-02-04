// edit after a break - 16:20z

#define button_1 12
#define button_2 11
#define bz        3
#define led_1     9
#define led_2    10

void pins_setup(void) {
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  pinMode(bz, OUTPUT); // push-pull
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
}


void cpl(int pin) {
    bool state = digitalRead(pin);
    state = !state ;
    digitalWrite(pin, state);
}

bool button_1_pressed = 0;

void act_on_button_1(void) {
    if (button_1_pressed) {
        cpl(led_1); // digitalWrite(led_1, 1);
        // delay(1000);
    }
}

void evaluate_booleans(void) {
    act_on_button_1();
}

void hysteresis(void) {
    for (volatile int slower = 9999;
    slower > 0; slower--);
}

void read_inputs(void) {
    button_1_pressed = 0;
    digitalRead(button_1_pressed);
    if (button_1_pressed) {
      hysteresis();
    }
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
    read_inputs();
    evaluate_booleans();
}

// END.
