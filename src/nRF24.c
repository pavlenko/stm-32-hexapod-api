#include "nRF24.h"

PE_nRF24_t nRF24;

void MX_nRF24_Init(PE_nRF24_t *handle) {
    PE_nRF24_Config_t config;
    GPIO_InitTypeDef gpio;

    config.rfChannel    = 2;
    config.payloadWidth = 1;
    config.crcScheme    = PE_nRF24_CRC_SCHEME_1BYTE;
    config.txPower      = PE_nRF24_TX_POWER_18dBm;
    config.dataRate     = PE_nRF24_DATA_RATE__250KBPS;
    config.retryCount   = PE_nRF24_RETRY_COUNT__1;
    config.retryDelay   = PE_nRF24_RETRY_DELAY_1000us;
    config.addressWidth = PE_nRF24_ADDR_WIDTH_5BIT;
    config.addressRX    = (uint8_t *) PE_nRF24_TEST_ADDRESS;
    config.addressTX    = (uint8_t *) PE_nRF24_TEST_ADDRESS;

    if (PE_nRF24L01_initialize(handle, &config) != PE_nRF24_RESULT_OK) {
        Error_Handler(__FILE__, __LINE__);
    }

    //PB11 ------> nRF24_CE
    //PB10 ------> nRF24_IRQ
    gpio.Pin   = GPIO_PIN_11;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOB, &gpio);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);

    gpio.Pin   = GPIO_PIN_10;
    gpio.Mode  = GPIO_MODE_IT_FALLING;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOB, &gpio);

    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

PE_nRF24_RESULT_t PE_nRF24L01_readData(PE_nRF24_t *handle, uint8_t *data, uint8_t size) {
    (void) handle;

    if (HAL_SPI_Receive(&SPIn, data, size, 1000) != HAL_OK) {
        return PE_nRF24_RESULT_ERROR;
    }

    return PE_nRF24_RESULT_OK;
}

PE_nRF24_RESULT_t PE_nRF24L01_sendData(PE_nRF24_t *handle, uint8_t *data, uint8_t size) {
    (void) handle;

    if (HAL_SPI_Transmit(&SPIn, data, size, 1000) != HAL_OK) {
        return PE_nRF24_RESULT_ERROR;
    }

    return PE_nRF24_RESULT_OK;
}

void PE_nRF24L01_setCE0(PE_nRF24_t *handle) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
    (void) handle;
}

void PE_nRF24L01_setCE1(PE_nRF24_t *handle) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
    (void) handle;
}

void PE_nRF24L01_setSS0(PE_nRF24_t *handle) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    (void) handle;
}

void PE_nRF24L01_setSS1(PE_nRF24_t *handle) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    (void) handle;
}

void PE_nRF24L01_onRXComplete(PE_nRF24_t *handle) {
    if (nRF24.buffer[0] != 0) {
        spiderV2.remote.moveY = 1;
    } else {
        spiderV2.remote.moveY = 0;
    }
    (void) handle;
    MX_LED_ON(5);
}

void EXTI15_10_IRQHandler(void) {
    //TODO check why not reflect to: if (EXTI->PR & GPIO_PIN_10) { EXTI->PR = GPIO_PIN_10; HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10); }
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_10) {
        PE_nRF24L01_handleIRQ(&nRF24);
    }
}
