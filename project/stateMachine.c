#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "drawing.h"
#include "draw_shapes.h"
#include "buzzer.h"

rectangle rect1;

void
update_text(int pressed){
  if(pressed){
    drawString5x7(20, 150, "Not Flappy Bird ", COLOR_WHITE, background_color);
  }
  else{
    drawString5x7(20, 150, "   dark mode   ", COLOR_WHITE, background_color);
  }
}

void
moveBird(void){
  draw_moving_shapes();
  
  if(switch1_down){ 
    moving_bird(&rect1, 0, 1);
    buzzer_set_period(12000);
    if(background_color == COLOR_BLACK){
      update_text(0);
    }
    else{
      update_text(1);
    }
  }
  if(switch2_down){
    moving_bird(&rect1, 1, 0);
    buzzer_set_period(5000);
  }
}
void
gameMode(void){
  if(switch3_down){
    if(background_color == COLOR_BLACK){
      background_color = COLOR_BLUE;
      clearScreen(background_color);
    }
    update_text(1);
    buzzer_set_period(0);
  }
  if(switch4_down){
    background_color = COLOR_BLACK;
    clearScreen(background_color);
    update_text(0);
  }
}
