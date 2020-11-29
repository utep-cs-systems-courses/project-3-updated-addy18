#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

//notes
#define A3 2273
#define B3 2025
#define G3 2551
#define E3 3033
#define C3 3846
#define C4 1911
#define D4 1703
#define E4 1517
#define F4 1432
#define G4 1276
#define A4 1136
#define B4 1012

void buzzer_init(){
  /*
    Direct timer A output "TA0.1" to P2.6.
    According to table 21 from data sheet:
    P2SEL2.6, P2SEL2.7, and P2SEL.7 must be zero
    P2SEL.6 must be 1
    Also: P2.6 direction must be output
  */
  timerAUpmode(); // used to drive speaker
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; // enable output to speaker (P2.6)
}

void buzzer_set_period(short cycles){ // buzzer clock = 2MHz. (period of 1k results in 2kHz tone)
  CCR0 = cycles;
  CCR1 = cycles >>1; // one half cycle
}

void song1(){
  int i = 0;
  int song[] = {A3, G3, F4, E3};
  /*
  for(int i = 0; i < sizeof(song) / sizeof(*song); i++){
    buzzer_set_period(song[i]);
    __delay_cycles(850000);
  }
  */

  while(i < sizeof(song)){
    int first = 0;
    while (first < 20){
      int second = 0;
      while(second < 30000){
	second++;
      }
      first++;
    }
    buzzer_set_period(song[i]);
    state_advance();
    i++;
  }
}

void song2(){
  int i = 0;
  int song[] = {B4, A4, F4};
  /*
  for(int i = 0; i < sizeof(song) / sizeof(*song); i++){
    buzzer_set_period(song[i]);
    __delay_cycles(8500000);
  }
  */
  while(i < sizeof(song)){
    int first = 0;
    while(first < 20){
      int second = 0;
      while(second < 30000){
	second++;
      }
      first++;
    }
    buzzer_set_period(song[i]);
    state_advance();
    i++;
  }
}

void song3(){
  int i = 0;
  int song[] = {G4, D4, C3, B3};
  /*
  for(int i = 0; i < sizeof(song) / sizeof(*song); i++){
    buzzer_set_period(song[i]);
    __delay_cycles(8500000);
  }
  */
  while(i < sizeof(song)){
    int first = 0;
    while(first < 20){
      int second = 0;
      while(second < 30000){
	second++;
      }
      first++;
    }
    buzzer_set_period(song[i]);
    state_advance();
    i++;
  }
}

void song4(){
  int i = 0;
  int song[] = {E4, C3, D4, A4, G3};
  /*
  for(int i = 0; i < sizeof(song) / sizeof(*song); i++){
    buzzer_set_period(song[i]);
    __delay_cycles(8500000);
  }
  */

  while(i < sizeof(song)){
    int first = 0;
    while(first < 20){
      int second = 0;
      while(second < 30000){
	second++;
      }
      first++;
    }
    buzzer_set_period(song[i]);
    state_advance();
    i++;
  }
}
