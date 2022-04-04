\ x

\ all #, in decimal

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

: testvv ." hd44780 LCD  02:12z" cr ;
