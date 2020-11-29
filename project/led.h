#ifndef led_included
#define led_included

#include <msp430.h>

#define LED_RED BIT0 // p1.0
#define LED_GREEN BIT6 //p1.6
#define LEDS (BIT0 | BIT6)

//extern unsigned char red_on, green_on;
//extern unsigned char led_changed;

void led_init();  //initializa LEDs
void led_update(); // update LEDs

//these are boolean flags
extern unsigned char red_on, green_on, led_changed;

#endif
