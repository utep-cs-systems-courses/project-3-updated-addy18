#include <msp430.h>
#include <libTimer.h>
#include "statemachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

char button_state = 0;
static int state = 0;

//draws three diamonds, different colors in each state
void lcdState(int COLOR1, int width, int height, int size){
  u_char centerWidth = screenWidth/2 + 1;
  u_char centerHeight = screenWidth/2 + 1;

  draw_diamond(centerWidth-width, centerHeight-height, size, COLOR1);
  draw_diamond(centerWidth+width, centerHeight+height, size, COLOR1);
  draw_diamond(centerWidth, centerHeight, size, COLOR1);
}

//clears previous diamonds, from previous states
void blankScreen(int width, int height, int size){
  u_char centerWidth = screenWidth/2 + 1;
  u_char centerHeight = screenWidth/2 + 1;

  draw_diamond(centerWidth-width, centerHeight-height, size, COLOR_TURQUOISE);
  draw_diamond(centerWidth+width, centerHeight+height, size, COLOR_TURQUOISE);
  draw_diamond(centerWidth, centerHeight, size, COLOR_TURQUOISE);

}

void draw_diamond(u_char col, u_char row, u_char size, u_int color1);

char toggle_red(){
  static char state = 0;
  switch(state){
  case 0: red_on = 1; state = 1;// buzzer_set_period(2000);
    break;
  case 1: red_on = 0; state = 0;// buzzer_set_period(0);
    break;
  }
  return 1;
}

char toggle_green(){
  char changed = 0;
  if(red_on){
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}

// red led flashes 
char state2(){
  static char state = 0;
  switch(state){
  case 0: green_on = 1; state = 1; //buzzer_set_period(1000);
    break;
  case 1: green_on = 0; state = 0; //buzzer_set_period(0);
    break;
  }
  return 1;
}
void buzzer_advance();
// red and green toggle
char state3(){
  //buzzer_advance();
  char changed = 0;
  static enum {R=0, G=1} color = G;
  switch(color){
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }
  led_changed = changed;
  led_update();
}

char state4(){
  red_on = 0;
  led_changed = 1;
  led_update();
  return 1;
}
// attempt to dim
char state25(){
  
}
