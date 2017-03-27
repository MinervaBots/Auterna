#line 1 "C:/Users/Gabriel Dias/Downloads/Auterna Shrink/Auterna Shrink.c"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for dspic/include/stdio.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for dspic/include/stdbool.h"



 typedef char _Bool;
#line 48 "C:/Users/Gabriel Dias/Downloads/Auterna Shrink/Auterna Shrink.c"
double clamp(double value, double min, double max)
{
 if (value < min) value = min;
 else if (value > max) value = max;
 return value;
}

void controlMotors(double,double);
void initRobot();
void seekAndDestroy();
void starStrategy();

unsigned ServoPeriod;
char buffer[255];

void controlMotors(double leftPower, double rightPower)
{
 leftPower = leftPower *  1 ;
 rightPower = rightPower *  -1  * 0.8;
#line 75 "C:/Users/Gabriel Dias/Downloads/Auterna Shrink/Auterna Shrink.c"
 if (leftPower > 100) leftPower = 100;
 if (leftPower < -100) leftPower = -100;

 if (rightPower > 100) rightPower = 100;
 if (rightPower < -100) rightPower = -100;

 if (leftPower >= 0)
  DAC1DAT  = ( 140  + ( ( 255  - 140 ) / 100.0  * leftPower));
 else
  DAC1DAT  = ( 140  + ( 140  / 100.0  * leftPower));

 if (rightPower > 0)
  DAC2DAT  = ( 140  + ( ( 255  - 140 ) / 100.0  * rightPower));
 else
  DAC2DAT  = ( 140  + ( 140  / 100.0  * rightPower));
#line 105 "C:/Users/Gabriel Dias/Downloads/Auterna Shrink/Auterna Shrink.c"
}

void seekAndDestroy()
{
 float error, powerR, powerL;
 int velocidade = 70;
 int sum = 0;

 sum = (RB3_bit + RB4_bit + RB5_bit + RB6_bit + RB7_bit);
 if(sum != 0)
 error = (1000 * RB4_bit + 2000 * RB3_bit + 3000 * RB5_bit + 4000 * RB6_bit + 5000 * RB7_bit)/sum - 3000;
#line 123 "C:/Users/Gabriel Dias/Downloads/Auterna Shrink/Auterna Shrink.c"
 if(ADC1_READ(0) < 300 || ADC1_READ(4) < 300)
 {
 controlMotors(-100,-100);
 delay_ms(150);
 controlMotors(-100,100);
 delay_ms(200);
 }
 else
 {
 if(error > -100 && error < 100)
 velocidade = 90;
 else
 velocidade = 70;


 powerR = velocidade - error/10.0;
 powerR = clamp(powerR, -100, 100);

 powerL = velocidade + error/10.0;
 powerL = clamp(powerL, -100, 100);

 controlMotors(powerL, powerR);
 }




}

void initRobot()
{


 TRISA0_bit = 1;
 TRISA1_bit = 1;

 TRISA4_bit = 1;
 TRISA7_bit = 1;
 TRISA.B5 = 1;
 TRISA.B6 = 1;



 AMP1CON = 0;
 TRISB0_bit = 0;
 TRISB1_bit = 0;
 TRISB2_bit = 1;
 TRISB3_bit = 1;
 TRISB4_bit = 1;
 TRISB5_bit = 1;
 TRISB6_bit = 1;
 TRISB7_bit = 1;
 TRISB8_bit = 1;
 TRISB9_bit = 1;
 TRISB10_bit = 0;
 TRISB11_bit = 1;
 TRISB12_bit = 0;
 TRISB13_bit = 1;
 TRISB14_bit = 0;
 TRISB15_bit = 1;
#line 189 "C:/Users/Gabriel Dias/Downloads/Auterna Shrink/Auterna Shrink.c"
 ANSA = 0b0000000000010011;
#line 195 "C:/Users/Gabriel Dias/Downloads/Auterna Shrink/Auterna Shrink.c"
 ANSB = 0b0101000000000100;
#line 207 "C:/Users/Gabriel Dias/Downloads/Auterna Shrink/Auterna Shrink.c"
 ADC1_Init();


 CM1CON = 0;
 CM2CON = 0;
 CM3CON = 0;


 DAC1CON = 0b1001001010000011;
 DAC2CON = 0b1001001010000011;

 BUFCON0 = 2;
 controlMotors(0,0);


 ServoPeriod = PWM3_Init(250,3,1);
 PWM3_Set_Duty(0.1 * ServoPeriod);
 PWM3_Start();
#line 235 "C:/Users/Gabriel Dias/Downloads/Auterna Shrink/Auterna Shrink.c"
}



void main()
{
 initRobot();
 controlMotors(0,0);
 return;

 while( RB15_bit )
 {
 if( RB11_bit )
 {
 delay_ms(5000);
 controlMotors(100,100);
 delay_ms(2000);
 controlMotors(0,0);
 delay_ms(2000);
 controlMotors(-100,-100);
 delay_ms(2000);
 controlMotors(0,0);
 delay_ms(2000);
 controlMotors(100,0);
 delay_ms(2000);
 controlMotors(0,0);
 delay_ms(2000);
 controlMotors(0,100);
 delay_ms(2000);
 controlMotors(0,0);
 delay_ms(2000);
 controlMotors(-100,0);
 delay_ms(2000);
 controlMotors(0,0);
 delay_ms(2000);
 controlMotors(0,-100);
 delay_ms(2000);
 controlMotors(0,0);
 }
 }
 return;





 initRobot();
 controlMotors(0,0);
 while( RB15_bit );
 delay_ms(1000);

 while( RB15_bit )
 {
 if( RB11_bit )
 {
 delay_ms(20);
 if( RB11_bit )
 {
 controlMotors(0, 0);
#line 297 "C:/Users/Gabriel Dias/Downloads/Auterna Shrink/Auterna Shrink.c"
 }
 }
 else
 {
 seekAndDestroy();
#line 311 "C:/Users/Gabriel Dias/Downloads/Auterna Shrink/Auterna Shrink.c"
 }
 }
 controlMotors(0,0);

}
