#include <msp430.h>
#include <libTimer.h>
#include "statemachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

char button_state = 0;

void lcdState(int COLOR1, int width, int height, int size){
  u_char centerWidth = screenWidth/2 + 1;
  u_char centerHeight = screenWidth/2 + 1;

  draw_diamond(centerWidth-width, centerHeight-height, size, COLOR1);
  draw_diamond(centerWidth+width, centerHeight+height, size, COLOR1);
  draw_diamond(centerWidth, centerHeight, size, COLOR1);
  //drawString5x7((centerWidth/2)+10, centerHeight+10, "Addy", COLOR1);
}

void draw_diamond(u_char col, u_char row, u_char size, u_int color1);

char toggle_red(){
  static char state = 0;
  switch(state){
  case 0: red_on = 1; state = 1; buzzer_set_period(2000); break;
  case 1: red_on = 0; state = 0; buzzer_set_period(0); break;
  }
  return 1;
}

char toggle_green(){
  char changed = 0;
  if(red_on){
    green_on ^= 1;
    changed = 1;
    buzzer_set_period(100);
  }
  return changed;
}

char state2(){
  static char state = 0;
  switch(state){
  case 0: green_on = 1; state = 1; buzzer_set_period(1000); break;
  case 1: green_on = 0; state = 0; buzzer_set_period(0); break;
  }
  return 1;
}

char state3(){
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
  static char state = 0;
  switch(state){
  case 0: red_on = 0; state = 1; break;
  case 1: red_on = 0; state = 2; break;
  case 2: red_on = 0; state = 3; break;
  case 3: red_on = 1; state = 0; break;
  }
  led_changed = 1;
  led_update();
}
