#include <stdio.h>
#include <stdbool.h>

#define  SERVO_RIGHT        1
#define  SERVO_CENTER       0
#define  SERVO_LEFT        -1
#define  SERVO_DUTY_RIGHT   0.12
#define  SERVO_DUTY_CENTER  0.075
#define  SERVO_DUTY_LEFT    0.03


/************************* PINS ************************************ */


#define  POWER_BUTTON RB11_bit
#define  REMOTE_CONTROL_PIN RB15_bit

#define  SWITCH_1_PIN RB13_bit
#define  SWITCH_2_PIN RA5_bit
#define  SWITCH_3_PIN PORTA.B6
#define  SWITCH_4_PIN RA7_bit

#define  LED_DEBUG RB1_bit



/* ********************* MOTORS **************************** */

//Revert motor (1 or -1)
#define RIGHT_MOTOR_INVERTER   -1
#define LEFT_MOTOR_INVERTER    1    //Manter essa configuracao para codigo de cores!!!

//Those Constants Set the stop points to each motor
#define STOP_V_LEFT        140  // 129 in usb
#define STOP_V_RIGHT         140  //  129 in usb

#define MOTOR_MAX_V 255
#define RIGHT_MOTOR_RISE_RATE        (MOTOR_MAX_V - STOP_V_RIGHT) / 100.0
#define RIGHT_MOTOR_DOWN_RATE        STOP_V_RIGHT / 100.0
#define LEFT_MOTOR_RISE_RATE         (MOTOR_MAX_V - STOP_V_LEFT) / 100.0
#define LEFT_MOTOR_DOWN_RATE         STOP_V_LEFT / 100.0

#define  LEFT_MOTOR  DAC1DAT
#define  RIGHT_MOTOR DAC2DAT

#define PRINT_DEBUG false

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
  leftPower = leftPower * LEFT_MOTOR_INVERTER;
  rightPower = rightPower * RIGHT_MOTOR_INVERTER * 0.8;
  /*
  leftPower = clamp(leftPower, -100, 100);
  rightPower = clamp(rightPower, -100, 100);

    // TODO
  LEFT_MOTOR = (STOP_V_LEFT + ( (leftPower >= 0 ? LEFT_MOTOR_RISE_RATE : LEFT_MOTOR_DOWN_RATE) * leftPower));
  RIGHT_MOTOR = (STOP_V_RIGHT + ( (rightPower >= 0 ? RIGHT_MOTOR_RISE_RATE : RIGHT_MOTOR_DOWN_RATE) * rightPower));
  */
  if (leftPower > 100) leftPower = 100;
  if (leftPower < -100) leftPower = -100;

  if (rightPower > 100) rightPower = 100;
  if (rightPower < -100) rightPower = -100;

  if (leftPower >= 0)
    LEFT_MOTOR = (STOP_V_LEFT + (LEFT_MOTOR_RISE_RATE * leftPower));
  else
    LEFT_MOTOR = (STOP_V_LEFT + (LEFT_MOTOR_DOWN_RATE * leftPower));

  if (rightPower > 0)
    RIGHT_MOTOR = (STOP_V_RIGHT + (RIGHT_MOTOR_RISE_RATE * rightPower));
  else
    RIGHT_MOTOR = (STOP_V_RIGHT + (RIGHT_MOTOR_DOWN_RATE * rightPower));

  #if (PRINT_DEBUG)

  UART2_Write_text( "Left Voltage: " );
  IntToStr(STOP_V_LEFT + (leftPower > 0 ? LEFT_MOTOR_RISE_RATE : LEFT_MOTOR_DOWN_RATE) * leftPower, buffer);
  UART2_Write_text(buffer);
  UART2_Write_text("\n");

  UART2_Write_text( "\tRight Voltage: ");
  IntToStr(STOP_V_RIGHT + (rightPower > 0 ? RIGHT_MOTOR_RISE_RATE : RIGHT_MOTOR_DOWN_RATE) * rightPower, buffer);
  UART2_Write_text(buffer);
  UART2_Write_text("\n");

  #endif

}

void seekAndDestroy()
{
  float error, powerR, powerL;
  int velocidade = 70;
  int sum = 0;

  sum = (RB3_bit + RB4_bit + RB5_bit + RB6_bit + RB7_bit);
  if(sum != 0)
    error = (1000 * RB4_bit + 2000 * RB3_bit + 3000 * RB5_bit + 4000 * RB6_bit + 5000 * RB7_bit)/sum - 3000;
  #if (PRINT_DEBUG)
  IntToStr(error,buffer);
  UART2_Write_Text(buffer);
  UART2_Write_Text("\t");
  UART2_Write_Text("\n");
  #endif
  
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
    
    // TODO
    powerR  = velocidade  - error/10.0;
    powerR = clamp(powerR, -100, 100);

    powerL = velocidade  + error/10.0;
    powerL = clamp(powerL, -100, 100);

    controlMotors(powerL, powerR);
  }
  //UART2_Write_Text("powerL: ");
  //IntToStr(powerL,buffer);
  //UART2_Write_Text(buffer);
  //UART2_Write_Text("\n");
}

void initRobot()
{
  //PINOS :
  /****** PORT A ******/
  TRISA0_bit = 1; //Borda Esquerda Frente (ANALOG)
  TRISA1_bit = 1; //Borda Direita Frente (ANALOG)
  // A2 e A3 São pinos do OSCIlADOR
  TRISA4_bit = 1; //Borda Direita Atras  (ANALOG)
  TRISA7_bit = 1; //Estratégia 4
  TRISA.B5 = 1;   //Estratégia 2
  TRISA.B6 = 1;   //Estratégia 3


  /****** PORT B ******/
  AMP1CON  = 0;
  TRISB0_bit = 0;  //Pino de UART : TX
  TRISB1_bit = 0;  //Pino de UART : RX
  TRISB2_bit = 1;  //Borda Esquerda Atras  (ANALOG)
  TRISB3_bit = 1;  //Oponente Direito - OD
  TRISB4_bit = 1;  //Oponente Diagonal Esquerdo - ODE. Esse pino também é o Secondary OSC. Tomar cuidado nas configs.Funcionando: SOSC Type : Digital e SOSC Power: Low Power.
  TRISB5_bit = 1;  //Oponente Centro - OC
  TRISB6_bit = 1;  //Oponente Esquerdo - OE
  TRISB7_bit = 1;  //Oponente Diagonal Direito - ODD
  TRISB8_bit = 1;  //Pino de I2C : SCL
  TRISB9_bit = 1;  //Pino de I2C : SDA
  TRISB10_bit = 0; //Servo Motor
  TRISB11_bit = 1; //Start/Stop Button
  TRISB12_bit = 0; //Motor1 (DAC1OUT)
  TRISB13_bit = 1; //Estratégia 1
  TRISB14_bit = 0; //Motor2 (DAC2OUT)
  TRISB15_bit = 1; //Controle Infra-Red

  //Configuração Pinos de Leitura Analógica :
  /****** PORT A ******/
  /*
  Analog pins: A0, A1 and A4
  */
  ANSA = 0b0000000000010011;

  /****** PORT B ******/
  /*
  Analog pins: B3, B12 and B14
  */
  ANSB = 0b0101000000000100;

  /*
  Channels:
   A0  -> AN0
   A1  -> AN1
   A4  -> AN16
   B2  -> AN4
   B12 -> DAC1OUT
   B14 -> DAC2OUT
  */

  ADC1_Init();

  /****** Comparadores ******/
  CM1CON = 0;
  CM2CON = 0;
  CM3CON = 0;

  //Configuracoes do DAC
  DAC1CON = 0b1001001010000011;
  DAC2CON = 0b1001001010000011;
  //Referencia em 2V
  BUFCON0 = 2;
  controlMotors(0,0);

  //Set PWM
  ServoPeriod =  PWM3_Init(250,3,1);
  PWM3_Set_Duty(0.1 * ServoPeriod);
  PWM3_Start();


  // Initialize UART module at 9600 bps
  #if PRINT_DEBUG
  UART2_Init(9600);
  Delay_ms(2000);
  UART2_Write_Text("UART Inicializado\n");
  #endif
  //initTimer();
  //Falta inicializar o controle IR. Falta também achar uma biblioteca para ele.
}



void main() 
{
  initRobot();
  controlMotors(0,0);
  //return;
 
  while(REMOTE_CONTROL_PIN)
  {
    if(POWER_BUTTON)
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
  while(REMOTE_CONTROL_PIN);
  delay_ms(1000);
  //PWM3_Set_Duty(0.1*ServoPeriod);
  while(REMOTE_CONTROL_PIN)
  {
    if(POWER_BUTTON)
    {
      delay_ms(20);
      if(POWER_BUTTON)
      {
        controlMotors(0, 0);
        #if PRINT_DEBUG
        UART2_Write_Text("Parou!\n");
        #endif
      }
    }
    else
    {
      seekAndDestroy();

      #if PRINT_DEBUG

      UART2_Write_Text("Seguiu!\n");
      UART2_Write_Text("IR: ");
      ByteToStr(REMOTE_CONTROL_PIN,buffer);
      UART2_Write_Text(buffer);
      UART2_Write_Text("\n");
      #endif
    }
  }
  controlMotors(0,0);
  //UART2_Write_Text("Saiu!!!!!!!!!!!!!!!!\n");
}