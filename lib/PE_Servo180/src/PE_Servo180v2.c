#include "PE_Servo180v2.h"

#include <stddef.h>

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
    return PE_Servo180_SUCCESS;
}

PE_Servo180_Status_t PE_Servo180_detachMotor(PE_Servo180_t *servo, PE_Servo180_Motor_t *motor) {
    return PE_Servo180_SUCCESS;
}
