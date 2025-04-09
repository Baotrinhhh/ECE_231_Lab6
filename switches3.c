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
    
    DDRD = (1 << REDLED) | (1 << GREENLED);  // Set LED pins as outputs
    // Enable pull-ups for buttons
    PORTD = (1 << REDBUTTON) | (1 << GREENBUTTON) | (1 << BOTHLEDS); 

    while (1) {
        int pressedCount = 0;
        
        r_button = (PIND & (1 << REDBUTTON));     // 1 when not pressed, 0 when pressed
        g_button = (PIND & (1 << GREENBUTTON));     // 1 when not pressed, 0 when pressed
        both_leds = (PIND & (1 << BOTHLEDS));         // 1 when not pressed, 0 when pressed

        _delay_ms(MYDELAY);  // Debounce delay
        if (r_button == 0) pressedCount++;
        if (g_button == 0) pressedCount++;
        if (both_leds == 0) pressedCount++;


        if (pressedCount == 1) {
            if (both_leds == 0) {  // Only both-button pressed
                for (i = 0; i < 10; i++) {
                    PORTD ^= (1 << REDLED) | (1 << GREENLED);  // Toggle both LEDs
                    _delay_ms(MYDELAY);
                }
            } else if (r_button == 0) {  // Only red button pressed
                for (i = 0; i < 10; i++) {
                    PORTD ^= (1 << REDLED);
                    _delay_ms(100);
                }
            } else if (g_button == 0) {  // Only green button pressed
                for (i = 0; i < 10; i++) {
                    PORTD ^= (1 << GREENLED);
                    _delay_ms(100);
                }
            }
        } else {
            // If none or more than one button is pressed, turn off both LEDs.
            PORTD &= ~((1 << REDLED) | (1 << GREENLED));
        }
    }
    return 0;
}

/**** End of File *****/


