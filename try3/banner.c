#include "shape.h"


/** Check function required by AbShape
 *  abbannerCheck returns true if the banner includes the selected pixel
 */
int 
abBannerCheck(const AbBanner *banner, const Vec2 *centerPos, const Vec2 *pixel)
{
  Vec2 relPos;
  int row, col, within = 0;
  int size = banner->size;
  int halfSize = size/2;
  vec2Sub(&relPos, pixel, centerPos); /* vector from center to pixel */
  row = relPos.axes[1]; col = -relPos.axes[0]; /* note that col is negated */
  row = (row >= 0) ? row : -row;/* row = |row| */
  if (row >= 0) {		/* not to right of banner */
    if (row <= halfSize) {	/* within rt half of banner */
      within = col <= row;
    } else if (row <= size) {	/* within lft hald of banner */
      within = row <= col;
    }
  }
  return within;
}
  
/** Check function required by AbShape
 *  abbannerGetBounds computes a banner's bounding box
 */
void 
abBannerGetBounds(const AbBanner *banner, const Vec2 *centerPos, Region *bounds)
{
  int size = banner->size, halfSize = size / 2;
  bounds->topLeft.axes[0] = centerPos->axes[0] - size;
  bounds->topLeft.axes[1] = centerPos->axes[1] - halfSize;
  bounds->botRight.axes[0] = centerPos->axes[0];
  bounds->botRight.axes[1] = centerPos->axes[1] + halfSize;
}


