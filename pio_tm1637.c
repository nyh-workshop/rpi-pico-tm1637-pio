#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
// Our assembled program:
#include "tm1637.pio.h"

int main()
{
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Choose which PIO instance to use (there are two instances)
    PIO pio = pio0;

    // Our assembled program needs to be loaded into this PIO's instruction
    // memory. This SDK function will find a location (offset) in the
    // instruction memory where there is enough space for our program. We need
    // to remember this location!
    uint offset = pio_add_program(pio, &tm1637_program);

    // Find a free state machine on our chosen PIO (erroring if there are
    // none). Configure it to run our program, and start it, using the
    // helper function we included in our .pio file.
    tm1637_program_init(pio, 0, offset, 2,3);

    stdio_init_all();

    // Light up all segments:
    pio_sm_put_blocking(pio0, 0, 0xffc0448a);
    pio_sm_put_blocking(pio0, 0, 0xffc1448a);
    pio_sm_put_blocking(pio0, 0, 0xffc2448a);
    pio_sm_put_blocking(pio0, 0, 0xffc3448a);

    sleep_ms(3000);

    // Wait 3 seconds, then print 123 with max brightness:    
    pio_sm_put_blocking(pio0, 0, 0x3fc0448f);
    pio_sm_put_blocking(pio0, 0, 0x06c1448f);
    pio_sm_put_blocking(pio0, 0, 0x5bc2448f);
    pio_sm_put_blocking(pio0, 0, 0x4fc3448f);

    // just wait here and blink LED like usual...
    while(1) {
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }

    return 0;
}
