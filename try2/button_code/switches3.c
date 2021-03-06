#include <msp430.h>
#include "switches3.h"
#include "led3.h"
#include "buzzer3.h"

char switch_one_down, switch_two_down;
char switch_three_down, switch_four_down, switch_state_changed; /* effectively boolean */
char switch_five_down;


static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}
static char 
switch_update_interrupt_sense_sw5()
{
  char p1val = P1IN;
  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (p1val & SWITCHLOW);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHLOW);	/* if switch down, sense up */
  return p1val;
}
void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches 1-4 */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  P1REN |= SWITCHLOW;		/* enables resistors for switch5 */
  P1IE = SWITCHLOW;		/* enable interrupts from switch5 */
  P1OUT |= SWITCHLOW;		/* pull-ups for switch5 */
  P1DIR &= ~SWITCHLOW;		/* set switch5's bits for input */
  switch_update_interrupt_sense_sw5();
  switch_interrupt_handler();	/* to initially read the switches */
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switch_one_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  switch_two_down = (p2val & SW2) ? 0 : 1; /* 0 when SW2 is up */
  switch_three_down = (p2val & SW3) ? 0 : 1; /* 0 when SW3 is up */
  switch_four_down = (p2val & SW4) ? 0 : 1; /* 0 when SW4 is up */
  char p1val = switch_update_interrupt_sense_sw5();
  switch_five_down = (p1val & SW5) ? 0 : 1; /* 0 when SW5 is up */
  
  switch_state_changed = 1;
  led_update();
  buzzer_update();
}
