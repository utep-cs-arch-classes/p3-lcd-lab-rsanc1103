#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "drawing.h"
#include "draw_shapes.h"
#include "buzzer.h"

rectangle rect1;
int gameOver = 0;
int pause;

void
update_text(int pressed){
  if(pressed){
    // subtitle
    drawString5x7(20, 150, "Not Flappy Bird ", COLOR_WHITE, background_color);
  }
  else{
    // subtitle
    drawString5x7(20, 150, "   dark mode   ", COLOR_WHITE, background_color);
  }
}

void
moveBird(void){
  if(!pause){
    // button 1 pressed
    if(switch1_down){
      // move bird 
      moving_bird(&rect1, 0, 1);
      // moving sound
      buzzer_set_period(12000);

      // keep theme settings
      if(background_color == COLOR_BLACK){
	update_text(0);
      }
      else{
	update_text(1);
      }
    }
    // button 2 pressed
    if(switch2_down){
      // change bird direction (up/down)
      moving_bird(&rect1, 1, 0);
      // change direction sound
      buzzer_set_period(5000);
    }
  }
}
void
gameMode(void){
  // button 3 pressed
  if(switch3_down){
    // stop sounds
    buzzer_set_period(0);

    // pause
    if(!pause){
      pause = 1;
      drawString5x7(50, 70, "PAUSE", COLOR_WHITE, background_color);
    }
    // continue
    else{
      pause = 0;
      drawString5x7(50, 70, "     ", COLOR_WHITE, background_color);
    }
  }
  // button 4 pressed
  if(switch4_down){
    // change theme to dark
    if(background_color == COLOR_BLACK){
      background_color = COLOR_BLUE;
      clearScreen(background_color);
      // dark mode subtitle
      update_text(1);
    }
    // change theme to light
    else{
      background_color = COLOR_BLACK;
      clearScreen(background_color);
      // normal subtitle
      update_text(0);
    }
  }
}
