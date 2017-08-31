
_myDAC1_init:

;DAC.c,3 :: 		void myDAC1_init(unsigned int reference) {
;DAC.c,5 :: 		DACSIDL_DAC1CON_bit = 0;
	BCLR	DACSIDL_DAC1CON_bit, BitPos(DACSIDL_DAC1CON_bit+0)
;DAC.c,6 :: 		DACSLP_DAC1CON_bit = 1;
	BSET	DACSLP_DAC1CON_bit, BitPos(DACSLP_DAC1CON_bit+0)
;DAC.c,7 :: 		DACFM_DAC1CON_bit = 0;
	BCLR	DACFM_DAC1CON_bit, BitPos(DACFM_DAC1CON_bit+0)
;DAC.c,8 :: 		SRDIS_DAC1CON_bit = 1;
	BSET	SRDIS_DAC1CON_bit, BitPos(SRDIS_DAC1CON_bit+0)
;DAC.c,9 :: 		DACTRIG_DAC1CON_bit = 0;
	BCLR	DACTRIG_DAC1CON_bit, BitPos(DACTRIG_DAC1CON_bit+0)
;DAC.c,10 :: 		DACOE_DAC1CON_bit = 1;
	BSET	DACOE_DAC1CON_bit, BitPos(DACOE_DAC1CON_bit+0)
;DAC.c,12 :: 		DACTSEL_4_DAC1CON_bit = 0;
	BCLR	DACTSEL_4_DAC1CON_bit, BitPos(DACTSEL_4_DAC1CON_bit+0)
;DAC.c,13 :: 		DACTSEL_3_DAC1CON_bit = 0;
	BCLR	DACTSEL_3_DAC1CON_bit, BitPos(DACTSEL_3_DAC1CON_bit+0)
;DAC.c,14 :: 		DACTSEL_2_DAC1CON_bit = 0;
	BCLR	DACTSEL_2_DAC1CON_bit, BitPos(DACTSEL_2_DAC1CON_bit+0)
;DAC.c,15 :: 		DACTSEL_1_DAC1CON_bit = 0;
	BCLR	DACTSEL_1_DAC1CON_bit, BitPos(DACTSEL_1_DAC1CON_bit+0)
;DAC.c,16 :: 		DACTSEL_0_DAC1CON_bit = 0;
	BCLR	DACTSEL_0_DAC1CON_bit, BitPos(DACTSEL_0_DAC1CON_bit+0)
;DAC.c,18 :: 		DACREF_0_DAC1CON_bit = 1;
	BSET	DACREF_0_DAC1CON_bit, BitPos(DACREF_0_DAC1CON_bit+0)
;DAC.c,19 :: 		DACREF_1_DAC1CON_bit = 1;
	BSET	DACREF_1_DAC1CON_bit, BitPos(DACREF_1_DAC1CON_bit+0)
;DAC.c,21 :: 		BUFCON0 = 0b10;  // Referência interna base (BGBUF1)é 1 V
	MOV	#2, W0
	MOV	WREG, BUFCON0
;DAC.c,23 :: 		DACEN_DAC1CON_bit = 1;  // Enable DAC1 module
	BSET	DACEN_DAC1CON_bit, BitPos(DACEN_DAC1CON_bit+0)
;DAC.c,24 :: 		}
L_end_myDAC1_init:
	RETURN
; end of _myDAC1_init

_myDAC1_write:

;DAC.c,26 :: 		void myDAC1_write(uint8_t value) {
;DAC.c,27 :: 		DAC1DAT = value;
	ZE	W10, W0
	MOV	WREG, DAC1DAT
;DAC.c,28 :: 		}
L_end_myDAC1_write:
	RETURN
; end of _myDAC1_write
