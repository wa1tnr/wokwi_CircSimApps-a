// Thu 31 Mar 00:29:05 UTC 2022

// GOOD ARM Forth seems to 'work' reasonably well but needs much work



// wa1tnr
// was: camelforth

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdio.h"     // rp2040_flash_ops.inc
#include <stdlib.h>         // rp2040_flash_ops.inc
#include "pico/stdlib.h"
#include "hardware/flash.h" // rp2040_flash_ops.inc

#define FLASH_TARGET_OFFSET_B 0x1E0000

const uint8_t *flash_target_contents_b = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET_B);

/// \tag::hello_uart[]

#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1
extern int _this_ws2812();

// extern void crufty_printer(void);
// extern void _pico_LED_init(void);
// extern void _pico_pip(void);
// extern int _pico_LED(void);

void _loop_delay_local(void) {
}

void blink_loop(void) {
    _loop_delay_local();
}

// forth.c
// 468:int forth_main() {

extern int forth_main();

int main(void) {
    sleep_ms(400);
    uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    stdio_init_all();

    sleep_ms(50);
#if 0
    printf( "\n  Hello - aa\n");
    sleep_ms(200);
    printf( "\n  Hello - bb\n");
    sleep_ms(200);
    printf( "\n  Hello - cc\n");
    sleep_ms(200);
#endif
#if 0

 // ///////////////////////   KEEP     ////////////////////
 // ///////////////////////   KEEP     ////////////////////
 // ///////////////////////   KEEP     ////////////////////

    uart_puts(UART_ID, "\r\n   camelforth-rp2040-b-MS-U r0.1.8-pre-alpha\r\n\r\n");
    printf(              "\n   camelforth-rp2040-b-MS-U r0.1.8-pre-alpha\n\n");

    uart_puts(UART_ID, "        +fl_sizing +alltargets +itsybitsy +blinkwait +feather\r\n");
    printf(            "        +fl_sizing +alltargets +itsybitsy +blinkwait +feather\n");

    uart_puts(UART_ID, "        +no_emit +auto_load +rewind +flaccept +erase +flwrite\r\n");
    printf(            "        +no_emit +auto_load +rewind +flaccept +erase +flwrite\n");

    uart_puts(UART_ID, "        +reflash +dump +blink +UART +USB\r\n");
    printf(            "        +reflash +dump +blink +UART +USB\n");

 // ///////////////////////   KEEP     ////////////////////
 // ///////////////////////   KEEP     ////////////////////
 // ///////////////////////   KEEP     ////////////////////

#endif

   // crufty_printer(); // examine ram with this nonsense function

   // int result = _this_ws2812(); // do a NEOPIX thing here

   // printf( "   NEOPIX activity here\n\n");

// kludge: bug with flash access in no_flash binary compile (see CMakeLists.txt for the toggle)
// #undef NO_FLASH_CMAKE
#ifdef NO_FLASH_CMAKE
    flash_range_erase(FLASH_TARGET_OFFSET_B, FLASH_SECTOR_SIZE);
    printf("   flash_range_erase is required (and completed).\n\n");
#endif

#define WANT_FORCED_ERASE_QTPY
#undef WANT_FORCED_ERASE_QTPY
#ifdef WANT_FORCED_ERASE_QTPY
    flash_range_erase(FLASH_TARGET_OFFSET_B, FLASH_SECTOR_SIZE);
    printf("   flash_range_erase is required (and completed).\n\n");
#endif // #ifdef WANT_FORCED_ERASE_QTPY

    uint32_t start_address = (uint32_t) XIP_BASE + (uint32_t) FLASH_TARGET_OFFSET_B ;
    // printf("%s", "\n\n       start_address: ");
    // printf("%8X", start_address);

    // printf("%s", "\n");
    // extern int forth_main();
    // printf( "\nwokwi port 30 March 2022\n");
    int result_ing = forth_main();
    
    // never executes:

    putchar('_');
    putchar('_');
    putchar('?');
    putchar('_');
    putchar('_');
    // while(1) {
        // interpreter(); // camelforth
    // }
}
// END.

