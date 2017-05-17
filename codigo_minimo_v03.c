#include <codigo_auto_20171_v03.h>

#define PERIODO 255 //periodo para o pwm
#define DELAY_RAMPA 100 //delay para rampa de aceleração, em micro segundos

double PWM_ATUAL_ESQ = 127;
double PWM_ATUAL_DIR = 127;
int LIGADO = 0;

char COMANDO_BT;

void INIT_ROBOT()
{
   //inicializa os registradores do interrupt
   ext_int_edge(L_TO_H); //define a mudança de estado na subida low to high (ou high to low, caso H_TO_L)
   enable_interrupts(INT_EXT2); //habilita interrupção pela porta de int externo 2 -- RA06 -- Porta 20
   enable_interrupts(INTR_GLOBAL); //habilita interrupções gerais
   
   
   //configura as portas RA0(porta 2) | RA1(porta 3)|
   //--------------------- borda Esq -|- borda Dir -|
   setup_adc_ports(sAN0 | sAN1, VSS_VDD);
   //OBSERVAÇÃO IMPORTANTE: CHECAR EMPIRICAMENTE SE REFERENCIAR A TENSÃO A PARTIR DE VDD FARÁ O PIC NÃO CONSEGUIR LER OS VALORES CORRETAMENTE, CASO O SENSOR RETORNE UMA TENSÃO MAIOR QUE 3.3 VOLTS
   setup_adc(ADC_CLOCK | ADC_TAD_MUL_0);


   //inicializa os registradores CCP para o PWM
   setup_ccp2(CCP_PWM);  // Configura CCP2 como PWM --- RB11 --- Porta 22
   set_timer_period_ccp2(PERIODO); //seta o período do módulo ccp2
   setup_ccp3(CCP_PWM);  // Configura CCP3 como PWM --- RB10 --- Porta 21
   set_timer_period_ccp3(PERIODO); //seta o período do módulo ccp3
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
         set_pwm2_duty(256 - ACELERACAO);
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
         set_pwm2_duty(256 - ACELERACAO);
      }
      
      PWM_ATUAL_ESQ = LEFT_POWER;//o valor do pwm do motor esquerdo é atualizado
   }
   
   if(RIGHT_POWER > PWM_ATUAL_DIR) //caso o motor direito tenha que aumentar a velocidade
   {
      for(int ACELERACAO = PWM_ATUAL_DIR+1; ACELERACAO <= RIGHT_POWER; ACELERACAO++)
      {
         delay_us(DELAY_RAMPA);
         set_pwm3_duty(256 - ACELERACAO);
      }
      
      PWM_ATUAL_DIR = RIGHT_POWER;//o valor do pwm do motor direito é atualizado
   }
   
   else if(RIGHT_POWER <= PWM_ATUAL_DIR) //caso o motor direito tenha que diminuir a velocidade
   {
      for(int ACELERACAO = PWM_ATUAL_DIR-1; ACELERACAO >= LEFT_POWER; ACELERACAO--)
      {
         delay_us(DELAY_RAMPA);
         set_pwm3_duty(256 - ACELERACAO);
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

   STAR_STRATEGY(BORDA_ESQUERDA, BORDA_DIREITA, OPONENTE_ESQ, OPONENTE_DIR, OPONENTE_CENTRAL, OPONENTE_DIAG_ESQ, OPONENTE_DIAG_DIR);
}

// l -- ligar
// d -- desligar
// 1 -- estratégia 1
// 2 -- estratégia 2
// 3 -- estratégia 3
// 4 -- estratégia 4

void main()
{
   INIT_ROBOT();
   while (LIGADO)
   {
      GET_SENSORS();
   }
}
