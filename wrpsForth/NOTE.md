Sat  9 Apr 15:59:14 UTC 2022   ONLINE edit on wokwi

status: 8kb RAM allocated - now working.

NOTE: GPIO6 through GPIO11 (six pins in total) are correct and current, 9 April 2022 13:56 UTC.

Formerly, GPIO16 through GPIO21 were in use for this.

Physical hardware was constructed (just the LED's not an LCD module) and
that may've led to the reorg of the pins onto GPIO6 thru 11.

try also:  h# 43 write-lcd
           but only after init-lcd was run. ;)

 // define RAMSIZE 8192   // 4096 crashed on wokwi

quick saved copy for new work 09 Apr 08:02:54 UTC 2022 here:

  https://wokwi.com/projects/328448054597255764

  reorganized pins so that .RS and .E are on the low end:

\  DB7 DB6 DB5 DB4 .RS  .E
\   21  20  19  18  17  16
\    x   x   x   x   x   x

  lcd 16x2 substituted - real hardware on-hand locally. ;)
  
  hd44780 LCD driver (in Forth) upstream example code:

  https://github.com/wa1tnr/amrforth-v6_4-linux/blob/master/amrforth/www.amresearch.com/v6/appnotes/appnote001.zip

  TODO: series-ff-qc quick copy no hist 02 apr 02:56z


\ \\\\\\\\\\\\   NEWS    \\\\\\\\\\\\\\

This variant of the program 'works' nice.

Can display characters on the LCD!


(as stated elsewhere):

    "I'm in the middle of a project where I control this
    LCD controller chip directly (not using a backpack).

    so I'm a bit refreshed on a few of the ideas. ;)


    Amazingly, without hardware, I was able to port init-lcd
    and write-lcd well enough to type stuff in:

    https://wokwi.com/projects/328448054597255764

    Sat  9 Apr 08:00:14 UTC 2022


Sample run (typed interactively):


h# 6 clr
h# 6 setb
h# 6 clr
h# 1 setb
h# 1 clr

h# 2 setb
h# 2 clr
h# 4 setb
h# 4 clr
h# 8 setb

init  \  do not type these comments or the slash
--> -99 -98 -97  

.s --> -99 -98 -97

init-lcd cr h# 43 emit  \ 'C' in Serial Monitor

h# 55 .s cr --> -99 -98 -97 85
drop .s cr --> -99 -98 -97
 
\ minus decimal slash 0 1 2
h# 2d write-lcd cr  \  -
h# 2e write-lcd cr  \  .
h# 2f write-lcd cr  \  /
h# 30 write-lcd cr  \  0
h# 31 write-lcd cr  \  1
h# 32 write-lcd cr  \  2

h# 20 write-lcd cr  \  space
h# 20 write-lcd cr  \  space

\ 'Wokwi':

h# 57 write-lcd cr  \ 'W'
h# 6f write-lcd cr  \ 'o'
h# 6b write-lcd cr  \ 'k'
h# 77 write-lcd cr  \ 'w'
h# 69 write-lcd cr  \ 'i'  i as in hijk

 
I'm a bit stunned by this result. 

Seems to say the LCD hardware is timing-tolerant by a very large factor (very slow works). 




Sat  2 Apr 01:20:25 UTC 2022  ONLINE edit on wokwi

  https://wokwi.com/projects/327585255775011410

dvlp-aa  -  nice  functional  Forth

diagram.json   sandbox-d.c   forth_defines.h
NOTE.md        forth.c       memory.hx

  https://github.com/wa1tnr/wokwi_CircSimApps-a/tree/dvlp-aa/wrpsForth

  https://github.com/wa1tnr/wokwi_CircSimApps-a/tree/main/series-ee.d/pico-sdk/sandbox-d

  ./c to compile memory.h in gforth.


  BUGFIX code here:

  https://wokwi.com/projects/327861210310509138

  for bitmask issue w/ gpio_set_mask();
```cpp
  #define SET_MASK_AA   0xf // LED's to brighten, bitmask

  void demo_gpio_masking() {
      thisMask = SET_MASK_AA;
      thisMask = thisMask * 0x10000;
      thisMask += 0xffff;
      gpio_set_mask(thisMask);
  }
```


  NEWEST_not_current:

  https://wokwi.com/projects/327506579910820436

  NEW:

  https://wokwi.com/projects/327415555705274962  Tue 29 Mar 17:58:24 UTC 2022  REUSED OLDER ONE

  PROOF:
  https://wokwi.com/projects/327496766680203859  shows LCD in use.

  OLD WIRING VERTICAL TARGET:

  https://wokwi.com/projects/327487469083689556  recent  Tue 29 Mar 17:40:14 UTC 2022

  SCAFFOLDING:  (in various states of clean compilation and broken compilation):
  
  https://wokwi.com/projects/327418197022081618    Mon 28 Mar 23:31:49 UTC 2022

  https://github.com/wa1tnr/wokwi_CircSimApps-a/series-ee.d/pico-sdk/sandbox-c

  OLD_NEW:

    https://wokwi.com/arduino/projects/324803566934950484

    https://github.com/wa1tnr/camelforth-rp2040-a/tree/main/17-camelforth-a.d/pico-examples

    wokwi_CircSimApps-a/series-ee.d/pico-sdk/sandbox-a

END.
