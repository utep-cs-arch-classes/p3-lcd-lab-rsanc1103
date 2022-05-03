#include "libTimer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "stateMachine.h"
#include "buzzer.h"
#include "wdtInterruptHandler.h"

void play(){  
   switch(gameOver){
   case 0:
     moveBird();
     gameMode();
     break; 
   case 1:
     gameOverText();
     buzzer_set_period(0); 
     break;
   }
   return;
}
