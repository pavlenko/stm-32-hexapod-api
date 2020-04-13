/* Includes ------------------------------------------------------------------*/

#include "tim.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

TIM_HandleTypeDef TIM2_Handle;
TIM_HandleTypeDef TIM3_Handle;
TIM_HandleTypeDef TIM4_Handle;

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
    sConfigOC.Pulse      = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(handle, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(handle, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(handle, &sConfigOC, TIM_CHANNEL_3);
    HAL_TIM_PWM_ConfigChannel(handle, &sConfigOC, TIM_CHANNEL_4);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_ENABLE;

    HAL_TIMEx_MasterConfigSynchronization(handle, &sMasterConfig);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim)
{
    if (tim->Instance == TIM2) {
        /* Peripheral clock enable */
        __HAL_RCC_TIM2_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }

    if (tim->Instance == TIM3) {
        /* Peripheral clock enable */
        __HAL_RCC_TIM3_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM3_IRQn);
    }

    if (tim->Instance == TIM4) {
        /* Peripheral clock enable */
        __HAL_RCC_TIM4_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM4_IRQn);
    }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim)
{
    if (tim->Instance == TIM2) {
        /* Peripheral clock disable */
        __HAL_RCC_TIM2_CLK_DISABLE();
    }

    if (tim->Instance == TIM3) {
        /* Peripheral clock disable */
        __HAL_RCC_TIM3_CLK_DISABLE();
    }

    if (tim->Instance == TIM4) {
        /* Peripheral clock disable */
        __HAL_RCC_TIM4_CLK_DISABLE();
    }
}

void TIM2_IRQHandler(void) {
    HAL_TIM_IRQHandler(&TIM2_Handle);
}

void TIM3_IRQHandler(void) {
    HAL_TIM_IRQHandler(&TIM3_Handle);
}

void TIM4_IRQHandler(void) {
    HAL_TIM_IRQHandler(&TIM4_Handle);
}
