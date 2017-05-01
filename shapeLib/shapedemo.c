#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"

const AbRect rect10 = {abRectGetBounds, abRectCheck, 60,10};; //makes horizontal banner across most of the screen
const AbRect rect5 = {abRectGetBounds, abRectCheck, 5,25};; //makes horizontal banner across most of the screen

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

  clearScreen(COLOR_BLUE);
  drawString5x7(20,40, "Testing my Pong", COLOR_GREEN, COLOR_BLUE);
  shapeInit();
  
  abDrawPos((AbShape*)&rect10, &rectPos, COLOR_ORANGE, COLOR_BLUE);
  drawString5x7(20,75, "Pong is Tested", COLOR_BLACK, COLOR_ORANGE);
  shapeInit();
  
  abDrawPos((AbShape*)&rect5, &rectPos, COLOR_YELLOW, COLOR_BLUE);
  drawString5x7(5,150, "SW1up", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(18,150, "SW2-Strt", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(35,150, "SW3-bl", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(52,150, "SW4-dn", COLOR_BLACK, COLOR_BLUE);
  drawString5x7(5,5,"Score: ", COLOR_WHITE, COLOR_BLUE);
  
}


