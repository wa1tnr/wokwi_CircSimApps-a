/* NUCLEO  C031C6 */
#include <Arduino.h>

/*  wa1tnr  https://wokwi.com/projects/368342926546418689  */
/*  Fri 23 Jun 16:37:24 UTC 2023 */

/*  https://github.com/CharleyShattuck/Feather-M0-interpreter */

/* Tiny interpreter,
   similar to myforth's Standalone Interpreter
   This example code is in the public domain */

/* Structure of a dictionary entry */
typedef struct {
    const char *name;
    void (*function)();
} entry;

/* Data stack for parameter passing
   This "stack" is circular,
   like a Green Arrays F18A data stack,
   so overflow and underflow are not possible
   Number of items must be a power of 2 */
const int STKSIZE = 8;
const int STKMASK = 7;
int stack[STKSIZE];
int p = 0;

/* TOS is Top Of Stack */
#define TOS stack[p]
/* NAMED creates a string in flash */
#define NAMED(x, y) const char x[] = y

/* Terminal Input Buffer for interpreter */
const byte maxtib = 16;
char tib[maxtib];
/* buffer required for strings read from flash */
char namebuf[maxtib];
byte pos;

/* push n to top of data stack */
void push(int n) {
    p = (p + 1) & STKMASK;
    TOS = n;
}

/* return top of stack */
int pop() {
    int n = TOS;
    p = (p - 1) & STKMASK;
    return n;
}

/* Global delay timer */
int spd = 15;

/* top of stack becomes current spd */
NAMED(_speed, "speed");
void speed() {
    Serial.print("  range:  4 to 21  ");
    int parm = pop();
    spd = max(4, parm);
    parm = min(21, spd);
    spd = parm;
}

/* discard top of stack */
NAMED(_drop, "drop");
void drop() { pop(); }

/* recover dropped stack item */
NAMED(_back, "back");
void back() {
    for (int i = 1; i < STKSIZE; i++)
        drop();
}

/* copy top of stack */
NAMED(_dup, "dup");
void dup() { push(TOS); }

/* exchange top two stack items */
NAMED(_swap, "swap");
void swap() {
    int a;
    int b;
    a = pop();
    b = pop();
    push(a);
    push(b);
}

/* copy second on stack to top */
NAMED(_over, "over");
void over() {
    int a;
    int b;
    a = pop();
    b = pop();
    push(b);
    push(a);
    push(b);
}
/* add top two items */
NAMED(_add, "+");
void add() {
    int a = pop();
    TOS = a + TOS;
}

/* bitwise and top two items */
NAMED(_and, "and");
void and_() {
    int a = pop();
    TOS = a & TOS;
}

/* inclusive or top two items */
NAMED(_or, "or");
void or_() {
    int a = pop();
    TOS = a | TOS;
}

/* exclusive or top two items */
NAMED(_xor, "xor");
void xor_() {
    int a = pop();
    TOS = a ^ TOS;
}

/* invert all bits in top of stack */
NAMED(_invert, "invert");
void invert() { TOS = ~(TOS); }

/* negate top of stack */
NAMED(_negate, "negate");
void negate() { TOS = -(TOS); }

/* destructively display top of stack, decimal */
NAMED(_dot, ".");
void dot() {
    Serial.print(pop());
    Serial.print(" ");
}

/* destructively display top of stack, hex */
NAMED(_dotHEX, ".h");
void dotHEX() {
    Serial.print(0xffff & pop(), HEX);
    Serial.print(" ");
}

/* display whole stack, hex */
NAMED(_dotShex, ".sh");
void dotShex() {
    for (int i = 0; i < STKSIZE; i++)
        dotHEX();
}

/* display whole stack, decimal */
NAMED(_dotS, ".s");
void dotS() {
    for (int i = 0; i < STKSIZE; i++)
        dot();
}

/* delay TOS # of milliseconds */
NAMED(_delay, "delay");
void del() { delay(pop()); }

void bad_gpio() {
    Serial.print("Bad GPIO pin number!");
    // push(13); // shuffle it to D13, safe to do.
    drop();
    push(13);
}

void no_gpio() {
    dup(); // for test
    int test = pop(); // no more extra copies
    if (test == 36) {
        bad_gpio();
        return;
    }
    if (test == 40) {
        bad_gpio();
    }
}
#define WIGGLES 4 // blinks

/* Toggle pin at TOS and delay(spd), repeat... */
NAMED(_wiggle, "wiggle");
void wiggle() {
    no_gpio();
    int a = pop();
    pinMode(a, OUTPUT);

    Serial.println(" ");

#ifdef WIGGLE_PRINTS
    Serial.println(" ");
    Serial.println("  LD4 .. the green LED_BUILTIN .. is D200  ");
    Serial.println("  the red LED is D30 ");
    Serial.print("  type:   30 wiggle ");
    Serial.println(" or  type:  200 wiggle ");
#endif

    for (int i = 0; i < WIGGLES; i++) {
        digitalWrite(a, HIGH);
        delay(spd * 3 * 3);
        digitalWrite(a, LOW);
        delay(spd * 9 * 3);
    }
}

/* TOS is pin number, set it HIGH */
NAMED(_high, "high");
void high() { digitalWrite(pop(), HIGH); }

/* set TOS pin LOW */
NAMED(_low, "low");
void low() { digitalWrite(pop(), LOW); }

/* read TOS pin */
NAMED(_in, "in");
void in() { TOS = digitalRead(TOS); }

/* make TOS pin an input */
NAMED(_input, "input");
void input() { pinMode(pop(), INPUT); }

/* make TOS pin an output */
NAMED(_output, "output");
void output() { pinMode(pop(), OUTPUT); }

/* make TOS pin an input with weak pullup */
NAMED(_input_pullup, "input_pullup");
void input_pullup() { pinMode(pop(), INPUT_PULLUP); }

/* print CR, LF or both */

#define LOCAL_LINE_ENDING 0x0a

NAMED(_cr, "cr");
void cr_() { Serial.write(LOCAL_LINE_ENDING); }

NAMED(_nvic_reset, "reset");
void nvic_reset_() { NVIC_SystemReset(); }

/* dump 16 bytes of RAM in hex with ascii on the side */
void dumpRAM() {
    char buffer[9] = "";
    char *ram;
    int p = pop();
    ram = (char *)p;
    sprintf(buffer, "%4x", p); // was 4x
    Serial.print(buffer);
    Serial.print("   ");
    for (int i = 0; i < 16; i++) {
        char c = *ram++;
        sprintf(buffer, " %2x", (c & 0xff));
        Serial.print(buffer);
    }
    ram = (char *)p;
    Serial.print("   ");
    for (int i = 0; i < 16; i++) {
        buffer[0] = *ram++;
        if (buffer[0] > 0x7f || buffer[0] < ' ')
            buffer[0] = '.';
        buffer[1] = '\0';
        Serial.print(buffer);
    }
    push(p + 16);
}

/* dump 256 bytes of RAM */
NAMED(_dumpr, "dump");
void rdumps() {
    for (int i = 0; i < 16; i++) {
        Serial.println();
        dumpRAM();
    }
}

/* End of Forth interpreter words */
/* ******************************************** */
/* Beginning of application words */

/* End of application words */
/* ******************************************** */
/* Now build the dictionary */

/* empty words don't cause an error */
NAMED(_nop, " ");
void nop() {}

/* Forward declaration required here */
NAMED(_words, "words");
void words();


NAMED(_dow, "dow");
void dow() { // dup output wiggle
    dup(); dotS(); output(); wiggle(); // cr_();
}

void strobings() {
        dup();
        dotS();
        drop();
        wiggle();
}



/* strobe all ports */
NAMED(_strall, "strall");
void strall() {
    int accum = pop(); // need a starting port pin number
    int start = max(0, accum); // zero or greater
    accum = start;
    start = min(253, accum); // 253 or less
    for (int port = start; port < 255; port++) {
        push(port); strobings();
    }
}

/*  findings */

/*
 *    PB7 = D0
 *    PB6 = D1
 *   PA10 = D2
 *    PB3 = D3
 *   PB10 = D4
 *    PB4 = D5
 *    PB5 = D6
 *   PA15 = D7
 *    PA9 = D8
 *    PC7 = D9
 *  PB0.2 = D10
 *    PA7 = D11
 *    PA6 = D12
 *    PA5 = D13  LED_BUILTIN
 *    PB9 = D14
 *    PB8 = D15
 *    PA3 =
 * 192-197  lights up A0 thru A5
 * 200 lights up D13
 * 203 lights up PA8/D41
 * 204 lights up D19
 * 
 * 
 * 
 */

/* strobe the wired LEDs */
NAMED(_strobes, "strobes");
void strobes() {
    for (int index = 16; index < 24; index++) {
        push(index); strobings();
    }
    for (int index = 30; index < 36; index++) {
        push(index); strobings();
    }
}

/* table of names and function addresses in flash */
const entry dictionary[] = {{_nop, nop},
                            {_nvic_reset, nvic_reset_},
                            {_cr, cr_},
                            {_strall, strall},
                            {_strobes, strobes},
                            {_words, words},
                            {_dup, dup},
                            {_drop, drop},
                            {_back, back},
                            {_swap, swap},
                            {_over, over},
                            {_add, add},
                            {_and, and_},
                            {_or, or_},
                            {_xor, xor_},
                            {_invert, invert},
                            {_negate, negate},
                            {_dotS, dotS},
                            {_dotShex, dotShex},
                            {_dot, dot},
                            {_dotHEX, dotHEX},
                            {_delay, del},
                            {_high, high},
                            {_low, low},
                            {_in, in},
                            {_input, input},
                            {_output, output},
                            {_input_pullup, input_pullup},
                            {_wiggle, wiggle},
                            {_dow, dow},
                            {_dumpr, rdumps},
                            {_speed, speed}};

/* Number of words in the dictionary */
const int entries = sizeof dictionary / sizeof dictionary[0];

/* Display all words in dictionary */
void words() {
    for (int i = entries - 1; i >= 0; i--) {
        strcpy(namebuf, dictionary[i].name);
        Serial.print(namebuf);
        Serial.print(" ");
    }
}

/* Find a word in the dictionary, returning its position */
int locate() {

    //  GOOD spot to print something to help user understand prgrm flow.

    //  Serial.println("    locate   BEGINS here:  ");

    for (int i = entries - 1; i >= 1; i--) {
        // strcpy(namebuf, dictionary[i].name);

#ifdef DEBUG_AABA
        // char namebuf[maxtib];  maxtib is 16
        char *buffer_ptr = (char *)namebuf;
        int buffer_addr = (int)buffer_ptr;

        push(buffer_addr - 16); // show 3 line memory dump

        Serial.println();
        for (int count = 3; count > 0; count--) {
            // iterates 3 then 2 then 1
            Serial.println();
            dumpRAM();
        }
        Serial.println(" ");
#endif

        int name_size = 15;

        // populate namebuf from current dictionary entry
        memcpy(namebuf, dictionary[i].name, name_size);

#ifdef DEBUG_BBCB // have already: AABA
        // good indication it's somewhat correct:
        int len = strlen(namebuf);

        Serial.print("  ");
        Serial.print(namebuf);
        Serial.print(" strlen: ");
        Serial.println(len);
#endif
        if (!strcmp(tib, namebuf)) {
            namebuf[0] = '\0';
            tib[0] = '\0';
            //      namebuf[0] = '\0';
            //      tib[0] = '\0';
            return i;
        }
    }
    return 0;
}

/* Is the word in tib a number? */
int isNumber() {
    char *endptr;
    strtol(tib, &endptr, 0);
    if (endptr == tib)
        return 0;
    if (*endptr != '\0')
        return 0;
    return 1;
}

/* Convert number in tib */
int number() {
    char *endptr;
    return (int)strtol(tib, &endptr, 0);
}

char ch;

void ok() {
    if (ch == '\n')
        Serial.println("ok"); // was \r
}

/* Incrementally read command line from serial port */
byte reading() {
    if (!Serial.available())
        return 1;
    ch = Serial.read();
    if (ch == '\r')
        return 1;
    if (ch == '\n')
        return 0;
    if (ch == ' ')
        return 0;
    if (pos < maxtib) {
        tib[pos++] = ch;
        tib[pos] = 0;
    }
    return 1;
}

/* Block on reading the command line from serial port */
/* then echo each word */
void readword() {
    pos = 0;
    tib[0] = 0;
    while (reading())
        ;
    Serial.print(tib);
    Serial.print(" ");
}

/* Run a word via its name */
void runword() {

    // Serial.println("  this is runword     ");

#ifdef MY_DEBUG_PRINTS
    Serial.print(" DEBUG runword: ");
    Serial.print(tib);
    Serial.print("  ");
    delay(100);
    char *tib_ptr = (char *)tib;
    uint32_t tib_adr = (uint32_t)tib_ptr;
    push(10);
    push(tib_adr);
    Serial.print("  pushed.  ");
    dotS();
    Serial.println("   y   ");
    Serial.println(" ");
    dumpRAM();
    Serial.println(" ");
    Serial.println("  That was dumpRAM(); ");
    Serial.println(" ");
    Serial.print(tib_adr);
    Serial.print("   x   ");
#endif

    int place = locate();

    //  Serial.println(" ");

    //  Serial.println("  place is possibly assigned to output of fn locate();
    //  sweet.");

    if (place != 0) {
        dictionary[place].function();
        ok();
        return;
    }
    if (isNumber()) {
        push(number());
        ok();
        return;
    }
    Serial.println("?");
}

/* Arduino main loop */

void setup() {
    Serial.begin(115200);
    while (!Serial)
        ;
    Serial.write(' ');
    Serial.println();
    Serial.println("Forth-like interpreter:");
    Serial.println(
        "    536871082  is  0x200000AA    use  536870912 for 0x0000 \n");
    Serial.println(" https://wokwi.com/projects/368342926546418689  nucleo "
                   "C031C6 on wokwi");
    words();
    Serial.println();
    // strobes();
}

void loop() {
    readword();
    // Serial.print("      the loop     ");
    runword();
}

// 23 June 02:22z
// END.
