#include "servo180.h"

PE_Servo180_Timer_t timer1;
PE_Servo180_Timer_t timer2;
PE_Servo180_Timer_t timer3;

PE_Servo180_Motor_t motor01 = {.ID = 0, .reverse = 0};
PE_Servo180_Motor_t motor02 = {.ID = 1, .reverse = 0};
PE_Servo180_Motor_t motor03 = {.ID = 2, .reverse = 0};
PE_Servo180_Motor_t motor04 = {.ID = 3, .reverse = 0};
PE_Servo180_Motor_t motor05 = {.ID = 4, .reverse = 1};
PE_Servo180_Motor_t motor06 = {.ID = 5, .reverse = 1};
PE_Servo180_Motor_t motor07 = {.ID = 6, .reverse = 0};
PE_Servo180_Motor_t motor08 = {.ID = 7, .reverse = 0};
PE_Servo180_Motor_t motor09 = {.ID = 8, .reverse = 0};
PE_Servo180_Motor_t motor10 = {.ID = 9, .reverse = 0};
PE_Servo180_Motor_t motor11 = {.ID = 10, .reverse = 0};
PE_Servo180_Motor_t motor12 = {.ID = 11, .reverse = 0};
PE_Servo180_Motor_t motor13 = {.ID = 12, .reverse = 0};
PE_Servo180_Motor_t motor14 = {.ID = 13, .reverse = 0};
PE_Servo180_Motor_t motor15 = {.ID = 14, .reverse = 0};
PE_Servo180_Motor_t motor16 = {.ID = 15, .reverse = 0};
PE_Servo180_Motor_t motor17 = {.ID = 16, .reverse = 0};
PE_Servo180_Motor_t motor18 = {.ID = 17, .reverse = 0};

typedef struct {
    GPIO_TypeDef *port;
    uint8_t      pin;
} Motor_Pin_t;

Motor_Pin_t motorPins[] = {
    {GPIOA, 0},
    {GPIOA, 1},
    {GPIOA, 2},
    //A3
    {GPIOA, 4},
    {GPIOA, 5},
    {GPIOA, 6},
    //A7
    {GPIOB, 12},
    {GPIOB, 13},
    {GPIOB, 14},
    //B15
    {GPIOA, 8},
    {GPIOA, 9},
    {GPIOA, 10},
    //A11
    {GPIOA, 12},
    {GPIOA, 15},
    {GPIOB, 3},
    //B4
    {GPIOB, 5},
    {GPIOB, 6},
    {GPIOB, 7},
    //B8
};

void MX_Servo180_Init(void) {
    GPIO_InitTypeDef gpio;

    PE_Servo180_createTimer(&timer1);
    PE_Servo180_createTimer(&timer2);
    PE_Servo180_createTimer(&timer3);

    PE_Servo180_attachMotor(&timer1, &motor01);
    PE_Servo180_attachMotor(&timer1, &motor02);
    PE_Servo180_attachMotor(&timer1, &motor03);

    PE_Servo180_attachMotor(&timer1, &motor04);
    PE_Servo180_attachMotor(&timer1, &motor05);
    PE_Servo180_attachMotor(&timer1, &motor06);

    PE_Servo180_attachMotor(&timer2, &motor07);
    PE_Servo180_attachMotor(&timer2, &motor08);
    PE_Servo180_attachMotor(&timer2, &motor09);

    PE_Servo180_attachMotor(&timer2, &motor10);
    PE_Servo180_attachMotor(&timer2, &motor11);
    PE_Servo180_attachMotor(&timer2, &motor12);

    PE_Servo180_attachMotor(&timer3, &motor13);
    PE_Servo180_attachMotor(&timer3, &motor14);
    PE_Servo180_attachMotor(&timer3, &motor15);

    PE_Servo180_attachMotor(&timer3, &motor16);
    PE_Servo180_attachMotor(&timer3, &motor17);
    PE_Servo180_attachMotor(&timer3, &motor18);

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    gpio.Pin = GPIO_PIN_0
            | GPIO_PIN_1
            | GPIO_PIN_2
            | GPIO_PIN_3
            | GPIO_PIN_4
            | GPIO_PIN_5
            | GPIO_PIN_6
            | GPIO_PIN_7
            | GPIO_PIN_8
            | GPIO_PIN_9
            | GPIO_PIN_10
            | GPIO_PIN_11
            | GPIO_PIN_12
            | GPIO_PIN_15;

    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio);

    gpio.Pin = GPIO_PIN_3
            | GPIO_PIN_4
            | GPIO_PIN_5
            | GPIO_PIN_6
            | GPIO_PIN_7
            | GPIO_PIN_8;

    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOB, &gpio);
}

void PE_Servo180_setTimerOverflow(PE_Servo180_Timer_t *timer, uint16_t value) {
    if (timer == &timer1) {
        __HAL_TIM_SET_AUTORELOAD(&TIM2_Handle, value);
    }
    if (timer == &timer2) {
        __HAL_TIM_SET_AUTORELOAD(&TIM3_Handle, value);
    }
    if (timer == &timer3) {
        __HAL_TIM_SET_AUTORELOAD(&TIM4_Handle, value);
    }
}

void PE_Servo180_setTimerRefresh(PE_Servo180_Timer_t *timer) {
    if (timer == &timer1) {
        HAL_TIM_GenerateEvent(&TIM2_Handle, TIM_EVENTSOURCE_UPDATE);
    }
    if (timer == &timer2) {
        HAL_TIM_GenerateEvent(&TIM3_Handle, TIM_EVENTSOURCE_UPDATE);
    }
    if (timer == &timer3) {
        HAL_TIM_GenerateEvent(&TIM4_Handle, TIM_EVENTSOURCE_UPDATE);
    }
}

void PE_Servo180_setMotorPin0(uint8_t id) {
    motorPins[id].port->BSRR = (1u << (motorPins[id].pin + 16u));
}

void PE_Servo180_setMotorPin1(uint8_t id) {
    motorPins[id].port->BSRR = (1u << motorPins[id].pin);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *tim) {
    MX_LED_ON(0);
    if (tim->Instance == TIM2) {
        PE_Servo180_onOverflow(&timer1);
    }
    if (tim->Instance == TIM3) {
        PE_Servo180_onOverflow(&timer2);
    }
    if (tim->Instance == TIM4) {
        PE_Servo180_onOverflow(&timer3);
    }
}
