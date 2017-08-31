
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
