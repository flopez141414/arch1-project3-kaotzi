#include <msp430.h>
#include "libTimer.h"
#include "led3.h"
#include "switches3.h"
#include "buzzer3.h"

void main(void) 
{  
  configureClocks();
  switch_init();
  led_init();
  buzzer_init();
  or_sr(0x18);  // CPU off, GIE on
} 
