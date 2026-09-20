#include <avr/io.h>
#include <util/delay.h>
#include "helper.h"

#define LED_PIN PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

int main(void) {
    // Set the LED_PIN as output
    LED_DDR |= (1 << LED_PIN);

    while (1) {
        // Toggle the LED state
        LED_PORT ^= (1 << LED_PIN);

        // Wait for 1 second (1000 milliseconds)
        _delay_ms(1000);
    }

    return 0;
}
