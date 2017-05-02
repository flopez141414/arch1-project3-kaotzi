#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"

const AbRect rect10 = {abRectGetBounds, abRectCheck, 60,10};; //makes horizontal banner across most of the screen
const AbRect rect5 = {abRectGetBounds, abRectCheck, 4,16};; //makes horizontal banner across most of the screen
AbTTile ttile = {abTTileGetBounds, abTTileCheck, 10}; //T tile
AbITile itile = {abITileGetBounds, abITileCheck, 10}; //I tile
AbLTile ltile = {abLTileGetBounds, abLTileCheck, 10}; //L tile

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
  Vec2 rectPos = screenCenter;
  Vec2 rectPos2 = { 20, 50 };
  Vec2 tPos = { 3, 80 };
  Vec2 iPos = { 30, 80 };
  Vec2 lPos = { 55, 80 };
  Vec2 t2Pos = { 80, 50 };
    
  clearScreen(COLOR_BLUE);
  drawString5x7(20,40, "Testing my Pong", COLOR_GREEN, COLOR_BLUE);
  
  drawString5x7(20,75, "Pong is Tested", COLOR_BLACK, COLOR_ORANGE);
  shapeInit();
  
  abDrawPos((AbShape*)&rect5, &rectPos2, COLOR_YELLOW, COLOR_BLUE); // over to the left, covering part of first line of text
  drawString5x7(5,150, "SW1up", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(25,140, "SW2-Strt", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(60,140, "SW3-bl", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(70,150, "SW4-dn", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(5,5,"Score: ", COLOR_WHITE, COLOR_BLUE);
  
  //testing TILT
  shapeInit();
  abDrawPos((AbShape*)&rect10, &rectPos, COLOR_ORANGE, COLOR_BLUE);
  shapeInit();
  abDrawPos((AbShape*)&ttile, &tPos, COLOR_ORANGE, COLOR_BLUE);
  shapeInit();
  abDrawPos((AbShape*)&itile, &tPos, COLOR_ORANGE, COLOR_BLUE);
  shapeInit();
  abDrawPos((AbShape*)&ltile, &tPos, COLOR_ORANGE, COLOR_BLUE);
  shapeInit();
  abDrawPos((AbShape*)&ttile, &t2Pos, COLOR_ORANGE, COLOR_BLUE);
  
}


