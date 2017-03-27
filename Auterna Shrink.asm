
_clamp:
	LNK	#0

;Auterna Shrink.c,48 :: 		double clamp(double value, double min, double max)
	MOV	[W14-10], W0
	MOV	[W14-8], W1
	MOV	W0, [W14-10]
	MOV	W1, [W14-8]
;Auterna Shrink.c,50 :: 		if (value < min) value = min;
	PUSH.D	W12
	PUSH.D	W10
	MOV.D	W12, W2
	MOV.D	W10, W0
	CALL	__Compare_Le_Fp
	CP0	W0
	CLR.B	W0
	BRA GE	L__clamp69
	INC.B	W0
L__clamp69:
	POP.D	W10
	POP.D	W12
	CP0.B	W0
	BRA NZ	L__clamp70
	GOTO	L_clamp0
L__clamp70:
	MOV.D	W12, W10
	GOTO	L_clamp1
L_clamp0:
;Auterna Shrink.c,51 :: 		else if (value > max) value = max;
	PUSH.D	W10
	MOV	[W14-10], W2
	MOV	[W14-8], W3
	MOV.D	W10, W0
	CALL	__Compare_Ge_Fp
	CP0	W0
	CLR.B	W0
	BRA LE	L__clamp71
	INC.B	W0
L__clamp71:
	POP.D	W10
	CP0.B	W0
	BRA NZ	L__clamp72
	GOTO	L_clamp2
L__clamp72:
	MOV	[W14-10], W10
	MOV	[W14-8], W11
L_clamp2:
L_clamp1:
;Auterna Shrink.c,52 :: 		return value;
	MOV.D	W10, W0
;Auterna Shrink.c,53 :: 		}
L_end_clamp:
	ULNK
	RETURN
; end of _clamp

_controlMotors:

;Auterna Shrink.c,63 :: 		void controlMotors(double leftPower, double rightPower)
;Auterna Shrink.c,65 :: 		leftPower = leftPower * LEFT_MOTOR_INVERTER;
;Auterna Shrink.c,66 :: 		rightPower = rightPower * RIGHT_MOTOR_INVERTER * 0.8;
	PUSH.D	W12
	PUSH.D	W10
	MOV.D	W12, W0
	MOV	#0, W2
	MOV	#49024, W3
	CALL	__Mul_FP
	MOV	#52429, W2
	MOV	#16204, W3
	CALL	__Mul_FP
	POP.D	W10
	POP.D	W12
	MOV.D	W0, W12
;Auterna Shrink.c,75 :: 		if (leftPower > 100) leftPower = 100;
	PUSH.D	W12
	PUSH.D	W10
	MOV	#0, W2
	MOV	#17096, W3
	MOV.D	W10, W0
	CALL	__Compare_Ge_Fp
	CP0	W0
	CLR.B	W0
	BRA LE	L__controlMotors74
	INC.B	W0
L__controlMotors74:
	POP.D	W10
	POP.D	W12
	CP0.B	W0
	BRA NZ	L__controlMotors75
	GOTO	L_controlMotors3
L__controlMotors75:
	MOV	#0, W10
	MOV	#17096, W11
L_controlMotors3:
;Auterna Shrink.c,76 :: 		if (leftPower < -100) leftPower = -100;
	PUSH.D	W12
	PUSH.D	W10
	MOV	#0, W2
	MOV	#49864, W3
	MOV.D	W10, W0
	CALL	__Compare_Le_Fp
	CP0	W0
	CLR.B	W0
	BRA GE	L__controlMotors76
	INC.B	W0
L__controlMotors76:
	POP.D	W10
	POP.D	W12
	CP0.B	W0
	BRA NZ	L__controlMotors77
	GOTO	L_controlMotors4
L__controlMotors77:
	MOV	#0, W10
	MOV	#49864, W11
L_controlMotors4:
;Auterna Shrink.c,78 :: 		if (rightPower > 100) rightPower = 100;
	PUSH.D	W12
	PUSH.D	W10
	MOV	#0, W2
	MOV	#17096, W3
	MOV.D	W12, W0
	CALL	__Compare_Ge_Fp
	CP0	W0
	CLR.B	W0
	BRA LE	L__controlMotors78
	INC.B	W0
L__controlMotors78:
	POP.D	W10
	POP.D	W12
	CP0.B	W0
	BRA NZ	L__controlMotors79
	GOTO	L_controlMotors5
L__controlMotors79:
	MOV	#0, W12
	MOV	#17096, W13
L_controlMotors5:
;Auterna Shrink.c,79 :: 		if (rightPower < -100) rightPower = -100;
	PUSH.D	W12
	PUSH.D	W10
	MOV	#0, W2
	MOV	#49864, W3
	MOV.D	W12, W0
	CALL	__Compare_Le_Fp
	CP0	W0
	CLR.B	W0
	BRA GE	L__controlMotors80
	INC.B	W0
L__controlMotors80:
	POP.D	W10
	POP.D	W12
	CP0.B	W0
	BRA NZ	L__controlMotors81
	GOTO	L_controlMotors6
L__controlMotors81:
	MOV	#0, W12
	MOV	#49864, W13
L_controlMotors6:
;Auterna Shrink.c,81 :: 		if (leftPower >= 0)
	PUSH.D	W12
	PUSH.D	W10
	CLR	W2
	CLR	W3
	MOV.D	W10, W0
	CALL	__Compare_Ge_Fp
	CP0	W0
	CLR.B	W0
	BRA LT	L__controlMotors82
	INC.B	W0
L__controlMotors82:
	POP.D	W10
	POP.D	W12
	CP0.B	W0
	BRA NZ	L__controlMotors83
	GOTO	L_controlMotors7
L__controlMotors83:
;Auterna Shrink.c,82 :: 		LEFT_MOTOR = (STOP_V_LEFT + (LEFT_MOTOR_RISE_RATE * leftPower));
	PUSH.D	W12
	MOV	#13107, W0
	MOV	#16275, W1
	MOV.D	W10, W2
	CALL	__Mul_FP
	MOV	#0, W2
	MOV	#17164, W3
	CALL	__AddSub_FP
	CALL	__Float2Longint
	POP.D	W12
	MOV	WREG, DAC1DAT
	GOTO	L_controlMotors8
L_controlMotors7:
;Auterna Shrink.c,84 :: 		LEFT_MOTOR = (STOP_V_LEFT + (LEFT_MOTOR_DOWN_RATE * leftPower));
	PUSH.D	W12
	MOV	#13107, W0
	MOV	#16307, W1
	MOV.D	W10, W2
	CALL	__Mul_FP
	MOV	#0, W2
	MOV	#17164, W3
	CALL	__AddSub_FP
	CALL	__Float2Longint
	POP.D	W12
	MOV	WREG, DAC1DAT
L_controlMotors8:
;Auterna Shrink.c,86 :: 		if (rightPower > 0)
	PUSH.D	W12
	CLR	W2
	CLR	W3
	MOV.D	W12, W0
	CALL	__Compare_Ge_Fp
	CP0	W0
	CLR.B	W0
	BRA LE	L__controlMotors84
	INC.B	W0
L__controlMotors84:
	POP.D	W12
	CP0.B	W0
	BRA NZ	L__controlMotors85
	GOTO	L_controlMotors9
L__controlMotors85:
;Auterna Shrink.c,87 :: 		RIGHT_MOTOR = (STOP_V_RIGHT + (RIGHT_MOTOR_RISE_RATE * rightPower));
	MOV	#13107, W0
	MOV	#16275, W1
	MOV.D	W12, W2
	CALL	__Mul_FP
	MOV	#0, W2
	MOV	#17164, W3
	CALL	__AddSub_FP
	CALL	__Float2Longint
	MOV	WREG, DAC2DAT
	GOTO	L_controlMotors10
L_controlMotors9:
;Auterna Shrink.c,89 :: 		RIGHT_MOTOR = (STOP_V_RIGHT + (RIGHT_MOTOR_DOWN_RATE * rightPower));
	MOV	#13107, W0
	MOV	#16307, W1
	MOV.D	W12, W2
	CALL	__Mul_FP
	MOV	#0, W2
	MOV	#17164, W3
	CALL	__AddSub_FP
	CALL	__Float2Longint
	MOV	WREG, DAC2DAT
L_controlMotors10:
;Auterna Shrink.c,105 :: 		}
L_end_controlMotors:
	RETURN
; end of _controlMotors

_seekAndDestroy:
	LNK	#18

;Auterna Shrink.c,107 :: 		void seekAndDestroy()
;Auterna Shrink.c,110 :: 		int velocidade = 70;
	PUSH	W10
	PUSH	W11
	PUSH	W12
	PUSH	W13
;Auterna Shrink.c,111 :: 		int sum = 0;
;Auterna Shrink.c,113 :: 		sum = (RB3_bit + RB4_bit + RB5_bit + RB6_bit + RB7_bit);
	CLR.B	W1
	BTSC	RB3_bit, BitPos(RB3_bit+0)
	INC.B	W1
	CLR.B	W0
	BTSC	RB4_bit, BitPos(RB4_bit+0)
	INC.B	W0
	ZE	W1, W1
	ZE	W0, W0
	ADD	W1, W0, W1
	CLR.B	W0
	BTSC	RB5_bit, BitPos(RB5_bit+0)
	INC.B	W0
	ZE	W0, W0
	ADD	W1, W0, W1
	CLR.B	W0
	BTSC	RB6_bit, BitPos(RB6_bit+0)
	INC.B	W0
	ZE	W0, W0
	ADD	W1, W0, W1
	CLR.B	W0
	BTSC	RB7_bit, BitPos(RB7_bit+0)
	INC.B	W0
	ZE	W0, W0
	ADD	W1, W0, W0
; sum start address is: 8 (W4)
	MOV	W0, W4
;Auterna Shrink.c,114 :: 		if(sum != 0)
	CP	W0, #0
	BRA NZ	L__seekAndDestroy87
	GOTO	L_seekAndDestroy11
L__seekAndDestroy87:
;Auterna Shrink.c,115 :: 		error = (1000 * RB4_bit + 2000 * RB3_bit + 3000 * RB5_bit + 4000 * RB6_bit + 5000 * RB7_bit)/sum - 3000;
	CLR.B	W0
	BTSC	RB4_bit, BitPos(RB4_bit+0)
	INC.B	W0
	ZE	W0, W1
	MOV	#1000, W0
	MUL.SS	W0, W1, W2
	CLR.B	W0
	BTSC	RB3_bit, BitPos(RB3_bit+0)
	INC.B	W0
	ZE	W0, W1
	MOV	#2000, W0
	MUL.SS	W0, W1, W0
	ADD	W2, W0, W2
	CLR.B	W0
	BTSC	RB5_bit, BitPos(RB5_bit+0)
	INC.B	W0
	ZE	W0, W1
	MOV	#3000, W0
	MUL.SS	W0, W1, W0
	ADD	W2, W0, W2
	CLR.B	W0
	BTSC	RB6_bit, BitPos(RB6_bit+0)
	INC.B	W0
	ZE	W0, W1
	MOV	#4000, W0
	MUL.SS	W0, W1, W0
	ADD	W2, W0, W2
	CLR.B	W0
	BTSC	RB7_bit, BitPos(RB7_bit+0)
	INC.B	W0
	ZE	W0, W1
	MOV	#5000, W0
	MUL.SS	W0, W1, W0
	ADD	W2, W0, W0
	REPEAT	#17
	DIV.S	W0, W4
	MOV	W0, W1
; sum end address is: 8 (W4)
	MOV	#3000, W0
	SUB	W1, W0, W0
	ASR	W0, #15, W1
	SETM	W2
	CALL	__Long2Float
	MOV	W0, [W14+0]
	MOV	W1, [W14+2]
L_seekAndDestroy11:
;Auterna Shrink.c,123 :: 		if(ADC1_READ(0) < 300 || ADC1_READ(4) < 300)
	CLR	W10
	CALL	_ADC1_Read
	MOV	#300, W1
	CP	W0, W1
	BRA GEU	L__seekAndDestroy88
	GOTO	L__seekAndDestroy65
L__seekAndDestroy88:
	MOV	#4, W10
	CALL	_ADC1_Read
	MOV	#300, W1
	CP	W0, W1
	BRA GEU	L__seekAndDestroy89
	GOTO	L__seekAndDestroy64
L__seekAndDestroy89:
	GOTO	L_seekAndDestroy14
L__seekAndDestroy65:
L__seekAndDestroy64:
;Auterna Shrink.c,125 :: 		controlMotors(-100,-100);
	MOV	#0, W12
	MOV	#49864, W13
	MOV	#0, W10
	MOV	#49864, W11
	CALL	_controlMotors
;Auterna Shrink.c,126 :: 		delay_ms(150);
	MOV	#8, W8
	MOV	#41249, W7
L_seekAndDestroy15:
	DEC	W7
	BRA NZ	L_seekAndDestroy15
	DEC	W8
	BRA NZ	L_seekAndDestroy15
	NOP
;Auterna Shrink.c,127 :: 		controlMotors(-100,100);
	MOV	#0, W12
	MOV	#17096, W13
	MOV	#0, W10
	MOV	#49864, W11
	CALL	_controlMotors
;Auterna Shrink.c,128 :: 		delay_ms(200);
	MOV	#11, W8
	MOV	#11309, W7
L_seekAndDestroy17:
	DEC	W7
	BRA NZ	L_seekAndDestroy17
	DEC	W8
	BRA NZ	L_seekAndDestroy17
;Auterna Shrink.c,129 :: 		}
	GOTO	L_seekAndDestroy19
L_seekAndDestroy14:
;Auterna Shrink.c,132 :: 		if(error > -100 && error < 100)
	MOV	#0, W2
	MOV	#49864, W3
	MOV	[W14+0], W0
	MOV	[W14+2], W1
	CALL	__Compare_Ge_Fp
	CP0	W0
	CLR.B	W0
	BRA LE	L__seekAndDestroy90
	INC.B	W0
L__seekAndDestroy90:
	CP0.B	W0
	BRA NZ	L__seekAndDestroy91
	GOTO	L__seekAndDestroy67
L__seekAndDestroy91:
	MOV	#0, W2
	MOV	#17096, W3
	MOV	[W14+0], W0
	MOV	[W14+2], W1
	CALL	__Compare_Le_Fp
	CP0	W0
	CLR.B	W0
	BRA GE	L__seekAndDestroy92
	INC.B	W0
L__seekAndDestroy92:
	CP0.B	W0
	BRA NZ	L__seekAndDestroy93
	GOTO	L__seekAndDestroy66
L__seekAndDestroy93:
L__seekAndDestroy62:
;Auterna Shrink.c,133 :: 		velocidade = 90;
	MOV	#90, W0
	MOV	W0, [W14+8]
	GOTO	L_seekAndDestroy23
;Auterna Shrink.c,132 :: 		if(error > -100 && error < 100)
L__seekAndDestroy67:
L__seekAndDestroy66:
;Auterna Shrink.c,135 :: 		velocidade = 70;
	MOV	#70, W0
	MOV	W0, [W14+8]
L_seekAndDestroy23:
;Auterna Shrink.c,138 :: 		powerR  = velocidade  - error/10.0;
	MOV	#0, W2
	MOV	#16672, W3
	MOV	[W14+0], W0
	MOV	[W14+2], W1
	CALL	__Div_FP
	MOV	W0, [W14+14]
	MOV	W1, [W14+16]
	MOV	[W14+8], W0
	ASR	W0, #15, W1
	SETM	W2
	CALL	__Long2Float
	MOV	[W14+14], W2
	MOV	[W14+16], W3
	CALL	__Sub_FP
;Auterna Shrink.c,139 :: 		powerR = clamp(powerR, -100, 100);
	MOV	#0, W12
	MOV	#49864, W13
	MOV.D	W0, W10
	MOV	#0, W0
	MOV	#17096, W1
	PUSH.D	W0
	CALL	_clamp
	SUB	#4, W15
	MOV	W0, [W14+4]
	MOV	W1, [W14+6]
;Auterna Shrink.c,141 :: 		powerL = velocidade  + error/10.0;
	MOV	#0, W2
	MOV	#16672, W3
	MOV	[W14+0], W0
	MOV	[W14+2], W1
	CALL	__Div_FP
	MOV	W0, [W14+14]
	MOV	W1, [W14+16]
	MOV	[W14+8], W0
	ASR	W0, #15, W1
	SETM	W2
	CALL	__Long2Float
	MOV	[W14+14], W2
	MOV	[W14+16], W3
	CALL	__AddSub_FP
;Auterna Shrink.c,142 :: 		powerL = clamp(powerL, -100, 100);
	MOV	#0, W12
	MOV	#49864, W13
	MOV.D	W0, W10
	MOV	#0, W0
	MOV	#17096, W1
	PUSH.D	W0
	CALL	_clamp
	SUB	#4, W15
;Auterna Shrink.c,144 :: 		controlMotors(powerL, powerR);
	MOV	[W14+4], W12
	MOV	[W14+6], W13
	MOV.D	W0, W10
	CALL	_controlMotors
;Auterna Shrink.c,145 :: 		}
L_seekAndDestroy19:
;Auterna Shrink.c,150 :: 		}
L_end_seekAndDestroy:
	POP	W13
	POP	W12
	POP	W11
	POP	W10
	ULNK
	RETURN
; end of _seekAndDestroy

_initRobot:

;Auterna Shrink.c,152 :: 		void initRobot()
;Auterna Shrink.c,156 :: 		TRISA0_bit = 1; //Borda Esquerda Frente (ANALOG)
	PUSH	W10
	PUSH	W11
	PUSH	W12
	PUSH	W13
	BSET	TRISA0_bit, BitPos(TRISA0_bit+0)
;Auterna Shrink.c,157 :: 		TRISA1_bit = 1; //Borda Direita Frente (ANALOG)
	BSET	TRISA1_bit, BitPos(TRISA1_bit+0)
;Auterna Shrink.c,159 :: 		TRISA4_bit = 1; //Borda Direita Atras  (ANALOG)
	BSET	TRISA4_bit, BitPos(TRISA4_bit+0)
;Auterna Shrink.c,160 :: 		TRISA7_bit = 1; //Estratégia 4
	BSET	TRISA7_bit, BitPos(TRISA7_bit+0)
;Auterna Shrink.c,161 :: 		TRISA.B5 = 1;   //Estratégia 2
	BSET	TRISA, #5
;Auterna Shrink.c,162 :: 		TRISA.B6 = 1;   //Estratégia 3
	BSET	TRISA, #6
;Auterna Shrink.c,166 :: 		AMP1CON  = 0;
	CLR	AMP1CON
;Auterna Shrink.c,167 :: 		TRISB0_bit = 0;  //Pino de UART : TX
	BCLR	TRISB0_bit, BitPos(TRISB0_bit+0)
;Auterna Shrink.c,168 :: 		TRISB1_bit = 0;  //Pino de UART : RX
	BCLR	TRISB1_bit, BitPos(TRISB1_bit+0)
;Auterna Shrink.c,169 :: 		TRISB2_bit = 1;  //Borda Esquerda Atras  (ANALOG)
	BSET	TRISB2_bit, BitPos(TRISB2_bit+0)
;Auterna Shrink.c,170 :: 		TRISB3_bit = 1;  //Oponente Direito - OD
	BSET	TRISB3_bit, BitPos(TRISB3_bit+0)
;Auterna Shrink.c,171 :: 		TRISB4_bit = 1;  //Oponente Diagonal Esquerdo - ODE. Esse pino também é o Secondary OSC. Tomar cuidado nas configs.Funcionando: SOSC Type : Digital e SOSC Power: Low Power.
	BSET	TRISB4_bit, BitPos(TRISB4_bit+0)
;Auterna Shrink.c,172 :: 		TRISB5_bit = 1;  //Oponente Centro - OC
	BSET	TRISB5_bit, BitPos(TRISB5_bit+0)
;Auterna Shrink.c,173 :: 		TRISB6_bit = 1;  //Oponente Esquerdo - OE
	BSET	TRISB6_bit, BitPos(TRISB6_bit+0)
;Auterna Shrink.c,174 :: 		TRISB7_bit = 1;  //Oponente Diagonal Direito - ODD
	BSET	TRISB7_bit, BitPos(TRISB7_bit+0)
;Auterna Shrink.c,175 :: 		TRISB8_bit = 1;  //Pino de I2C : SCL
	BSET	TRISB8_bit, BitPos(TRISB8_bit+0)
;Auterna Shrink.c,176 :: 		TRISB9_bit = 1;  //Pino de I2C : SDA
	BSET	TRISB9_bit, BitPos(TRISB9_bit+0)
;Auterna Shrink.c,177 :: 		TRISB10_bit = 0; //Servo Motor
	BCLR	TRISB10_bit, BitPos(TRISB10_bit+0)
;Auterna Shrink.c,178 :: 		TRISB11_bit = 1; //Start/Stop Button
	BSET	TRISB11_bit, BitPos(TRISB11_bit+0)
;Auterna Shrink.c,179 :: 		TRISB12_bit = 0; //Motor1 (DAC1OUT)
	BCLR	TRISB12_bit, BitPos(TRISB12_bit+0)
;Auterna Shrink.c,180 :: 		TRISB13_bit = 1; //Estratégia 1
	BSET	TRISB13_bit, BitPos(TRISB13_bit+0)
;Auterna Shrink.c,181 :: 		TRISB14_bit = 0; //Motor2 (DAC2OUT)
	BCLR	TRISB14_bit, BitPos(TRISB14_bit+0)
;Auterna Shrink.c,182 :: 		TRISB15_bit = 1; //Controle Infra-Red
	BSET	TRISB15_bit, BitPos(TRISB15_bit+0)
;Auterna Shrink.c,189 :: 		ANSA = 0b0000000000010011;
	MOV	#19, W0
	MOV	WREG, ANSA
;Auterna Shrink.c,195 :: 		ANSB = 0b0101000000000100;
	MOV	#20484, W0
	MOV	WREG, ANSB
;Auterna Shrink.c,207 :: 		ADC1_Init();
	CALL	_ADC1_Init
;Auterna Shrink.c,210 :: 		CM1CON = 0;
	CLR	CM1CON
;Auterna Shrink.c,211 :: 		CM2CON = 0;
	CLR	CM2CON
;Auterna Shrink.c,212 :: 		CM3CON = 0;
	CLR	CM3CON
;Auterna Shrink.c,215 :: 		DAC1CON = 0b1001001010000011;
	MOV	#37507, W0
	MOV	WREG, DAC1CON
;Auterna Shrink.c,216 :: 		DAC2CON = 0b1001001010000011;
	MOV	#37507, W0
	MOV	WREG, DAC2CON
;Auterna Shrink.c,218 :: 		BUFCON0 = 2;
	MOV	#2, W0
	MOV	WREG, BUFCON0
;Auterna Shrink.c,219 :: 		controlMotors(0,0);
	CLR	W12
	CLR	W13
	CLR	W10
	CLR	W11
	CALL	_controlMotors
;Auterna Shrink.c,222 :: 		ServoPeriod =  PWM3_Init(250,3,1);
	MOV	#1, W12
	MOV	#3, W11
	MOV	#250, W10
	CALL	_PWM3_Init
	MOV	W0, _ServoPeriod
;Auterna Shrink.c,223 :: 		PWM3_Set_Duty(0.1 * ServoPeriod);
	CLR	W1
	CALL	__Long2Float
	MOV	#52429, W2
	MOV	#15820, W3
	CALL	__Mul_FP
	CALL	__Float2Longint
	MOV	W0, W10
	CALL	_PWM3_Set_Duty
;Auterna Shrink.c,224 :: 		PWM3_Start();
	CALL	_PWM3_Start
;Auterna Shrink.c,235 :: 		}
L_end_initRobot:
	POP	W13
	POP	W12
	POP	W11
	POP	W10
	RETURN
; end of _initRobot

_main:
	MOV	#2048, W15
	MOV	#6142, W0
	MOV	WREG, 32
	MOV	#1, W0
	MOV	WREG, 52
	MOV	#4, W0
	IOR	68

;Auterna Shrink.c,239 :: 		void main()
;Auterna Shrink.c,241 :: 		initRobot();
	PUSH	W10
	PUSH	W11
	PUSH	W12
	PUSH	W13
	CALL	_initRobot
;Auterna Shrink.c,242 :: 		controlMotors(0,0);
	CLR	W12
	CLR	W13
	CLR	W10
	CLR	W11
	CALL	_controlMotors
;Auterna Shrink.c,315 :: 		}
;Auterna Shrink.c,243 :: 		return;
;Auterna Shrink.c,315 :: 		}
L_end_main:
	POP	W13
	POP	W12
	POP	W11
	POP	W10
L__main_end_loop:
	BRA	L__main_end_loop
; end of _main
