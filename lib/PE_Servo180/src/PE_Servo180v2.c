#include "PE_Servo180v2.h"

#include <stddef.h>

#define PE_Servo180_REFRESH_INTERVAL 20000

PE_Servo180_Status_t PE_Servo180_attachTimer(PE_Servo180_t *servo, PE_Servo180_Timer_t *timer) {
    PE_Servo180_Timer_t **t;

    for (t = &(servo->timer); t != NULL; t = &((*t)->next)) {
        if (*t == timer) {
            // Timer already attached
            return PE_Servo180_FAILURE;
        }
    }

    timer->next  = servo->timer;
    servo->timer = timer;

    return PE_Servo180_SUCCESS;
}

PE_Servo180_Status_t PE_Servo180_detachTimer(PE_Servo180_t *servo, PE_Servo180_Timer_t *timer) {
    PE_Servo180_Timer_t **t;

    for (t = &(servo->timer); t != NULL; t = &((*t)->next)) {
        if (*t == timer) {
            *t = timer->next;
            timer->next = NULL;
            return PE_Servo180_SUCCESS;
        }
    }

    return PE_Servo180_FAILURE;
}

PE_Servo180_Status_t PE_Servo180_attachMotor(PE_Servo180_t *servo, PE_Servo180_Motor_t *motor) {
    if (motor->min == 0) {
        motor->min = PE_Servo180_MOTOR_MIN;
    }

    if (motor->max == 0) {
        motor->max = PE_Servo180_MOTOR_MAX;
    }

    return PE_Servo180_SUCCESS;
}

PE_Servo180_Status_t PE_Servo180_detachMotor(PE_Servo180_t *servo, PE_Servo180_Motor_t *motor) {
    return PE_Servo180_SUCCESS;
}

int PE_Servo180_mapRange(int value, int srcMin, int srcMax, int dstMin, int dstMax) {
    int slope = (dstMax - dstMin) / (srcMax - srcMin);
    return dstMin + slope * (value - srcMin);
}

void PE_Servo180_setDegree(PE_Servo180_Motor_t *motor, uint16_t value) {
    if (value > 180) {
        value = 180;
    }

    value = PE_Servo180_mapRange(value, 0, 180, motor->min, motor->max);

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
            *(timer->compare) = *(timer->counter) + timer->motorItems[timer->motorIndex]->ticks;

            PE_Servo180_setMotorPin1(timer->motorItems[timer->motorIndex]->ID);
        }
    } else {
        uint16_t refresh = PE_Servo180_REFRESH_INTERVAL;//TODO convert to ticks

        if (*(timer->counter) < (refresh + 4)) {
            *(timer->compare) = refresh;
        } else {
            *(timer->compare) = *(timer->counter) + 4;
        }

        timer->motorIndex = -1;
    }
}

__attribute__((weak))
void PE_Servo180_setMotorPin0(uint8_t id) {
    (void) id;
}

__attribute__((weak))
void PE_Servo180_setMotorPin1(uint8_t id) {
    (void) id;
}
