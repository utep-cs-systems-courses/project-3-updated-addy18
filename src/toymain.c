#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "statemachine.h"
#include "buzzer.h"
#include "led.h"

short redrawScreen = 1;
u_int fontFgColor = COLOR_PURPLE;
long COLOR1;
long COLOR2;

static int prev = 0;

u_char centerWidth = (screenWidth/2) + 1;
u_char centerHeight = (screenHeight/2) + 1;

static u_char colorState = 0;

void draw_diamond(u_char col, u_char row, u_char size, u_int color1){  
      for(u_char r = 0; r < size; r++){
	for(u_char c = 0; c < r; c++){
	  drawPixel(col-c, row-r-1, color1);
	  drawPixel(col-c, row+r-(2*size), color1);
	  drawPixel(col+c, row-r-1, color1);
	  drawPixel(col+c, row+r-(2*size), color1);
	}
      }
}

void wdt_c_handler(){
  static int count = 0;
  static int count2 = 0;
  static int count3 = 0;
 
   if(button_state == 1){
    if((++count % 5) == 0) buzzer_advance();
    if(count == 250){
      state_advance();
      count = 0;
    }
   }
  if(++count2 == 125){
    state_advance();
    count2 = 0;
    count++;
    redrawScreen = 1;
  }
  if(button_state == 4){
    if(++count3 == 250){
      count3 = 0;
      fontFgColor = (fontFgColor == COLOR_PURPLE) ? COLOR_BLACK : COLOR_PURPLE;
      redrawScreen = 1;
    }
  }
}

void main(){
  led_init();
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN; //red light will be on when msp is turned on
  
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x8);

  clearScreen(COLOR_TURQUOISE);

  while(1){ // on forever
    if(redrawScreen){
      switch(button_state){
	// displays a blank turquoise screen with my name at the buttom 
      case 0: drawString5x7(screenWidth/2, screenHeight-15, "Adelyn", COLOR_BLUE, COLOR_TURQUOISE); break;
      case 1:
	//	clearScreen(COLOR_BLUE);
	if(prev == 2){
	  blankScreen(25, 30, 15);
	}else if(prev == 3){
	  blankScreen(45,20,20);
	}
	lcdState(COLOR_BLACK, 50, 50, 15); prev = 1; break;
      case 2:
	//	clearScreen(COLOR_TURQUOISE);
	if(prev == 1){
	  blankScreen(50,50,15);
	}else if(prev == 3){
	  blankScreen(45,20,20);
	}
	lcdState(COLOR_RED, 25, 30, 15); prev = 2; break;
      case 3:
	//	clearScreen(COLOR_PURPLE);
	if(prev == 1){
	  blankScreen(50,50,15);
	}else if(prev == 2){
	  blankScreen(25, 30, 15);
	}
	lcdState(COLOR_GREEN, 45, 20, 20); prev = 3; break;
      case 4:
	if(prev == 1){
	  blankScreen(50,50,15);
	}else if(prev == 2){
	  blankScreen(25, 30, 15);
	}else if(prev == 3){
	  blankScreen(45, 20, 20);
	}
	//	 clearScreen(COLOR_BLACK);
		drawString5x7(10,10,"Merry Christmas", fontFgColor, COLOR_TURQUOISE); prev = 4; break;
      }
    }
  }
}
