#include "constantes.h"
#include "myDAC.h"

// a ideia dessa função é gerar um erro para colocar na função de controle do motor.
// o erro gerado é colocado no argumento de angular velocity.

float mySensorControl (){

    char buffer[255];
    int soma = 0;
    float erro = 0;
    //faz uma média entre os sensores. Os pesos escolhidos precisam ser testados
    soma = ((-2*RB6_bit) + (3*RA7_bit) + RB5_bit + (-3*RB4_bit) + (2*RB3_bit) + (-4*RA6_bit) + (4*RA3_bit));
    //o erro dividido por 10 é para gerar um número entre 0.1 e 0.4
    erro = soma/10;
    
    //se o erro for igual a 0.1 significa que o inimigo está a frente
    if (erro == 0.1 ){
            UART2_Write_Text("inimigo logo a frente");
            erro = erro*0;
            return erro;

   }
   // o inimigo se encontra a direita
   if (erro >0.1){
      //somando esse 0.6 aumenta a velocidade do motor para ele sempre tentar funcionar no máximo

      erro = erro  + 0.6;
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
   // inimigo se encontra na esquerda
   if (erro <0.1){
      //somando esse 0.6 aumenta a velocidade do motor para ele sempre tentar funcionar no máximo
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
    //declarando os pinos para digital/analógicos (1= analógico, 0= digital)
    ANSB= 0b110100110000000;
    
    ANSA= 0b000000000000011;
    
    UART2_init(9600);
    
    //declarando os pinos para input/output (1= input, 0 = output)

    TRISB= 0b100100110111111;


    
    //delay inicial da partida
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
                       MotorController(1,Curva_Direita);
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
                   
                   MotorController(1,Curva_Esquerda);
    }
    if(ADC1_Read(0) <1000){
                   int EdgeLeft = ADC1_read(0);
                   IntToStr(EdgeLeft,left);
                   UART2_Write_Text(left);
                   UART2_Write_Text("Sensor de borda esquerda fora da arena");
                   Uart2_Write_Text("/n");

                   MotorController(1,Curva_Direita);

    }
}