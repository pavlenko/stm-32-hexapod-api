#include "PE_SPI.h"

PE_SPI_Status_t PE_SPI_initDriver(PE_SPI_Driver_t *driver, void *hw)
{
    if (NULL == driver || NULL == hw) {
        return PE_SPI_STATUS_ERROR;
    }

    driver->hw     = hw;
    driver->device = NULL;

    return PE_SPI_STATUS_OK;
}

PE_SPI_Status_t PE_SPI_initDevice(PE_SPI_Device_t *device, uint32_t baudRate, PE_SPI_BitOrder_t bitOrder, PE_SPI_DataMode_t dataMode)
{
    if (NULL == device) {
        return PE_SPI_STATUS_ERROR;
    }

    device->baudRate = baudRate;
    device->bitOrder = bitOrder;
    device->dataMode = dataMode;

    return PE_SPI_STATUS_OK;
}

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

__attribute__((weak))
void PE_SPI_onTXCompleted(PE_SPI_Driver_t *driver)
{
    (void) driver;
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
void PE_SPI_onRXCompleted(PE_SPI_Driver_t *driver)
{
    (void) driver;
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
