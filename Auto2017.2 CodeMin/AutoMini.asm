
_main:
	MOV	#2048, W15
	MOV	#6142, W0
	MOV	WREG, 32
	MOV	#1, W0
	MOV	WREG, 52
	MOV	#4, W0
	IOR	68

;AutoMini.c,4 :: 		void main() {
;AutoMini.c,5 :: 		init_robot();
	CALL	_init_robot
;AutoMini.c,6 :: 		while(1){
L_main0:
;AutoMini.c,7 :: 		Sniffing();
	CALL	_Sniffing
;AutoMini.c,8 :: 		}
	GOTO	L_main0
;AutoMini.c,10 :: 		}
L_end_main:
L__main_end_loop:
	BRA	L__main_end_loop
; end of _main
