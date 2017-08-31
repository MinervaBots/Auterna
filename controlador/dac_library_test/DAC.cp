#line 1 "C:/Users/rafae/Documents/MinervaBots/tests/MikroC/dac_library_test/DAC.c"
#line 1 "c:/users/rafae/documents/minervabots/tests/mikroc/dac.h"
#line 1 "c:/users/rafae/documents/mikroelektronika/mikroc pro for dspic/include/stdint.h"




typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;



typedef signed int int_fast8_t;
typedef signed int int_fast16_t;
typedef signed long int int_fast32_t;


typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned long int uint_fast32_t;


typedef signed int intptr_t;
typedef unsigned int uintptr_t;


typedef signed long int intmax_t;
typedef unsigned long int uintmax_t;
#line 7 "c:/users/rafae/documents/minervabots/tests/mikroc/dac.h"
extern void myDAC1_init(unsigned int reference);
extern void myDAC1_write(uint8_t value);
#line 3 "C:/Users/rafae/Documents/MinervaBots/tests/MikroC/dac_library_test/DAC.c"
void myDAC1_init(unsigned int reference) {

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

 BUFCON0 = 0b10;

 DACEN_DAC1CON_bit = 1;
}

void myDAC1_write(uint8_t value) {
 DAC1DAT = value;
}
