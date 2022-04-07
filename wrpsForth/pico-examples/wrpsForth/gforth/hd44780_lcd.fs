\ hd44780_lcd.fs  4 April 2022

\ long pin on the right, resistor on short pin to ground
\ that makes long pin anode
\ red led  2.2k limiting resistor
\ all measured 2.167 k
\ LED's double-spaced and straddle center gap breadboard
\ hookup wire cut custom lengths to reach IDE headers in breadboard other columns nearby same side

\ Pinout right to left progressing higher in number:

\ skip 1-8 and 8 is a ground
\ 9-12 four pins are GP6 thru GP9
\ pin 13 is a ground
\ pins 14 and 15 map to GP10 and GP11
\ GP12 on pin 16 is available and unused here.
\ pins 17 thru 20 entirely unavailable (no headers)

\ GP6 in Red
\ GP7 in Orange
\ GP8 in Yellow
\ GP9 in Green
\ GROUND - fifth pin of this array right to left
\ GP10 in Blue
\ GP11 in Violet

\ GP11 GP10 GP9 GP8  Viol Blue Gree Yell  data bus
\ GP7 GP6 control .E .RS or swapped in Orange Red (GP7 GP6)


\ void _gpio_put_masked() // ( mask value  -- )
\ mask value gpio_put_masked

\ all #, in decimal

\ tusec sleep_us(1)

\ msec  sleep us(1000)

\ 100 us  10 * the tusec period
\ 10 ms   10 * the msec  period
\ 100 ms  100 * the msec period
\ 200 ms  200 * the msec period

0 [if]

The pin assignments in the original example (keylcd.fs)
can be intuited here:

   135  code writing  (  - )
   136  \ - Configure the data pins for output.
   137          %00001011 # pins mov  data?
   138          %11111100 # dirs orl  push-pull
   139          next c;

The application note says that the first two pins of P0
(an 8-bit wide GPIO port) are used for the USART and are
(mostly) ignored - they aren't part of the wiring for the
LCD (or pb switches, possibly, multiplexed).

That leaves the upper six bits for the LCD (HD44780).

   136  \ - Configure the data pins for output.
   137          %00001011 # pins mov  data?
   138          %11111100 # dirs orl  push-pull
   xxx          %11111111 # pin state?

The '1011' bit pattern is seen elsewhere.  The lower two
bits aren't of concern, leaving the higher two bits set
at '10'.

                                           RS R/W DB7 DB6 DB5 DB4
The guess here:  1011 means  'Function set  0   0   0   0   1  DL   N   F   *   *'
                                                            1   0   1   1
The unlabeled columns are the USART pins.

That leaves DB5 set and DB4 ('DL') reset.

Does that match an instruction?

Datasheet (page 27, Adafruit 16x2 product's version of Hitachi datasheet) says:

Function Set

DL: Sets the interface data length.

Data is sent or received in 8-bit lengths (DB7 to DB0) when DL is 1,
and in 4-bit lengths (DB7 to DB4) when DL is 0.

When 4-bit length is selected, data must be sent or received twice.

N: Sets the number of display lines.

F: Sets the character font.

Note: Perform the function at the head of the program before
executing any instructions (except for the read busy flag and
address instruction).

From this point, the function set instruction cannot be executed
unless the interface data length is changed.

Source example, again:

   137          %00001011 # pins mov  data?

1011 means 10 are good but 11 are irrelevant.

10 means DB5 set ('Function set') and DB4 (DL) reset.

 ".. and in 4-bit lengths (DB7 to DB4) when DL is 0."

So this '10' instruction says 'Function set, 4-bit mode'
which seems to match what the keylcd.fs source file is saying.

: w_rite-lcd  ( c - )

\ - Based on working BASIC code.
	[ in-assembler
	%00001011 # pins anl ]  \ instruction
	dup
	[ in-assembler
	SP inc  Apop
	%11110000 # A anl  \ potentially says the upper four bits are the data bus
	A pins orl ]
	pulseout-E
	16 *
	[ in-assembler
	SP inc  Apop
	%00001011 # pins anl
	A pins orl ]
	pulseout-E
	;


but:

a: .E
\ - Give bit 2 of port 0 the name .E, for Enable.
	2 .P0 ;a

a: .RS
\ - Give bit 3 of port 0 the name .RS, for Register Select.
	3 .P0 ;a

a: pins
\ - Name port 0 pins, as in BASIC.
	P0 ;a

a: dirs
\ - Name the port 0 config register dirs, for direction.
	PRT0CF ;a

So, 2 .P0 is here:

00000x00

and 3. P0 is here:

0000x000

and so, the two lower bits are .RS and .E .. which leaves the new guess as:

  DB7 DB6 DB5 DB4 .RS  .E   U  U'    (U and U' are the USART)
    x   x   x   x   x   x   x   x
    x   x   x   x   x   x   x   x


Here's the initializer again:

: init-lcd  (  - )
\ - Also based on working BASIC code.
	[ in-assembler
	%00000011 # pins mov   \ preserve USART states, instruction ('command') mode (.RS reset)
	%11111100 # dirs orl ] \ six GPIO pins set to OUTPUT (push-pull)
	200 ms
	[ in-assembler
	%00110000 # pins mov ]  \ Function set: DB5 and DB4 set, DB6 and DB7 reset - 8 bit mode

                                \ send that data to the LCD controller chip:
	pulseout-E-10 100 ms
	pulseout-E-10 100 ms
	pulseout-E-10 100 ms

	[ in-assembler
	%00100000 # pins mov ]  \ Function set: DB5 set, DB4 reset - 4 bit mode
	pulseout-E-10 100 ms

	$28 write-lcd 100 ms    \ now send it some stuff we want sent ;)
	$0e write-lcd 10 ms
	$01 write-lcd 100 ms
	$02 write-lcd 10 ms
	data
	;

What is $28 for?

Try this first:  %0010 1000

remembering that the two lowest bits are the USART, and
the two above those are control lines (not data).

That makes .RS a 1 (set) and .E a 0 (reset).

Data is 0x10 (2 in decimal).

.RS as a 1 means 'data' not 'instruction'.

write-lcd implies the high bits of an ascii char are sent first,
followed by a left-shift.

So, ASCII 'A' (decimal 65):

decimal 65 hex . 40 ok

%0100 0000

%0100 sent first.  left-shift four bits.  %0000 sent second.


[then]





: qqstimex 384 \ 900
  #, for
      msec
  next
; \ 900 milliseconds


\ 100 us - only instance upstream

: us ( c -- )
  for tusec next
;

: ms ( c -- ) \ good as-is
  \ msec  sleep us(1000)
  for msec next
;



\ : PINSsetup initGPIO ;

\  DB7 DB6 DB5 DB4 .RS  .E
\   21  20  19  18  17  16
\    x   x   x   x   x   x

\  32: GP21  DB7
\  16: GP20  DB6
\   8: GP19  DB5
\   4: GP18  DB4
\   2: GP17  .RS
\   1: GP16  .E

: .E   1 #, ; ( -- n )  \ port pin GP16 Enable
: .RS  2 #, ; ( -- n )  \ port pin GP17 RS

: clr clrmask ;
: setb setmask ;

: gpm gpio_put_masked ; ( mask value -- ) \ alias
: orl $3f #, gpm ; ( mask -- )
: anl invert 0 #,  gpm ; ( mask -- )

\ illustrative:

\ h# 3 orl cr  \ set gang of pins no resets
\ h# 30 orl cr \ set gang of pins no sets

\ h# $3f h# c gpm cr  \ set and reset in one go

\ h# 3 orl cr  \ set gang of pins no resets
\ h# 30 orl cr
\ h# 3f h# c gpm cr
\ h# 3f h# 3f gpm cr
\ h# c anl

\ %001100 anl

: instruction
  \  initGPIO
  .RS clr ;

: data
  \ initGPIO
  .RS setb ;

: dark instruction ;
: bright data ;













\ : pulseout-E-10 1 #, drop ;

\ : pulseout-E-10  (  - ) [ asm  .E cpl ] 100 us [ asm  .E cpl ] ;

\ : xxpulseout-E-10  (  - )  .E setb 100 #, us .E clr ;
: pulseout-E  (  - )  .E setb 800 #, ms .E clr ;
: poute pulseout-E ;

\ ." dark h# 100 ms bright h# 200 ms dark cr" cr ;

: clrbits ( -- )
  \   0011 1111 \ clear all six bits
  $3f #, clrmask
;



: xxwrite-lcd  ( c - )
  \ mask value gpio_put_masked
  \ 000010 pins anl
  \ 000010
  \ 111101   000000
  \ 11 1101   000000
  $3d #, $0 #, gpio_put_masked  \ %000010 pins anl
  \ $3d #, clrmask \ %00001011

  \ %00001011 pins anl \ Instruction mode, clear data bus.
  \ %0000 0010 pins anl \ Instruction mode, clear data bus.
  \ $11 1101 clrmask
  \ $3d clrmask



  $3d #, clrmask \ reset all but the one bit
  $2  #, setmask \ Instruction mode, clear data bus.
  \ %111101
  \ %
  \ %
  dup
  $3  #, clrmask \ clear control bits
  setmask \ TOS written to data bits

  drop \ balance stack kludge

;

: wait
  250 #, ms
  250 #, ms
  250 #, ms
  250 #, ms
  250 #, ms
  250 #, ms
;

\ : orl $3f #, gpm ; ( mask -- )
\ : anl invert 0 #,  gpm ; ( mask -- )

: pins 1 #, drop ; \ syntax sugar

: write-lcd  ( c - )
\ - Based on working BASIC code.
	\ [ in-assembler
	\ %00001011 # pins anl ]  \ amr instruction
        \ %000010   # pins anl \ without USART
        $2 #, anl \ .RS setb \ data wrpsForth  four data bit set to zero the 11 is USART
        wait
	dup \ both wrpsForth and amrForth - for split nybble
	\ [ in-assembler
	\ SP inc  Apop
	\ %11110000 # A anl
        $f0 #, and \ reset TOS lower four bits wrpsForth

  	\ A pins orl ] \ amrForth
        2/ 2/ orl \ right-shift data wrpsForth
        wait
	pulseout-E
        wait
	$10 #, * \ left-shift nybble
	\ [ in-assembler
	\ SP inc  Apop
	\ %00001011 # pins anl \ amr
        $2 #, anl \ instruction wrpsForth  four data bit set to zero the 11 is USART
        wait
	\ A pins orl ]
        2/ 2/ orl \ wrpsForth
        wait
	pulseout-E
        wait
	;

\ ###bookmark
\ h# ff orl .s --> -99 -98 -97  cr 
\ h# 2 anl .s --> -99 -98 -97  cr 
\ h# 41 dup .s --> -99 -98 -97 65 65  cr 
\ h# f0 and .s --> -99 -98 -97 65 64  cr 
\ 2/ 2/ .s --> -99 -98 -97 65 16  cr 
\ orl .s --> -99 -98 -97 65  cr 
\ pulseout-E .s --> -99 -98 -97 65  cr 
\ pulseout-E .s --> -99 -98 -97 65  cr 
\ h# 10 * .s --> -99 -98 -97 1040  cr 
\ h# 400 - .s --> -99 -98 -97 16  cr 
\ h# 2 anl .s --> -99 -98 -97 16  cr 
\ 2/ 2/ .s --> -99 -98 -97 4  cr 
\ orl .s --> -99 -98 -97  cr 


: init-lcd ( -- )
  clrbits    \ %00000011 # pins mov \ Set command mode, 0 command.
  initGPIO   \ %11111100 # dirs orl \ Set pins as outputs.
  200 #, ms  \ wait 200 ms for LCD reset.
  clrbits
  $c #, setmask \ %00110000 # pins mov \ Init instruction
  wait
  pulseout-E 100 #, ms
  wait
  pulseout-E 100 #, ms
  wait
  pulseout-E 100 #, ms
  wait
  clrbits
  wait
  $8 #, setmask
  wait
  pulseout-E 100 #, ms
  wait
  $28 #, write-lcd 100 #, ms
  wait
  $0e #, write-lcd  10 #, ms
  wait
  $01 #, write-lcd 100 #, ms
  wait
  $02 #, write-lcd  10 #, ms
  wait
  data
;







: testus dark bright
  \ results: 3x longer at six seconds wokwi than expected (testms was fine on wokwi)

  \ two seconds LED on
  200 #, for \ 2000 in realtime hardware but 200 for wokwi

  \ one millisecond begins
      4 #, for
          25 #, us \ 250 real world so try 25 wokwi
      next
  \ one millisecond ends
  next
  dark
;

: testms dark bright
  \ same human interval 2 sec as in testus
  100 #, for 2 #, ms next \ 1000 realtime 100 wokwi
  dark
;

\ for testus and testms:
\     03:05z 04 Apr 2022: both tests give about 2 seconds of LED ON time.

: pulsed ( -- ) ." pulsed ( -- ) "
  ." dark h# 100 ms bright h# 200 ms dark cr" cr ;

: testvv ." hd44780 LCD  02:45z" cr cr
  ." try:  testus  or  testms to see LED blink for a 2 second interval." cr
;

: tell ." Thu  7 Apr 07:12:59 UTC 2022" cr ;

: init 0x63 #, negate dup 1+ dup 1+ cr .s cr ;

\  END.
