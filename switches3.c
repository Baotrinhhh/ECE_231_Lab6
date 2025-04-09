/* switches3.c This code turns on LEDs when  momentary pushbutton  
switches are pressed. Input pins on PD3 and PD4. LEDS on PD6 on PD7
This is an updated version of switches2.c D. McLaughlin 2/21/22 
and uses #define macros and other variables to clean up code
A video showing code & the wiring of the circuit is here: 
https://youtu.be/SJE_TObvd-Q?feature=shared
D. McLaughlin 4/13/24 */

#include <avr/io.h>
#include <util/delay.h>
#define REDBUTTON PD3   // Arduino Uno pin 3
#define GREENBUTTON PD4 // Arduino Uno pin 4
#define REDLED PD6      // Arduino Uno pin 6
#define GREENLED PD7    // Arduino Uno pin 7
#define BOTHLEDS PD5    // Arduino Uno pin 5 
#define MYDELAY 100     // This will be the delay in msec

int main(void) {
    unsigned char r_button, g_button, both_leds;
    int i;

    DDRD = (1<<REDLED) | (1<<GREENLED);  // Set REDLED and GREENLED as outputs
    PORTD = (1<<REDBUTTON) | (1<<GREENBUTTON) | (1<<BOTHLEDS); // Enable pull-ups

    while(1) {
        r_button = (PIND & (1<<REDBUTTON));     // 1 when not pressed, 0 when pressed
        g_button = (PIND & (1<<GREENBUTTON));   // 1 when not pressed, 0 when pressed
        both_leds = (PIND & (1<<BOTHLEDS));     // 1 when not pressed, 0 when pressed

        if (r_button + g_button + both_leds >= 2){
            if (both_leds == 0) {  // If both buttons are pressed
                for (i = 0; i < 10; i++) {  // Blink both LEDs 10 times
                    PORTD ^= (1<<REDLED) | (1<<GREENLED);  // Toggle both LEDs
                    _delay_ms(MYDELAY);                     // Delay for MYDELAY
                }
            } else {
                PORTD &= ~((1<<REDLED) | (1<<GREENLED)); // Turn off both LEDs
            }

            if (r_button == 0) {  // If red button is pressed
                // Blink red LED at 5Hz (200ms period for each blink)
                for (i = 0; i < 10; i++) {  // Blink 10 times (adjust for desired duration)
                    PORTD ^= (1<<REDLED);  // Toggle the REDLED
                    _delay_ms(100);        // Delay for 100ms (half of 200ms period)
                }
            } else {
                PORTD &= ~(1<<REDLED); // Turn off REDLED if button is not pressed
            }

            if (g_button == 0) {   // If green button is pressed
                // Blink green LED at 5Hz (200ms period for each blink)
                for (i = 0; i < 10; i++) {  // Blink 10 times (adjust for desired duration)
                    PORTD ^= (1<<GREENLED);  // Toggle the GREENLED
                    _delay_ms(100);          // Delay for 100ms (half of 200ms period)
                }
            } else {
                PORTD &= ~(1<<GREENLED); // Turn off GREENLED
            }
        } else {
            PORTD &= ~((1<<REDLED) | (1<<GREENLED)); // Turn off both LEDs
        }
    }
}


/**** End of File *****/


