#include <msp430.h>
#include "diamond.h"

void draw(u_char center, u_int state){
  u_int color;
  if(state == 0){
    color = COLOR_RED;
  }else{
    color = COLOR_BLUE;
  }
  for(u_char r=0; r < 15; r++){
    for(u_char c=0; compare(c,r); c++){
      drawPixel(center + c, r, color); // right triangle
      drawPixel(center - c, r, color); // left triangle
    }
  }
  for(u_char c=0; c<15; c++){
    for(u_char r=15; r <= 30-c; r++){
      drawPixel(center + c, r, color); // bottom right triangle
      drawPixel(center - c, r, color): // bottom left triangle
    }
  }
}
