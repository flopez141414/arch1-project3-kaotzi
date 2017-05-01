/** started w/ p2sw-demo.c  *** adapted to show simple call to pong start screen **/
/**from buttonCode.c (working 5 button model) **/
#include <msp430.h>
#include "libTimer.h"
#include "led3.h"
#include "switches3.h"
#include "buzzer3.h"
#include "pongstartscreen.h"

void main(void) 
{  
  configureClocks();
  switch_init();
  led_init();   //enables all 5 switches
  buzzer_init();
  lcd_init(); 
  pongstartscreen();
  enableWDTinterupts();
  or_sr(0x18);  // CPU off, GIE on
} 
/** ex. from  p2sw-demo.c (modified)
#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <switches3.h>
#include <buzzer3.h>

/** Initializes everything, clears the screen, draws 
void main()
{
  configureClocks();
  lcd_init();
  p2sw_init(15);
  or_sr(0x8);			/* GIE (enable interrupts) 
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(10,10, "switches:", COLOR_GREEN, COLOR_BLUE);
  while (1) {
    u_int switches = p2sw_read(), i;
    char str[5];
    for (i = 0; i < 4; i++)
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;
    str[4] = 0;
    drawString5x7(20,20, str, COLOR_GREEN, COLOR_BLUE);
  } 
}
*/
