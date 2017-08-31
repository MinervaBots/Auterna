// Teste de serial funcional

void main() {     
    // ANSA = ANSB = 0;        // Configure AN pins as digital
    // C1ON_bit = C2ON_bit = 0;        // Disable comparators
    UART1_Init(9600);               // Initialize UART module at 9600 bps</i>
    Delay_ms(100);                  // Wait for UART module to become stable</i>
    UART1_Write_Text("Start");

    while (1) {                     // Endless loop
          UART1_Write_text("9\n");   // and send data back via UART
    }
}