unsigned adc_value;
char buffer[12];

/*char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}*/

void main() {
  // Configura pinos seriais como digitais
  ANSB2_bit = 0;
  ANSB7_bit = 0;
  
  TRISB7_bit = 0;
  TRISB2_bit = 1;
  
  // Configura pino do sensor de borda como analógico
  ANSB9_bit = 1;
  
  // Configura pino para gerar sinal lógico alto
  TRISB14_bit = 0;
  RB14_bit = 1;
  
  UART1_Init_Advanced(9600,_UART_8BIT_NOPARITY, _UART_ONE_STOPBIT,_UART_HI_SPEED);
  Delay_ms(100);                  // Wait for UART module to stabilize
  UART1_Write_Text("Start");
  
  while(1) {
    adc_value = ADC1_Read(21);
    intToStr(adc_value, buffer);
    UART1_write_text(buffer);
    UART1_write('\n');
    delay_ms(500);
  }
}