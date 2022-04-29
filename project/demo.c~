#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachine.h"

char redraw_screen = 1;

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!!

void main()
{
  configureClocks();
  switch_init();
  lcd_init();
  clearScreen(background_color);
  switch_init();
  init_shapes();
  buzzer_init();

  enableWDTInterrupts();

  or_sr(0x18);	/**< CPU off , GIE on*/
}
