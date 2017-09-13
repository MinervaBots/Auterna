
_main:
	MOV	#2048, W15
	MOV	#6142, W0
	MOV	WREG, 32
	MOV	#1, W0
	MOV	WREG, 52
	MOV	#4, W0
	IOR	68

;SensorReading.c,3 :: 		void main() {
;SensorReading.c,4 :: 		init_robot();
	CALL	_init_robot
;SensorReading.c,5 :: 		while(1){
L_main0:
;SensorReading.c,6 :: 		mySensorControl();
	CALL	_mySensorControl
;SensorReading.c,7 :: 		}
	GOTO	L_main0
;SensorReading.c,8 :: 		}
L_end_main:
L__main_end_loop:
	BRA	L__main_end_loop
; end of _main
