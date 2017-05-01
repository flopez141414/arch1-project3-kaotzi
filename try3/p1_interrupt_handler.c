#include <msp430.h>
#include "switches3.h"

// SWITCHES at P2.0 : P2.1 

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
     
    if (P2IFG & SWITCHES) {	          // did a button cause this interrupt? 
        P2IFG &= ~SWITCHES;		      // clear pending switches interrupts 
        switch_interrupt_handler();	
    }
       
} 