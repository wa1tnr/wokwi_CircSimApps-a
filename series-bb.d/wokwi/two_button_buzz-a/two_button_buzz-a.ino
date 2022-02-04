// compiles only - nothing tested 13:46z
c
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

void setup() {
    pins_setup();
}

bool button_1_pressed = 0;

void act_on_button_1(void) {
    if (button_1_pressed) {
      digitalWrite(led_1, 1);
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

void loop() {
    read_inputs();
    evaluate_booleans();
}

// END.
