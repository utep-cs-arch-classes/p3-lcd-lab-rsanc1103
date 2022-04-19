#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "drawing.h"

// global vars for the rectangle
rectangle rect1;
/* int rect_row, rect_col; */
/* int old_rect_row, old_rect_col; */
/* u_char height, width; */

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
}

void
draw_moving_shapes(void)
{
  int left_col = rect1.old_rect_col - (rect1.width / 2);
  int top_row  = rect1.old_rect_row - (rect1.height / 2);

  // blank out the old rectangle
  fillRectangle(left_col, top_row, rect1.width, rect1.height, background_color);

  // draw and update the rectangle
  moving_rectangle(&rect1);
 
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
  static int x_vel = 0;
  static int y_vel = 10;

  int left_col = to_draw->rect_col - (to_draw->width+30);
  int top_row  = to_draw->rect_row+30 - (to_draw->width+40);

  unsigned int blue = 16, green = 0, red = 31;
  unsigned int color = (blue << 11) | (green << 5) | red;

  // draw rectangle at current position
  //fillRectangle(0, top_row, to_draw->width+25, to_draw->height+10, background_color);
  flappyBird(0, top_row);

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
       (to_draw->rect_row - to_draw->height / 2) <= 20) {              // top
    // top or bottom hit, reverse y velocity
    y_vel = y_vel * -1;
  }

}
