#ifndef STM_32_HEXAPOD_API_PE_SERVO180_H
#define STM_32_HEXAPOD_API_PE_SERVO180_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define PE_Servo180_REFRESH_INTERVAL 20000
#define PE_Servo180_MOTOR_PER_TIMER 8
#define PE_Servo180_MOTOR_MIN 500
#define PE_Servo180_MOTOR_MAX 2500

typedef struct PE_Servo180_Motor_s {
    uint8_t attached: 1;
    uint8_t ID: 7;// public
    uint16_t ticks;// private
    uint16_t value;// private
    uint16_t min;// public
    uint16_t max;// public
} PE_Servo180_Motor_t;

typedef PE_Servo180_Motor_t *PE_Servo180_Motor_p;

typedef struct PE_Servo180_Timer_s {
    int8_t motorIndex;
    uint8_t motorCount;
    PE_Servo180_Motor_p motorItems[PE_Servo180_MOTOR_PER_TIMER];
    volatile uint16_t *compare;// public
    volatile uint16_t *counter;// public
    volatile uint16_t counter2;// public
} PE_Servo180_Timer_t;

typedef enum PE_Servo180_Status_s {
    PE_Servo180_SUCCESS,
    PE_Servo180_FAILURE,
} PE_Servo180_Status_t;

/**
 * @param timer
 * @param motor
 * @return
 */
PE_Servo180_Status_t PE_Servo180_attachMotor(PE_Servo180_Timer_t *timer, PE_Servo180_Motor_t *motor);

/**
 * @param timer
 * @param motor
 * @return
 */
PE_Servo180_Status_t PE_Servo180_detachMotor(PE_Servo180_Timer_t *timer, PE_Servo180_Motor_t *motor);

/**
 * Set motor radian -> convert radian value to ticks (just set to motor->ticks)
 *
 * @param motor
 * @param value
 */
void PE_Servo180_setRadian(PE_Servo180_Motor_t *motor, float value);

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

/**
 * Dispatch timer motors this may call from mcu timer compare interrupt
 *
 * @param timer
 */
void PE_Servo180_dispatchTimer(PE_Servo180_Timer_t *timer);

void PE_Servo180_setTimerCompare(PE_Servo180_Timer_t *timer, uint16_t value);
void PE_Servo180_setTimerRefresh(PE_Servo180_Timer_t *timer);

/**
 * Set motor pin to HIGH
 * WARNING: This function must be redefined in user code to manipulate GPIO
 *
 * @param id
 */
void PE_Servo180_setMotorPin0(uint8_t id);

/**
 * Set motor pin to LOW
 * WARNING: This function must be redefined in user code to manipulate GPIO
 *
 * @param id
 */
void PE_Servo180_setMotorPin1(uint8_t id);

#ifdef __cplusplus
}
#endif

#endif //STM_32_HEXAPOD_API_PE_SERVO180_H
