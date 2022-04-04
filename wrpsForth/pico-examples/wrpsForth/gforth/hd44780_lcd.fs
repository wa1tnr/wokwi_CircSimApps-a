\ hd44780_lcd.fs  4 April 2022

\ all #, in decimal

\ tusec sleep_us(1)

\ msec  sleep us(1000)

\ 100 us  10 * the tusec period
\ 10 ms   10 * the msec  period
\ 100 ms  100 * the msec period
\ 200 ms  200 * the msec period

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

: .E  16 #, ; ( -- n )  \ port pin GP20 Enable
: .RS 32 #, ; ( -- n )  \ port pin GP21 RS

: clr clrmask ;
: setb setmask ;

: instruction
  \  initGPIO
  .RS clr ;

: data
  \ initGPIO
  .RS setb ;

: dark instruction ;
: bright data ;

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
