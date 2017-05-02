#include "shape.h"


/** Check function required by AbShape
 *  abTTileCheck returns true if the tile includes the selected pixel
 *  --center is the middle of the rt side.
 */
int 
abTTileCheck(const TTile *tile, const Vec2 *centerPos, const Vec2 *pixel)
{
  Vec2 relPos;
  int row, col, within = 0;
  int size = tile->size;
  int tenthSize = size/10;
  int fifthSize = size/5;
  vec2Sub(&relPos, pixel, centerPos); /* vector from center to pixel */
  row = relPos.axes[1]; col = -relPos.axes[0]; /* note that col is negated */
  if ((col >= 0)||(-halfSize<= row <= halfSize)) {		/* not to right of tile or outside upper/lower bounds */
    if ((col <= fifthSize)||((4*fifthSize)<col<=size)) {	/* within first or last fifth of tile */
      within = 1;
     } else if ((fifthSize< col <= (2*fifthSize))||((3*fifthSize)< col <= (4*fifthSize))) {	/* within second or fourth fifth of tile */
        within =((row >(3*tenthSize))||(row <= tenthSize))  /*not in second fifth of tile ht*/
        }else if ((2*fifthSize)<row<=(3*fifthSize)){  /* center fifth of tile*/
           within=((row >(3*tenthSize))||(row <=(-3*tenthSize)));
         }
     }
  return within;
}
  
/** Check function required by AbShape
 *  abTTileGetBounds computes a tile's bounding box
 */
void 
abTTileGetBounds(const AbTTile *tile, const Vec2 *centerPos, Region *bounds)
{
  int size = tile->size, halfSize = size / 2;
  bounds->topLeft.axes[0] = centerPos->axes[0] - Size;
  bounds->topLeft.axes[1] = centerPos->axes[1] - halfSize;
  bounds->botRight.axes[0] = centerPos->axes[0];
  bounds->botRight.axes[1] = centerPos->axes[1] + halfSize;
}

/** Check function required by AbShape
 *  abITileCheck returns true if the tile includes the selected pixel
 *  --center is the middle of the rt side.
 */
int 
abITileCheck(const ITile *tile, const Vec2 *centerPos, const Vec2 *pixel)
{
  Vec2 relPos;
  int row, col, within = 0;
  int size = tile->size;
  int tenthSize = size/10;
  int fifthSize = size/5;
  vec2Sub(&relPos, pixel, centerPos); /* vector from center to pixel */
  row = relPos.axes[1]; col = -relPos.axes[0]; /* note that col is negated */
  row = (row >= 0) ? row : -row;/* row = |row| -- I is semetric side to side*/
   if ((col >= 0)||(-halfSize<= row <= halfSize)) {		/* not to right of tile or outside upper/lower bounds */
    if ((col <= fifthSize)||((4*fifthSize)<col<=size)) {	/* within first or last fifth of tile */
      within = 1;
     } else if ((fifthSize< col <= (2*fifthSize))||((3*fifthSize)< col <= (4*fifthSize))) {	/* within second or fourth fifth of tile */
        within =(tenthSize< row <= (3*tenthSize))  /*not in second fifth of tile ht*/
        }else if ((2*fifthSize)<row<=(3*fifthSize)){  /* center fifth of tile*/
           within=(row >(3*tenthSize));
         }
     }
  return within;
}
  
/** Check function required by AbShape
 *  abITileGetBounds computes a tile's bounding box
 */
void 
abITileGetBounds(const AbITile *tile, const Vec2 *centerPos, Region *bounds)
{
  int size = tile->size, halfSize = size / 2;
  bounds->topLeft.axes[0] = centerPos->axes[0] - Size;
  bounds->topLeft.axes[1] = centerPos->axes[1] - halfSize;
  bounds->botRight.axes[0] = centerPos->axes[0];
  bounds->botRight.axes[1] = centerPos->axes[1] + halfSize;
}

/** Check function required by AbShape
 *  abLTileCheck returns true if the tile includes the selected pixel
 *  --center is the middle of the rt side.
 */
int 
abLTileCheck(const LTile *tile, const Vec2 *centerPos, const Vec2 *pixel)
{
  Vec2 relPos;
  int row, col, within = 0;
  int size = tile->size;
  int tenthSize = size/10;
  int fifthSize = size/5;
  vec2Sub(&relPos, pixel, centerPos); /* vector from center to pixel */
  row = relPos.axes[1]; col = -relPos.axes[0]; /* note that col is negated */
  if ((col >= 0)||(-halfSize<= row <= halfSize)) {		/* not to right of tile or outside upper/lower bounds */
    if ((col <= fifthSize)||((4*fifthSize)<col<=size)) {	/* within first or last fifth of tile */
      within = 1;
     } else if (fifthSize< col <= (3*fifthSize)) {	/* within second or third fifth of tile */
        within =((row >(-tenthSize))||(row <= (-3*tenthSize)))  /*not in fourth fifth of tile ht*/
        }else if ((3*fifthSize)<col<=(4*fifthSize)){  /* fourth fifth of tile horiz*/
           within=((row >(3*tenthSize))||(row <=(-3*tenthSize)));
         }
     }
  return within;
}
  
/** Check function required by AbShape
 *  abLTileGetBounds computes a tile's bounding box
 */
void 
abLTileGetBounds(const AbLTile *tile, const Vec2 *centerPos, Region *bounds)
{
  int size = tile->size, halfSize = size / 2;
  bounds->topLeft.axes[0] = centerPos->axes[0] - Size;
  bounds->topLeft.axes[1] = centerPos->axes[1] - halfSize;
  bounds->botRight.axes[0] = centerPos->axes[0];
  bounds->botRight.axes[1] = centerPos->axes[1] + halfSize;
}
