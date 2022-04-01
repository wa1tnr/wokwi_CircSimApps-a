{
  "version": 1,
  "author": "PROVEN GOOD w LCD - wa1tnr / nis - Thu 31 Mar 16:47:19 UTC 2022",
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
    { "type": "wokwi-lcd2004", "id": "lcd1", "top": -340, "left": -150, "attrs": {} },
    { "type": "wokwi-led", "id": "led1", "top": -100, "left": 700, "attrs": { "color": "brown" } },
    { "type": "wokwi-led", "id": "led2", "top": -100, "left": 670, "attrs": { "color": "red" } },
    {
      "type": "wokwi-led",
      "id": "led3",
      "top": -100,
      "left": 640,
      "attrs": { "color": "orange" }
    },
    {
      "type": "wokwi-led",
      "id": "led4",
      "top": -100,
      "left": 610,
      "attrs": { "color": "yellow" }
    },
    { "type": "wokwi-led", "id": "led5", "top": -100, "left": 550, "attrs": { "color": "green" } },
    { "type": "wokwi-led", "id": "led6", "top": -100, "left": 520, "attrs": { "color": "blue" } },
    {
      "type": "wokwi-resistor",
      "id": "r1",
      "top": 30,
      "left": 679,
      "rotate": 90,
      "attrs": { "value": "1000" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r2",
      "top": 30,
      "left": 649,
      "rotate": 90,
      "attrs": { "value": "1000" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r3",
      "top": 30,
      "left": 619,
      "rotate": 90,
      "attrs": { "value": "1000" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r4",
      "top": 30,
      "left": 589,
      "rotate": 90,
      "attrs": { "value": "1000" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r5",
      "top": 30,
      "left": 529,
      "rotate": 90,
      "attrs": { "value": "1000" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r6",
      "top": 30,
      "left": 499,
      "rotate": 90,
      "attrs": { "value": "1000" }
    }
  ],
  "connections": [
    [ "pico:GP0", "$serialMonitor:RX", "", [] ],
    [ "pico:GP1", "$serialMonitor:TX", "", [] ],
    [ "pico:GND.1", "lcd1:VSS", "black", [ "v30", "h-120", "v-290", "h0" ] ],
    [ "pico:VBUS", "lcd1:VDD", "red", [ "v-40", "h0" ] ],
    [ "pico:GND.1", "lcd1:RW", "black", [ "v30", "h-120", "v-290", "h0" ] ],

    [ "led1:C", "r1:1", "brown", [ "h-5", "v10", "*", "h0" ] ],
    [ "led2:C", "r2:1", "red", [ "h-5", "v10", "*", "h0" ] ],
    [ "led3:C", "r3:1", "orange", [ "h-5", "v10", "*", "h0" ] ],
    [ "led4:C", "r4:1", "yellow", [ "h-5", "v10", "*", "h0" ] ],
    [ "led5:C", "r5:1", "green", [ "h-5", "v10", "*", "h0" ] ],
    [ "led6:C", "r6:1", "blue", [ "h-5", "v10", "*", "h0" ] ],
    [ "r1:2", "r2:2", "black", [ "h0" ] ],
    [ "r2:2", "r3:2", "black", [ "h0" ] ],
    [ "r3:2", "r4:2", "black", [ "h0" ] ],
    [ "r4:2", "r5:2", "black", [ "h0" ] ],
    [ "r5:2", "r6:2", "black", [ "h0" ] ],
    [ "r6:2", "pico:GND.1", "black", [ "v100", "h0" ] ],
    
    [ "pico:GP21", "led6:A", "blue", [ "v-20", "h-80", "v-15", "h0" ] ],
    [ "pico:GP20", "led5:A", "purple", [ "v-30", "h-70", "v-15", "h0" ] ],
    [ "pico:GP19", "led4:A", "green", [ "v-40", "h-70", "v-15", "h0" ] ],
    [ "pico:GP18", "led3:A", "brown", [ "v-50", "h-70", "v-15", "h0" ] ],
    [ "pico:GP17", "led2:A", "gold", [ "v-60", "h-70", "v-15", "h0" ] ],

    [ "pico:GP16", "led1:A", "gray", [ "v-70" ] ]
  ]
}
