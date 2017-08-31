#line 1 "C:/Users/rafae/Documents/MinervaBots/tests/MikroC/edge_sensor_read/edge_sensor_read.c"
unsigned adc_value;
char buffer[12];
#line 24 "C:/Users/rafae/Documents/MinervaBots/tests/MikroC/edge_sensor_read/edge_sensor_read.c"
void main() {

 ANSB2_bit = 0;
 ANSB7_bit = 0;

 TRISB7_bit = 0;
 TRISB2_bit = 1;


 ANSB9_bit = 1;


 TRISB14_bit = 0;
 RB14_bit = 1;

 UART1_Init_Advanced(9600,_UART_8BIT_NOPARITY, _UART_ONE_STOPBIT,_UART_HI_SPEED);
 Delay_ms(100);
 UART1_Write_Text("Start");

 while(1) {
 adc_value = ADC1_Read(21);
 intToStr(adc_value, buffer);
 UART1_write_text(buffer);
 UART1_write('\n');
 delay_ms(500);
 }
}
