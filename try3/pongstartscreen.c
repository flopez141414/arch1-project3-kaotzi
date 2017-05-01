#include <msp430.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <shape.h>

/** Initializes everything, clears the screen, draws (taken from p2sw-demo.c)*/
void main()
{
  configureClocks();
  lcd_init();
  //p2sw_init(15);
  or_sr(0x8);			/* GIE (enable interrupts) */
  u_char width = screenWidth, height = screenHeight;
  
  shapeInit();
  Vec2 rectPos = screenCenter;
  clearScreen(COLOR_GREEN);
    /*shapeInit();
  
  abDrawPos((AbShape*)&rect10, &rectPos, COLOR_ORANGE, COLOR_BLUE);*/
  drawString5x7(10,10, "PONG", COLOR_GREEN, COLOR_BLUE);
  /*while (1) {
    u_int switches = p2sw_read(), i;
    char str[5];
    for (i = 0; i < 4; i++)
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;
    str[4] = 0;
    drawString5x7(20,20, str, COLOR_BLUE, COLOR_GREEN);
  } */
  drawString5x7(10,30, "Press SW1 to Start", COLOR_BLUE, COLOR_GREEN);
 drawString5x7(10,50, "Press SW2 to Quit", COLOR_BLUE, COLOR_GREEN);
 drawString5x7(10,70, "Press lower switch to stop game.", COLOR_BLUE, COLOR_GREEN);
 /* from shapedemo.c  
  shapeInit();
  Vec2 rectPos = screenCenter;

  clearScreen(COLOR_BLUE);
  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  shapeInit();
  
  abDrawPos((AbShape*)&rect10, &rectPos, COLOR_ORANGE, COLOR_BLUE);
 */
}
