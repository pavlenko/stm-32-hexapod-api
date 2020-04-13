#include "main.h"
#include "led.h"
#include "nRF24.h"
#include "servo180.h"
#include "spi.h"
#include "tim.h"

PE_Button_Key_t key1;
PE_Button_Key_t key2;

PE_SpiderV2_t spiderV2 = {
    .moving = {.height = 50},
    .legs = {
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {-85, 120, 0},  .src = {-135, 190, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {85, 120, 0},   .src = {135, 190, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {-170, 0, 0},   .src = {-270, 0, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {170, 0, 0},    .src = {270, 0, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {-85, -120, 0}, .src = {-135, -190, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {85, -120, 0},  .src = {135, -190, 0}},
    }
};

void SystemClock_Config(void);
void MX_GPIO_Init();

int main()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_LED_Init();
    MX_LED_OFF(1);
    //MX_SPI2_Init(&SPIn);
    //MX_nRF24_Init(&nRF24);

    MX_TIM_PWM_Init(TIM2, &TIM2_Handle);
    MX_TIM_PWM_Init(TIM3, &TIM3_Handle);
    MX_TIM_PWM_Init(TIM4, &TIM4_Handle);

    MX_Servo180_Init();

    HAL_TIM_Base_Start_IT(&TIM2_Handle);
    HAL_TIM_Base_Start_IT(&TIM3_Handle);
    HAL_TIM_Base_Start_IT(&TIM4_Handle);

    HAL_TIM_PWM_Start_IT(&TIM2_Handle, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start_IT(&TIM3_Handle, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start_IT(&TIM4_Handle, TIM_CHANNEL_1);

    if (PE_SpiderV2_initialize(&spiderV2) != PE_SPIDER_V2_STATUS_SUCCESS) {
        Error_Handler(__FILE__, __LINE__);
    }

    spiderV2.remote.moveX   = 0;
    spiderV2.remote.moveY   = 0;
    spiderV2.remote.rotateZ = 0;

    while (1) {
        //PE_SpiderV2_refreshMs(&spiderV2, HAL_GetTick());

        PE_Button_dispatchKey(&key1, HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == 0, HAL_GetTick());
        PE_Button_dispatchKey(&key2, HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 0, HAL_GetTick());

        //MX_LED_ON(0);
        //HAL_Delay(500);
        MX_LED_OFF(0);
        //HAL_Delay(500);
    }
}

void PE_Button_onPress(PE_Button_Key_t *key) {
    if (key == &key1) {
        spiderV2.remote.moveY = 1;
    }
    if (key == &key2) {
        spiderV2.remote.off = 1;
    }
}

void PE_Button_onRelease(PE_Button_Key_t *key) {
    if (key == &key1) {
        spiderV2.remote.moveY = 0;
    }
}

void PE_SpiderV2_refreshOnEntering(PE_SpiderV2_t *spider) {
    (void) spider;
    MX_LED_ON(1);
}

void PE_SpiderV2_refreshOnComplete(PE_SpiderV2_t *spider) {
    PE_Servo180_setRadian(&motor01, spider->legs[PE_SPIDER_V2_LEG_POS_FL].cDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor02, spider->legs[PE_SPIDER_V2_LEG_POS_FL].fDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor03, spider->legs[PE_SPIDER_V2_LEG_POS_FL].tDegree, PE_SpiderV2_DELAY_MS_MOVE);

    PE_Servo180_setRadian(&motor04, spider->legs[PE_SPIDER_V2_LEG_POS_FR].cDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor05, spider->legs[PE_SPIDER_V2_LEG_POS_FR].fDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor06, spider->legs[PE_SPIDER_V2_LEG_POS_FR].tDegree, PE_SpiderV2_DELAY_MS_MOVE);

    PE_Servo180_setRadian(&motor07, spider->legs[PE_SPIDER_V2_LEG_POS_ML].cDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor08, spider->legs[PE_SPIDER_V2_LEG_POS_ML].fDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor09, spider->legs[PE_SPIDER_V2_LEG_POS_ML].tDegree, PE_SpiderV2_DELAY_MS_MOVE);

    PE_Servo180_setRadian(&motor10, spider->legs[PE_SPIDER_V2_LEG_POS_MR].cDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor11, spider->legs[PE_SPIDER_V2_LEG_POS_MR].fDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor12, spider->legs[PE_SPIDER_V2_LEG_POS_MR].tDegree, PE_SpiderV2_DELAY_MS_MOVE);

    PE_Servo180_setRadian(&motor13, spider->legs[PE_SPIDER_V2_LEG_POS_BL].cDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor14, spider->legs[PE_SPIDER_V2_LEG_POS_BL].fDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor15, spider->legs[PE_SPIDER_V2_LEG_POS_BL].tDegree, PE_SpiderV2_DELAY_MS_MOVE);

    PE_Servo180_setRadian(&motor16, spider->legs[PE_SPIDER_V2_LEG_POS_BR].cDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor17, spider->legs[PE_SPIDER_V2_LEG_POS_BR].fDegree, PE_SpiderV2_DELAY_MS_MOVE);
    PE_Servo180_setRadian(&motor18, spider->legs[PE_SPIDER_V2_LEG_POS_BR].tDegree, PE_SpiderV2_DELAY_MS_MOVE);
}

void MX_GPIO_Init() {
    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO clock enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStruct.Pin   = GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 72000000
 *            HCLK(Hz)                       = 72000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 2
 *            APB2 Prescaler                 = 1
 *            HSE Frequency(Hz)              = 8000000
 *            HSE PREDIV1                    = 1
 *            PLL2MUL                        = 9
 *            Flash Latency(WS)              = 2
 * @param  None
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    // Initializes the CPU clock source
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL     = RCC_PLL_MUL9;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler(__FILE__, __LINE__);
    }

    // Initializes the CPU, AHB and APB buses clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK
                                  | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1
                                  | RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler(__FILE__, __LINE__);
    }

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
        Error_Handler(__FILE__, __LINE__);
    }
}

/**
 * @brief  Initializes the Global MSP.
 * @param  None
 * @retval None
 */
void HAL_MspInit(void)
{
    /* Alternate Function I/O clock enable */
    __HAL_RCC_AFIO_CLK_ENABLE();

    /* Power interface clock enable */
    __HAL_RCC_PWR_CLK_ENABLE();
}

/**
 * @brief  DeInitializes the Global MSP.
 * @param  None
 * @retval None
 */
void HAL_MspDeInit(void)
{}

/**
 * @brief   This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
    HAL_IncTick();
}

/**
 * @brief This function is executed in case of error occurrence.
 *
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void Error_Handler(const char * file, int line)
{
    UNUSED(file);
    UNUSED(line);

    const uint16_t sequence[] = {
            100,
            200,
            100,
            200,
            100,
            1200,
    };

    while (1) {
        MX_LED_PLAY(sequence, 6);
        __NOP();
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    UNUSED(file);
    UNUSED(line);
}
#endif
