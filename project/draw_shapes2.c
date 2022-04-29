#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "drawing.h"

rectangle rect1;
circle cir1;
u_int background_color = COLOR_BLUE;

void
init_shapes(void)
{
   // vars for the rectangle
  rect1.rect_row = 40;
  rect1.rect_col = screenWidth / 2;
  rect1.old_rect_row = 40;
  rect1.old_rect_col = screenWidth / 2;
  rect1.height = 10;
  rect1.width  = 60;
  
  // vars for the circle
  cir1.cir_y = 60;
  cir1.cir_x = screenWidth / 2;
  cir1.old_cir_y = 60;
  cir1.old_cir_x = screenWidth / 2;
  cir1.r = 10;
}

void
drawHorizontalLine(u_int x_start, u_int x_end, u_int y, u_int colorBGR){
  u_int length = x_end - x_start;
  // set the draw area from the start of the line to the end
  // height is 1 since its a line
  lcd_setArea(x_start, y, x_end, y);
  for(u_int i = 0; i < length; i++){
    lcd_writeColor(colorBGR);
  }
}


void
drawLines(u_int x_coord, u_int y_coord, u_int x_point, u_int y_point, u_int color){
  // bottom
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord + y_point, color);
  // top
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord - y_point, color);
  // and the middle two
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord + y_point, color);
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord - y_point, color);
}


void
draw_circle(int x, int y, int r, u_int color){
  int x_coord = x;
  int y_coord = y;
  // first point will be the very top
  int x_point = 0;
  int y_point = r;
  int decision = (2 * r);

  drawLines(x_coord, y_coord, x_point, y_point, COLOR_GREEN);

  while(y_point >= x_point){
    // move x over one
    x_point++;
    // check decision point
    if(decision > 0){
      y_point--;
      decision = decision + 4 * (x_point - y_point) + 10;
    }
    else{
      decision = decision + 4 * x_point + 6;
    }
    drawLines(x_coord, y_coord, x_point, y_point, COLOR_GREEN);
  }
}

void
draw_moving_shapes(void)
{
  //draw_circle(cir1.old_cir_x, cir1.old_cir_y, cir1.r, COLOR_GREEN);
  // moving_circle();

  int left_col = rect1.old_rect_col - (rect1.width / 2);
  int top_row  = rect1.old_rect_row - (rect1.height / 2);

  // blank out the old rectangle
  // fillRectangle(left_col, top_row, rect1.width, rect1.height, background_color);

  // blank out the old circle
  draw_circle(cir1.old_cir_x, cir1.old_cir_y, cir1.r, background_color);

  // draw and update the rectangle
  // moving_rectangle(&rect1);
  
  // draw and update the circle
  moving_circle();

}


void
draw_rectangle(void)
{
  int left_col = rect1.rect_col - (rect1.width / 2);
  int top_row  = rect1.rect_row - (rect1.height / 2);

  unsigned int blue = 16, green = 0, red = 31;
  unsigned int color = (blue << 11) | (green << 5) | red;

  fillRectangle(left_col, top_row, rect1.width, rect1.height, color);
}


void
moving_rectangle(rectangle *to_draw)
{
  static int x_vel = 10;
  static int y_vel = 5;

  int left_col = to_draw->rect_col - (to_draw->width / 2);
  int top_row  = to_draw->rect_row - (to_draw->height / 2);

  unsigned int blue = 16, green = 0, red = 31;
  unsigned int color = (blue << 11) | (green << 5) | red;

  // draw rectangle at current position
  fillRectangle(left_col, top_row, to_draw->width, to_draw->height, color);

  // save current position
  to_draw->old_rect_row = to_draw->rect_row;
  to_draw->old_rect_col = to_draw->rect_col;

  // update position
  to_draw->rect_row += y_vel;
  to_draw->rect_col += x_vel;

  // check boundaries, see if rectangle has hit the edges
  if ( ( to_draw->rect_col - (to_draw->width / 2) ) <= 0 ||            // left boundary
       ( to_draw->rect_col + (to_draw->width / 2) ) >= screenWidth ) { // right boundary
    // right or left hit, reverse x velocity
    x_vel = x_vel * -1;
  }
  if ( (to_draw->rect_row + to_draw->height / 2) >= screenHeight ||   // bottom
       (to_draw->rect_row - to_draw->height / 2) <= 0) {              // top
    // top or bottom hit, reverse y velocity
    y_vel = y_vel * -1;
  }

}

void
moving_bird(rectangle *to_draw, int moveUp, int moveDown, int moveLeft, int moveRight)
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
}

void
moving_circle(void){
  static int x_vel = 10;
  static int y_vel = 2;

  u_int color = COLOR_GREEN;
  
  draw_circle(cir1.cir_x, cir1.cir_y, cir1.r, color);

  //save current position
  cir1.old_cir_x = cir1.cir_x;
  cir1.old_cir_y = cir1.cir_y;

  // update position
  cir1.cir_x += x_vel;
  cir1.cir_y -= y_vel;

  // check boundaries, see circle has hit the edges
  if((cir1.cir_x + cir1.r) >= screenWidth || (cir1.cir_x - cir1.r) <= 0){
    x_vel = x_vel * -1;
  }
  if((cir1.cir_y - cir1.r) <= 0 || (cir1.cir_y + cir1.r) >= screenHeight){
    y_vel = y_vel * -1;
  }
}
