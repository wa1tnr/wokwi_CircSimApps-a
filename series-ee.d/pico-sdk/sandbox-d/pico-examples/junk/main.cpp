// Wed 30 Mar 10:21:14 UTC 2022 - ONLINE edit

void cpl(int pin) {
}

void psdelay(long pdelay) {
    for (volatile long count = pdelay;
        count > 0; count--) { }
}

void blink(void) {
    cpl(5); // cpl(LED_BUILTIN);
    psdelay(650033);
    cpl(5); // cpl(LED_BUILTIN);
    psdelay(3500444);
}

void setup_oldmain(void) {
//  SERIAL.println("ITC-ish Forth - LCD  27 Mar 2022");
}

void loop_oldmain(void) { }

#if 0

// - - -   diagram.json   - - -

{
  "version": 1,
  "author": "PROVEN GOOD w LCD - wa1tnr / nis - Wed 30 Mar 10:21:14 UTC 2022",
  "editor": "wokwi",
  "parts": [
    {
      "type": "wokwi-pi-pico",
      "id": "pico",
      "top": 0,
      "left": 0,
      "rotate": 270,
      "attrs": { "builder": "pico-sdk" }
    },
    { "type": "wokwi-lcd2004", "id": "lcd1", "top": -340, "left": -150, "attrs": {} }
  ],
  "connections": [
    [ "pico:GP0", "$serialMonitor:RX", "", [] ],
    [ "pico:GP1", "$serialMonitor:TX", "", [] ],
    [ "pico:GND.1", "lcd1:VSS", "black", [ "v30", "h-120", "v-290", "h0" ] ],
    [ "pico:VBUS", "lcd1:VDD", "red", [ "v-40", "h0" ] ],
    [ "pico:GND.1", "lcd1:RW", "black", [ "v30", "h-120", "v-290", "h0" ] ],
    [ "pico:GP16", "lcd1:D7", "gray", [ "v-160", "h0" ] ],
    [ "pico:GP17", "lcd1:D6", "gold", [ "v-150", "h0" ] ],
    [ "pico:GP18", "lcd1:D5", "brown", [ "v-140", "h0" ] ],
    [ "pico:GP19", "lcd1:D4", "green", [ "v-130", "h0" ] ],
    [ "pico:GP20", "lcd1:E", "purple", [ "v-70", "h0" ] ],
    [ "pico:GP21", "lcd1:RS", "blue", [ "v-60", "h0" ] ]
  ]
}


#endif
// END.
