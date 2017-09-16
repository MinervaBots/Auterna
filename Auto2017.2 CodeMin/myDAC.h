#include <stdint.h>

#define BUFFER_REF_2V 1
#define BUFFER_REF_1V 0

extern void myDAC2_init(unsigned int reference);

extern void myDAC2_write(uint8_t value);

extern void MotorController(float linear,float angular);