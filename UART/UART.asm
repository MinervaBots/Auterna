
_main:
	MOV	#2048, W15
	MOV	#6142, W0
	MOV	WREG, 32
	MOV	#1, W0
	MOV	WREG, 52
	MOV	#4, W0
	IOR	68

;UART.c,3 :: 		void main() {
;UART.c,6 :: 		UART1_Init(9600);               // Initialize UART module at 9600 bps</i>
	PUSH	W10
	PUSH	W11
	MOV	#9600, W10
	MOV	#0, W11
	CALL	_UART1_Init
;UART.c,7 :: 		Delay_ms(100);                  // Wait for UART module to become stable</i>
	MOV	#3, W8
	MOV	#2261, W7
L_main0:
	DEC	W7
	BRA NZ	L_main0
	DEC	W8
	BRA NZ	L_main0
;UART.c,8 :: 		UART1_Write_Text("Start");
	MOV	#lo_addr(?lstr1_UART), W10
	CALL	_UART1_Write_Text
;UART.c,10 :: 		while (1) {                     // Endless loop
L_main2:
;UART.c,11 :: 		UART1_Write_text("9\n");   // and send data back via UART
	MOV	#lo_addr(?lstr2_UART), W10
	CALL	_UART1_Write_Text
;UART.c,12 :: 		}
	GOTO	L_main2
;UART.c,13 :: 		}
L_end_main:
	POP	W11
	POP	W10
L__main_end_loop:
	BRA	L__main_end_loop
; end of _main
