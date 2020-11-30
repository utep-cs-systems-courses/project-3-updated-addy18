#include <msp430.h>
#include "State_Machine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h" 
#include "lcdutils.h"
#include "lcddraw.h"

static short two = 1;
static char dimState = 0;

char toggle_red(){
  static char state = 0;
  switch(state){
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
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

char state2(){
  static char state = 0;
  switch(state){
  case 0:
    green_on = 1;
    state = 1;
    break;
  case 1:
    green_on = 0;
    state = 0;
    break;
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

void dim25(){
  switch(dimState){
  case 0: red_on = 1; break; 
  case 1: 
  case 2:
  case 3: red_on = 0; break;
  default: dimState = 0; break;
  }
  led_changed = 1;
  led_update();
}

void dim50(){
  switch(dimState){
  case 0: 
  case 1: red_on = 1; break;
  case 2: 
  case 3: red_on = 0; break;
  default: dimState = 0; break;
  }
  led_changed = 1;
  led_update();
}

void dim75(){
  switch(dimState){
  case 0:red_on = 0; break;
  case 1:
  case 2:
  case 3: red_on = 1; break;
  default: dimState = 0; break;
  }
  led_changed = 1;
  led_update();
}

char state4(){
  static char dim = 0;
  switch(dim){
  case 0:
    dim25();
    dim = 1;
    break;
  case 1:
    dim50();
    dim = 2;
    break;
  case 2:
    dim75();
    dim = 0;
    break;
  default:
    red_on = 0;
    green_on = 0;
    dim = 0;
    break;
  }
  return 1;
}

void state_advance(){
  char changed = 0;
  switch(switch_state_changed){
   case 1:
     drawString8x12(20, 10,"0", COLOR_WHITE, COLOR_BLACK);
    changed = toggle_red();
    break;
  case 2:
    changed = state2();
    break;
  case 3:
    changed = state3();
    break;
  case 4:
    changed = state4();
    break;
  }
  led_changed = changed;
  led_update();
}
