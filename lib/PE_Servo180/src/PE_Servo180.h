#ifndef PE_SERVO180_H
#define PE_SERVO180_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//TODO maybe make this library for only control servos structures to be hardware independent

void PE_Servo180_initialize(uint8_t total);

#ifdef __cplusplus
}
#endif

#endif //PE_SERVO180_H
