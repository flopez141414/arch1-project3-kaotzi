#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "shape.h"
#include <abCircle.h>


//each letter is approx screenWidth/6 x screenHeight/4
const AbRect rectp1 = {abRectGetBounds, abRectCheck, screenWidth/18,screenHeight/4};; //P leg
const AbRect rectn1 = {abRectGetBounds, abRectCheck, screenWidth/6,ScreenHeight/9};; //N base

void
abDrawPos(AbShape *shape, Vec2 *shapeCenter, u_int fg_color, u_int bg_color)
{
  u_char row, col;
  Region bounds;
  abShapeGetBounds(shape, shapeCenter, &bounds);
  lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1],
	      bounds.botRight.axes[0]-1, bounds.botRight.axes[1]-1);
  for (row = bounds.topLeft.axes[1]; row < bounds.botRight.axes[1]; row++) {
    for (col = bounds.topLeft.axes[0]; col < bounds.botRight.axes[0]; col++) {
      Vec2 pixelPos = {col, row};
      int color = abShapeCheck(shape, shapeCenter, &pixelPos) ?
	fg_color : bg_color;
      lcd_writeColor(color);
    }
  }
}



int
main()
{
  configureClocks();
  lcd_init();
  shapeInit();
  Vec2 p1Pos = {screenWidth/6,screenHeight/3};
  Vec2 p2Pos = { screenWidth*4/18, screenHeight/12 };
  Vec2 p3Pos = { 30, screenHeight/3 };
  Vec2 o1Pos = { 60, screenHeight/3 };
  Vec2 o2Pos = { 90, screenHeight/3 };
  Vec2 n1Pos = { screenWidth/2, screenHeight/3 };
  Vec2 n2Pos = { 120, screenHeight/3 };
  Vec2 n3Pos = { 120, screenHeight/3 };
  Vec2 g1Pos = { 120, screenHeight/3 };
  Vec2 g2Pos = { 120, screenHeight/3 };
  Vec2 g3Pos = { 120, screenHeight/3 };
  Vec2 g4Pos = { 120, screenHeight/3 };
  
  clearScreen(COLOR_BLUE);
  drawString5x7(15,10, "Testing my Pong", COLOR_GREEN, COLOR_BLUE);
  
  shapeInit();
  
  drawString5x7(5,150, "SW1up", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(25,140, "SW2-Strt", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(60,140, "SW3-bl", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(70,150, "SW4-dn", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(5,5,"Score: ", COLOR_WHITE, COLOR_BLUE);
  
  //testing TILT
  //shapeInit();
  abDrawPos((AbShape*)&rectp1, &p1Pos2, COLOR_YELLOW, COLOR_BLUE); // P leg
  abDrawPos((AbShape*)&rectn1, &n1Pos, COLOR_ORANGE, COLOR_BLUE);
  //shapeInit();
  abDrawPos((AbShape*)&circle8, &p2Pos, COLOR_RED, COLOR_BLUE);
  /*shapeInit();
  abDrawPos((AbShape*)&itile, &iPos, COLOR_YELLOW, COLOR_BLUE);
  shapeInit();
  abDrawPos((AbShape*)&ltile, &lPos, COLOR_WHITE, COLOR_BLUE);
  shapeInit();
  abDrawPos((AbShape*)&ttile, &t2Pos, COLOR_GREEN, COLOR_BLUE);
  */
}


