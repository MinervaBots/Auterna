#include <codigo_auto_20171_v03.h>

#define DELAY_RAMPA 100 //delay para rampa de aceleração, em micro segundos

//os valores para as constantes do primeiro DAC(right) e para o segundo(left)
#define DAC_RIGHT_ON 1  //RB12
#define DAC_RIGHT    1

#define DAC_LEFT_ON  2  //RB14
#define DAC_LEFT     2

double PWM_ATUAL_ESQ = 127;
double PWM_ATUAL_DIR = 127;
int LIGADO = 0;

char COMANDO_BT = 0;
int ESTRATEGIA = 1;

void INIT_ROBOT()
{
   //inicializa os registradores do interrupt
   enable_interrupts(INT_RDA);
   enable_interrupts(INTR_GLOBAL);
   
   
   //configura as portas RA0(porta 2) | RA1(porta 3)|
   //--------------------- borda Esq -|- borda Dir -|
   setup_adc_ports(sAN0 | sAN1, VSS_VDD);
   //OBSERVAÇÃO IMPORTANTE: CHECAR EMPIRICAMENTE SE REFERENCIAR A TENSÃO A PARTIR DE VDD FARÁ O PIC NÃO CONSEGUIR LER OS VALORES CORRETAMENTE, CASO O SENSOR RETORNE UMA TENSÃO MAIOR QUE 3.3 VOLTS
   setup_adc(ADC_CLOCK | ADC_TAD_MUL_0);


   setup_dac(DAC_RIGHT_ON, DAC_ON | DAC_OUTPUT | DAC_REF_VDD); //habilita o módulo DAC, a saída DAC e o valor de referência de tensão para o DAC
   setup_dac(DAC_LEFT_ON, DAC_ON | DAC_OUTPUT | DAC_REF_VDD);
}

void CONTROL_MOTORS(double LEFT_POWER, double RIGHT_POWER)
{
   //o "256 - " é usado para normalizar o valor, já que sem a normalização o valor de maior tensão seria 1 e o menor 256.
   //com a normalização, o maior volta para o senso comum, sendo 255 e o menor 0.
   if(LEFT_POWER > PWM_ATUAL_ESQ) //caso o motor esquerdo tenha que aumentar a velocidade
   {
      for(int ACELERACAO = PWM_ATUAL_ESQ+1; ACELERACAO <= LEFT_POWER; ACELERACAO++)
      {
         delay_us(DELAY_RAMPA);
         //o pwm será setado para valores maiores a uma unidade do valor anterior, até alcançar a velocidade máxima
         //o valor a ser incrementado poderá ser alterado depois de testes
         dac_write(DAC_LEFT, ACELERACAO);
         //o "256 - " é usado para normalizar o valor, já que sem a normalização o valor de maior tensão seria 1 e o menor 256.
         //com a normalização, o maior volta para o senso comum, sendo 255 e o menor 0.
      }
      
      PWM_ATUAL_ESQ = LEFT_POWER;//o valor do pwm do motor esquerdo é atualizado
   }
   
   else if(LEFT_POWER <= PWM_ATUAL_ESQ) //caso o motor esquerdo tenha que diminuir a velocidade
   {
      for(int ACELERACAO = PWM_ATUAL_ESQ-1; ACELERACAO >= LEFT_POWER; ACELERACAO--) 
      {
         delay_us(DELAY_RAMPA);
         //o pwm será setado para valores menores a uma unidade do valor anterior, até alcançar a velocidade mínimo
         //o valor a ser decrementado poderá ser alterado depois de testes
         dac_write(DAC_LEFT, ACELERACAO);
      }
      
      PWM_ATUAL_ESQ = LEFT_POWER;//o valor do pwm do motor esquerdo é atualizado
   }
   
   if(RIGHT_POWER > PWM_ATUAL_DIR) //caso o motor direito tenha que aumentar a velocidade
   {
      for(int ACELERACAO = PWM_ATUAL_DIR+1; ACELERACAO <= RIGHT_POWER; ACELERACAO++)
      {
         delay_us(DELAY_RAMPA);
         dac_write(DAC_RIGHT, ACELERACAO);
      }
      
      PWM_ATUAL_DIR = RIGHT_POWER;//o valor do pwm do motor direito é atualizado
   }
   
   else if(RIGHT_POWER <= PWM_ATUAL_DIR) //caso o motor direito tenha que diminuir a velocidade
   {
      for(int ACELERACAO = PWM_ATUAL_DIR-1; ACELERACAO >= LEFT_POWER; ACELERACAO--)
      {
         delay_us(DELAY_RAMPA);
         dac_write(DAC_RIGHT, ACELERACAO);
      }
      
      PWM_ATUAL_DIR = RIGHT_POWER;//o valor do pwm do motor direito é atualizado
   }
}

void STAR_STRATEGY(int BORDA_ESQUERDA, int BORDA_DIREITA, int OPONENTE_ESQ, int OPONENTE_DIR, int OPONENTE_CENTRAL, int OPONENTE_DIAG_ESQ, int OPONENTE_DIAG_DIR)
{  
   if(BORDA_ESQUERDA >= 70)//70 é um valor hipotético que acionaria o sensor de borda, valor real a ser medido e testa com a arena
   {
      CONTROL_MOTORS(0, 255);//caso borda esquerda detecte, gira em torno do próprio eixo
      delay_ms(150);//tempo hipotético que o auto levaria para rodar no próprio eixo
      CONTROL_MOTORS(127, 127);
   }
   
   else if(BORDA_DIREITA >= 70)//70 é um valor hipotético que acionaria o sensor de borda, valor real a ser medido e testa com a arena
   {
      CONTROL_MOTORS(255, 0);//caso borda direita detecte, gira em torno do próprio eixo
      delay_ms(150);
      CONTROL_MOTORS(127, 127);//após 150ms, os motores param
   }
   
   //else if comentado pois coincide com a rotina padrão da estratégia, sendo desnecessário tal redundância
//!   else if(OPONENTE_CENTRAL)
//!   {
//!      CONTROL_MOTORS(255, 255);//se o oponente for detetado pelo sensor central, velocidade máxima para frente
//!   }
   
   else if(OPONENTE_ESQ | OPONENTE_DIAG_ESQ) 
   {
      CONTROL_MOTORS(190, 255);//se o oponente for detectado por um dos sensores esquerdos, faz uma curva não muito fechada para esquerda
   }
   
   else if(OPONENTE_DIR | OPONENTE_DIAG_DIR)
   {
      CONTROL_MOTORS(255, 190);//se o oponente for detectado por um dos sensores direitos, faz uma curva não muito fechada para direita
   }
   
   else
   {
      //rotina padrão da estratégia, caso nenhum dos sensores seja acionado
      CONTROL_MOTORS(255, 255);
   }
}

void ESTRATEGIA_GIRO_NO_EIXO(int BORDA_ESQUERDA, int BORDA_DIREITA, int OPONENTE_ESQ, int OPONENTE_DIR, int OPONENTE_CENTRAL, int OPONENTE_DIAG_ESQ, int OPONENTE_DIAG_DIR)
{
    if(OPONENTE_ESQ | OPONENTE_DIAG_ESQ) 
    {
      CONTROL_MOTORS(190, 255); //se o oponente for detectado por um dos sensores esquerdos, faz uma curva nao muito fechada para esquerda
    }
    
    else if(OPONENTE_CENTRAL)
    {
      CONTROL_MOTORS(255, 255); //se o oponente for detetado pelo sensor central, velocidade maxima para frente
    }
    
    else if(OPONENTE_DIR | OPONENTE_DIAG_DIR)
    {
        CONTROL_MOTORS(255, 190); //se o oponente for detectado por um dos sensores direitos, faz uma curva nao muito fechada para direita
    }
   
    else
    { 
        CONTROL_MOTORS(0, 255); //rotina padrao da estrategia, caso nenhum dos sensores seja acionado
    }
    //os valores passados a funcao CONTROL_MOTORS sao hipoteticos, ainda precisam ser testados na arena
}

void ESTRATEGIA_OLE(int BORDA_ESQUERDA, int BORDA_DIREITA, int OPONENTE_ESQ, int OPONENTE_DIR, int OPONENTE_CENTRAL, int OPONENTE_DIAG_ESQ, int OPONENTE_DIAG_DIR)
{
    CONTROL_MOTORS(0, 0);
    STAR_STRATEGY(BORDA_ESQUERDA, BORDA_DIREITA, OPONENTE_ESQ, OPONENTE_DIR, OPONENTE_CENTRAL, OPONENTE_DIAG_ESQ, OPONENTE_DIAG_DIR);
}

void ESTRATEGIA_CURVA_CEGA(int BORDA_ESQUERDA, int BORDA_DIREITA, int OPONENTE_ESQ, int OPONENTE_DIR, int OPONENTE_CENTRAL, int OPONENTE_DIAG_ESQ, int OPONENTE_DIAG_DIR)
{
    CONTROL_MOTORS(255, 190); //faz uma curva nao muito fechada para direita
    STAR_STRATEGY(BORDA_ESQUERDA, BORDA_DIREITA, OPONENTE_ESQ, OPONENTE_DIR, OPONENTE_CENTRAL, OPONENTE_DIAG_ESQ, OPONENTE_DIAG_DIR);
}

void GET_SENSORS()
{
   set_adc_channel(0);//seleciona a porta analógica que será usada em seguida. No caso, 0 pois se trata da porta AN0.
   delay_us(10);//delay recomendado pelo compilador
   
   int BORDA_ESQUERDA = read_adc();//lê o sensor de borda esq e armazena
   
   set_adc_channel(1);//seleciona a porta analógica que será usada em seguida. No caso, 1 pois se trata da porta AN1.
   delay_us(10);//delay recomendado pelo compilador
   
   int BORDA_DIREITA = read_adc();//lê o sensor de borda dir e armazena
   
   //lê e armazena os dados dos sensores de oponente
   int OPONENTE_ESQ = input(PIN_OPONENTE_ESQ);
   int OPONENTE_DIR = input(PIN_OPONENTE_DIR);
   int OPONENTE_CENTRAL = input(PIN_OPONENTE_CENTRAL);
   int OPONENTE_DIAG_ESQ = input(PIN_OPONENTE_DIAG_ESQ);
   int OPONENTE_DIAG_DIR = input(PIN_OPONENTE_DIAG_DIR);
   
   //chama a estratégia de acordo com o comando dado por BT
   switch(ESTRATEGIA)
   {
      case 1 :
         STAR_STRATEGY(BORDA_ESQUERDA, BORDA_DIREITA, OPONENTE_ESQ, OPONENTE_DIR, OPONENTE_CENTRAL, OPONENTE_DIAG_ESQ, OPONENTE_DIAG_DIR);
         break;
      case 2 :
         ESTRATEGIA_GIRO_NO_EIXO(BORDA_ESQUERDA, BORDA_DIREITA, OPONENTE_ESQ, OPONENTE_DIR, OPONENTE_CENTRAL, OPONENTE_DIAG_ESQ, OPONENTE_DIAG_DIR);
         break;
      case 3 :
         ESTRATEGIA_OLE(BORDA_ESQUERDA, BORDA_DIREITA, OPONENTE_ESQ, OPONENTE_DIR, OPONENTE_CENTRAL, OPONENTE_DIAG_ESQ, OPONENTE_DIAG_DIR);
         break;
      case 4 :
         ESTRATEGIA_CURVA_CEGA(BORDA_ESQUERDA, BORDA_DIREITA, OPONENTE_ESQ, OPONENTE_DIR, OPONENTE_CENTRAL, OPONENTE_DIAG_ESQ, OPONENTE_DIAG_DIR);
         break;
   }
}

// l -- ligar
// d -- desligar
// 1 -- estratégia 1
// 2 -- estratégia 2
// 3 -- estratégia 3
// 4 -- estratégia 4

#INT_RDA
void  rda_isr(void) 
{
   //interrupt caso um comando seja dado por BT
   disable_interrupts(INTR_GLOBAL);
   COMANDO_BT = getch(); //armazena o comando recebido no pino rx do uart1
   
   //separa os comandos em uma variável que selecionará as estratégias, e outra que ligará e desligará o robô
   switch(COMANDO_BT)
   {
      case "l" :
         printf("LIGOU!");
         delay_ms(5000); //delay para o início da luta
         LIGADO = 1;
         break;
      case "d" :
         printf("DESLIGOU!");
         LIGADO = 0;
         break;
      case "1" :
         printf("Estratégia 1 selecionada");
         ESTRATEGIA = 1;
         break;
      case "2" :
         printf("Estratégia 2 selecionada");
         ESTRATEGIA = 2;
         break;
      case "3" :
         printf("Estratégia 3 selecionada");
         ESTRATEGIA = 3;
         break;
      case "4" :
         printf("Estratégia 4 selecionada");
         ESTRATEGIA = 4;
         break;
      default :
         printf("Comando nao identificado");
         break;
   }
   
      clear_interrupt(INT_RDA);//zera a flag do interrupt
      enable_interrupts(INTR_GLOBAL);
}

void main()
{
   INIT_ROBOT();
   printf("Digite '1', '2', '3', '4' para a selecao da estrategia\n");
   printf("1 - Star\n");
   printf("2 - giro\n");
   printf("3 - ole\n");
   printf("4 - curva\n");
   printf("Digite 'l' ou 'd' para ligar ou desligar\n");
   while (LIGADO)
   {
      GET_SENSORS();
   }
}
