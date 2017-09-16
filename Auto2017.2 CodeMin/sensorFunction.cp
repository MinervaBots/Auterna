#line 1 "C:/Users/Gabriel/Desktop/Nova pasta (2)/sensorFunction.c"
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
#line 7 "C:/Users/Gabriel/Desktop/Nova pasta (2)/sensorFunction.c"
float mySensorControl (){

 char buffer[255];
 int soma = 0;
 float erro = 0;

 soma = ((-2*RB6_bit) + (3*RA7_bit) + RB5_bit + (-3*RB4_bit) + (2*RB3_bit) + (-4*RA6_bit) + (4*RA3_bit));

 erro = soma/10;


 if (erro == 0.1 ){
 UART2_Write_Text("inimigo logo a frente");
 erro = erro*0;
 return erro;

 }

 if (erro >0.1){


 erro = erro + 0.6;
 IntToStr(erro,buffer);
 UART2_Write_Text("Inimigo visto na direita");
 UART2_Write_Text("/n");

 if (erro > 1){
 erro = 1;
 return erro;
 }
 else
 return erro;

 }

 if (erro <0.1){

 erro = erro - 0.6;
 UART2_Write_Text(buffer);
 UART2_Write_Text("inimigo visto na esquerda");
 UART2_Write_Text("/n");
 if (erro > -1){
 erro = -1;
 return erro;
 }
 }
 else
 return erro;

}

void init_robot(){

 ANSB= 0b110100110000000;

 ANSA= 0b000000000000011;

 UART2_init(9600);



 TRISB= 0b100100110111111;




 delay_ms(5000);

}

void Sniffing(){
 char left[255];
 char right[255];

 if(ADC1_Read(0)&& ADC1_Read(1) > 1000){

 int EdgeRight = ADC1_read(1);
 int EdgeLeft = ADC1_read(0);

 IntToStr(EdgeLeft,left);
 IntToStr(EdgeRight,right);

 UART2_Write_Text(left);
 UART2_Write_Text("Sensor de borda esquerda dentro da arena");
 UART2_Write_Text("/n");

 UART2_Write_Text(right);
 UART2_Write_Text("Sensor de borda direita dentro da arena");
 Uart2_Write_Text("/n");

 if(mySensorControl == 0){
 MotorController(1, 1 );
 }
 else{
 MotorController(1,mySensorControl());
 }
 }


 if(ADC1_Read(1) <1000){
 int EdgeRight = ADC1_read(1);
 IntToStr(EdgeRight,right);
 UART2_Write_Text(right);

 UART2_Write_Text("Sensor de borda direita fora da arena");
 Uart2_Write_Text("/n");

 MotorController(1, -1 );
 }
 if(ADC1_Read(0) <1000){
 int EdgeLeft = ADC1_read(0);
 IntToStr(EdgeLeft,left);
 UART2_Write_Text(left);
 UART2_Write_Text("Sensor de borda esquerda fora da arena");
 Uart2_Write_Text("/n");

 MotorController(1, 1 );

 }
}
