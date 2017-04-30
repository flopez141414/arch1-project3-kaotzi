#include <msp430.h>
#include "led3.h"
#include "switches3.h"

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

void led_update(){
  if (switch_state_changed) {
    char ledFlags = 0; /* by default, no LEDs on */

    ledFlags |= switch_one_down ? LED_GREEN : 0;
    ledFlags |= switch_one_down ? 0 : 0;
    ledFlags |= switch_two_down ? LED_RED : 0;
    ledFlags |= switch_two_down ? 0 : 0;
    ledFlags |= switch_three_down ? LED_GREEN : 0;
    ledFlags |= switch_three_down ? 0 : 0;
    ledFlags |= switch_four_down ? LED_RED : 0;
    ledFlags |= switch_four_down ? 0 : 0;
    ledFlags |= switch_five_down ? LED_RED : 0;
    ledFlags |= switch_five_down ? LED_GREEN : 0;
    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
  }
  switch_state_changed = 0;
}

