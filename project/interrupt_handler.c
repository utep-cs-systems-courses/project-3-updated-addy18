#include <msp430.h>
#include "switches.h"

//switch on P2
void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){  //button cause an interrupt?
    P2IFG &= ~SWITCHES;  // clear pending sw interrupt
    switch_interrupt_handler(); // single handler for all switches
  }
}
