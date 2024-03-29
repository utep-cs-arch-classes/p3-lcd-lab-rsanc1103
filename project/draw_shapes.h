#ifndef _DRAW_SHAPES_H_
#define _DRAW_SHAPES_H_

#include <lcdutils.h>

typedef struct rect_st {
  int rect_row;
  int rect_col;
  int old_rect_row;
  int old_rect_col;
  u_char height;
  u_char width;
} rectangle;

typedef struct cir_st {
  int cir_x;
  int cir_y;
  int old_cir_x;
  int old_cir_y;
  int r;
} circle;

extern u_int background_color;
extern int gameOver;
extern int pause;

/* initializes shape positions */
void init_shapes(void);

/* handles erasing and updating all the shapes */
void draw_moving_shapes(void);

/* handles flappy bird, updates its 
   position and draws it at its new location */
void moving_bird(rectangle* to_draw, int moveUp, int moveDown);

/* handles a single circle, updates its 
   position and draws it at its new location */
void moving_circle(void);

#endif // _DRAW_SHAPES_H_
