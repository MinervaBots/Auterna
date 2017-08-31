#include "myDAC.h"

uint8_t i = 127;

void main() {
  myDAC2_init(DAC_INTERNAL_REF_2V);
  
  myDAC2_write(i);
  
  while(1) {
    for(; i < 255; i+= 5) {
      myDAC2_write(i);
      delay_ms(200);
    }
    for(; i > 0; i -= 5) {
      myDAC2_write(i);
      delay_ms(200);
    }
    for(; i < 127; i += 5) {
      myDAC2_write(i);
      delay_ms(200);
    }
  }
}