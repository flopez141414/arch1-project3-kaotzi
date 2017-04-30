#include <msp430.h>
#include "libTimer.h"
#include "buzzer3.h"
#include "switches3.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */

    buzzer_update();	/* start buzzing!!! */
}

void buzzer_update()
{
  short buzCycle = 0 ; /* silence please */
  if (switch_one_down)
    { buzCycle = 450; }
  if (switch_two_down)
    { buzCycle = 750; }
  if (switch_three_down)
    { buzCycle = 1000; }
  if (switch_four_down)
    { buzCycle = 600; }
  if (switch_five_down)
    { buzCycle = 1200; }
  CCR0 = buzCycle; 
  CCR1 = buzCycle >> 1;		/* one half cycle */
}


    
    
  

