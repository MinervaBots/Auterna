#line 1 "C:/Users/rafae/Documents/MinervaBots/tests/MikroC/dac_library_test/dac_library_test.c"
#line 1 "c:/users/rafae/documents/minervabots/tests/mikroc/mydac.h"
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
#line 7 "c:/users/rafae/documents/minervabots/tests/mikroc/mydac.h"
extern void myDAC1_init(unsigned int reference);
extern void myDAC1_write(uint8_t value);

extern void myDAC2_init(unsigned int reference);
extern void myDAC2_write(uint8_t value);
#line 3 "C:/Users/rafae/Documents/MinervaBots/tests/MikroC/dac_library_test/dac_library_test.c"
uint8_t i = 127;

void main() {
 myDAC2_init( 0b10 );

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
