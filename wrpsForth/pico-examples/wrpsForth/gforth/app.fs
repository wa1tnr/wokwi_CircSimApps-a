\ Thu 31 Mar 18:18:41 UTC 2022

: stimex 384 \ 900
  #, for
      msec
  next
; \ 900 milliseconds

: n867
  6 #, cmd! start

  begin

  ." STACK: " .s cr

  gl_ lv2!  \ __blank 2 write 3
  gl_ lv3!

  gl_ lv1!  \ __blank 1 write 2
  gl_ lv2!

  gl_ lv0!  \ __blank 0 write 1
  gl_ lv1!

  \ stanza

  gl_ lv0! stimex stimex stimex stimex




  gl_ lv2!
  gl_ lv3!

  gl_ lv1!
  gl_ lv2!

  gl_ lv0!
  gl_ lv1!

  \ stanza

  gl5 lv0! stimex stimex stimex stimex




  gl_ lv2!
  gl_ lv3!

  gl_ lv1!
  gl_ lv2!

  gl_ lv0!
  gl5 lv1!

  \ stanza

  gl2 lv0! stimex stimex stimex stimex




  gl_ lv2!
  gl_ lv3!

  gl_ lv1!
  gl5 lv2!

  gl_ lv0!
  gl2 lv1!

  \ stanza

  gl4 lv0! stimex stimex stimex stimex



  gl_ lv2!
  gl5 lv3!

  gl_ lv1!
  gl2 lv2!

  gl_ lv0!
  gl4 lv1!

  \ stanza

  gl8 lv0! stimex stimex stimex stimex


  gl_ lv2!
  gl2 lv3!

  gl_ lv1!
  gl4 lv2!

  gl_ lv0!
  gl8 lv1!

  \ stanza

  gl1 lv0! stimex stimex stimex stimex


  gl_ lv2!
  gl4 lv3!

  gl_ lv1!
  gl8 lv2!

  gl_ lv0!
  gl1 lv1!

  \ stanza

  gl2 lv0! stimex stimex stimex stimex


  gl_ lv2!
  gl8 lv3!

  gl_ lv1!
  gl1 lv2!

  gl_ lv0!
  gl2 lv1!

  \ stanza

  gl3 lv0! stimex stimex stimex stimex

  gl_ lv2!
  gl1 lv3!

  gl_ lv1!
  gl2 lv2!

  gl_ lv0!
  gl3 lv1!

  \ stanza

  gl_ lv0! stimex stimex stimex stimex

  gl_ lv2!
  gl2 lv3!

  gl_ lv1!
  gl3 lv2!

  gl_ lv0!
  gl_ lv1!

  \ stanza

  gl_ lv0! stimex stimex stimex stimex


  gl_ lv2!
  gl3 lv3!

  gl_ lv1!
  gl_ lv2!

  gl_ lv0!
  gl_ lv1!

  \ stanza

  gl_ lv0! stimex stimex stimex stimex

  gl_ lv2!
  gl_ lv3!

  gl_ lv1!
  gl_ lv2!

  gl_ lv0!
  gl_ lv1!

  \ stanza

  gl_ lv0! stimex stimex stimex stimex

  again

;

: setupgpio ( -- )
  initGPIO 19 #, setmask
  16 #, on  stimex
  16 #, off stimex
  17 #, on  stimex
  17 #, off stimex
  18 #, on  stimex
  18 #, off stimex
  19 #, on  stimex
  19 #, off stimex
  20 #, on  stimex
  20 #, off stimex
  21 #, on  stimex
  21 #, off stimex
;  \ verify decimal - 0x13 is decimal 19

0 [if]
: foo
  decimal
  16 17 or hex . 11
  decimal 16 17 or 18 or 19 or hex . 13
  decimal 16 17 or 18 or 19 or     . 19
  decimal 19 hex . 13
;
[then]

: tell ." Thu 31 Mar 18:18:41 UTC 2022 " cr ;

\ gforth doesn't need a gap between last char and closing quote

\ so   : foo ." this" ;  \ is just fine.

: hint ." setupgpio   << now very good demo" cr
       ." setupgpio  initGPIO  h# 13  setmask" cr
       ." h# 10 on   h# 11 on   thru   h# 15 on" cr ;

: run 5 #, 3 #, over over cr ." dot S: " .s cr ;

\ : run n867 ;

\ end.
