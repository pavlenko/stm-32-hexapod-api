#include "PE_I2C.h"

#include <stddef.h>
#include <stdint.h>

PE_I2C_Status_t PE_I2C_open(PE_I2C_Driver_t *driver, PE_I2C_Device_t *device) {
    if (driver->device != NULL) {
        return PE_I2C_STATUS_ERROR;
    }
    if (driver->state != PE_I2C_STATE_READY) {
        return PE_I2C_STATUS_BUSY;
    }

    driver->device = device;

    return PE_I2C_STATUS_OK;
}

PE_I2C_Status_t PE_I2C_wait(PE_I2C_Driver_t *driver) {
    //TODO maybe check timeout here & pass value for compare
    return PE_I2C_STATUS_OK;
}

PE_I2C_Status_t PE_I2C_stop(PE_I2C_Driver_t *driver) {
    if (driver->state != PE_I2C_STATE_READY) {
        return PE_I2C_STATUS_BUSY;
    }

    driver->device = NULL;
    return PE_I2C_STATUS_OK;
}

PE_I2C_Status_t PE_I2C_send(PE_I2C_Driver_t *driver, uint8_t *data, uint16_t size) {
    if (driver->state != PE_I2C_STATE_READY) {
        return PE_I2C_STATUS_BUSY;
    }

    driver->device->txBufferData  = data;
    driver->device->txBufferCount = 0;
    driver->device->txBufferTotal = size;

    driver->state = PE_I2C_STATE_BUSY_TX;

    //TODO pass to implementation
    return PE_I2C_STATUS_OK;
}

PE_I2C_Status_t PE_I2C_read(PE_I2C_Driver_t *driver, uint8_t *data, uint16_t size) {
    if (driver->state != PE_I2C_STATE_READY) {
        return PE_I2C_STATUS_BUSY;
    }

    driver->device->rxBufferData  = data;
    driver->device->rxBufferCount = 0;
    driver->device->rxBufferTotal = size;

    driver->state = PE_I2C_STATE_BUSY_RX;

    //TODO pass to implementation
    return PE_I2C_STATUS_OK;
}
