#include <msp430.h>
#include "p2switches.h"

static unsigned char switch_mask;
static unsigned char switches_last_reported;
static unsigned char switches_current;
static unsigned char switch_mask5;
static unsigned char switches_last_reported_sw5;
static unsigned char switches_current_sw5;

static void
switch_update_interrupt_sense()
{
  switches_current = P2IN & switch_mask;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (switches_current);  /* if switch up, sense down */
  P2IES &= (switches_current | ~switch_mask); /* if switch down, sense up */
}

static void
switch_update_interrupt_sense_sw5()
{
  switches_current_sw5 = P1IN & switch_mask5;
  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (switches_current);  /* if switch up, sense down */
  P1IES &= (switches_current | ~switch_mask5); /* if switch down, sense up */
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
}

void
p1sw_init()
{
  switch_mask5 = 3;
  P1REN |= 3;    /* enables resistors for switches */
  P1IE = 3;      /* enable interrupts from switches */
  P1OUT |= 3;    /* pull-ups for switches */
  P1DIR &= ~3;   /* set switches' bits for input */
  switch_update_interrupt_sense_sw5();
}
/* Returns a word where:
 * the high-order byte is the buttons that have changed,
 * the low-order byte is the current state of the buttons
 */
unsigned int 
p2sw_read() {  /* Reads upper four switches from port2 */
  unsigned int sw_changed = switches_current ^ switches_last_reported;
  switches_last_reported = switches_current;
  return switches_current | (sw_changed << 8);
}
unsigned int
p1sw_read() {  /* Reads lower switch from P1.3 */
  unsigned int sw_changed = switches_current_sw5 ^ switches_last_reported_sw5;
  switches_last_reported_sw5 = switches_current_sw5;
  return switches_current_sw5 | (sw_changed << 8);
}

/* Switch on P2 (S1) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & switch_mask) {  /* did a button cause this interrupt? */
    P2IFG &= ~switch_mask;	/* clear pending sw interrupts */
    switch_update_interrupt_sense();
  }
}
/* Switch on P1.3 (S5) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & switch_mask5) {  /* did a button cause this interrupt? */
    P1IFG &= ~switch_mask5;	/* clear pending sw interrupts */
    switch_update_interrupt_sense_sw5();
  }
}
