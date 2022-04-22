// [8:02 PM] KazeofHope:
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define MYDELAY 1

#define SWITCH1 PC2 // button1
#define SWITCH2 PC3 // button2

int main (void) {
    // Button Pin Setup (PORT C NOT DONE)
    DDRC = (1 << SWITCH1);
    PORTC = (1 << SWITCH1);

    DDRC = (2 << SWITCH2);
    PORTC = (2 << SWITCH2);

    // PB3 as output (PORT B DONE)
    DDRB |= (1 << DDB3);

    // set PWM duty cycle
    OCR2A = 0;
    // set non-inverting mode
    TCCR2A |= (1 << COM2A1);
    // set fast PWM Mode
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    // set prescaler to 8 and starts PWM
    TCCR2B |= (1 << CS21);

    while (1) {
        if (((PINC & (1 << SWITCH1)) == 0) && ((PINC & (1 << SWITCH2)) == 0)) {
            OCR2A = 255;
        }
        else if ((PINC & (1 << SWITCH1)) == 0) {
            OCR2A = 20;
        }
        else if ((PINC & (1 << SWITCH2)) == 0) {
            OCR2A = 0;
        }
//''
        _delay_ms (MYDELAY);
    }

    return 0;

}
