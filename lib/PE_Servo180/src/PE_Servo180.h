#ifndef PE_SERVO180_H
#define PE_SERVO180_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//TODO maybe make this library for only control servos structures to be hardware independent

typedef struct {
    uint16_t micros; // Current value
    uint16_t target; // Target value for slow move
    uint16_t step;   // Step for slow move
    uint16_t min;    // Calibration min
    uint16_t max;    // Calibration max
} PE_Servo180_Motor_t;

void PE_Servo180_initialize(uint8_t total);

uint16_t PE_Servo180_getMicros();

void PE_Servo180_setMicros(uint16_t micros, uint16_t time);

uint16_t PE_Servo180_getDegree();

void PE_Servo180_setDegree(uint16_t degree, uint16_t time);

uint16_t PE_Servo180_getMinimum();

void PE_Servo180_setMinimum(uint16_t micros);

uint16_t PE_Servo180_getMaximum();

void PE_Servo180_setMaximum(uint16_t micros);

#ifdef __cplusplus
}
#endif

#endif //PE_SERVO180_H
