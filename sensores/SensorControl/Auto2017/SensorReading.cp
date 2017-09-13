#line 1 "D:/MikroElektronika dsPIC 6.21/Nova pasta/mikroC PRO for dsPIC/Examples/Auto2017/SensorReading.c"
#line 1 "c:/users/gabriel/desktop/auto/constantes.h"
extern float mySensorControl();

extern void init_robot();
#line 3 "D:/MikroElektronika dsPIC 6.21/Nova pasta/mikroC PRO for dsPIC/Examples/Auto2017/SensorReading.c"
void main() {
 init_robot();
 while(1){
 mySensorControl();
 }
}
