#include "PE_SPI.h"

PE_SPI_Status_t PE_SPI_send(PE_SPI_Driver_t *driver, PE_SPI_Device_t *device, uint8_t *data, uint16_t size)
{
    if (NULL == driver || NULL == device || NULL == data || 0 == size) {
        return PE_SPI_STATUS_ERROR;
    }
    if (PE_SPI_STATUS_OK != driver->status) {
        return PE_SPI_STATUS_BUSY_TX;
    }

    device->txBuffer = data;
    device->txTotal  = size;
    device->txCount  = size;

    driver->device = device;
    driver->status = PE_SPI_STATUS_BUSY_TX;

    PE_SPI_init(driver);
    PE_SPI_chipSelect(device, PE_SPI_CS_LO);
    PE_SPI_doSend(driver);

    return PE_SPI_STATUS_OK;
}

__attribute__((weak))
void PE_SPI_doSend(PE_SPI_Driver_t *driver)
{
    (void) driver;
}

PE_SPI_Status_t PE_SPI_read(PE_SPI_Driver_t *driver, PE_SPI_Device_t *device, uint8_t *data, uint16_t size)
{
    if (NULL == driver || NULL == device || NULL == data || 0 == size) {
        return PE_SPI_STATUS_ERROR;
    }
    if (PE_SPI_STATUS_OK != driver->status) {
        return PE_SPI_STATUS_BUSY_RX;
    }

    device->rxBuffer = data;
    device->rxTotal  = size;
    device->rxCount  = size;

    driver->device = device;
    driver->status = PE_SPI_STATUS_BUSY_TX;

    PE_SPI_init(driver);
    PE_SPI_chipSelect(device, PE_SPI_CS_LO);
    PE_SPI_doRead(driver);

    return PE_SPI_STATUS_OK;
}

void PE_SPI_onTX_ISR(PE_SPI_Driver_t *driver, uint8_t *data)
{
    if (NULL == driver) {
        return;
    }
    if (NULL == driver->device) {
        driver->status = PE_SPI_STATUS_ERROR;
        return;
    }

    if (0U == driver->device->txCount) {
        // Send completed
        PE_SPI_chipSelect(driver->device, PE_SPI_CS_HI);
        driver->status = PE_SPI_STATUS_OK;
        PE_SPI_onTXCompleted(driver);
    } else {
        // Send next byte
        *data = (*driver->device->txBuffer++);
        driver->device->txCount--;
    }
}

void PE_SPI_onRX_ISR(PE_SPI_Driver_t *driver, uint8_t *data)
{
    *driver->device->rxBuffer = *data;
    driver->device->rxCount--;

    if (0U == driver->device->rxCount) {
        PE_SPI_chipSelect(driver->device, PE_SPI_CS_HI);
        driver->status = PE_SPI_STATUS_OK;
        PE_SPI_onRXCompleted(driver);
    }
}

__attribute__((weak))
void PE_SPI_init(PE_SPI_Driver_t *driver)
{
    (void) driver;
}

__attribute__((weak))
void PE_SPI_wait(PE_SPI_Driver_t *driver)
{
    (void) driver;
}

__attribute__((weak))
void PE_SPI_chipSelect(PE_SPI_Device_t *device, PE_SPI_CS_t value)
{
    (void) device;
    (void) value;
}

__attribute__((weak))
void PE_SPI_onTXCompleted(PE_SPI_Driver_t *driver)
{
    (void) driver;
}

__attribute__((weak))
void PE_SPI_onRXCompleted(PE_SPI_Driver_t *driver)
{
    (void) driver;
}

static void SPI_2linesTxISR_8BIT(struct __SPI_HandleTypeDef *hspi) {
    *(__IO uint8_t *)&hspi->Instance->DR = (*hspi->pTxBuffPtr++);
    hspi->TxXferCount--;

    /* check the end of the transmission */
    if (hspi->TxXferCount == 0U) {
        /* Disable TXE interrupt */
        __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);

        if(hspi->RxXferCount == 0U) {
            SPI_CloseRxTx_ISR(hspi);
        }
    }
}

static void SPI_TxISR_8BIT(struct __SPI_HandleTypeDef *hspi) {
    *(__IO uint8_t *)&hspi->Instance->DR = (*hspi->pTxBuffPtr++);
    hspi->TxXferCount--;

    if (hspi->TxXferCount == 0U) {
        SPI_CloseTx_ISR(hspi);
    }
}

static void SPI_RxISR_8BIT(struct __SPI_HandleTypeDef *hspi) {
    *hspi->pRxBuffPtr++ = (*(__IO uint8_t *)&hspi->Instance->DR);
    hspi->RxXferCount--;

    if (hspi->RxXferCount == 0U) {
        SPI_CloseRx_ISR(hspi);
    }
}

static void SPI_2linesRxISR_8BIT(struct __SPI_HandleTypeDef *hspi) {
    /* Receive data in 8bit mode */
    *hspi->pRxBuffPtr++ = *((__IO uint8_t *)&hspi->Instance->DR);
    hspi->RxXferCount--;

    /* check end of the reception */
    if (hspi->RxXferCount == 0U) {
        /* Disable RXNE interrupt */
        __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));

        if (hspi->TxXferCount == 0U) {
            SPI_CloseRxTx_ISR(hspi);
        }
    }
}

static void SPI_CloseRxTx_ISR(SPI_HandleTypeDef *hspi) {
    uint32_t tickstart = 0U;
    __IO uint32_t count = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);
    /* Init tickstart for timeout managment*/
    tickstart = HAL_GetTick();

    /* Disable ERR interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_ERR);

    /* Wait until TXE flag is set */
    do {
        if (count-- == 0U) {
            SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
            break;
        }
    } while((hspi->Instance->SR & SPI_FLAG_TXE) == RESET);

    /* Check the end of the transaction */
    if (SPI_CheckFlag_BSY(hspi, SPI_DEFAULT_TIMEOUT, tickstart)!=HAL_OK) {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    }

    /* Clear overrun flag in 2 Lines communication mode because received is not read */
    if (hspi->Init.Direction == SPI_DIRECTION_2LINES) {
        __HAL_SPI_CLEAR_OVRFLAG(hspi);
    }

    if (hspi->ErrorCode == HAL_SPI_ERROR_NONE) {
        if (hspi->State == HAL_SPI_STATE_BUSY_RX) {
            hspi->State = HAL_SPI_STATE_READY;
            HAL_SPI_RxCpltCallback(hspi);
        } else {
            hspi->State = HAL_SPI_STATE_READY;
            HAL_SPI_TxRxCpltCallback(hspi);
        }
    } else {
        hspi->State = HAL_SPI_STATE_READY;
        HAL_SPI_ErrorCallback(hspi);
    }
}

static void SPI_CloseRx_ISR(SPI_HandleTypeDef *hspi) {
    /* Disable RXNE and ERR interrupt */
    __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));

    /* Check the end of the transaction */
    if ((hspi->Init.Mode == SPI_MODE_MASTER) && ((hspi->Init.Direction == SPI_DIRECTION_1LINE) || (hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY))) {
        /* Disable SPI peripheral */
        __HAL_SPI_DISABLE(hspi);
    }

    /* Clear overrun flag in 2 Lines communication mode because received is not read */
    if (hspi->Init.Direction == SPI_DIRECTION_2LINES) {
        __HAL_SPI_CLEAR_OVRFLAG(hspi);
    }
    hspi->State = HAL_SPI_STATE_READY;

    if (hspi->ErrorCode == HAL_SPI_ERROR_NONE) {
        HAL_SPI_RxCpltCallback(hspi);
    } else {
        HAL_SPI_ErrorCallback(hspi);
    }
}

static void SPI_CloseTx_ISR(SPI_HandleTypeDef *hspi) {
    uint32_t tickstart = 0U;
    __IO uint32_t count = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);

    /* Init tickstart for timeout management*/
    tickstart = HAL_GetTick();

    /* Wait until TXE flag is set */
    do {
        if (count-- == 0U) {
            SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
            break;
        }
    } while((hspi->Instance->SR & SPI_FLAG_TXE) == RESET);

    /* Disable TXE and ERR interrupt */
    __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_ERR));

    /* Check Busy flag */
    if (SPI_CheckFlag_BSY(hspi, SPI_DEFAULT_TIMEOUT, tickstart) != HAL_OK) {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    }

    /* Clear overrun flag in 2 Lines communication mode because received is not read */
    if (hspi->Init.Direction == SPI_DIRECTION_2LINES) {
        __HAL_SPI_CLEAR_OVRFLAG(hspi);
    }

    hspi->State = HAL_SPI_STATE_READY;
    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE) {
        HAL_SPI_ErrorCallback(hspi);
    } else {
        HAL_SPI_TxCpltCallback(hspi);
    }
}
