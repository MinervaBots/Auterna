void main() {
  RB15_bit = 0;
  TRISB15_bit = 1;
  UART1_init(9600);
              
  while(1) {
    if(RB15_bit)
      UART1_write_text("Opponent detected");
    else
      UART1_write_text("Undetected");
  }
}