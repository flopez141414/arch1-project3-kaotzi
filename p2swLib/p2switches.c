#include <msp430.h>

#include "p2switches.h"
#define GREEN_LED BIT6


static unsigned char switch_mask;
static unsigned char switches_last_reported;
static unsigned char switches_current;

static void
switch_update_interrupt_sense()
{
  switches_current = P2IN & switch_mask;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (switches_current);  /* if switch up, sense down */
  P2IES &= (switches_current | ~switch_mask); /* if switch down, sense up */
}

char 
switch_update_interrupt_sense_sw5()
{
  char p1val = P1IN;
  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (p1val & SWITCHLOW);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHLOW);	/* if switch down, sense up */
  return p1val;
}

void 
p2sw_init(unsigned char mask)
{
  switch_mask = mask;
  P2REN |= mask;    /* enables resistors for switches */
  P2IE = mask;      /* enable interrupts from switches */
  P2OUT |= mask;    /* pull-ups for switches */
  P2DIR &= ~mask;   /* set switches' bits for input */
  switch_update_interrupt_sense();

  P1REN |= SWITCHLOW;		/* enables resistors for switch5 */
  P1IE = SWITCHLOW;		/* enable interrupts from switch5 */
  P1OUT |= SWITCHLOW;		/* pull-ups for switch5 */
  P1DIR &= ~SWITCHLOW;		/* set switch5's bits for input */
  switch_update_interrupt_sense_sw5();
  switch5_interrupt_handler();

}

/* Returns a word where:
 * the high-order byte is the buttons that have changed,
 * the low-order byte is the current state of the buttons
 */
unsigned int 
p2sw_read() {
  unsigned int sw_changed = switches_current ^ switches_last_reported;
  switches_last_reported = switches_current;
  return switches_current | (sw_changed << 8);
}

void
switch5_interrupt_handler()
{
    char lowsw= switch_update_interrupt_sense_sw5();
    char   switch_five_down = (lowsw & SW5) ? 0 : 1; /* 0 when SW5 is up */
    if (switch_five_down)
     {  drawString5x7(20,40, "BUTTON 5 DETECTED!" , COLOR_RED, COLOR_BLUE);}
    else { drawString5x7(20,40, "                  " , COLOR_RED, COLOR_BLUE);}
}  

/* Switch on P2 (S1) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & switch_mask) {  /* did a button cause this interrupt? */
    P2IFG &= ~switch_mask;	/* clear pending sw interrupts */
    switch_update_interrupt_sense();
  }
}
/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHLOW) {	      /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHLOW;		      /* clear pending sw interrupts */
    switch_update_interrupt_sense_sw5();	/* single handler for all switches --bottom board*/
    switch5_interrupt_handler();

  }
}



