#ifndef switches3_included
#define switches3_included

#define SW1 BIT0		// switch1 is p2.0 
#define SW2 BIT1        // switch1 is p2.1 
#define SW3 BIT2        // switch1 is p2.2 
#define SW4 BIT3        // switch1 is p2.3 
#define SWITCHES (SW1 | SW2 | SW3 | SW4)
#define SW5 BIT3           //switch5 is p1.3
#define SWITCHLOW SW5

void switch_init();
void switch_interrupt_handler();

extern char switch_one_down, switch_two_down, switch_three_down, switch_four_down, switch_five_down, switch_state_changed; /* effectively boolean */

#endif // included
