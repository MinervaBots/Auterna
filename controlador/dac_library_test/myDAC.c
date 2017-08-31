#include "myDAC.h"

void myDAC1_init(unsigned int reference) {
  // Configuração DAC
  DACSIDL_DAC1CON_bit = 0;
  DACSLP_DAC1CON_bit = 1;
  DACFM_DAC1CON_bit = 0;
  SRDIS_DAC1CON_bit = 1;
  DACTRIG_DAC1CON_bit = 0;
  DACOE_DAC1CON_bit = 1;

  DACTSEL_4_DAC1CON_bit = 0;
  DACTSEL_3_DAC1CON_bit = 0;
  DACTSEL_2_DAC1CON_bit = 0;
  DACTSEL_1_DAC1CON_bit = 0;
  DACTSEL_0_DAC1CON_bit = 0;

  DACREF_0_DAC1CON_bit = 1;
  DACREF_1_DAC1CON_bit = 1;

  BUFCON0 = reference;  // Referência interna base (BGBUF1)é 1 V
  
  DACEN_DAC1CON_bit = 1;  // Enable DAC1 module
}

void myDAC1_write(uint8_t value) {
  DAC1DAT = value;
}

void myDAC2_init(unsigned int reference) {
 // Configuração DAC
  DACSIDL_DAC2CON_bit = 0;
  DACSLP_DAC2CON_bit = 1;
  DACFM_DAC2CON_bit = 0;
  SRDIS_DAC2CON_bit = 1;
  DACTRIG_DAC2CON_bit = 0;
  DACOE_DAC2CON_bit = 1;

  DACTSEL_4_DAC2CON_bit = 0;
  DACTSEL_3_DAC2CON_bit = 0;
  DACTSEL_2_DAC2CON_bit = 0;
  DACTSEL_1_DAC2CON_bit = 0;
  DACTSEL_0_DAC2CON_bit = 0;

  DACREF_0_DAC2CON_bit = 1;
  DACREF_1_DAC2CON_bit = 1;

  BUFCON0 = reference;  // Referência interna base (BGBUF1)é 1 V

  DACEN_DAC2CON_bit = 1;  // Enable DAC2 module
}

void myDAC2_write(uint8_t value) {
  DAC2DAT = value;
}