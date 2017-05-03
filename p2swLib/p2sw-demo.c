/** \file lcddemo.c
 *  \brief A simple demo that draws a string and circle -- or not
 */

#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include <shape.h>
#include "p2sw-demo.h"

int covery;
int  paddley;
int gamex;

AbRect paddle = {abRectGetBounds, abRectCheck, {screenWidth/5, 5}};
AbDiamond dball = {abDiamondGetBounds, abDiamondCheck, 15};



/** Initializes everything, clears the screen, draws "hello" and the circle */
void main()
{
   
    
  configureClocks();
  lcd_init();
  p2sw_init(15);
  or_sr(0x8);			/* GIE (enable interrupts) */
  u_char width = screenWidth, height = screenHeight;
  covery=0;
  paddley=screenHeight-3;
  gamex=screenWidth/2;
  clearScreen(COLOR_BLUE);

   Vec2 padPos = { screenWidth/2, screenHeight-3 };
   Vec2 balPos =  screenCenter;
  abDrawPos((AbShape*)&paddle, &padPos, COLOR_BLACK, COLOR_BLUE);
  abDrawPos((AbShape*)&dball, &balPos, COLOR_BLACK, COLOR_BLUE);
  
  drawString5x7(10,10, "speed:", COLOR_GREEN, COLOR_BLUE);
  while (1) {
    u_int switches = p2sw_read(), i;
    move_up(i);
    char str[5];
    for (i = 0; i < 4; i++)
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;
    str[4] = 0;
    drawString5x7(20,20, str, COLOR_GREEN, COLOR_BLUE);
   
  }


}


void move_bar (int dist)
{
  if ((paddley - dist) > (screenHeight+7)){
      covery=paddley;
      paddley= paddley-dist;
      Vec2 padPosUp={gamex, paddley};
      Vec2 covPosUp={gamex, covery};
      abDrawPos((AbShape*)&paddle, &padPosUp , COLOR_BLACK, COLOR_BLUE);
      abDrawPos((AbShape*)&paddle, &covPosUp , COLOR_BLUE, COLOR_BLUE);
   } else{
      covery=paddley;
      paddley= screenHeight-3;
      Vec2 padPosDn={gamex, paddley};
      Vec2 covPosDn={gamex, covery};
      abDrawPos((AbShape*)&paddle, &padPosDn , COLOR_BLACK, COLOR_BLUE);
      abDrawPos((AbShape*)&paddle, &covPosDn , COLOR_BLUE, COLOR_BLUE);
       }
}