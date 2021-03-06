#ifndef switches_included
#define switches_included

#define SW1 BIT0		// switch1 is p2.0 
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

void switch_init();
void switch_interrupt_handler();

extern char switch_one_down, switch_two_down, switch_three_down, switch_four_down, switch_state_changed; /* effectively boolean */

#endif // included
