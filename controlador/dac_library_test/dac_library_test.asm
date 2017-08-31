
_main:
	MOV	#2048, W15
	MOV	#6142, W0
	MOV	WREG, 32
	MOV	#1, W0
	MOV	WREG, 52
	MOV	#4, W0
	IOR	68

;dac_library_test.c,5 :: 		void main() {
;dac_library_test.c,6 :: 		myDAC2_init(DAC_INTERNAL_REF_2V);
	PUSH	W10
	MOV	#2, W10
	CALL	_myDAC2_init
;dac_library_test.c,8 :: 		myDAC2_write(i);
	MOV	#lo_addr(_i), W0
	MOV.B	[W0], W10
	CALL	_myDAC2_write
;dac_library_test.c,10 :: 		while(1) {
L_main0:
;dac_library_test.c,11 :: 		for(; i < 255; i+= 5) {
L_main2:
	MOV	#lo_addr(_i), W0
	MOV.B	[W0], W1
	MOV.B	#255, W0
	CP.B	W1, W0
	BRA LTU	L__main18
	GOTO	L_main3
L__main18:
;dac_library_test.c,12 :: 		myDAC2_write(i);
	MOV	#lo_addr(_i), W0
	MOV.B	[W0], W10
	CALL	_myDAC2_write
;dac_library_test.c,13 :: 		delay_ms(200);
	MOV	#5, W8
	MOV	#4523, W7
L_main5:
	DEC	W7
	BRA NZ	L_main5
	DEC	W8
	BRA NZ	L_main5
;dac_library_test.c,11 :: 		for(; i < 255; i+= 5) {
	MOV.B	#5, W1
	MOV	#lo_addr(_i), W0
	ADD.B	W1, [W0], [W0]
;dac_library_test.c,14 :: 		}
	GOTO	L_main2
L_main3:
;dac_library_test.c,15 :: 		for(; i > 0; i -= 5) {
L_main7:
	MOV	#lo_addr(_i), W0
	MOV.B	[W0], W0
	CP.B	W0, #0
	BRA GTU	L__main19
	GOTO	L_main8
L__main19:
;dac_library_test.c,16 :: 		myDAC2_write(i);
	MOV	#lo_addr(_i), W0
	MOV.B	[W0], W10
	CALL	_myDAC2_write
;dac_library_test.c,17 :: 		delay_ms(200);
	MOV	#5, W8
	MOV	#4523, W7
L_main10:
	DEC	W7
	BRA NZ	L_main10
	DEC	W8
	BRA NZ	L_main10
;dac_library_test.c,15 :: 		for(; i > 0; i -= 5) {
	MOV.B	#5, W1
	MOV	#lo_addr(_i), W0
	SUBR.B	W1, [W0], [W0]
;dac_library_test.c,18 :: 		}
	GOTO	L_main7
L_main8:
;dac_library_test.c,19 :: 		for(; i < 127; i += 5) {
L_main12:
	MOV	#lo_addr(_i), W0
	MOV.B	[W0], W1
	MOV.B	#127, W0
	CP.B	W1, W0
	BRA LTU	L__main20
	GOTO	L_main13
L__main20:
;dac_library_test.c,20 :: 		myDAC2_write(i);
	MOV	#lo_addr(_i), W0
	MOV.B	[W0], W10
	CALL	_myDAC2_write
;dac_library_test.c,21 :: 		delay_ms(200);
	MOV	#5, W8
	MOV	#4523, W7
L_main15:
	DEC	W7
	BRA NZ	L_main15
	DEC	W8
	BRA NZ	L_main15
;dac_library_test.c,19 :: 		for(; i < 127; i += 5) {
	MOV.B	#5, W1
	MOV	#lo_addr(_i), W0
	ADD.B	W1, [W0], [W0]
;dac_library_test.c,22 :: 		}
	GOTO	L_main12
L_main13:
;dac_library_test.c,23 :: 		}
	GOTO	L_main0
;dac_library_test.c,24 :: 		}
L_end_main:
	POP	W10
L__main_end_loop:
	BRA	L__main_end_loop
; end of _main
