
_main:
	MOV	#2048, W15
	MOV	#6142, W0
	MOV	WREG, 32
	MOV	#1, W0
	MOV	WREG, 52
	MOV	#4, W0
	IOR	68

;edge_sensor_read.c,24 :: 		void main() {
;edge_sensor_read.c,26 :: 		ANSB2_bit = 0;
	PUSH	W10
	PUSH	W11
	PUSH	W12
	PUSH	W13
	BCLR	ANSB2_bit, BitPos(ANSB2_bit+0)
;edge_sensor_read.c,27 :: 		ANSB7_bit = 0;
	BCLR	ANSB7_bit, BitPos(ANSB7_bit+0)
;edge_sensor_read.c,29 :: 		TRISB7_bit = 0;
	BCLR	TRISB7_bit, BitPos(TRISB7_bit+0)
;edge_sensor_read.c,30 :: 		TRISB2_bit = 1;
	BSET	TRISB2_bit, BitPos(TRISB2_bit+0)
;edge_sensor_read.c,33 :: 		ANSB9_bit = 1;
	BSET	ANSB9_bit, BitPos(ANSB9_bit+0)
;edge_sensor_read.c,36 :: 		TRISB14_bit = 0;
	BCLR	TRISB14_bit, BitPos(TRISB14_bit+0)
;edge_sensor_read.c,37 :: 		RB14_bit = 1;
	BSET	RB14_bit, BitPos(RB14_bit+0)
;edge_sensor_read.c,39 :: 		UART1_Init_Advanced(9600,_UART_8BIT_NOPARITY, _UART_ONE_STOPBIT,_UART_HI_SPEED);
	CLR	W13
	CLR	W12
	MOV	#9600, W10
	MOV	#0, W11
	MOV	#1, W0
	PUSH	W0
	CALL	_UART1_Init_Advanced
	SUB	#2, W15
;edge_sensor_read.c,40 :: 		Delay_ms(100);                  // Wait for UART module to stabilize
	MOV	#3, W8
	MOV	#2261, W7
L_main0:
	DEC	W7
	BRA NZ	L_main0
	DEC	W8
	BRA NZ	L_main0
;edge_sensor_read.c,41 :: 		UART1_Write_Text("Start");
	MOV	#lo_addr(?lstr1_edge_sensor_read), W10
	CALL	_UART1_Write_Text
;edge_sensor_read.c,43 :: 		while(1) {
L_main2:
;edge_sensor_read.c,44 :: 		adc_value = ADC1_Read(21);
	MOV	#21, W10
	CALL	_ADC1_Read
	MOV	W0, _adc_value
;edge_sensor_read.c,45 :: 		intToStr(adc_value, buffer);
	MOV	#lo_addr(_buffer), W11
	MOV	W0, W10
	CALL	_IntToStr
;edge_sensor_read.c,46 :: 		UART1_write_text(buffer);
	MOV	#lo_addr(_buffer), W10
	CALL	_UART1_Write_Text
;edge_sensor_read.c,47 :: 		UART1_write('\n');
	MOV	#10, W10
	CALL	_UART1_Write
;edge_sensor_read.c,48 :: 		delay_ms(500);
	MOV	#11, W8
	MOV	#11309, W7
L_main4:
	DEC	W7
	BRA NZ	L_main4
	DEC	W8
	BRA NZ	L_main4
;edge_sensor_read.c,49 :: 		}
	GOTO	L_main2
;edge_sensor_read.c,50 :: 		}
L_end_main:
	POP	W13
	POP	W12
	POP	W11
	POP	W10
L__main_end_loop:
	BRA	L__main_end_loop
; end of _main
