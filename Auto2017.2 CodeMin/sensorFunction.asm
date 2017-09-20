
_mySensorControl:
	LNK	#258

;sensorFunction.c,7 :: 		float mySensorControl (){
;sensorFunction.c,10 :: 		int soma = 0;
	PUSH	W10
	PUSH	W11
;sensorFunction.c,11 :: 		float erro = 0;
;sensorFunction.c,13 :: 		soma = ((-2*RB6_bit) + (3*RA7_bit) + RB5_bit + (-3*RB4_bit) + (2*RB3_bit) + (-4*RA6_bit) + (4*RA3_bit));
	CLR.B	W0
	BTSC	RB6_bit, BitPos(RB6_bit+0)
	INC.B	W0
	MOV	#65534, W1
	ZE	W0, W0
	MUL.SS	W1, W0, W2
	CLR.B	W0
	BTSC	RA7_bit, BitPos(RA7_bit+0)
	INC.B	W0
	ZE	W0, W1
	MOV	#3, W0
	MUL.SS	W0, W1, W0
	ADD	W2, W0, W1
	CLR.B	W0
	BTSC	RB5_bit, BitPos(RB5_bit+0)
	INC.B	W0
	ZE	W0, W0
	ADD	W1, W0, W2
	CLR.B	W0
	BTSC	RB4_bit, BitPos(RB4_bit+0)
	INC.B	W0
	MOV	#65533, W1
	ZE	W0, W0
	MUL.SS	W1, W0, W0
	ADD	W2, W0, W1
	CLR.B	W0
	BTSC	RB3_bit, BitPos(RB3_bit+0)
	INC.B	W0
	ZE	W0, W0
	SL	W0, #1, W0
	ADD	W1, W0, W2
	CLR.B	W0
	BTSC	RA6_bit, BitPos(RA6_bit+0)
	INC.B	W0
	MOV	#65532, W1
	ZE	W0, W0
	MUL.SS	W1, W0, W0
	ADD	W2, W0, W1
	CLR.B	W0
	BTSC	RA3_bit, BitPos(RA3_bit+0)
	INC.B	W0
	ZE	W0, W0
	SL	W0, #2, W0
	ADD	W1, W0, W0
;sensorFunction.c,15 :: 		erro = soma/10;
	MOV	#10, W2
	REPEAT	#17
	DIV.S	W0, W2
	ASR	W0, #15, W1
	SETM	W2
	CALL	__Long2Float
; erro start address is: 8 (W4)
	MOV.D	W0, W4
;sensorFunction.c,18 :: 		if (erro == 0.1 ){
	PUSH.D	W4
	MOV	#52429, W2
	MOV	#15820, W3
	CALL	__Compare_Le_Fp
	CP0	W0
	CLR.B	W0
	BRA NZ	L__mySensorControl20
	INC.B	W0
L__mySensorControl20:
	POP.D	W4
	CP0.B	W0
	BRA NZ	L__mySensorControl21
	GOTO	L_mySensorControl0
L__mySensorControl21:
; erro end address is: 8 (W4)
;sensorFunction.c,19 :: 		UART2_Write_Text("inimigo logo a frente");
	MOV	#lo_addr(?lstr1_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,21 :: 		return erro;
	CLR	W0
	CLR	W1
	GOTO	L_end_mySensorControl
;sensorFunction.c,23 :: 		}
L_mySensorControl0:
;sensorFunction.c,25 :: 		if (erro >0.1){
; erro start address is: 8 (W4)
	PUSH.D	W4
	MOV.D	W4, W0
	MOV	#52429, W2
	MOV	#15820, W3
	CALL	__Compare_Ge_Fp
	CP0	W0
	CLR.B	W0
	BRA LE	L__mySensorControl22
	INC.B	W0
L__mySensorControl22:
	POP.D	W4
	CP0.B	W0
	BRA NZ	L__mySensorControl23
	GOTO	L_mySensorControl1
L__mySensorControl23:
;sensorFunction.c,28 :: 		erro = erro  + 0.6;
	MOV	#39322, W0
	MOV	#16153, W1
	MOV.D	W4, W2
	CALL	__AddSub_FP
; erro end address is: 8 (W4)
; erro start address is: 6 (W3)
	MOV	W0, W3
	MOV	W1, W4
;sensorFunction.c,29 :: 		IntToStr(erro,buffer);
	ADD	W14, #0, W2
	MOV	W2, [W14+256]
	PUSH	W3
	PUSH	W4
	CALL	__Float2Longint
	MOV	[W14+256], W1
	MOV	W1, W11
	MOV	W0, W10
	CALL	_IntToStr
	POP	W4
	POP	W3
;sensorFunction.c,30 :: 		UART2_Write_Text("Inimigo visto na direita");
	MOV	#lo_addr(?lstr2_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,31 :: 		UART2_Write_Text("/n");
	MOV	#lo_addr(?lstr3_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,33 :: 		if (erro > 1){
	PUSH	W3
	PUSH	W4
	MOV	W3, W0
	MOV	W4, W1
	MOV	#0, W2
	MOV	#16256, W3
	CALL	__Compare_Ge_Fp
	CP0	W0
	CLR.B	W0
	BRA LE	L__mySensorControl24
	INC.B	W0
L__mySensorControl24:
	POP	W4
	POP	W3
	CP0.B	W0
	BRA NZ	L__mySensorControl25
	GOTO	L_mySensorControl2
L__mySensorControl25:
; erro end address is: 6 (W3)
;sensorFunction.c,35 :: 		return erro;
	MOV	#0, W0
	MOV	#16256, W1
	GOTO	L_end_mySensorControl
;sensorFunction.c,36 :: 		}
L_mySensorControl2:
;sensorFunction.c,38 :: 		return erro;
; erro start address is: 6 (W3)
	MOV	W3, W0
	MOV	W4, W1
; erro end address is: 6 (W3)
	GOTO	L_end_mySensorControl
;sensorFunction.c,40 :: 		}
L_mySensorControl1:
;sensorFunction.c,42 :: 		if (erro <0.1){
; erro start address is: 8 (W4)
	PUSH.D	W4
	MOV.D	W4, W0
	MOV	#52429, W2
	MOV	#15820, W3
	CALL	__Compare_Le_Fp
	CP0	W0
	CLR.B	W0
	BRA GE	L__mySensorControl26
	INC.B	W0
L__mySensorControl26:
	POP.D	W4
	CP0.B	W0
	BRA NZ	L__mySensorControl27
	GOTO	L_mySensorControl4
L__mySensorControl27:
;sensorFunction.c,44 :: 		erro = erro - 0.6;
	MOV	#39322, W2
	MOV	#16153, W3
	MOV.D	W4, W0
	CALL	__Sub_FP
; erro end address is: 8 (W4)
; erro start address is: 4 (W2)
	MOV.D	W0, W2
;sensorFunction.c,45 :: 		UART2_Write_Text(buffer);
	ADD	W14, #0, W0
	MOV	W0, W10
	CALL	_UART2_Write_Text
;sensorFunction.c,46 :: 		UART2_Write_Text("inimigo visto na esquerda");
	MOV	#lo_addr(?lstr4_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,47 :: 		UART2_Write_Text("/n");
	MOV	#lo_addr(?lstr5_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,48 :: 		if (erro > -1){
	MOV.D	W2, W0
	MOV	#0, W2
	MOV	#49024, W3
	CALL	__Compare_Ge_Fp
	CP0	W0
	CLR.B	W0
	BRA LE	L__mySensorControl28
	INC.B	W0
L__mySensorControl28:
; erro end address is: 4 (W2)
	CP0.B	W0
	BRA NZ	L__mySensorControl29
	GOTO	L_mySensorControl5
L__mySensorControl29:
;sensorFunction.c,50 :: 		return erro;
	MOV	#0, W0
	MOV	#49024, W1
	GOTO	L_end_mySensorControl
;sensorFunction.c,51 :: 		}
L_mySensorControl5:
;sensorFunction.c,52 :: 		}
	GOTO	L_mySensorControl6
L_mySensorControl4:
;sensorFunction.c,54 :: 		return erro;
; erro start address is: 8 (W4)
	MOV.D	W4, W0
; erro end address is: 8 (W4)
	GOTO	L_end_mySensorControl
L_mySensorControl6:
;sensorFunction.c,56 :: 		}
L_end_mySensorControl:
	POP	W11
	POP	W10
	ULNK
	RETURN
; end of _mySensorControl

_init_robot:

;sensorFunction.c,58 :: 		void init_robot(){
;sensorFunction.c,60 :: 		ANSB= 0b110100110000000;
	PUSH	W10
	PUSH	W11
	MOV	#27008, W0
	MOV	WREG, ANSB
;sensorFunction.c,62 :: 		ANSA= 0b000000000000011;
	MOV	#3, W0
	MOV	WREG, ANSA
;sensorFunction.c,64 :: 		UART2_init(9600);
	MOV	#9600, W10
	MOV	#0, W11
	CALL	_UART2_Init
;sensorFunction.c,68 :: 		TRISB= 0b100100110111111;
	MOV	#18879, W0
	MOV	WREG, TRISB
;sensorFunction.c,73 :: 		delay_ms(5000);
	MOV	#102, W8
	MOV	#47563, W7
L_init_robot7:
	DEC	W7
	BRA NZ	L_init_robot7
	DEC	W8
	BRA NZ	L_init_robot7
	NOP
;sensorFunction.c,75 :: 		}
L_end_init_robot:
	POP	W11
	POP	W10
	RETURN
; end of _init_robot

_Sniffing:
	LNK	#510

;sensorFunction.c,77 :: 		void Sniffing(){
;sensorFunction.c,81 :: 		if(ADC1_Read(0)&& ADC1_Read(1) > 1000){
	PUSH	W10
	PUSH	W11
	PUSH	W12
	PUSH	W13
	CLR	W10
	CALL	_ADC1_Read
	CP0	W0
	BRA NZ	L__Sniffing32
	GOTO	L__Sniffing18
L__Sniffing32:
	MOV	#1, W10
	CALL	_ADC1_Read
	MOV	#1000, W1
	CP	W0, W1
	BRA GTU	L__Sniffing33
	GOTO	L__Sniffing17
L__Sniffing33:
L__Sniffing16:
;sensorFunction.c,83 :: 		int EdgeRight = ADC1_read(1);
	MOV	#1, W10
	CALL	_ADC1_Read
; EdgeRight start address is: 10 (W5)
	MOV	W0, W5
;sensorFunction.c,84 :: 		int EdgeLeft = ADC1_read(0);
	CLR	W10
	CALL	_ADC1_Read
;sensorFunction.c,86 :: 		IntToStr(EdgeLeft,left);
	ADD	W14, #0, W1
	MOV	W1, W11
	MOV	W0, W10
	CALL	_IntToStr
;sensorFunction.c,87 :: 		IntToStr(EdgeRight,right);
	MOV	#255, W0
	ADD	W14, W0, W0
	MOV	W0, W11
	MOV	W5, W10
; EdgeRight end address is: 10 (W5)
	CALL	_IntToStr
;sensorFunction.c,89 :: 		UART2_Write_Text(left);
	ADD	W14, #0, W0
	MOV	W0, W10
	CALL	_UART2_Write_Text
;sensorFunction.c,90 :: 		UART2_Write_Text("Sensor de borda esquerda dentro da arena");
	MOV	#lo_addr(?lstr6_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,91 :: 		UART2_Write_Text("/n");
	MOV	#lo_addr(?lstr7_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,93 :: 		UART2_Write_Text(right);
	MOV	#255, W0
	ADD	W14, W0, W0
	MOV	W0, W10
	CALL	_UART2_Write_Text
;sensorFunction.c,94 :: 		UART2_Write_Text("Sensor de borda direita dentro da arena");
	MOV	#lo_addr(?lstr8_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,95 :: 		Uart2_Write_Text("/n");
	MOV	#lo_addr(?lstr9_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,97 :: 		if(mySensorControl == 0){
	MOV	#lo_addr(_mySensorControl), W0
	CP	W0, #0
	BRA Z	L__Sniffing34
	GOTO	L_Sniffing12
L__Sniffing34:
;sensorFunction.c,98 :: 		MotorController(1,Curva_Direita);
	MOV	#0, W12
	MOV	#16256, W13
	MOV	#0, W10
	MOV	#16256, W11
	CALL	_MotorController
;sensorFunction.c,99 :: 		}
	GOTO	L_Sniffing13
L_Sniffing12:
;sensorFunction.c,101 :: 		MotorController(1,mySensorControl());
	CALL	_mySensorControl
	MOV.D	W0, W12
	MOV	#0, W10
	MOV	#16256, W11
	CALL	_MotorController
;sensorFunction.c,102 :: 		}
L_Sniffing13:
;sensorFunction.c,81 :: 		if(ADC1_Read(0)&& ADC1_Read(1) > 1000){
L__Sniffing18:
L__Sniffing17:
;sensorFunction.c,106 :: 		if(ADC1_Read(1) <1000){
	MOV	#1, W10
	CALL	_ADC1_Read
	MOV	#1000, W1
	CP	W0, W1
	BRA LTU	L__Sniffing35
	GOTO	L_Sniffing14
L__Sniffing35:
;sensorFunction.c,107 :: 		int EdgeRight = ADC1_read(1);
	MOV	#1, W10
	CALL	_ADC1_Read
;sensorFunction.c,108 :: 		IntToStr(EdgeRight,right);
	MOV	#255, W1
	ADD	W14, W1, W1
	MOV	W1, W11
	MOV	W0, W10
	CALL	_IntToStr
;sensorFunction.c,109 :: 		UART2_Write_Text(right);
	MOV	#255, W0
	ADD	W14, W0, W0
	MOV	W0, W10
	CALL	_UART2_Write_Text
;sensorFunction.c,111 :: 		UART2_Write_Text("Sensor de borda direita fora da arena");
	MOV	#lo_addr(?lstr10_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,112 :: 		Uart2_Write_Text("/n");
	MOV	#lo_addr(?lstr11_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,114 :: 		MotorController(1,Curva_Esquerda);
	MOV	#0, W12
	MOV	#49024, W13
	MOV	#0, W10
	MOV	#16256, W11
	CALL	_MotorController
;sensorFunction.c,115 :: 		}
L_Sniffing14:
;sensorFunction.c,116 :: 		if(ADC1_Read(0) <1000){
	CLR	W10
	CALL	_ADC1_Read
	MOV	#1000, W1
	CP	W0, W1
	BRA LTU	L__Sniffing36
	GOTO	L_Sniffing15
L__Sniffing36:
;sensorFunction.c,117 :: 		int EdgeLeft = ADC1_read(0);
	CLR	W10
	CALL	_ADC1_Read
;sensorFunction.c,118 :: 		IntToStr(EdgeLeft,left);
	ADD	W14, #0, W1
	MOV	W1, W11
	MOV	W0, W10
	CALL	_IntToStr
;sensorFunction.c,119 :: 		UART2_Write_Text(left);
	ADD	W14, #0, W0
	MOV	W0, W10
	CALL	_UART2_Write_Text
;sensorFunction.c,120 :: 		UART2_Write_Text("Sensor de borda esquerda fora da arena");
	MOV	#lo_addr(?lstr12_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,121 :: 		Uart2_Write_Text("/n");
	MOV	#lo_addr(?lstr13_sensorFunction), W10
	CALL	_UART2_Write_Text
;sensorFunction.c,123 :: 		MotorController(1,Curva_Direita);
	MOV	#0, W12
	MOV	#16256, W13
	MOV	#0, W10
	MOV	#16256, W11
	CALL	_MotorController
;sensorFunction.c,125 :: 		}
L_Sniffing15:
;sensorFunction.c,126 :: 		}
L_end_Sniffing:
	POP	W13
	POP	W12
	POP	W11
	POP	W10
	ULNK
	RETURN
; end of _Sniffing
