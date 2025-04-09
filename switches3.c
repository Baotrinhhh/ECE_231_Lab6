/* switches3.c 
 * ----------------------------------------------------------------------------
 * File: switches3.c
 * Description:
 *   This code controls two LEDs (red and green) on an Arduino Uno board based on
 *   three momentary push-button switches.
 *
 *   Functionality:
 *     • When the red button (input PD3) is pressed, the red LED (output PD6)
 *       blinks at a 5 Hz rate (on-off cycles at 100 msec intervals).
 *     • When the green button (input PD4) is pressed, the green LED (output PD7)
 *       blinks at a 5 Hz rate (on-off cycles at 100 msec intervals).
 *     • When the both-LEDs button (input PD5) is pressed (and only that button
 *       is active), both LEDs blink simultaneously at a 5 Hz rate.
 *     • When no buttons are pressed or when more than one button is pressed simultaneously,
 *       the code turns off both LEDs.
 *
 *   Note:
 *     • This implementation meets the requirements for the ECE-231 Lab Assignment 8.1.
 *     • It uses #define macros to set up pin assignments for easier code management.
 *
 * Author: Bao Trinh
 * Date: 04/09/25
 * ----------------------------------------------------------------------------
 */

 #include <avr/io.h>
 #include <util/delay.h>
 
 // Define button pins: Active low (1 when not pressed, 0 when pressed)
 #define REDBUTTON   PD3   // Red button connected to Arduino Uno digital pin 3
 #define GREENBUTTON PD4   // Green button connected to Arduino Uno digital pin 4
 #define BOTHLEDS    PD5   // Both-LEDs button (third switch) connected to digital pin 5
 
 // Define LED pins
 #define REDLED      PD6   // Red LED connected to Arduino Uno digital pin 6
 #define GREENLED    PD7   // Green LED connected to Arduino Uno digital pin 7
 
 // Define delay period in milliseconds (100 ms for half cycle, yielding 5 Hz blink rate)
 #define MYDELAY     100   // Delay duration in milliseconds
 
 int main(void) {
     // Variable declarations:
     // r_button, g_button, both_leds are used to store the state of the buttons.
     unsigned char r_button, g_button, both_leds;
     int i;  // Loop counter for LED toggling loops
     
     // Configure LED pins as outputs.
     // DDRD: Data Direction Register for port D.
     DDRD = (1 << REDLED) | (1 << GREENLED);  
     
     // Enable internal pull-up resistors for the button input pins.
     // By writing a logic high to the PORT register for these pins, the internal pull-ups get enabled.
     PORTD = (1 << REDBUTTON) | (1 << GREENBUTTON) | (1 << BOTHLEDS); 
 
     // Main program loop: continuously checks button statuses and controls LED blinking.
     while (1) {
         int pressedCount = 0;  // Count of buttons currently pressed
         
         // Read the current state of the buttons.
         // Logic: 1 indicates button not pressed, 0 indicates button pressed.
         r_button = (PIND & (1 << REDBUTTON));
         g_button = (PIND & (1 << GREENBUTTON));
         both_leds = (PIND & (1 << BOTHLEDS));
 
         _delay_ms(MYDELAY);  // Debounce delay to allow signal settling
         
         // Increment pressedCount for each button that is detected as pressed (logic 0).
         if (r_button == 0) pressedCount++;
         if (g_button == 0) pressedCount++;
         if (both_leds == 0) pressedCount++;
 
         // Execute LED blinking only if exactly one button is pressed.
         if (pressedCount == 1) {
             // Case 1: Only the both-LEDs button is pressed: blink both red and green LEDs.
             if (both_leds == 0) {
                 for (i = 0; i < 10; i++) {
                     // Toggle both LED states (on/off) to create blinking effect.
                     PORTD ^= (1 << REDLED) | (1 << GREENLED);
                     _delay_ms(MYDELAY);
                 }
             }
             // Case 2: Only the red button is pressed: blink red LED.
             else if (r_button == 0) {
                 for (i = 0; i < 10; i++) {
                     // Toggle red LED only.
                     PORTD ^= (1 << REDLED);
                     _delay_ms(100);
                 }
             }
             // Case 3: Only the green button is pressed: blink green LED.
             else if (g_button == 0) {
                 for (i = 0; i < 10; i++) {
                     // Toggle green LED only.
                     PORTD ^= (1 << GREENLED);
                     _delay_ms(100);
                 }
             }
         } else {
             // If no button or more than one button is pressed,
             // ensure that both LEDs remain off.
             PORTD &= ~((1 << REDLED) | (1 << GREENLED));
         }
     }
     return 0;  // This line is never reached due to infinite loop.
 }
 
 /**** End of File *****/
 