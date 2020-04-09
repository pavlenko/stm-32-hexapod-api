#include "i2c.h"

typedef enum {
    I2C_STATUS_READY   = 0x00U,
    I2C_STATUS_LISTEN  = 0x01U,
    I2C_STATUS_BUSY_RX = 0x02U,
    I2C_STATUS_BUSY_TX = 0x03U,
    I2C_STATUS_SUCCESS = 0x04U,
    I2C_STATUS_FAILURE = 0x05U,
} I2C_Status_t;

I2C_Status_t I2C2_Status;
uint8_t *I2C2_rxBufferData;
uint8_t I2C2_rxBufferSize;
uint8_t *I2C2_txBufferData;
uint8_t I2C2_txBufferSize;

void MX_I2C2_Init(uint16_t address) {
    I2C2_Handle.Instance             = I2C2;
    I2C2_Handle.Init.ClockSpeed      = 400000;
    I2C2_Handle.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    I2C2_Handle.Init.OwnAddress1     = address;
    I2C2_Handle.Init.OwnAddress2     = 0xFF;
    I2C2_Handle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    I2C2_Handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2C2_Handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2C2_Handle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&I2C2_Handle) != HAL_OK) {
        Error_Handler(__FILE__, __LINE__);
    }
}

void MX_I2C2_dispatch() {
    //TODO replace ist 3 if statements with switch
    if (I2C2_Status == I2C_STATUS_READY) {
        if (HAL_I2C_EnableListen_IT(&I2C2_Handle) != HAL_OK) {
            Error_Handler(__FILE__, __LINE__);
        }

        I2C2_Status = I2C_STATUS_LISTEN;
    }

    if (I2C2_Status == I2C_STATUS_SUCCESS) {
        //TODO on success
    }

    if (I2C2_Status == I2C_STATUS_FAILURE) {
        //TODO on failure
    }

    if (I2C2_Status == I2C_STATUS_SUCCESS || I2C2_Status == I2C_STATUS_FAILURE) {
        I2C2_txBufferSize = 0;
        I2C2_rxBufferSize = 0;

        I2C2_Status = I2C_STATUS_READY;
    }
}

/* SLAVE CALLBACKS ****************************************************************************************************/

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *i2c, uint8_t direction, uint16_t address) {
    if (i2c->Instance == I2C2) {
        if (direction == I2C_DIRECTION_TRANSMIT) {
            I2C2_Status = I2C_STATUS_BUSY_RX;
            //TODO remove Error_Handler call
            if (HAL_I2C_Slave_Sequential_Receive_IT(&I2C2_Handle, &(I2C2_rxBufferData[I2C2_rxBufferSize]), 1, I2C_FIRST_FRAME) != HAL_OK) {
                Error_Handler(__FILE__, __LINE__);
            }

            I2C2_rxBufferSize++;
        } else {
            I2C2_Status = I2C_STATUS_BUSY_TX;

            //TODO on request data (i2c restart occurred with change direction)
            //TODO remove Error_Handler call
            if (HAL_I2C_Slave_Sequential_Transmit_IT(&I2C2_Handle, &(I2C2_txBufferData[0]), I2C2_txBufferSize, I2C_LAST_FRAME) != HAL_OK) {
                Error_Handler(__FILE__, __LINE__);
            }
        }
    }
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *i2c) {
    if (i2c->Instance == I2C2) {
        //TODO on receive byte completed
        //TODO remove Error_Handler call
        //TODO if buffer overflow - pass dummy pointer to follow i2c flow
        if (HAL_I2C_Slave_Sequential_Receive_IT(&I2C2_Handle, &(I2C2_rxBufferData[I2C2_rxBufferSize]), 1, I2C_FIRST_FRAME) != HAL_OK) {
            Error_Handler(__FILE__, __LINE__);
        }

        I2C2_rxBufferSize++;
    }
}

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *i2c) {
    if (i2c->Instance == I2C2) {
        I2C2_txBufferSize = 0;
    }
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *i2c) {
    if (i2c->Instance == I2C2) {
        //TODO on receive data completed
        I2C2_Status = I2C_STATUS_SUCCESS;
    }
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *i2c) {
    if (i2c->Instance == I2C2) {
        //TODO store error to var for prevent call Error_Handler in IRQ handler
        if (HAL_I2C_GetError(i2c) != HAL_I2C_ERROR_AF) {
            Error_Handler(__FILE__, __LINE__);
        }

        I2C2_Status = I2C_STATUS_FAILURE;
    }
}

/* INTERRUPTS *********************************************************************************************************/

void I2C2_EV_IRQHandler(void) {
    HAL_I2C_EV_IRQHandler(&I2C2_Handle);
}

void I2C2_ER_IRQHandler(void) {
    HAL_I2C_ER_IRQHandler(&I2C2_Handle);
}

/* GPIO ***************************************************************************************************************/

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2c) {
    GPIO_InitTypeDef gpio;

    if (i2c->Instance == I2C2) {
        __HAL_RCC_I2C2_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        // PB6 ------> I2C_SCL
        // PB7 ------> I2C_SDA
        gpio.Pin   = GPIO_PIN_10 | GPIO_PIN_11;
        gpio.Mode  = GPIO_MODE_AF_OD;
        gpio.Speed = GPIO_SPEED_FREQ_HIGH;

        HAL_GPIO_Init(GPIOB, &gpio);

        HAL_NVIC_SetPriority(I2C2_EV_IRQn, 1, 1);
        HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);

        HAL_NVIC_SetPriority(I2C2_ER_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
    }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2c) {
    if (i2c->Instance == I2C2) {
        __HAL_RCC_I2C2_CLK_DISABLE();

        // PB6 ------> I2C_SCL
        // PB7 ------> I2C_SDA
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

        HAL_NVIC_DisableIRQ(I2C2_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C2_ER_IRQn);
    }
}
