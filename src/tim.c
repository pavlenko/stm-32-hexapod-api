/* Includes ------------------------------------------------------------------*/

#include "tim.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void MX_TIM_PWM_Init(TIM_TypeDef *tim, TIM_HandleTypeDef *handle)
{
    TIM_OC_InitTypeDef sConfigOC;
    TIM_MasterConfigTypeDef sMasterConfig;

    handle->Instance           = tim;
    handle->Init.Prescaler     = (uint32_t) (SystemCoreClock / 1000000) - 1;
    handle->Init.CounterMode   = TIM_COUNTERMODE_UP;
    handle->Init.Period        = 20000;
    handle->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_PWM_Init(handle);

    sConfigOC.OCMode     = TIM_OCMODE_PWM1;
    sConfigOC.Pulse      = 2000;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(handle, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(handle, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(handle, &sConfigOC, TIM_CHANNEL_3);
    HAL_TIM_PWM_ConfigChannel(handle, &sConfigOC, TIM_CHANNEL_4);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_ENABLE;

    HAL_TIMEx_MasterConfigSynchronization(handle, &sMasterConfig);

    HAL_TIM_PWM_Start_IT(handle, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start_IT(handle, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start_IT(handle, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start_IT(handle, TIM_CHANNEL_4);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    if (tim->Instance == TIM1) {
        /* GPIO clock enable */
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /* Peripheral clock enable */
        __HAL_RCC_TIM1_CLK_ENABLE();

        /**
         * TIM GPIO Configuration
         * PA8  ------> TIM_CH1
         * PA9  ------> TIM_CH2
         * PA10 ------> TIM_CH3
         * PA11 ------> TIM_CH4
         */
        GPIO_InitStruct.Pin   = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }

    if (tim->Instance == TIM4) {
        /* GPIO clock enable */
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /* Peripheral clock enable */
        __HAL_RCC_TIM4_CLK_ENABLE();

        /**
         * TIM GPIO Configuration
         * PB6 ------> TIM_CH1
         * PB7 ------> TIM_CH2
         * PB8 ------> TIM_CH3
         * PB9 ------> TIM_CH4
         */
        GPIO_InitStruct.Pin   = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM4_IRQn);
    }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim)
{
    if (tim->Instance == TIM1) {
        /* Peripheral clock disable */
        __HAL_RCC_TIM1_CLK_DISABLE();

        /**
         * TIM1 GPIO Configuration
         * PA8  ------> TIM1_CH1
         * PA9  ------> TIM1_CH2
         * PA10 ------> TIM1_CH3
         * PA11 ------> TIM1_CH4
         */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11);
    }

    if (tim->Instance == TIM4) {
        /* Peripheral clock disable */
        __HAL_RCC_TIM4_CLK_DISABLE();

        /**
         * TIM GPIO Configuration
         * PB6 ------> TIM_CH1
         * PB7 ------> TIM_CH2
         * PB8 ------> TIM_CH3
         * PB9 ------> TIM_CH4
         */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);
    }
}
