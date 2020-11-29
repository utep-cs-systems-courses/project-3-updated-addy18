//Alternate LEDs from off, Green and Red 
#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "libTimer.h"

int main(void){
  configureClocks(); //setup master oscillator, CPU & peripheral clocks
  led_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts(); //enable periodic interrupt
  //  buzzer_set_period(1000); // start buzzing

  or_sr(0x18); //CPU off, GIE on 
}
