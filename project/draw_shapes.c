#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "drawing.h"

circle cir1;
circle cir2;
u_int background_color = COLOR_BLUE;
int gameOver = 0;
int pause;
int cirPosX;
int cirPosY;
int cir2PosX;
int cir2PosY;

void
init_shapes(void)
{

  // vars for the circle
  cir1.cir_y = 60;
  cir1.cir_x = screenWidth / 2;
  cir1.old_cir_y = 60;
  cir1.old_cir_x = screenWidth / 2;
  cir1.r = 12;

  cir2.cir_y = 80;
  cir2.cir_x = 100;
  cir2.old_cir_y = 80;
  cir2.old_cir_x = 100;
  cir2.r = 6;
}


void
drawHorizontalLine(u_int x_start, u_int x_end, u_int y, u_int colorBGR)
{
  u_int length = x_end - x_start;
  // set the draw area from the start of the line to the end
  // height is 1 since its a line
  lcd_setArea(x_start, y, x_end, y);
  
  for (u_int i = 0; i < length; i++) {
    lcd_writeColor(colorBGR);
  }
  
}

void
drawLines(u_int x_coord, u_int y_coord, u_int x_point, u_int y_point, u_int color)
{
  // bottom
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord + y_point, color);
  // top
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord - y_point, color);
  // and the middle two
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord + x_point, color);
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord - x_point, color);
					  
}

void
draw_circle(int x, int y, int r, u_int color)
{
  int x_coord = x;
  int y_coord = y;
  // first point will be the very top;
  int x_point = 0;
  int y_point = r;
  int decision = 3 - (2 * r);

  drawLines(x_coord, y_coord, x_point, y_point, color);

  while (y_point >= x_point) {
    // move x over one
    x_point++;

    // check decision point
    if (decision > 0) {
      // move y down one
      y_point--;
      decision = decision + 4 * (x_point - y_point) + 10;
    } else {
      decision = decision + 4 * x_point + 6;
    }
    drawLines(x_coord, y_coord, x_point, y_point, color);
  }
}

void
moving_circle(void)
{
  static int x_vel = 5;
  static int y_vel = 3;
  
  u_int color = COLOR_GREEN;


  // draw at the new position
  draw_circle(cir1.cir_x, cir1.cir_y, cir1.r, color);
  
  
  // save current position
  cir1.old_cir_x = cir1.cir_x;
  cir1.old_cir_y = cir1.cir_y;

  // update position
  cir1.cir_x += x_vel;
  cir1.cir_y += y_vel;
  
  // check boundaries, see if rectangle has hit the edges
  if ( (cir1.cir_x + cir1.r) >= screenWidth || (cir1.cir_x - cir1.r) <= 0) {
    // top or bottom hit, reverse x velocity
    x_vel = x_vel * -1;
  }
  if ( ( cir1.cir_y - cir1.r ) <= 0 ||            // left boundary
       ( cir1.cir_y + cir1.r ) >= screenHeight ) { // right boundary
    // right or left hit, reverse y velocity
    y_vel = y_vel * -1;
  }
}

void
moving_circle2(void)
{
  static int x_vel = 3;
  static int y_vel = 1;
  
  u_int color = COLOR_RED;


  // draw at the new position
  draw_circle(cir2.cir_x, cir2.cir_y, cir2.r, color);
  
  
  // save current position
  cir2.old_cir_x = cir2.cir_x;
  cir2.old_cir_y = cir2.cir_y;
  
  // update position
  cir2.cir_x += x_vel;
  cir2.cir_y += y_vel;
  
  // check boundaries, see if rectangle has hit the edges
  if ( (cir2.cir_x + cir2.r) >= screenWidth || (cir2.cir_x - cir2.r) <= 0) {
    // top or bottom hit, reverse x velocity
    x_vel = x_vel * -1;
  }
  if ( ( cir2.cir_y - cir2.r ) <= 0 ||            // left boundary
       ( cir2.cir_y + cir2.r ) >= screenHeight ) { // right boundary
    // right or left hit, reverse y velocity
    y_vel = y_vel * -1;
  }
}


void
draw_moving_shapes(void)
{
  // blank out the old circle
  draw_circle(cir1.old_cir_x, cir1.old_cir_y, cir1.r, background_color);
  draw_circle(cir2.old_cir_x, cir2.old_cir_y, cir2.r, background_color);

  if(!pause){
    // draw and update the circle
    moving_circle();
    moving_circle2();
  }
}

void
moving_bird(rectangle *to_draw, int moveUp, int moveDown)
{
  static int y_vel = 5;

  int left_col = to_draw->rect_col - (to_draw->width);
  int top_row  = to_draw->rect_row - (to_draw->width);

  // draw rectangle at current position
  flappyBird(0, top_row, to_draw->width, to_draw->height, background_color);
  // save current position
  to_draw->old_rect_row = to_draw->rect_row;
  to_draw->old_rect_col = to_draw->rect_col;

  // update position
  to_draw->rect_row += y_vel;

  if(moveDown){
    y_vel = y_vel * 1;
  } 
  if(moveUp){
    y_vel = y_vel * -1;
  }
  // check boundaries, see if rectangle has hit the edges
  if ( (to_draw->rect_row+15 - to_draw->height / 2) <= 0 ||
       (to_draw->rect_row+35 + to_draw->height / 2) >= screenHeight) {
    gameOver = 1;
  }

}
