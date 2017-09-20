
_myDAC1_init:

;myDAC.c,3 :: 		void myDAC1_init(unsigned int reference) {
;myDAC.c,5 :: 		DACSIDL_DAC1CON_bit = 0;
	BCLR	DACSIDL_DAC1CON_bit, BitPos(DACSIDL_DAC1CON_bit+0)
;myDAC.c,6 :: 		DACSLP_DAC1CON_bit = 1;
	BSET	DACSLP_DAC1CON_bit, BitPos(DACSLP_DAC1CON_bit+0)
;myDAC.c,7 :: 		DACFM_DAC1CON_bit = 0;
	BCLR	DACFM_DAC1CON_bit, BitPos(DACFM_DAC1CON_bit+0)
;myDAC.c,8 :: 		SRDIS_DAC1CON_bit = 1;
	BSET	SRDIS_DAC1CON_bit, BitPos(SRDIS_DAC1CON_bit+0)
;myDAC.c,9 :: 		DACTRIG_DAC1CON_bit = 0;
	BCLR	DACTRIG_DAC1CON_bit, BitPos(DACTRIG_DAC1CON_bit+0)
;myDAC.c,10 :: 		DACOE_DAC1CON_bit = 1;
	BSET	DACOE_DAC1CON_bit, BitPos(DACOE_DAC1CON_bit+0)
;myDAC.c,12 :: 		DACTSEL_4_DAC1CON_bit = 0;
	BCLR	DACTSEL_4_DAC1CON_bit, BitPos(DACTSEL_4_DAC1CON_bit+0)
;myDAC.c,13 :: 		DACTSEL_3_DAC1CON_bit = 0;
	BCLR	DACTSEL_3_DAC1CON_bit, BitPos(DACTSEL_3_DAC1CON_bit+0)
;myDAC.c,14 :: 		DACTSEL_2_DAC1CON_bit = 0;
	BCLR	DACTSEL_2_DAC1CON_bit, BitPos(DACTSEL_2_DAC1CON_bit+0)
;myDAC.c,15 :: 		DACTSEL_1_DAC1CON_bit = 0;
	BCLR	DACTSEL_1_DAC1CON_bit, BitPos(DACTSEL_1_DAC1CON_bit+0)
;myDAC.c,16 :: 		DACTSEL_0_DAC1CON_bit = 0;
	BCLR	DACTSEL_0_DAC1CON_bit, BitPos(DACTSEL_0_DAC1CON_bit+0)
;myDAC.c,18 :: 		DACREF_0_DAC1CON_bit = 1;
	BSET	DACREF_0_DAC1CON_bit, BitPos(DACREF_0_DAC1CON_bit+0)
;myDAC.c,19 :: 		DACREF_1_DAC1CON_bit = 1;
	BSET	DACREF_1_DAC1CON_bit, BitPos(DACREF_1_DAC1CON_bit+0)
;myDAC.c,21 :: 		BUFCON0 = reference;  // Referência interna base (BGBUF1)é 1 V
	MOV	W10, BUFCON0
;myDAC.c,23 :: 		DACEN_DAC1CON_bit = 1;  // Enable DAC1 module
	BSET	DACEN_DAC1CON_bit, BitPos(DACEN_DAC1CON_bit+0)
;myDAC.c,24 :: 		}
L_end_myDAC1_init:
	RETURN
; end of _myDAC1_init

_myDAC1_write:

;myDAC.c,26 :: 		void myDAC1_write(uint8_t value) {
;myDAC.c,27 :: 		DAC1DAT = value;
	ZE	W10, W0
	MOV	WREG, DAC1DAT
;myDAC.c,28 :: 		}
L_end_myDAC1_write:
	RETURN
; end of _myDAC1_write

_myDAC2_init:

;myDAC.c,30 :: 		void myDAC2_init(unsigned int reference) {
;myDAC.c,32 :: 		DACSIDL_DAC2CON_bit = 0;
	BCLR	DACSIDL_DAC2CON_bit, BitPos(DACSIDL_DAC2CON_bit+0)
;myDAC.c,33 :: 		DACSLP_DAC2CON_bit = 1;
	BSET	DACSLP_DAC2CON_bit, BitPos(DACSLP_DAC2CON_bit+0)
;myDAC.c,34 :: 		DACFM_DAC2CON_bit = 0;
	BCLR	DACFM_DAC2CON_bit, BitPos(DACFM_DAC2CON_bit+0)
;myDAC.c,35 :: 		SRDIS_DAC2CON_bit = 1;
	BSET	SRDIS_DAC2CON_bit, BitPos(SRDIS_DAC2CON_bit+0)
;myDAC.c,36 :: 		DACTRIG_DAC2CON_bit = 0;
	BCLR	DACTRIG_DAC2CON_bit, BitPos(DACTRIG_DAC2CON_bit+0)
;myDAC.c,37 :: 		DACOE_DAC2CON_bit = 1;
	BSET	DACOE_DAC2CON_bit, BitPos(DACOE_DAC2CON_bit+0)
;myDAC.c,39 :: 		DACTSEL_4_DAC2CON_bit = 0;
	BCLR	DACTSEL_4_DAC2CON_bit, BitPos(DACTSEL_4_DAC2CON_bit+0)
;myDAC.c,40 :: 		DACTSEL_3_DAC2CON_bit = 0;
	BCLR	DACTSEL_3_DAC2CON_bit, BitPos(DACTSEL_3_DAC2CON_bit+0)
;myDAC.c,41 :: 		DACTSEL_2_DAC2CON_bit = 0;
	BCLR	DACTSEL_2_DAC2CON_bit, BitPos(DACTSEL_2_DAC2CON_bit+0)
;myDAC.c,42 :: 		DACTSEL_1_DAC2CON_bit = 0;
	BCLR	DACTSEL_1_DAC2CON_bit, BitPos(DACTSEL_1_DAC2CON_bit+0)
;myDAC.c,43 :: 		DACTSEL_0_DAC2CON_bit = 0;
	BCLR	DACTSEL_0_DAC2CON_bit, BitPos(DACTSEL_0_DAC2CON_bit+0)
;myDAC.c,45 :: 		DACREF_0_DAC2CON_bit = 1;
	BSET	DACREF_0_DAC2CON_bit, BitPos(DACREF_0_DAC2CON_bit+0)
;myDAC.c,46 :: 		DACREF_1_DAC2CON_bit = 1;
	BSET	DACREF_1_DAC2CON_bit, BitPos(DACREF_1_DAC2CON_bit+0)
;myDAC.c,48 :: 		BUFCON0 = reference;  // Referência interna base (BGBUF1)é 1 V
	MOV	W10, BUFCON0
;myDAC.c,50 :: 		DACEN_DAC2CON_bit = 1;  // Enable DAC2 module
	BSET	DACEN_DAC2CON_bit, BitPos(DACEN_DAC2CON_bit+0)
;myDAC.c,51 :: 		}
L_end_myDAC2_init:
	RETURN
; end of _myDAC2_init

_myDAC2_write:

;myDAC.c,53 :: 		void myDAC2_write(uint8_t value) {
;myDAC.c,54 :: 		DAC2DAT = value;
	ZE	W10, W0
	MOV	WREG, DAC2DAT
;myDAC.c,55 :: 		}
L_end_myDAC2_write:
	RETURN
; end of _myDAC2_write

_MotorController:
	LNK	#20

;myDAC.c,57 :: 		void MotorController(float linear,float angular){
;myDAC.c,59 :: 		float right = (linear + angular)/2;
	PUSH	W10
	PUSH	W11
	PUSH.D	W12
	PUSH.D	W10
	MOV.D	W10, W0
	MOV.D	W12, W2
	CALL	__AddSub_FP
	MOV	#0, W2
	MOV	#16384, W3
	CALL	__Div_FP
	POP.D	W10
	POP.D	W12
	MOV	W0, [W14+0]
	MOV	W1, [W14+2]
;myDAC.c,60 :: 		float left = (linear - angular)/2;
	MOV.D	W12, W2
	MOV.D	W10, W0
	CALL	__Sub_FP
	MOV	#0, W2
	MOV	#16384, W3
	CALL	__Div_FP
	MOV	W0, [W14+4]
	MOV	W1, [W14+6]
;myDAC.c,62 :: 		float rightPWM = 127 + 127*right;
	MOV	#0, W0
	MOV	#17150, W1
	MOV	[W14+0], W2
	MOV	[W14+2], W3
	CALL	__Mul_FP
	MOV	#0, W2
	MOV	#17150, W3
	CALL	__AddSub_FP
	MOV	W0, [W14+8]
	MOV	W1, [W14+10]
;myDAC.c,63 :: 		float leftPWM = 127 - 127*left;
	MOV	#0, W0
	MOV	#17150, W1
	MOV	[W14+4], W2
	MOV	[W14+6], W3
	CALL	__Mul_FP
	MOV	W0, [W14+16]
	MOV	W1, [W14+18]
	MOV	#0, W0
	MOV	#17150, W1
	MOV	[W14+16], W2
	MOV	[W14+18], W3
	CALL	__Sub_FP
	MOV	W0, [W14+12]
	MOV	W1, [W14+14]
;myDAC.c,65 :: 		myDAC2_write(rightPWM);
	MOV	[W14+8], W0
	MOV	[W14+10], W1
	CALL	__Float2Longint
	MOV.B	W0, W10
	CALL	_myDAC2_write
;myDAC.c,66 :: 		myDAC1_write(leftPWM);
	MOV	[W14+12], W0
	MOV	[W14+14], W1
	CALL	__Float2Longint
	MOV.B	W0, W10
	CALL	_myDAC1_write
;myDAC.c,67 :: 		}
L_end_MotorController:
	POP	W11
	POP	W10
	ULNK
	RETURN
; end of _MotorController
