/** \file lcddemo.c
 *  \brief A simple demo that draws a string and circle
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and the circle */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  drawString8x12(40,40,"world",COLOR_DKBLUE, COLOR_YELLOW);
  drawString11x16(70, 70, "PONG", COLOR_MAGENTA, COLOR_SPRING_GREEN);
  fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  
}
