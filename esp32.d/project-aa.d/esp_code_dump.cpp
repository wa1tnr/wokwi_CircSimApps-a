// an ESP32 thing

extern "C" {
    #include <stdio.h>
    #include "driver/gpio.h"
    #include "freertos/FreeRTOS.h"
}

#include <Arduino.h>

#define SLEW_RATE 3 // 300

#define LED_RED GPIO_NUM_2
#define BTN_RED GPIO_NUM_13

#define DELAY_TIME 4 // 200  // 0.1 lowest

volatile bool button_pressed = false;

static void gpio_isr_handler(void* arg) {
    button_pressed = true;
}

// ref http://www.neilkolban.com/esp32/docs/cpp_utils/html/md__r_e_a_d_m_e.html
extern "C" {
   void app_main();
}

void button_config() {
    gpio_install_isr_service(0);
    printf("configuring button\n");
    gpio_reset_pin(BTN_RED);
    gpio_set_direction(BTN_RED, GPIO_MODE_INPUT);
    gpio_pullup_en(BTN_RED);
    gpio_set_intr_type(BTN_RED, GPIO_INTR_POSEDGE);
    gpio_isr_handler_add(BTN_RED, gpio_isr_handler, NULL);
    printf("config complete\n");
}

void led_config() {
    gpio_reset_pin(LED_RED);
    gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);
}

void print_report_aa(void) {
    // demo printing techniques - various approaches
    char buffer[25];
    char* buf_ptr = buffer;
    // 'void* memcpy(void*, const void*, size_t)'
    memcpy(buffer, "HHqqpprrssttuuvv", sizeof(buffer)) ;
    printf(buffer);
    char buffer_b[25] = "Cranston";
    char buf_two[25];
    // 'int snprintf(char*, size_t, const char*, ...)'
    snprintf(buf_two, sizeof(buffer_b), buffer_b);
    printf(buf_two);
    printf("hhiijj");
    printf("\n");
}

uint8_t led_value = 0;

void eval_button(void) {
    if (button_pressed) {
        button_pressed = false;
        led_value = !led_value;
        gpio_set_level(LED_RED, led_value);
        print_report_aa();
    }
}

void scan_pb_switch(void) {
    bool count_exceeded;
    int print_counter = 0;
    int iterations = 0;
    char buffer[25];
    char* buf_ptr = buffer;
    while (!button_pressed) {
        int buttonState = digitalRead(BTN_RED); // curiosity only?
        // if(!buttonState) { printf(" got very statey all of a sudden\n"); }
        // buttonState = 17; // mask
        print_counter++;
        iterations++; // never resets
        if (print_counter >= SLEW_RATE) {
            printf("\n");
            print_counter = 0; // reset
            count_exceeded = true;
        }
        if (count_exceeded) {
            count_exceeded = false; // reset trap
            printf(" A: ");
            // char* itoa (int val, char *s, int radix);
            itoa(buttonState, buf_ptr, 10);
            printf(buf_ptr); // //////////////// PAYLOAD /////////////
            itoa(iterations, buf_ptr, 10);
            printf(" B: ");
            printf(buf_ptr);
            printf(" C: ");
        }
        vTaskDelay(DELAY_TIME / portTICK_PERIOD_MS);
    } // while
    eval_button();
}

void setup(void) {
    button_config();
    led_config();
}

void loop(void) {
    scan_pb_switch();
}
// END.
