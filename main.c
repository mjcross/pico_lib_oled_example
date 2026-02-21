#include <stdio.h>
#include "pico/stdlib.h"
#include "lib_oled.h"

#ifndef DEBUG
#   ifdef DEBUG_BUILD
#       define DEBUG 1
#   else
#       define DEBUG 0
#   endif
#endif
#define debug_printf(...) do { stdio_filter_driver(&stdio_uart); if (DEBUG) fprintf(stderr, __VA_ARGS__); stdio_filter_driver(ptr_oled_stdio_driver); } while (0)

int main() {
    // We are enabling both the stdio driver for both the UART and our custom frame-buffer
    // and using stdio_filter_driver() to select between them 

    stdio_init_all();
    stdio_driver_t *ptr_oled_stdio_driver = oled_init();
    stdio_filter_driver(ptr_oled_stdio_driver);     // filter STDOUT to OLED only

    printf("Hello, World");

    debug_printf("debug message to UART only\n");

    // show a moving 'snake'
    int head_x = NUM_Y_PIXELS - 1, head_y = NUM_Y_PIXELS - 1, head_dx = 1, head_dy = 1;
    int tail_x = FONT_BYTES_PER_CODE + 1, tail_y = FONT_BYTES_PER_CODE + 1, tail_dx = 1, tail_dy = 1;
    while(true) {
        set_pixel(head_x, head_y);
        clear_pixel(tail_x, tail_y);
        if (head_x + head_dx < 0 || head_x + head_dx >= NUM_X_PIXELS) {
            head_dx = -head_dx;
        }
        head_x += head_dx;
        if (head_y + head_dy <= FONT_BYTES_PER_CODE || head_y + head_dy >= NUM_Y_PIXELS) {
            head_dy = -head_dy;
        }
        head_y += head_dy;
        if (tail_x + tail_dx < 0 || tail_x + tail_dx >= NUM_X_PIXELS) {
            tail_dx = -tail_dx;
        }
        tail_x += tail_dx;
        if (tail_y + tail_dy <= FONT_BYTES_PER_CODE || tail_y + tail_dy >= NUM_Y_PIXELS) {
            tail_dy = -tail_dy;
        }
        tail_y += tail_dy;
        sleep_ms(5);
    }
}