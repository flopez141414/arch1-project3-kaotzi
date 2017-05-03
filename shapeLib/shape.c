#include "shape.h"

const Vec2 screenSize = {screenWidth, screenHeight};
const Vec2 screenCenter= {screenWidth/2, screenHeight/2};
const Vec2 vec2Unit = {1,1}, vec2Zero = {0,0};;

void
shapeInit()
{
  /* no longer needed */
}

void 
abShapeGetBounds(const AbShape *s, const Vec2 *centerPos, Region *bounds)
{
  (*s->getBounds)(s, centerPos, bounds);
}

int
abShapeCheck(const AbShape *s, const Vec2 *centerPos, const Vec2 *pixelLoc)
{
  return (*s->check)(s, centerPos, pixelLoc);
}

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


