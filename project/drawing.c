#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"

void
flappyBird(u_char x, u_char y, u_char w, u_char h, u_int bg){
  // base rectangle
  fillRectangle(x+14, y+5, 45, 45, bg);
  //body
  fillRectangle(x+20, y+10, 32, 32, COLOR_BLACK);
  fillRectangle(x+22, y+12, 28, 28, COLOR_YELLOW);
  // eye
  fillRectangle(x+38, y+10, 16, 16, COLOR_BLACK);
  fillRectangle(x+40, y+12, 12, 12, COLOR_WHITE);
  fillRectangle(x+45, y+16, 5, 5, COLOR_BLACK);
  // wing
  fillRectangle(x+16, y+20, 18, 15, COLOR_BLACK);
  fillRectangle(x+18, y+22, 14, 11, COLOR_YELLOW);
  // beak
  fillRectangle(x+40, y+26, 18, 13, COLOR_BLACK);
  fillRectangle(x+42, y+28, 14, 9, COLOR_ORANGE);
  fillRectangle(x+40, y+32, 18, 2, COLOR_BLACK);
  // more body
  fillRectangle(x+24, y+40, 24, 3, COLOR_YELLOW);
  fillRectangle(x+24, y+42, 24, 3, COLOR_BLACK);
}
