#include "PE_Servo180.h"

#include <math.h>
#include <stddef.h>

PE_Servo180_Status_t PE_Servo180_attachMotor(PE_Servo180_Timer_t *timer, PE_Servo180_Motor_t *motor) {
    if (timer->motorCount == PE_Servo180_MOTOR_PER_TIMER || motor->attached) {
        return PE_Servo180_FAILURE;
    }

    if (motor->min == 0) {
        motor->min = PE_Servo180_MOTOR_MIN;
    }

    if (motor->max == 0) {
        motor->max = PE_Servo180_MOTOR_MAX;
    }

    motor->attached = 1;
    timer->motorItems[timer->motorCount] = motor;
    timer->motorCount++;

    return PE_Servo180_SUCCESS;
}

PE_Servo180_Status_t PE_Servo180_detachMotor(PE_Servo180_Timer_t *timer, PE_Servo180_Motor_t *motor) {
    uint8_t index;

    for (index = 0; index < timer->motorCount; index++) {
        if (timer->motorItems[index] == motor) {
            timer->motorItems[index] = NULL;
            return PE_Servo180_SUCCESS;
        }
    }

    return PE_Servo180_FAILURE;
}

float PE_Servo180_mapRange(float value, float srcMin, float srcMax, float dstMin, float dstMax) {
    float slope = (dstMax - dstMin) / (srcMax - srcMin);
    return dstMin + slope * (value - srcMin);
}

void PE_Servo180_setRadian(PE_Servo180_Motor_t *motor, float value) {
    if (value < 0) {
        value = 0;
    }

    if (value > M_PI) {
        value = M_PI;
    }

    value = (uint16_t) PE_Servo180_mapRange(value, 0, M_PI, motor->min, motor->max);

    PE_Servo180_setMicros(motor, value);
}

void PE_Servo180_setDegree(PE_Servo180_Motor_t *motor, uint16_t value) {
    if (value > 180) {
        value = 180;
    }

    value = (uint16_t) PE_Servo180_mapRange(value, 0, 180, motor->min, motor->max);

    PE_Servo180_setMicros(motor, value);
}

void PE_Servo180_setMicros(PE_Servo180_Motor_t *motor, uint16_t value) {
    if (value < motor->min) {
        value = motor->min;
    }

    if (value > motor->max) {
        value = motor->max;
    }

    motor->ticks = value;//TODO convert to ticks
}

void PE_Servo180_dispatchTimer(PE_Servo180_Timer_t *timer) {
    if (timer->motorIndex < 0) {
        *(timer->counter) = 0;
    } else if (timer->motorItems[timer->motorIndex] != NULL) {
        PE_Servo180_setMotorPin0(timer->motorItems[timer->motorIndex]->ID);
    }

    timer->motorIndex++;

    if (timer->motorCount > 0 && timer->motorIndex < PE_Servo180_MOTOR_PER_TIMER) {
        if (timer->motorItems[timer->motorIndex] != NULL) {
            PE_Servo180_setTimerCompare(timer, *(timer->counter) + timer->motorItems[timer->motorIndex]->ticks);
            PE_Servo180_setMotorPin1(timer->motorItems[timer->motorIndex]->ID);
        }
    } else {
        uint16_t refresh = PE_Servo180_REFRESH_INTERVAL;//TODO convert to ticks

        if (*(timer->counter) < (refresh + 4)) {
            PE_Servo180_setTimerCompare(timer, refresh);
        } else {
            PE_Servo180_setTimerCompare(timer, *(timer->counter) + 4);
        }

        timer->motorIndex = -1;
    }
}

__attribute__((weak))
void PE_Servo180_setTimerCompare(PE_Servo180_Timer_t *timer, uint16_t value) {
    *(timer->compare) = value;
}

__attribute__((weak))
void PE_Servo180_setMotorPin0(uint8_t id) {
    (void) id;
}

__attribute__((weak))
void PE_Servo180_setMotorPin1(uint8_t id) {
    (void) id;
}
