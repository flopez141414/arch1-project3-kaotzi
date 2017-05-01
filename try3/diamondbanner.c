#include "shape.h"


/** Check function required by AbShape
 *  abDiamondCheck returns true if the diamond includes the selected pixel
 */
int 
abDiamondCheck(const AbDiamond *diamond, const Vec2 *centerPos, const Vec2 *pixel)
{
  Vec2 relPos;
  int row, col, within = 0;
  int size = diamond->size;
  int halfSize = size/2;
  vec2Sub(&relPos, pixel, centerPos); /* vector from center to pixel */
  row = relPos.axes[1]; col = -relPos.axes[0]; /* note that col is negated */
  row = (row >= 0) ? row : -row;/* row = |row| */
  if (col >= 0) {		/* not to right of diamond */
    if (col <= halfSize) {	/* within rt half of diamond */
      within = row <= col;
    } else if (col <= size) {	/* within lft hald of diamond */
      within = row >= col;
    }
  }
  return within;
}
  
/** Check function required by AbShape
 *  abDiamondGetBounds computes a diamond's bounding box
 */
void 
abDiamondGetBounds(const AbDiamond *diamond, const Vec2 *centerPos, Region *bounds)
{
  int size = diamond->size, halfSize = size / 2;
  bounds->topLeft.axes[0] = centerPos->axes[0] - size;
  bounds->topLeft.axes[1] = centerPos->axes[1] - halfSize;
  bounds->botRight.axes[0] = centerPos->axes[0];
  bounds->botRight.axes[1] = centerPos->axes[1] + halfSize;
}


