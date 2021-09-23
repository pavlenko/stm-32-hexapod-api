#ifndef PE_I2C_H
#define PE_I2C_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef enum {
    PE_I2C_STATUS_OK      = 0x00U,
    PE_I2C_STATUS_ERROR   = 0x01U,
    PE_I2C_STATUS_BUSY    = 0x02U,
    PE_I2C_STATUS_TIMEOUT = 0x03U,
} PE_I2C_Status_t;

typedef enum {
    PE_I2C_STATE_READY   = 0x00U,
    PE_I2C_STATE_LISTEN  = 0x01U,
    PE_I2C_STATE_BUSY_RX = 0x02U,
    PE_I2C_STATE_BUSY_TX = 0x03U,
    PE_I2C_STATE_SUCCESS = 0x04U,//TODO move to result?
    PE_I2C_STATE_FAILURE = 0x05U,//TODO move to result?
} PE_I2C_State_t;

typedef struct {
    uint16_t address;
    uint8_t *rxBufferData;
    uint8_t rxBufferCount;
    uint8_t rxBufferTotal;
    uint8_t *txBufferData;
    uint8_t txBufferCount;
    uint8_t txBufferTotal;
} PE_I2C_Device_t;

typedef struct {
    void *hw;
    uint32_t speed;
    PE_I2C_Device_t *device;
    PE_I2C_State_t state;
} PE_I2C_Driver_t;

// Master functions
PE_I2C_Status_t PE_I2C_open(PE_I2C_Driver_t *driver, PE_I2C_Device_t *device);
PE_I2C_Status_t PE_I2C_wait(PE_I2C_Driver_t *driver);
PE_I2C_Status_t PE_I2C_stop(PE_I2C_Driver_t *driver);

PE_I2C_Status_t PE_I2C_send(PE_I2C_Driver_t *driver, uint8_t *data, uint16_t size);// send data in async mode
PE_I2C_Status_t PE_I2C_read(PE_I2C_Driver_t *driver, uint8_t *data, uint16_t size);// read data in async mode

PE_I2C_Status_t PE_I2C_setMem(PE_I2C_Driver_t *driver, uint16_t *addr, uint8_t addrSize, uint8_t *data, uint8_t size);// send data internal memory address
PE_I2C_Status_t PE_I2C_getMem(PE_I2C_Driver_t *driver, uint16_t *addr, uint8_t addrSize, uint8_t *data, uint8_t size);// read data internal memory address

// Slave functions
void PE_I2C_listenTo(PE_I2C_Driver_t *driver);// init slave mode with specific address + configure bus
void PE_I2C_onReceive();// call when master use send mode
void PE_I2C_onRequest();// call when master use read mode

// Interrupt handlers
void PE_I2C_TX_interrupt(PE_I2C_Driver_t *driver);
void PE_I2C_RX_interrupt(PE_I2C_Driver_t *driver);
void PE_I2C_ER_interrupt(PE_I2C_Driver_t *driver);

//TODO callbacks

#ifdef __cplusplus
}
#endif

#endif //PE_I2C_H
