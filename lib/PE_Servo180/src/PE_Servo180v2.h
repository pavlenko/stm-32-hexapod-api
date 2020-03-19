#ifndef STM_32_HEXAPOD_API_PE_SERVO180V2_H
#define STM_32_HEXAPOD_API_PE_SERVO180V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct PE_Servo180_Timer_s PE_Servo180_Timer_t;
typedef struct PE_Servo180_Motor_s PE_Servo180_Motor_t;

typedef struct PE_Servo180_Motor_s {
    uint8_t index;
    uint16_t ticks;
    uint16_t value;
    uint16_t min;
    uint16_t max;
} PE_Servo180_Motor_t;

typedef struct PE_Servo180_Timer_s {
    uint8_t index;
    PE_Servo180_Timer_t *next;
    volatile uint16_t *compare;
    volatile uint16_t *counter;
} PE_Servo180_Timer_t;

typedef struct PE_Servo180_s {
    PE_Servo180_Timer_t *timer;
    PE_Servo180_Motor_t *motor;
} PE_Servo180_t;

typedef enum PE_Servo180_Status_s {
    PE_Servo180_SUCCESS,
    PE_Servo180_FAILURE,
} PE_Servo180_Status_t;

PE_Servo180_Status_t PE_Servo180_attachTimer(PE_Servo180_t *servo, PE_Servo180_Timer_t *timer);

PE_Servo180_Status_t PE_Servo180_detachTimer(PE_Servo180_t *servo, PE_Servo180_Timer_t *timer);

PE_Servo180_Status_t PE_Servo180_attachMotor(PE_Servo180_t *servo, PE_Servo180_Motor_t *motor);

PE_Servo180_Status_t PE_Servo180_detachMotor(PE_Servo180_t *servo, PE_Servo180_Motor_t *motor);

#ifdef __cplusplus
}
#endif

#endif //STM_32_HEXAPOD_API_PE_SERVO180V2_H
