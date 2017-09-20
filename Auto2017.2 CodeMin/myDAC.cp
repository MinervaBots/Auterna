#line 1 "C:/Users/Gabriel/Desktop/Nova pasta (2)/myDAC.c"
#line 1 "c:/users/gabriel/desktop/nova pasta (2)/mydac.h"
#line 1 "d:/mikroelektronika dspic 6.21/nova pasta/mikroc pro for dspic/include/stdint.h"




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
#line 6 "c:/users/gabriel/desktop/nova pasta (2)/mydac.h"
extern void myDAC2_init(unsigned int reference);

extern void myDAC2_write(uint8_t value);

extern void MotorController(float linear,float angular);
#line 3 "C:/Users/Gabriel/Desktop/Nova pasta (2)/myDAC.c"
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

 BUFCON0 = reference;

 DACEN_DAC1CON_bit = 1;
}

void myDAC1_write(uint8_t value) {
 DAC1DAT = value;
}

void myDAC2_init(unsigned int reference) {

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

 BUFCON0 = reference;

 DACEN_DAC2CON_bit = 1;
}

void myDAC2_write(uint8_t value) {
 DAC2DAT = value;
}

void MotorController(float linear,float angular){

 float right = (linear + angular)/2;
 float left = (linear - angular)/2;

 float rightPWM = 127 + 127*right;
 float leftPWM = 127 - 127*left;

 myDAC2_write(rightPWM);
 myDAC1_write(leftPWM);
}
