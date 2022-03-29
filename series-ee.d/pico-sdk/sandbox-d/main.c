// Tue 29 Mar 17:58:24 UTC 2022 - ONLINE edit

// PRESERVED WIRING VERTICAL TARGET ORIENTATION

// https://wokwi.com/projects/327415555705274962  current Tue 29 Mar 17:58:24 UTC 2022  REUSED OLDER ONE

// https://wokwi.com/projects/327487469083689556  recent  Tue 29 Mar 17:40:14 UTC 2022  LAST VERT TARGET

// https://wokwi.com/projects/327418197022081618  recent  Tue 29 Mar 00:20:32z

#if 0
// we are pico-sdk not Arduino IDE

// RS E D4 D5 D6 D7

#include <LiquidCrystal.h>

LiquidCrystal lcd(
 21, // RS blue   to Uno:D12 pico:GP21
 20, //  E purple to Uno:D11 pico:GP20
 // 4-bit data bus:
 19, // D4 green  to Uno:D10 pico:GP19
 18, // D5 brown  to Uno:D9  pico:GP18
 17, // D6 gold   to Uno:D8  pico:GP17
 16  // D7 gray   to Uno:D7  pico:GP16
);

// Connect K Kathode to GND
// Connect Uno:5 Volts to A Anode via 330 Ohms
#endif


/* rp2040 */
#include <stdio.h>
#include <string.h> // strcpy
#include "pico/stdio.h"
#include "pico/stdlib.h"

// ///////////////////// // #include "rp2040_pico.h" /////////////////////
// ///////////////////// // #include "rp2040_pico.h" /////////////////////

#define stack_buffer_length 64

#if CONF_USBD_HS_SP
#define CDCD_ECHO_BUF_SIZCF CONF_USB_CDCD_ACM_DATA_BULKIN_MAXPKSZ_HS
#else
// #define CDCD_ECHO_BUF_SIZCF CONF_USB_CDCD_ACM_DATA_BULKIN_MAXPKSZ
#define TEST_CBC77 1
#endif

char print_string[stack_buffer_length];
// extern char usbd_cdc_in_buffer[CDCD_ECHO_BUF_SIZCF / 4];

// ///////////////////// // #include "rp2040_pico.h" /////////////////////
// ///////////////////// // #include "rp2040_pico.h" /////////////////////

#define RP2040_PICO
#ifdef RP2040_PICO

// ///////////////////// // #include "forth_c.h"     /////////////////////
// ///////////////////// // #include "forth_c.h"     /////////////////////
// #define DATE_STAMP "Mon Feb 28 11:25:51 UTC 2022"
#define DATE_STAMP "Mon 28 Mar 23:31:49 UTC 2022"
// old standard width for this field: #define BRANCH_STAMP "erase_sector-a"
#define BRANCH_STAMP  "dvlp-aa                            __"
#define COMMIT_STAMP  "49723cf"
#define FEATURE_STAMP "+wokwi +auto_load +rewind            "
// #define MODE_STAMP "copy_to_ram"
#define MODE_STAMP "copy_to_ram"
// #define MODE_STAMP "no_flash   "
// #define MODE_STAMP "no_flash   "
#define VERS_CFORTH ("\103CamelForth in C v0.1 - 14 Feb 2016 - " DATE_STAMP "  ");
// old count reasonable branch stamp: #define DOFILLS_datus ("\200\n\n +flwrite +erase " DATE_STAMP " \n branch " BRANCH_STAMP " " COMMIT_STAMP " UNDER TEST    \n " MODE_STAMP " mode\n\n            ");
#define DOFILLS_datus ("\237\n\n " FEATURE_STAMP DATE_STAMP " \n branch " BRANCH_STAMP " " COMMIT_STAMP " UNDER TEST   \n " MODE_STAMP " mode\n\n");
// special attempt: make some pointerish things more robust by superstitiously using 'volatile' all over the place ;)
// surprisingly, all these changes in this commit do compile cleanly.

#if 0
// mass code disable 28 M_r 2022 23:05:53 first instance of this.
#endif

#include <stdint.h>
#include <stdbool.h>

#if 0
// #include "forth.h"
// ///////////////////// // #include "forth.h"       /////////////////////
// ///////////////////// // #include "forth.h"       /////////////////////
#endif

#define RP2040_PICO               /* for use with Raspberry Pi Pico RP2040 based target */
#define USB_IFACE                 /* only some implementations */

#if 0
#endif

// ///////////////////// // #include "forth.h"       /////////////////////
// ///////////////////// // #include "forth.h"       /////////////////////

/* not sure where this goes 07 M_r 2021 tnr */
uint32_t getFlKey_counter = 0;

#if 0
#endif

#ifdef RP2040_PICO

// #include "rp2040_pico_inc.h"

// ///////////////////// // #include "rp2040_pico_inc.h"       ///////////
// ///////////////////// // #include "rp2040_pico_inc.h"       ///////////

/****h* camelforth-a/src/cf/rp2040_pico/rp2040_pico.inc
 */

// #include "rp2040_pico.h"
// ///////////////////// // #include "rp2040_pico.h"       ///////////////
// ///////////////////// // #include "rp2040_pico.h"       ///////////////

// Nothing inserted - exists above  28 Feb 2022 10:55z

// ///////////////////// // #include "rp2040_pico.h"       ///////////////
// ///////////////////// // #include "rp2040_pico.h"       ///////////////

// #include "rp2040_pico_getkey_usb_inc.h"
// ///////////////////// // #include "rp2040_pico_getkey_usb_inc.h"   ////
// ///////////////////// // #include "rp2040_pico_getkey_usb_inc.h"   ////


// #include "rp2040_pico.h"

uint8_t getKey(void) {     // hardware-independent wrapper xa
    uint8_t ch_read;
    do {
        ch_read = getchar_timeout_us(18); // 4 tries per 87 uSec char window at 115200 bps
    } while ((ch_read == '\0') || (ch_read == 0xff));
    return ch_read;
}

void queryKey(void) {
    // TODO wa1tnr
}

// ///////////////////// // #include "rp2040_pico_getkey_usb_inc.h"   ////
// ///////////////////// // #include "rp2040_pico_getkey_usb_inc.h"   ////

// #include "rp2040_flashkey_inc.h"
// ///////////////////// // #include "rp2040_flashkey_inc.h"       ///////
// ///////////////////// // #include "rp2040_flashkey_inc.h"       ///////

// Sun M_r  7 16:57:29 UTC 2021
// #include "rp2040_pico.h" // redundant? YES.
// #include "pico/stdlib.h" // redundant?  YES.

#define FL_KEY_BASE 0x10040000 // same as example code SDK // xcc

#if 0
#endif
// ENiD,

// ///////////////////// // #include "rp2040_flashkey_inc.h"       ///////
// ///////////////////// // #include "rp2040_flashkey_inc.h"       ///////

// #include "cut_inc.h"              // string cutter utility, for long USB printf's
// ///////////////////// // #include "cut_inc.h"       ///////////////////
// ///////////////////// // #include "cut_inc.h"       ///////////////////

// #include <stdio.h> // redundant?  YES.
// #include <string.h> // redundant?  YES.

#define BUFFLEN 128
#define CHOP_LN 5

char instring[BUFFLEN];
char tempstring[BUFFLEN];

void init_cutter(void) {
    strcpy(instring, print_string);
}

/*
 *      Remove given section from string. Negative len means remove
 *      everything up to the end. xc
 */

int str_cut(char *str, int begin, int len) {
    int l = strlen(str);

    if (len < 0)
        len = l - begin;
    if (begin + len > l)
        len = l - begin;
    memmove(str + begin, str + begin + len, l - len + 1);

    return len;
}

void slower(void) {
    for (volatile int i = 1295; i > 0; i--) {
    }
}

// printf_cutter() needs rework or discard - is why it says 'cccc' for a dump or a .S 08 Feb 2021
void printf_cutter(void) {
    // cdcdf_acm_write((uint8_t *) tempstring, strlen(tempstring));
    putchar('c'); // cdcdf_acm_write((uint8_t *) tempstring, strlen(tempstring));
    slower();                   // no ringbuffer - kludge
}

void do_output(void) {
    printf_cutter();
}

void slicer(char *instring) {
    tempstring[0] = '\0';
    tempstring[1] = '\0';

    int origin = 0;
    int chopln = CHOP_LN;       // chop length
    int to_end = -1;

    int l = (strlen(instring) / chopln);

    for (int index = 1; index < (l + 1); index++) {
        int j = chopln * index;
        int k = j - chopln;
        strcpy(tempstring, instring);
        str_cut(tempstring, j, to_end);
        if (index > 1) {
            str_cut(tempstring, origin, k);
        }
        do_output();
    }

    if ((strlen(instring)) > ((strlen(instring) / chopln) * chopln)) {
        strcpy(tempstring, instring);
        int c = l * chopln;
        str_cut(tempstring, 0, c);
        do_output();
    }

}

void cut_main(void) {
    init_cutter();
    slicer(instring);
}

// primary api is chopped_acm_write(print_string) from caller

void chopped_acm_write(char *str) {
    cut_main();
}

#ifdef NEVER_DEFINED_EVER
/*

Stack Overflow

permalink:

 [ https://stackoverflow.com/a/20346241 ]

other link:

 [ https://stackoverflow.com/questions/20342559/how-to-cut-part-of-a-string-in-c ]

The following function cuts a given range out of a char buffer.
The range is identified by startng index and length. A negative
length may be specified to indicate the range from the starting
index to the end of the string.
*/

/*
 *      Remove given section from string. Negative len means
 *      remove everything up to the end.
 */

int str_cut(char *str, int begin, int len) {
    int l = strlen(str);

    if (len < 0)
        len = l - begin;
    if (begin + len > l)
        len = l - begin;
    memmove(str + begin, str + begin + len, l - len + 1);

    return len;
}

/*

The char range is cut out by moving everything after the
range including the terminating '\0' to the starting index
with memmove, thereby overwriting the range. The text in
the range is lost.

Note that you need to pass a char buffer whose contents
can be changed. Don't pass string literals that are stored
in read-only memory.

answered Dec 3 '13 at 8:33
M Oehm

site design / logo © 2018 Stack Exchange Inc;
user contributions
licensed under cc by-sa 3.0 with attribution required.
rev 2018.9.14.31567
*/
#endif // #ifdef NEVER_DEFINED_EVER

// ///////////////////// // #include "cut_inc.h"       ///////////////////
// ///////////////////// // #include "cut_inc.h"       ///////////////////

// ###bookmark-e  is getKey and getFlKey present or not

// 347: uint8_t getKey(void) {     // hardware-independent wrapper xa
// 393: uint8_t getFlKey(void) {     // hardware-independent wrapper
 
// extern uint8_t getKey(void);       // hardware-independent wrapper
// extern uint8_t getFlKey(void);     // get 'keystroke' from QSPI flashROM RP2040

// extern int _pico_LED();

// #define NULL 0  // already defined for Atmel Start and gcc:

/*
 * Terminal I/O functions
 */

int length_print_string = 0;    // would like to shed this global

/* USB based */
#ifdef NOT_DEFINED_RP2040
#define printf(format,integer) \
    length_print_string = 0; \
    print_string[0] = (uint32_t) "\0"; \
    sprintf(print_string, format, integer); \
    length_print_string = strlen(print_string); \
        chopped_acm_write(print_string)
#endif // not defined rp2040

#define getch getKey // keep rp2040


/* replace with a new version Fri 12 Feb 2021 01:27 33: */
void putch(char c) {
    char *p;
    p = &c;
    c = *p +0;
    print_string[0] = c;
    print_string[1] = '\0';
    printf("%s", print_string);
}

int getquery(void) {
    return -1;                  /* TODO wa1tnr */
}

/****f* main/main
 */

// ///////////////////// // #include "rp2040_pico_inc.h"       ///////////
// ///////////////////// // #include "rp2040_pico_inc.h"       ///////////

#endif

#if 0
/* TERMINAL I/O */

CODE(key) {
    // *--psp = (unsigned int)getch();
    *--psp = (uint8_t)getch();
}

CODE(emit) {
    putch((char)*psp++);
}

CODE(dot) {        /* temporary definition for testing */
    printf(" %d", *psp++);
}
#endif

// 29 Mar 2022 keep above intact

// #include "pico-LED_c.h"
// ///////////////////// // #include "pico-LED_c.h"       ////////////////
// ///////////////////// // #include "pico-LED_c.h"       ////////////////

int _pico_LED() {
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    // while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    // }
}



#if 0
// ///////////////////// // #include "pico-LED_c.h"       ////////////////
// ///////////////////// // #include "pico-LED_c.h"       ////////////////
// extern int _pico_LED(void);
CODE(blink) { /* -- */
    _pico_LED();
}
#endif


#define READING_SIZE 4096

char buffer[READING_SIZE];



// void interpreter(void) { }

char dofilldatus[] = DOFILLS_datus

void crufty_printer(void) {
    printf("%s", dofilldatus);
}

// rp2040_reflash.inc

#include "pico/bootrom.h"

#if 0
void reflash(void) {  /*  --  */
    reset_usb_boot(0, 0);
}
#endif
// ///////////////////// // #include "rp2040_reflash_inc.h"     //////////
// ///////////////////// // #include "rp2040_reflash_inc.h"     //////////

// #include "hardware/resets.h"
// #include "hardware/regs/m0plus.h"
#endif



#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1


int main() {
    sleep_ms(100);
    uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    stdio_init_all();

    // uart_putc_raw(UART_ID, 'A');

    sleep_ms(100);
    uart_puts(UART_ID, "\r\nnew wokwi RPi Pico RP2040  Forth 29 Mar 2022\r\n\r\n");

    uart_puts(UART_ID, " pico-sdk  based\r\n\r\n");

    putchar(' ');
    putchar(' ');
    putchar('4');
    putchar('-');
    putchar('b');
    putchar('i');
    putchar('t');
    putchar(' ');
    putchar('L');
    putchar('C');
    putchar('D');
    putchar(' ');
    putchar('F');
    putchar('o');
    putchar('r');
    putchar('t');
    putchar('h');
    putchar(' ');
    putchar('\r');
    putchar('\n');

    strcpy(print_string, "  greet  Tue 29 Mar 17:58:24 UTC 2022");
    printf("%s", print_string);
    putchar('\n');

    while(1) {
        uint8_t ch_key = getKey();
        putchar(ch_key); // seems okay - no further research yet
    }
}

/// \end::hello_uart[]
