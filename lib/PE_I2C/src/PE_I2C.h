#ifndef PE_I2C_H
#define PE_I2C_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef enum {
    I2C_STATE_READY   = 0x00U,
    I2C_STATE_LISTEN  = 0x01U,
    I2C_STATE_BUSY_RX = 0x02U,
    I2C_STATE_BUSY_TX = 0x03U,
    I2C_STATE_SUCCESS = 0x04U,
    I2C_STATE_FAILURE = 0x05U,
} PE_I2C_State_t;

typedef struct {
    uint32_t speed;
    uint8_t rxBufferData[5];
    uint8_t rxBufferSize;
    uint8_t txBufferData[4];
    uint8_t txBufferSize;
} PE_I2C_Device_t;

typedef struct {
    void *hw;
    PE_I2C_Device_t *device;
    PE_I2C_State_t status;
} PE_I2C_Driver_t;

//TODO PE_I2C_send(driver, device, data, size)
//TODO PE_I2C_read(driver, device, data, size)

#ifdef __cplusplus
}
#endif

#endif //PE_I2C_H
