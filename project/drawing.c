#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"

void
flappyBird(char x, char y){

  fillRectangle(14, y-10, 48, 150, COLOR_BLUE);
  fillRectangle(20, y+20, 32, 32, COLOR_BLACK);
  fillRectangle(22, y+22, 28, 28, COLOR_YELLOW);

  fillRectangle(38, y+20, 16, 16, COLOR_BLACK);
  fillRectangle(40, y+22, 12, 12, COLOR_WHITE);
  fillRectangle(45, y+26, 5, 5, COLOR_BLACK);

  fillRectangle(16, y+30, 18, 15, COLOR_BLACK);
  fillRectangle(18, y+32, 14, 11, COLOR_YELLOW);
  
  fillRectangle(40, y+36, 18, 13, COLOR_BLACK);
  fillRectangle(42, y+38, 14, 9, COLOR_ORANGE);
  fillRectangle(40, y+42, 18, 2, COLOR_BLACK);

  fillRectangle(24, y+50, 24, 3, COLOR_YELLOW);
  fillRectangle(24, y+52, 24, 3, COLOR_BLACK);
}
