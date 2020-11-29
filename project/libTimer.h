#ifndef libTimer_included
#define libTimer_included

void configureClocks();
void enableWDTInterrupts();
void timerAUpmode();

unsigned char gert_sr();

void set_sr();
void or_sr();
void and_sr();

#endif
