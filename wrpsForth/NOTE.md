Mon  4 Apr 01:01:04 UTC 2022   ONLINE edit on wokwi

  lcd 16x2 substituted - real hardware on-hand locally. ;)
  
  hd44780 LCD driver (in Forth) upstream example code:

  https://github.com/wa1tnr/amrforth-v6_4-linux/blob/master/amrforth/www.amresearch.com/v6/appnotes/appnote001.zip

  TODO: series-ff-qc quick copy no hist 02 apr 02:56z
     
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
