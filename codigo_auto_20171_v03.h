#include <24F16KM202.h>
#device ADC=8
#device ICSP=1
#use delay(crystal=20000000)
#use rs232(UART1, baud=9600, stream=UART_PORT1)

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOIESO                   //Internal External Switch Over mode disabled
#FUSES CKSFSM                   //Clock Switching is enabled, fail Safe clock monitor is enabled
#FUSES NOWINDIS                 //Watch Dog Timer in Window mode
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOPUT                    //No Power Up Timer
#FUSES BORV_LOW                 //Brown-out Reset set to lowest voltage
#FUSES NOMCLR                   //Master Clear pin used for I/O

#use FIXED_IO( B_outputs=PIN_B11,PIN_B10 )

#define PIN_BORDA_ESQUERDA      PIN_A0
#define PIN_BORDA_DIREITA       PIN_A1

#define PIN_OPONENTE_DIR        PIN_B3
#define PIN_OPONENTE_DIAG_ESQ   PIN_B4
#define PIN_OPONENTE_CENTRAL    PIN_B5
#define PIN_OPONENTE_ESQ        PIN_B6
#define PIN_OPONENTE_DIAG_DIR   PIN_B7
#define PIN_MOTOR_ESQ           PIN_B11
#define PIN_MOTOR_DIR           PIN_B12





