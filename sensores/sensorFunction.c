#include "Constantes.h"



float SensorControl (){

    int buffer[255]
    int soma = 0;
    float erro = 0;

    soma = ((-2*RB6_bit) + (3*RA7_bit) + RB5_bit + (-3*RB4_bit) + (2*RB3_bit) + (-4*RA6_bit) + (4*RA3_bit))
    erro = soma/10
    if (erro = 0.1 ){
            UART2_Write_Text("inimigo logo a frente")
            erro = erro*0
            return erro

   }
   if (erro >0.1){
      erro = erro + 0.6
      IntToStr(erro,buffer)
      UART2_Write_Text("Inimigo visto na direita")
      UART2_Write_Text("/n")
      
      if (erro > 1){
         erro = 1
         return erro
      }
      else
         return erro
   
   }
   if erro <0.1){
      erro = erro - 0.6
      IntToStr(erro,buffer)
      UART2_Write_Text(buffer)
      UART2_Write_Text("inimigo visto na esquerda")
      Uart2_Write_Text(/n)
      if (erro > -1){
         erro = -1
         return erro
      }
      else
          return erro


}