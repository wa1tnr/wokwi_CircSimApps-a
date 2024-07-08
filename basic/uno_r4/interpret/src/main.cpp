#include <Arduino.h>

// Serial, SerialUSB, Serial1

// if using a live terminal like picocom, then
// swap the following two lines:
#undef REAL_TERMINAL_IN_USE
#define REAL_TERMINAL_IN_USE

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
#define NAMED(x, y) const char x[]=y

/* Terminal Input Buffer for interpreter */
const byte maxtib = 16;
char tib[maxtib];
/* buffer required for strings read from flash */
char namebuf[maxtib];
byte pos;

/* push n to top of data stack */
void push(int n) {
  p = (p + 1)& STKMASK;
  TOS = n;
}

/* return top of stack */
int pop() {
  int n = TOS;
  p = (p - 1)& STKMASK;
  return n;
}

char ch;

void ok() {
  if (ch == '\r')
    Serial.print(" ok ");
}

#define BACKSPACE '\010'

uint8_t ahua_flg = 0;
uint8_t first_run_flg = 1; // raise for first run

/* Incrementally read command line from serial port */
uint8_t reading() {
  if (!Serial.available())
    return 1;

  ch = Serial.read();

  if (ahua_flg) {
    int counted;
    counted = 6;

    for (int count = counted; count > 0; count--) {
      Serial.write(' ');
      Serial.flush();
      Serial.write(BACKSPACE);
      Serial.flush();
      Serial.write(BACKSPACE);
      Serial.flush();
    }
    Serial.write(' ');
    Serial.flush();
    ahua_flg = 0; // reset
  }

  if (ch == BACKSPACE) {
    Serial.write(' ');
    Serial.write(BACKSPACE);
    Serial.flush();
    if (pos > 0) {
      Serial.write(BACKSPACE);
      Serial.write(' ');
      Serial.write(BACKSPACE);
      Serial.flush();
      tib[--pos] = 0; // obliterate
    }
    if (pos == 0) {
      Serial.write(BACKSPACE);
      Serial.write(' ');
      Serial.write(BACKSPACE);
      Serial.print(" ahua!");
      Serial.flush();
      ahua_flg = 1;
    }
    return 1;
  }

#ifdef REAL_TERMINAL_IN_USE
  Serial.write(ch); // no echo on wokwi but use otherwise
  Serial.flush();
#endif

  if (ch == '\n')
    return 0; // was 1 not zero TODO

  if (ch == '\r') {
    Serial.write('\n');
    Serial.flush();
    return 1; // was 0 not one TODO
  }

  if (ch == ' ')
    return 0;

  if (pos < maxtib) {
    tib[pos++] = ch;
    tib[pos] = 0;
  }
  return 1;
}

void readword() {
  Serial.flush();
  pos = 0;
  tib[0] = 0;
  while (reading())
    ;
  Serial.println("   <-- exited readword()");
}


void examine_tib() {
  Serial.print(" tib:  '");
  Serial.print(tib);
  Serial.println("'  <-- tib");
  tib[0]= 0;
}

void first_run() {
  delay(5000);
  Serial.print("  awaiting first space or press of ENTER key.. ");
  while (reading()) { ; }
  Serial.println("  FIRST RUN");
  first_run_flg = 0; // lower
}

void setup() {
  delay(800);
  Serial.begin(115200);
  delay(800);
  Serial.write('\n');
  Serial.write('\n');
  Serial.write('\n');
  Serial.write('\n');
  Serial.write('\n');
  Serial.write('\n');
  Serial.write('\n');
  Serial.write('\n');
  if (first_run_flg) { first_run(); }
  Serial.write('\n');
  Serial.write('\n');
  Serial.write('\n');
  Serial.write('.');
  Serial.write('\n');
  Serial.println(" type: three short words:");
  Serial.println("");
}
void loop() {
  readword();
  examine_tib();
  Serial.flush();
  delay(300);
}

