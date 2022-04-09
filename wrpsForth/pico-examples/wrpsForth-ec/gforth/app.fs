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


\ gforth doesn't need a gap between last char and closing quote

\ so   : foo ." this" ;  \ is just fine.

: hint ." setupgpio   << now very good demo" cr
       ." setupgpio  initGPIO  h# 13  setmask" cr
       ." h# 10 on   h# 11 on   thru   h# 15 on" cr
       cr
       ." h# f setmask"     cr
       ." stimex h# 13 off" cr
       ." stimex h# 12 off" cr
       ." stimex h# 11 off" cr
       ." stimex h# 10 off" cr
       ." h# b setmask" cr
       ." run   <-- demo" cr
;

: run

  15 #, setmask stimex stimex
  15 #, clrmask stimex stimex

  14 #, setmask stimex stimex
  14 #, clrmask stimex stimex

  13 #, setmask stimex stimex
  13 #, clrmask stimex stimex

  12 #, setmask stimex stimex
  12 #, clrmask stimex stimex

  11 #, setmask stimex stimex
  11 #, clrmask stimex stimex

  10 #, setmask stimex stimex
  10 #, clrmask stimex stimex

   9 #, setmask stimex stimex
   9 #, clrmask stimex stimex

   8 #, setmask stimex stimex
   8 #, clrmask stimex stimex

   7 #, setmask stimex stimex
   7 #, clrmask stimex stimex

   6 #, setmask stimex stimex
   6 #, clrmask stimex stimex

   5 #, setmask stimex stimex
   5 #, clrmask stimex stimex

   4 #, setmask stimex stimex
   4 #, clrmask stimex stimex

   3 #, setmask stimex stimex
   3 #, clrmask stimex stimex

   2 #, setmask stimex stimex
   2 #, clrmask stimex stimex

   1 #, setmask stimex stimex
   1 #, clrmask stimex stimex
;

: bbrun 5 #, 3 #, over over cr ." dot S: " .s cr ;

\ : run n867 ;

\ : tell ." Thu  7 Apr 06:32:55 UTC 2022" cr ;
\ end.
