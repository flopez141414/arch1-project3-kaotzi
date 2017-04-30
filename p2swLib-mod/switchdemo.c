#include <msp430.h>
#include <sr.h>
#include "p2switches.h"
#define RED_LED BIT0
#define GREEN_LED BIT6

int
main()
{
  p2sw_init(1);
/*  or_sr(0x8);			 GIE (enable interrupts) */
p1sw_init();
  or_sr(0x8);			/* GIE (enable interrupts) */
  
  P1DIR |= RED_LED;
  P2DIR |= GREEN_LED;
  for(;;) {
    P1OUT = (1 & p2sw_read());
  }
  
  for(;;) {
    P2OUT = (1 & p1sw_read());
  }
}

