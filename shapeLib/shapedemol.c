#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"

AbLTile ltile = {abLTileGetBounds, abLTileCheck, 80}; //T tile

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
  Vec2 tPos = { 100, 70 };
  
  clearScreen(COLOR_BLUE);
  drawString5x7(5,15, "Testing my Pong", COLOR_GREEN, COLOR_BLUE);
  shapeInit();
  
  //line of text
  drawString5x7(5,150, "SW1up", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(25,140, "SW2-Strt", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(60,140, "SW3-bl", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(70,150, "SW4-dn", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(5,5,"Score: ", COLOR_WHITE, COLOR_BLUE);
  
  //testing TILT
  shapeInit();
  abDrawPos((AbShape*)&ltile, &tPos, COLOR_RED, COLOR_BLUE);
  /*shapeInit();
  shapeInit();
  abDrawPos((AbShape*)&ttile, &iPos, COLOR_YELLOW, COLOR_BLUE);
  shapeInit();
  abDrawPos((AbShape*)&itile, &t2Pos, COLOR_GREEN, COLOR_BLUE);
  */
}


