#line 1 "C:/Users/rafae/Documents/MinervaBots/tests/MikroC/UART/UART.c"


void main() {


 UART1_Init(9600);
 Delay_ms(100);
 UART1_Write_Text("Start");

 while (1) {
 UART1_Write_text("9\n");
 }
}
