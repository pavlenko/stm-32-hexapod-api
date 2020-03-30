#include "PE_Servo180.h"

#include <math.h>
#include <stddef.h>

float PE_Servo180_mapRange(float value, float srcMin, float srcMax, float dstMin, float dstMax);

PE_Servo180_Status_t PE_Servo180_createTimer(PE_Servo180_Timer_t *timer) {
    timer->motorIndex = -1;
    timer->motorCount = 0;
    timer->counter    = 0;

    uint8_t index;
    for (index = 0; index < PE_Servo180_MOTOR_PER_TIMER; index++) {
        timer->motorItems[index] = NULL;
    }

    return PE_Servo180_SUCCESS;
}

PE_Servo180_Status_t PE_Servo180_attachMotor(PE_Servo180_Timer_t *timer, PE_Servo180_Motor_t *motor) {
    if (timer->motorCount == PE_Servo180_MOTOR_PER_TIMER) {
        return PE_Servo180_FAILURE;
    }

    uint8_t index;
    for (index = 0; index < timer->motorCount; index++) {
        if (timer->motorItems[index] == motor) {
            return PE_Servo180_FAILURE;
        }
    }

    if (motor->min == 0) {
        motor->min = PE_Servo180_MOTOR_MIN;
    }

    if (motor->max == 0) {
        motor->max = PE_Servo180_MOTOR_MAX;
    }

    motor->ticks = PE_Servo180_MOTOR_MID;
    motor->value = PE_Servo180_MOTOR_MID;
    motor->speed = 0;

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

void PE_Servo180_setRadian(PE_Servo180_Motor_t *motor, float value, uint16_t time) {
    if (value < 0) {
        value = 0;
    }

    if (value > M_PI) {
        value = M_PI;
    }

    value = (uint16_t) PE_Servo180_mapRange(value, 0, M_PI, motor->min, motor->max);

    PE_Servo180_setMicros(motor, value, time);
}

void PE_Servo180_setDegree(PE_Servo180_Motor_t *motor, uint16_t value, uint16_t time) {
    if (value > 180) {
        value = 180;
    }

    value = (uint16_t) PE_Servo180_mapRange(value, 0, 180, motor->min, motor->max);

    PE_Servo180_setMicros(motor, value, time);
}

void PE_Servo180_setMicros(PE_Servo180_Motor_t *motor, uint16_t value, uint16_t time) {
    if (value < motor->min) {
        value = motor->min;
    }

    if (value > motor->max) {
        value = motor->max;
    }

    if (motor->reverse) {
        value = (motor->max + motor->min) - value;
    }

    motor->ticks = motor->value;
    motor->value = value;

    if (time > 0) {
        uint16_t steps = (time / 25) + 1;

        if (steps > 1) {
            if (motor->value > motor->ticks) {
                motor->speed = (motor->value - motor->ticks) / steps;
            } else {
                motor->speed = (motor->ticks - motor->value) / steps;
            }

            return;
        }
    }

    motor->ticks = value;
    motor->speed = 0;
}

void PE_Servo180_onOverflow(PE_Servo180_Timer_t *timer) {
    if (timer->motorIndex < 0) {
        timer->counter = 0;
    } else if (timer->motorItems[timer->motorIndex] != NULL) {
        PE_Servo180_setMotorPin0(timer->motorItems[timer->motorIndex]->ID);
    }

    timer->motorIndex++;

    if (timer->motorCount > 0 && timer->motorIndex < PE_Servo180_MOTOR_PER_TIMER) {
        uint16_t ticks;

        if (timer->motorItems[timer->motorIndex] != NULL) {
            if (timer->motorItems[timer->motorIndex]->speed > 0) {
                if (timer->motorItems[timer->motorIndex]->value > timer->motorItems[timer->motorIndex]->ticks) {
                    timer->motorItems[timer->motorIndex]->ticks += timer->motorItems[timer->motorIndex]->speed;

                    if (timer->motorItems[timer->motorIndex]->value <= timer->motorItems[timer->motorIndex]->ticks) {
                        timer->motorItems[timer->motorIndex]->ticks = timer->motorItems[timer->motorIndex]->value;
                        timer->motorItems[timer->motorIndex]->speed = 0;
                    }
                } else {
                    timer->motorItems[timer->motorIndex]->ticks -= timer->motorItems[timer->motorIndex]->speed;

                    if (timer->motorItems[timer->motorIndex]->value >= timer->motorItems[timer->motorIndex]->ticks) {
                        timer->motorItems[timer->motorIndex]->ticks = timer->motorItems[timer->motorIndex]->value;
                        timer->motorItems[timer->motorIndex]->speed = 0;
                    }
                }
            }

            PE_Servo180_setMotorPin1(timer->motorItems[timer->motorIndex]->ID);
            ticks = timer->motorItems[timer->motorIndex]->ticks;
        } else {
            ticks = 100;
        }

        PE_Servo180_setTimerOverflow(timer, ticks);

        timer->counter += ticks;
    } else {
        uint16_t refresh = PE_Servo180_REFRESH_INTERVAL;

        if (timer->counter + 4 < refresh) {
            PE_Servo180_setTimerOverflow(timer, refresh - timer->counter);
        } else {
            PE_Servo180_setTimerRefresh(timer);
        }

        timer->motorIndex = -1;
    }
}

float PE_Servo180_mapRange(float value, float srcMin, float srcMax, float dstMin, float dstMax) {
    float slope = (dstMax - dstMin) / (srcMax - srcMin);
    return dstMin + slope * (value - srcMin);
}

__attribute__((weak))
void PE_Servo180_setTimerOverflow(PE_Servo180_Timer_t *timer, uint16_t value) {
    (void) timer;
    (void) value;
}

__attribute__((weak))
void PE_Servo180_setTimerRefresh(PE_Servo180_Timer_t *timer) {
    (void) timer;
}

__attribute__((weak))
void PE_Servo180_setMotorPin0(uint8_t id) {
    (void) id;
}

__attribute__((weak))
void PE_Servo180_setMotorPin1(uint8_t id) {
    (void) id;
}
