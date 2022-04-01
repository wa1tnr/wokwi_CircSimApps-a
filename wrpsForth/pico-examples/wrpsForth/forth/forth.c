// Fri 01 Apr 02:27:33 UTC 2022

// ../gforth/memory.h read by CMakeLists.txt

//  h# 20    enters  decimal 32 literal

// +  and  .s  wark mostly as-expected.


// https://wokwi.com/projects/327506579910820436 current NOW



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

#define DATE_STAMP "Mon 28 Mar 23:31:49 UTC 2022"
#define MODE_STAMP "copy_to_ram"
#define VERS_CFORTH ("\103CamelForth in C v0.1 - 14 Feb 2016 - " DATE_STAMP "  ");

#include <stdint.h>
#include <stdbool.h>

#define RP2040_PICO               /* for use with Raspberry Pi Pico RP2040 based target */
#define USB_IFACE                 /* only some implementations */

/* not sure where this goes 07 M_r 2021 tnr */
uint32_t getFlKey_counter = 0;

#ifdef RP2040_PICO

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

#define FL_KEY_BASE 0x10040000 // same as example code SDK // xcc

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

int _pico_LED() {
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    // while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
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

// char dofilldatus[] = FEATURE_STAMP // DOFILLS_datus

void crufty_printer(void) {
    printf(" rescinded cruft print");
    // printf("%s", dofilldatus);
}

// rp2040_reflash.inc

#warning no bootrom code
// #include "pico/bootrom.h"

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



// n_sketch.cpp


// ###bookmark
#include <stdio.h>
#include <string.h> // strcpy
// #include "pico/stdio.h"

#include "pico/stdlib.h"

#include "memory.h"
// #include "compatibility.h"


// Wed 30 Mar 10:21:14 UTC 2022

// warn 002: #warning seen compatibility.h

#undef  RP2040_VARIANT
#define RP2040_VARIANT

#ifdef RP2040_VARIANT
#define RP2040_PRESENT -1 // TRUE
#endif

#ifndef RP2040_VARIANT
#define RP2040_PRESENT -0 // FALSE
#endif

// was in upstream // #include <Wire.h>
// #was in upstream // include <Keyboard.h>
// #include "rp2040.h" // rp2040.cpp has routines that belong in main .ino file

// Wed 30 Mar 10:21:14 UTC 2022 - ONLINE edit

// rp2040.h

// extern void _reflashing(void);
void _reflashing(void) { }

// extern void _blink_led(void);

void _blink_led(void) {
    _pico_LED();
    // write a '.'
}

#include "forth_defines.h" // textual tags

// Fri 01 Apr 02:26:29 UTC 2022 - ONLINE edit

void _wait_10_usec(void) {
    sleep_us(10);
}

void _wait_1000_usec(void) {
    sleep_us(1000);
}

// Forth registers
uint32_t T=0; // cached top of data stack
uint32_t N=0; // not cached, another stack item
uint16_t I=0; // VM interpreter pointer
uint16_t W=0; // VM working register
uint8_t S=0; // data stack pointer
uint8_t R=0; // return stack pointer
uint16_t P=0; // program memory pointer
uint16_t A=0; // RAM pointer
unsigned long elapsed=0; // for counter timer
uint64_t D=0; // for double result of multiplication

// application regs and flags
uint8_t FL=0; // flags
uint8_t CMD=0; // command - shift regs for 7 segment display on the other core
uint8_t LVAL_0; // glyph encoded into 8 bits
uint8_t LVAL_1;
uint8_t LVAL_2;
uint8_t LVAL_3;

// data stack
#define STKSIZE 16
uint32_t stack[STKSIZE];
#define DROP T=stack[--S]
#define DUP stack[S++]=T

// return stack
#define RSTKSIZE 16
uint32_t rstack[RSTKSIZE];
#define PUSH rstack[R++]=T
#define POP T=rstack[--R]

// RAM
#define RAMSIZE 2048
uint8_t ram[RAMSIZE];

// Forth code words

void _off(){
    int pin = T;
    // digitalWrite(pin, LOW);
    DROP;
}

void _on(){
    int pin = T;
    // digitalWrite(pin, HIGH);
    DROP;
}

void _emit(){
    // Serial1.write(T);
    putchar(T); // provisional 29 Mar
    DROP;
}


//    strcpy(print_string, "  greet  Tue 29 Mar 17:58:24 UTC 2022");
//    printf("%s", print_string);

char b_print_string[64];
extern uint8_t getKey(void);

void _key(){
    DUP;
    uint8_t ch_key = getKey();
    // uint8_t str_size = sizeof(b_print_string); // no idea what this returns KLUDGE
    // memcpy(b_print_string, "DEBUG L71 n_sketch.cpp", str_size);
    // printf("%s", b_print_string);
    // T=Serial1.read();
    T=ch_key;
}

void _enter(){
    rstack[R++]=I;
    I=W;
}

void _fth_exit(){
    I=rstack[--R];
}

void _quit(){
    R=0;
    I=memory[0];
}

void _abort(){
    S=0;
    _quit();
}

void _branch(){
    I=memory[I];
}


void _zbranch(){
    if(T==0){
        I=memory[I];
        return;
    }
    I+=1;
}

void _dropzbranch(){
    if(T==0){
        DROP;
        I=memory[I];
        return;
    }
    DROP;
    I+=1;
}

void _pbranch(){
    if(T&0x80000000){
        I+=1;
        return;
    }
    I=memory[I];
}

// read 32 bits inline
// uint32_t T=0; // cached top of data stack
void _lit(){
    uint32_t TQ=0;
    DUP;
 // T=memory[I++]+(memory[I++]<<16);
    TQ = memory[I++];
    T = (memory[I++]<<16) + TQ;
}

void _next(){
    N=rstack[R-1];
    if(N){
        rstack[R-1]=N-1;
        I=memory[I];
        return;
    }
    R-=1;
    I+=1;
}

void _tor(){
    PUSH;
    DROP;
}

void _rfrom(){
    DUP;
    POP;
}

void _rfetch(){
    DUP;
    T=rstack[R-1];
}

void _variable(){
    DUP;
    T=memory[W];
}

void _dotsh(){
//  Serial1.print(" ");

    putchar(' '); // provisional 29 Mar


    switch(S){
    case 0:
        // Serial1.print("empty ");
        return;
    case 1:
        // Serial1.print(T, HEX);
        // Serial1.print(' ');
        return;
    default:
        for(uint8_t i=1; i<S; i++){
            // Serial1.print(stack[i], HEX);
            // Serial1.print(' ');
        }
        // Serial1.print(T, HEX);
        // Serial1.print(' ');
    }
}

void _dnumber(){
    DUP;
    // T=Serial1.parseInt(SKIP_WHITESPACE);
    T=43;
}

void _counter(){
    // elapsed=millis();
}

void _timer(){
    // Serial1.print(millis()-elapsed);
}

void _dup(){
    DUP;
}

void _drop(){
    DROP;
}

void _swap(){
    N=stack[S-1];
    stack[S-1]=T;
    T=N;
}

void _over(){
    stack[S++]=T;
    T=stack[S-2];
}

void _plus(){
    T+=stack[--S];
}

void _minus(){
    T=stack[--S]-T;
}

void _ms(){
    sleep_ms(T);
    // delay(T);
    DROP;
}

void _cr(){
    // Serial1.println();
    putchar('\n'); // provisional 29 Mar

}

void _and(){
    T&=stack[--S];
}

void _or(){
    T|=stack[--S];
}

void _xor(){
    T^=stack[--S];
}

void _invert(){
    T^=(-1);
}

void _negate(){
    T^=(-1);
    T+=1;
}

void _abs(){
    if(T&0x80000000) _negate();
}

void _twostar(){
    T=T<<1;
}

void _cfetch(){
    T=ram[T];
}

void _fetch(){
    W=T+3;
    T=ram[W--];
    T=T<<8;
    T+=ram[W--];
    T=T<<8;
    T+=ram[W--];
    T=T<<8;
    T+=ram[W];
}

void _fetchplus(){
    DUP;
    T=ram[A++];
    T+=(ram[A++]<<8);
    T+=(ram[A++]<<16);
    T+=(ram[A++]<<24);
}

void _wfetchplus(){
    DUP;
    T=ram[A++];
    T+=(ram[A++]<<8);
}

void _wfetch(){
    W=T;
    T=ram[W++];
    T+=(ram[W]<<8);
}

void _fetchpplus(){
    DUP;
    T=memory[P++];
}

void _twoslash(){
    T=T>>1;
}

void _a(){
    DUP;
    T=A;
}

void _astore(){
    A=T;
    DROP;
}

void _p(){
    DUP;
    T=P;
}

void _pstore(){
    P=T;
    DROP;
}

void _fetchp(){
    T=memory[T];
}

void _wstoreplus(){
    ram[A++]=(T&0xff);
    ram[A++]=((T>>8)&0xff);
    DROP;
}

void _wstore(){
    W=T;
    DROP;
    ram[W++]=(T&0xff);
    ram[W]=((T>>8)&0xff);
    DROP;
}

void _cstore(){
    W=T;
    DROP;
    ram[W]=T&0xff;
    DROP;
}
    
void _store(){
    W=T;
    DROP;
    ram[W++]=T&0xff;
    T=T>>8;
    ram[W++]=T&0xff;
    T=T>>8;
    ram[W++]=T&0xff;
    T=T>>8;
    ram[W++]=T&0xff;
    DROP;
}

void _cstoreplus(){
    ram[A++]=T&0xff;
    DROP;
}

void _storeplus(){
    ram[W++]=T&0xff;
    ram[W++]=(T>>8)&0xff;
    ram[W++]=(T>>8)&0xff;
    ram[W++]=(T>>8)&0xff;
    DROP;
}
// ###bookmark
void _depth(){
    DUP;
    T=S-1;
}

void _huh(){
    // Serial1.write(" ?\n");
    putchar(' ');
    putchar('?');
    putchar('\n');
    _abort();
}

void _cfetchplus(){
    DUP;
    T=ram[A++];
}

void _umstar(){
    D=T;
    DROP;
    D*=T;
    T=D&0xffffffff;
    DUP;
    T=(D>>32)&0xffffffff;
}

void _umslashmod(){
    N=T;
    DROP;
    D=T;
    D=D<<32;
    DROP;
    D+=T;
    T=D%N;
    DUP;
    T=D/N;
}

void _dnegate(){
    D=T;
    DROP;
    D=D<<32;
    D+=T;
    D=(-D);
    T=D&0xffffffff;
    DUP;
    T=(D>>32)&0xffffffff;
}

void _squote(){
    DUP;
    T=I+1;
    DUP;
    T=memory[I++];
    I+=T;
}

void _nip(){
    S-=1;
}

/*
void _initMCP23017(){
    Wire.begin();
    Wire.beginTransmission(0x20);
    Wire.write(0x0c); // GPPUA
    Wire.write(0xff);
    Wire.write(0xff);
    Wire.endTransmission();
}

// only one port expander in the system
void _fetchMCP23017(){
    DUP;
    Wire.beginTransmission(0x20);
    Wire.write(0x12); // GPIOA
    Wire.endTransmission();
    Wire.requestFrom(0x20, 2);
    T=Wire.read();
    W=Wire.read();
    T|=W<<8;
    T^=0xffff;
    T&=0xffff;
}

*/

#ifdef RP2040_VARIANT
#define FIRST_GPIO 16
#define LAST_GPIO 19
// all the I/O pins needed for the attached peripheral (HD44780 4-bit, initially)
// https://github.com/raspberrypi/pico-examples/blob/master/gpio/hello_7segment/hello_7segment.c#L51
void _initGPIO(){
    _pico_LED();
    for (int gpio = FIRST_GPIO; gpio < LAST_GPIO + 1; gpio++) {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_OUT); // GPIO_OUT defined by pico-sdk
    }

#if 0
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(9, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);
 // pinMode(A4, INPUT_PULLUP); // is4fse
 // pinMode(A5, INPUT_PULLUP);
#endif
}

void _fetchGPIO(){
    DUP;
    T=7; // KLUDGE
#if 0
    T=digitalRead(9);
    T|=digitalRead(10)<<1;
    T|=digitalRead(11)<<2;
    T|=digitalRead(12)<<3;
    T|=digitalRead(A1)<<4;
    T|=digitalRead(A2)<<5;
    T|=digitalRead(A3)<<6;
 // T|=digitalRead(A4)<<7;
 // T|=digitalRead(A5)<<8;
 #endif

    T^=0x01ff;
}
#endif // #ifdef RP2040_VARIANT

#ifndef RP2040_VARIANT
void _initGPIO(){
#if 0
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(9, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);
    pinMode(A4, INPUT_PULLUP);
    pinMode(A5, INPUT_PULLUP);
#endif
}

void _fetchGPIO(){
#if 0
    DUP;
    T=digitalRead(9);
    T|=digitalRead(10)<<1;
    T|=digitalRead(11)<<2;
    T|=digitalRead(12)<<3;
    T|=digitalRead(A1)<<4;
    T|=digitalRead(A2)<<5;
    T|=digitalRead(A3)<<6;
    T|=digitalRead(A4)<<7;
    T|=digitalRead(A5)<<8;
    T^=0x01ff;
#endif
}
#endif // #ifndef RP2040_VARIANT

void _lshift(){
    W=T;
    DROP;
    T=T<<W;
}

void _rshift(){
    W=T;
    DROP;
    T=T>>W;
}

// +code setmask 65,
#if 0
4.1.9.3.28. gpio_set_mask

static void gpio_set_mask (uint32_t mask)

Drive high every GPIO appearing in mask.

Parameters
   • mask Bitmask of GPIO values to set, as bits 0-29
#endif
void _setmask(){
    // gpio_set_mask (uint32_t mask);
    gpio_set_mask ((uint32_t) T);
    DROP;
}

// +code clrmask 66,
void _clrmask(){
}

#if 0
void _Keyboard_begin(){
    Keyboard.begin();
}

void _Keyboard_press(){
    Keyboard.press(T);
    DROP;
}

void _Keyboard_release(){
    Keyboard.release(T);
    DROP;
}

void _Keyboard_releaseAll(){
    Keyboard.releaseAll();
}

void _Keyboard_end(){
    Keyboard.end();
}

#endif

void _flstore(){
    FL=T;
    DROP;
}

void _flfetch(){
    DUP;
    T=FL;
}

void _cpl() {
//    bool state = digitalRead(T);
//    state = !state;
//    digitalWrite(T, state);
}

void _cmd_fetch() {
    DUP;
    T=CMD;
}

void _cmd_store() { // hum
// model on _flstore()
    CMD=T;
    DROP;
/*

   Forth runs on core0.

   Functions executed in its setup() and loop() apply
   only to itself - setup1() and loop1() ignore them.

   commands written in forth must be communicated to
   the other core through various mechanisms.

   The first trial will be through either the (forth)
   stack itself, or perhaps a cvariable (for simplicity).

*/
}

void _lv0_store() {
    LVAL_0=T; // glyph encoded into 8 bits
    DROP;
}

void _lv1_store() {
    LVAL_1=T;
    DROP;
}

void _lv2_store() {
    LVAL_2=T;
    DROP;
}

void _lv3_store() {
    LVAL_3=T;
    DROP;
}

void _execute();

void (*function[])()={
    _enter , _fth_exit , _abort , _quit , // 3
    _emit , _key , _lit , // 6
    _branch , _zbranch , _pbranch ,  _next , // 10
    _tor , _rfrom , _rfetch , _variable , // 14
    _dotsh , _dnumber , _counter , _timer , // 18
    _dup , _drop , _swap , _over , _plus , _minus , // 24
    _ms , _cr , _and , _or , _xor ,  // 29
    _invert , _negate , _abs , _twostar ,  _twoslash , // 34
    _cfetch , _fetch , _fetchplus , _fetchpplus , // 38
    _a , _astore , _p , _pstore , // 42
    _wstoreplus , _fetchp , _cstore , // 45
    _store , _cstoreplus , _storeplus , // 48
    _depth , _execute , _huh , _cfetchplus , // 52
    _wfetchplus , _umstar , _umslashmod , // 55
    _wfetch , _wstore , _dnegate , // 58
    _squote , _nip , //  _initMCP23017 , _fetchMCP23017 , // 62
    _initGPIO , _fetchGPIO , _lshift , _rshift , // 64
    _setmask , _clrmask , // 66

#if 0

 code lshift  63 ,
 code rshift  64 ,

+code setmask 65,
+code clrmask 66,

-code tusec 78 ,
-code msec 79 ,
--code /branch  80 ,

+code blink 67 ,
+code reflash 68 ,
+code on 69 ,
+code off 70 ,
+code fl@ 71 ,
+code fl! 72 ,
+code cpl 73 ,
+code cmd! 74 , \ new
+code cmd@ 75 , \ new
+code lv0! 76 , \ new
+code lv1! 77 , \ new
+code lv2! 78 , \ new
+code lv3! 79 , \ new
+code tusec 80 ,
+code msec 81 ,
+-code /branch  82 ,
#endif
    // _Keyboard_begin , _Keyboard_press ,
    // _Keyboard_release , _Keyboard_releaseAll , _Keyboard_end ,
    _blink_led ,  // 67 simple integer count
    _reflashing , // 68 // just add two 01 Apr 2022
    _on ,       // 69
    _off ,      // 70
    _flfetch,   // 71
    _flstore,   // 72
    _cpl,       // 73
    _cmd_store, // 74
    _cmd_fetch, // 75 new
    _lv0_store, // 76
    _lv1_store, // 77
    _lv2_store, // 78
    _lv3_store, // 79
    _wait_10_usec, // 80
    _wait_1000_usec, // 81
    _dropzbranch , // 82
};

void _execute(){
    W=T;
    DROP;
    (*function[memory[W++]])();
}

#define PRE_LAUNCH_T 27000

void blink_core_1(void) {
#if 0
    if(
        (millis() >= PRE_LAUNCH_T) // initial system delay
      ) {
        if ((millis() - elapsed) > 1000) {
            DUP ; T=LED_BUILTIN ; _cpl(); DROP ;
            elapsed = millis();
        }
    }
#endif
}

void noop(void) { }

void time_out_blinker(void) {
    for (volatile uint32_t sh_t = 1732144; sh_t > 0; sh_t--) {
        noop();
    }
}

void login_msgs(void) {
#if 0


    Serial1.println(RECENT_STAMP);
    Serial1.println(PROGRAM_NAME);
    Serial1.println(IP_NOTICE);
    Serial1.println(LOCAL_CONTRIB);
    Serial1.println();
    Serial1.print(COMMIT_TIME_STAMP);
    Serial1.print("            ");
    Serial1.println(COMMIT_STAMP);
    Serial1.println(BRANCH_STAMP);
    Serial1.println();
    Serial1.println(FEATURE_STAMP);
    Serial1.println(" on wokwi 23:27z");
#endif
}

void loop_forth(){
abort:
    S=0;
quit:
    R=0;
    I=memory[0];
next:
    W=memory[I++];
    (*function[memory[W++]])();
    goto next;
    while(-1);  // trap
    goto abort; // compiler kludge
    goto quit;  // compiler kludge
}

// extern void setup_sr(void);

// arduino initialization
void ar_setup(){
  //  Serial1.begin(115200);
  //  delay(200);

  //  pinMode(LED_BUILTIN, 1);
  //  digitalWrite(LED_BUILTIN, LOW); // inverted
  //  setup_sr();

  //  delay(800); // testing only
  //  if(Serial1) {
        login_msgs();
  //  }
// }

// void setup1(){
//    delay(1);
#if 0
    for (volatile int pq = (3 + 2);  pq > 0; pq--) {
        DUP ; T=LED_BUILTIN ; _cpl(); DROP ;
        time_out_blinker();
        DUP ; T=LED_BUILTIN ; _cpl(); DROP ;
        time_out_blinker();
        time_out_blinker();
        time_out_blinker();
    }
    digitalWrite(LED_BUILTIN, LOW);
    time_out_blinker();
#endif
}

// extern void loop_sr(void);

// arduino main loop
void pq_loop() {
    loop_forth();
// }


// second core
// void loop1(){
    if (FL != 179) { // stop blinking
    //  loop_sr();
        // blink_core_1();
    }
}
// END.




int forth_main() {
    sleep_ms(100);
    _pico_LED(); _pico_LED(); _pico_LED();
    uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    stdio_init_all();

    // uart_putc_raw(UART_ID, 'A');

    sleep_ms(100);
    uart_puts(UART_ID, "\n  new wokwi RPi Pico RP2040  Forth 31 Mar 2022\r\n");
    uart_puts(UART_ID, "  pico-sdk +/or wokwi based\r\n");

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

    strcpy(print_string, "  greet  Thu 31 Mar 00:41:02 UTC 2022");
    printf("%s", print_string);
    // putchar('\n');

    printf("\ntry:   h# 5 h# 3 over over * . cr .s cr");
    printf("\ntry:   words\n");
    while(1) {
        // uint8_t ch_key = getKey();
        // putchar(ch_key); // seems okay - no further research yet
        loop_forth();
        // bug catcher:
        putchar('_');
        putchar('_');
        putchar('?');
        putchar('L');
        putchar('_');
        putchar('_');

    }
}

/// \end::hello_uart[]
