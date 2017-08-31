
_main:
	MOV	#2048, W15
	MOV	#6142, W0
	MOV	WREG, 32
	MOV	#1, W0
	MOV	WREG, 52
	MOV	#4, W0
	IOR	68

;opponent_sensor_read.c,1 :: 		void main() {
;opponent_sensor_read.c,2 :: 		RB15_bit = 0;
	PUSH	W10
	PUSH	W11
	BCLR	RB15_bit, BitPos(RB15_bit+0)
;opponent_sensor_read.c,3 :: 		TRISB15_bit = 1;
	BSET	TRISB15_bit, BitPos(TRISB15_bit+0)
;opponent_sensor_read.c,4 :: 		UART1_init(9600);
	MOV	#9600, W10
	MOV	#0, W11
	CALL	_UART1_Init
;opponent_sensor_read.c,6 :: 		while(1) {
L_main0:
;opponent_sensor_read.c,7 :: 		if(RB15_bit)
	BTSS	RB15_bit, BitPos(RB15_bit+0)
	GOTO	L_main2
;opponent_sensor_read.c,8 :: 		UART1_write_text("Opponent detected");
	MOV	#lo_addr(?lstr1_opponent_sensor_read), W10
	CALL	_UART1_Write_Text
	GOTO	L_main3
L_main2:
;opponent_sensor_read.c,10 :: 		UART1_write_text("Undetected");
	MOV	#lo_addr(?lstr2_opponent_sensor_read), W10
	CALL	_UART1_Write_Text
L_main3:
;opponent_sensor_read.c,11 :: 		}
	GOTO	L_main0
;opponent_sensor_read.c,12 :: 		}
L_end_main:
	POP	W11
	POP	W10
L__main_end_loop:
	BRA	L__main_end_loop
; end of _main
