Wed  9 Feb 20:48:11 UTC 2022

search:

arduino debounce with interrupt site:arduino.stackexchange.com

Basically, the prevailing advice (atm, not all read of course) seems to imply that the human factor governs - interrupts on pushbuttons not normally a great idea (scroll to JUST_WHY).

Unlike, say, a rotary encoder, with much finer timings (presumed here in this write-up, anway) - the pushbutton switch needs to be carefully debounced for human factors.

And so, it appears is a good candidate for a polling style rather than an interrupt-driven style, of coding (at least for this one subsystem of a given program running on an Arduino IDE compatible target MCU).

No harm (of course) in ignoring all that and going ahead and trying to get interrupt-based pb debouncing (somewhat) functional. ;)


https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

Good general advice/write-up.

https://forum.arduino.cc/t/debouncing-a-switch-on-an-interrupt-pin/632166/6

https://playground.arduino.cc/Main/MsTimer2/

https://forum.arduino.cc/t/debouncing-an-interrupt-trigger/45110/15

in irons on this one, now. 9 Feb 2022 12:16 UTC


mild interest in this one:

https://arduino.stackexchange.com/questions/66761/debouncing-a-button-with-interrupt

nice diagram of events:

https://arduino.stackexchange.com/questions/17443/how-to-simulate-delay-to-debounce-mechanical-button-using-millis/18545#18545

nice hardware debouncing discussion:

https://arduino.stackexchange.com/questions/34054/multiple-buttons-on-single-interrupt-how-to-debounce

also, quite good hardware debounce discussion here:

http://www.ganssle.com/debouncing-pt2.htm



JUST_WHY

At Ganssle it was said:

_Similarly, don't tie undebounced switches, even if Schmitt Triggered, to interrupt inputs on the CPU. Usually the interrupt pin goes to the clock input of an internal flip flop. As processors become more complex their datasheets give less useful electrical information; they're awash in programming data but leave designers adrift without complete timing specs. Generally we have no idea what the CPU expects as a max rise time or the min pulse width. Those internal flops aren't perfect, so don't flirt with danger by feeding them garbage._


This makes sense and doesn't rely on an unsourced heuristic.  It sounds solid (to me).

_smokimus gunimus_

END.
