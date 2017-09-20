#line 1 "C:/Users/Gabriel/Desktop/Nova pasta (2)/AutoMini.c"
#line 1 "c:/users/gabriel/desktop/nova pasta (2)/constantes.h"



extern float mySensorControl();

extern void init_robot();

extern void Sniffing();
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
#line 4 "C:/Users/Gabriel/Desktop/Nova pasta (2)/AutoMini.c"
void main() {
 init_robot();
 while(1){
 Sniffing();
 }

}
