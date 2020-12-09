#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define LED_GREEN BIT6

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

long COLOR1;
long COLOR2;

void wdt_c_handler(){
  static int count = 0;
  count++;
  if(count == 250){
    count = 0;
    redrawScreen = 1;
  }
}

void main(){
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();

  enableWDTInterrupts();
  or_sr(0x8);

  clearScreen(COLOR_BLACK);

  u_char centerWidth = (screenWidth/2) + 1;
  u_char centerHeight = (screenHeight/2) + 1;

  static u_char colorState = 0;

  while(1){
    if(redrawScreen){
      redrawScreen = 0;

      switch(colorState){
      case 0: COLOR1 = COLOR_RED; COLOR2 = COLOR_WHITE; colorState = 1; break;
      case 1: COLOR1 = COLOR_WHITE; COLOR2 = COLOR_RED; colorState = 0; break;
      }

      for(u_char r = 0; r < 10; r++){
	for(u_char c = 0; c <= r; c++){
	  drawPixel(centerWidth-c, centerHeight-r-1, COLOR1);
	  drawPixel(centerWidth+c, centerHeight-r-1, COLOR1);
	  drawPixel(centerWidth-c, centerHeight+r-20, COLOR1);
	  drawPixel(centerWidth+c, centerHeight+r-20, COLOR1);
	}
      }
      char* StrOnScreen = " adds";

      drawString5x7(centerWidth-(3*12), centerHeight+10, StrOnScreen, COLOR2, COLOR_BLACK);
    }

    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}
