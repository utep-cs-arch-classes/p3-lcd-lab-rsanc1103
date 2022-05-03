#include <msp430.h>
#include "libTimer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "stateMachine.h"
#include "buzzer.h"

void
gameOverText(void){
  drawString5x7(40, 80, "You Lost!", COLOR_WHITE, background_color);
}

// function that handles interrupts
// from the periodic timer
// The timer fires an event 250 times/sec
void
__interrupt_vec(WDT_VECTOR) WDT(){
  const  u_int second_limit = 25;
  static u_int second_count = 0;
  
  second_count++;

  if (second_count >= second_limit) {
     second_count = 0;
     play();
   }
} 
