#include <msp430.h>
#include <libTimer.h>
#include "statemachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

char button_state = 0;
extern short int state = 0;
extern freq = 500;

/*
state 1: flashed green, with noise, and 3 black diamonds
state 2: flashes red, with noise, and 3 red diamonds
state 3: flashes red and green, with noise, and 3 green diamonds
state 4: no leds, no noise, blank screen with "merry christmas" printed
 */

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

  draw_diamond(centerWidth-width, centerHeight-height, size, COLOR_BLUE);
  draw_diamond(centerWidth+width, centerHeight+height, size, COLOR_BLUE);
  draw_diamond(centerWidth, centerHeight, size, COLOR_BLUE);
}


char toggle_red(){
  static char state = 0;
  switch(state){
  case 0: red_on = 1; state = 1; break;
  case 1: red_on = 0; state = 0; break;
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


// helps in buzzer_advance.s
short get_period(short freq){
  return 2000000/freq;
}


// blinks green led while playing sounds from buzzer advance 
char state1(){
  static short stat = 0;
  switch(stat){
  case 0: red_on = 1; state = 1; stat = 1; break;
  case 1: red_on = 0; state = 0; stat = 0; break;
  }
  return 1;
}


// red led flashes 
char state2(){
  static char state = 0;
  switch(state){
  case 0: green_on = 1; state = 1; buzzer_set_period(1000); break;
  case 1: green_on = 0; state = 0; buzzer_set_period(0); break;
  }
  return 1;
}


// red and green toggle
char state3(){
  char changed = 0;
  static enum {R=0, G=1} color = G;
  switch(color){
  case R: changed = toggle_red(); color = G; buzzer_set_period(2000); break;
  case G: changed = toggle_green(); color = R; buzzer_set_period(1000); break;
  }
  led_changed = changed;
  led_update();
}


// turns off leds 
char state4(){
  green_on = 0;
  buzzer_set_period(0);
  led_changed = 1;
  led_update();
  return 1;
}

