#ifndef STM_32_HEXAPOD_API_PE_SERVO180V2_H
#define STM_32_HEXAPOD_API_PE_SERVO180V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define PE_Servo180_MOTOR_MIN 500
#define PE_Servo180_MOTOR_MAX 2500

typedef struct PE_Servo180_Timer_s PE_Servo180_Timer_t;
typedef struct PE_Servo180_Motor_s PE_Servo180_Motor_t;

typedef struct PE_Servo180_Motor_s {
    uint8_t index;// private, are this needed???
    uint16_t ticks;// private
    uint16_t value;// private
    uint16_t min;// public
    uint16_t max;// public
} PE_Servo180_Motor_t;

typedef struct PE_Servo180_Timer_s {
    uint8_t index;// private, are this needed???
    PE_Servo180_Timer_t *next;// private
    volatile uint16_t *compare;// public
    volatile uint16_t *counter;// public
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

PE_Servo180_Status_t PE_Servo180_attachMotor(PE_Servo180_t *servo, PE_Servo180_Motor_t *motor);//TODO attach motor to timer instead

PE_Servo180_Status_t PE_Servo180_detachMotor(PE_Servo180_t *servo, PE_Servo180_Motor_t *motor);//TODO attach motor to timer instead

/**
 * Set motor degree -> convert degree value to ticks (just set to motor->ticks)
 *
 * @param motor
 * @param value
 */
void PE_Servo180_setDegree(PE_Servo180_Motor_t *motor, uint16_t value);

/**
 * Set motor micros -> convert micros value to ticks (just set to motor->ticks)
 *
 * @param motor
 * @param value
 */
void PE_Servo180_setMicros(PE_Servo180_Motor_t *motor, uint16_t value);

#ifdef __cplusplus
}
#endif

#endif //STM_32_HEXAPOD_API_PE_SERVO180V2_H
