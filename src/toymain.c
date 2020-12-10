#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "statemachine.h"
#include "buzzer.h"
#include "led.h"

//#define LED_GREEN BIT6

short redrawScreen = 1;
static short prev = 0;
//u_int fontFgColor = COLOR_GREEN;

long COLOR1;
long COLOR2;

u_char centerWidth = (screenWidth/2) + 1;
u_char centerHeight = (screenHeight/2) + 1;

static u_char colorState = 0;

void draw_diamond(u_char col, u_char row, u_char size, u_int color1, u_int color2){
  while(1){
    if(redrawScreen){
      redrawScreen = 0;

      switch(colorState){
      case 0: COLOR1 = color1; COLOR2 = color2; colorState = 1; break;
      case 1: COLOR1 = color2; COLOR2 = color1; colorState = 0; break;
      }
      
      for(u_char r = 0; r < size; r++){
	for(u_char c = 0; c < r; c++){
	  drawPixel(col-c, row-r-1, COLOR1);
	  drawPixel(col-c, row+r-(2*size), COLOR1);
	  drawPixel(col+c, row-r-1, COLOR1);
	  drawPixel(col+c, row+r-(2*size), COLOR1);
	}
      }
    }
  }
}

void wdt_c_handler(){
  static int count = 0;
  static int count2 = 0;
  if(button_state == 4){
    if(++count == 250){
      state_advance();
      count = 0;
      redrawScreen = 1;
    }
  }
  if(++count2 == 125){
    state_advance();
    count2 = 0;
  }
}

void main(){
  led_init();
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x8);

  clearScreen(COLOR_YELLOW);

  while(1){
    if(redrawScreen){
      redrawScreen = 0;

      switch(button_state){
      case 0: drawString5x7(screenWidth/2, screenHeight-10, "Adelyn", COLOR_BLUE, COLOR_YELLOW); break;
      case 1: lcdState(COLOR_BLACK); break;
      case 2: lcdState(COLOR_RED); break;
      case 3: lcdState(COLOR_GREEN); break;
      }
    }
  /*
      char* StrOnScreen = " adds";

      drawString5x7(centerWidth-(3*12), centerHeight+10, StrOnScreen, COLOR2, COLOR_BLACK);
  */
    
    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}
