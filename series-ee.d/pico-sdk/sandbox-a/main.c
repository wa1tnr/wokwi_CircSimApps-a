// eight captures main.c peculiar to wokwi pico-sdk

/*
  Forth virtual machine

  This code is in the public domain.

  https://wokwi.com/arduino/projects/324782964543062610

  https://github.com/CharleyShattuck/Steno-Keyboard-Arduino/blob/master/Cortex-Forth.ino

  from

  https://github.com/CharleyShattuck/Steno-Keyboard-Arduino.git

  27 February 2022   21:16:43 UTC

*/

/* rp2040 */
#include <stdio.h>
#include <string.h> // strcpy
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "rp2040_pico.h"

/* cortex forth */
#include "cortex-forth.h"

#define RAM_SIZE 0x1200
#define S0 0x1000
#define R0 0x0f00
#define NAME(m, f, c, x, y, z) {memory.data [m] = f + c + (x << 8) + (y << 16) + (z << 24);}
#define LINK(m, a) {memory.data [m] = a;}
#define CODE(m, a) {memory.program [m] = a;}
#define DATA(m, a) {memory.data [m] = a;}
#define IMMED 0x80

#define RP2040_PICO
#ifdef RP2040_PICO

// #include "rp2040_pico.inc"
#include "rp2040_pico_inc.h"

// #include "rp2040_reflash.inc"
#include "rp2040_reflash_inc.h"

// #include "hardware/resets.h"
// #include "hardware/regs/m0plus.h"
#endif

// global variables
union Memory {
  int data [RAM_SIZE];
  void (*program [0]) (void);
} memory;

// String tib = "";
int S = S0; // data stack pointer
int R = R0; // return stack pointer
int I = 0; // instruction pointer
int W = 0; // working register
// uint8_t getKey()
int T = 0; // top of stack
int H = 0; // dictionary pointer, HERE
int D = 0; // dictionary list entry point
int base = 10;
bool state = false; // compiling or not

/*  A word in the dictionary has these fields:
  name  32b word,  a 32 bit int, made up of byte count and three letters
  link  32b word, point to next word in list, 0 says end of list
  code  32b word, a pointer to some actual C compiled code,
        all native code is in this field
  data  32b word, at least, a list to execute or a data field of some kind


*/


// primitive definitions

void _LBRAC (void) {
  state = false; // interpreting
}

void _RBRAC (void) {
  state = true; // compiling
}

void _NOP (void) {
  return;
}

void _EXIT (void) {
  I = memory.data [R++];
}

void _DROP (void) {
  T = memory.data [S++];
}

void _DUP (void) {
  memory.data [--S] = T;
}

void _QDUP (void) {
  if (T) _DUP ();
}

void _KEY (void) {
  _DUP ();
  // uint8_t getKey(void);
  T = getKey();
  // while (!Serial.available ());
  // T = Serial.read ();
//  Serial.write (T);
}

void _EMIT (void) {
  char c = T;
  // Serial.write (c);
  // void putch(char c);
  putch(c);
  _DROP ();
}

void _CR (void) {
  putch('\n');
  // Serial.println (" ");
}

void _OK (void) {
  // if (tib [tib.length () - 1] == 10) Serial.println (" Ok");
  // strcpy(print_string, "\n\nOkay my friend\n\n"); // demo use
  strcpy(print_string, "  Ok");
  printf("%s", print_string);
  strcpy(print_string, "  ~~");
}

void _SWAP (void) {
  W = memory.data [S];
  memory.data [S] = T;
  T = W;
}

void _OVER (void) {
  _DUP ();
  T = memory.data [S + 1];
}

// #include "rp2040_reflash.inc"

#include "Cortex-Forth.h" // balance of upstream code is here

void interpreter(void) {
   uint8_t gotkey ;
   _KEY();
   gotkey = T;
   if ( (gotkey == '\n') ||
        (gotkey == '\r') ||
        (gotkey == '~' ) ||
        (gotkey == '+' ) ||
        (gotkey == '-' ) ) {
      _OK();
      if (gotkey == '\n') _CR();
      if (gotkey == '~' ) reflash();
      return ;
    }
    _EMIT();//  _CR(); _OK();
}

// Mon Feb 22 17:15:42 UTC 2021


// Mon Feb 15 18:55:13 UTC 2021
// wa1tnr
// cortex-forth for RP2040

/**
 * template is Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// #include <stdio.h>
// #include <string.h> // strcpy
// #include "pico/stdlib.h"
// #include "rp2040_pico.h"

/// \tag::hello_uart[]

// ###bookmark

#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1
extern void interpreter(void);
// extern int _pico_LED(void);

// void interpreter(void) { }

extern void _OK(void);
// extern char print_string[stack_buffer_length];

int main() {
    sleep_ms(1800);
    uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    stdio_init_all();

    // uart_putc_raw(UART_ID, 'A');

    sleep_ms(800);
    // for (int i=3;i>0;i--) _pico_LED();
    // uart_puts(UART_ID, "\r\n\r\n   cortex-forth-rp2040-aU r0.1.0-pre-alpha\r\n\r\n");
    //      0.1.0-pre-alpha  checked carefully - available and appropriate
    _OK(); // Cortex-Forth.c
    uart_puts(UART_ID, "\r\n\r\n   cortex-forth-rp2040-a r0.1.0-pre-alpha\r\n\r\n");
    putchar(' ');
    putchar(' ');
    putchar('C');
    putchar('o');
    putchar('r');
    putchar('t');
    putchar('e');
    putchar('x');
    putchar(' ');
    putchar(' ');
    putchar('F');
    putchar('o');
    putchar('r');
    putchar('t');
    putchar('h');
    putchar(' ');
    putchar('\r');
    putchar('\n');
    // printf("%s" "printf here\r\n\r\n   cortex-forth-rp2040-a r0.1.0-pre-alpha\r\n\r\n");
/*
113:  strcpy(print_string, "  Ok");
114:  printf("%s", print_string);
*/

    strcpy(print_string, "  greet  27 Feb 21:23 UTC 2022");
    printf("%s", print_string);
    putchar('\n');

    while(1) {
        // _pico_LED(); // test using GPIO hardware to blink Pi Pico onboard LED
        interpreter(); // camelforth
    }
}

/// \end::hello_uart[]
