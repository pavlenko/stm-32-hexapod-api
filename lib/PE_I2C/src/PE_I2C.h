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

// Master functions
void PE_I2C_init(PE_I2C_Device_t *dev);// configure bus
void PE_I2C_wait(PE_I2C_Device_t *dev);// wait operation completed
void PE_I2C_stop(PE_I2C_Device_t *dev);// un-configure device (need?)

void PE_I2C_send(PE_I2C_Device_t *dev, uint8_t *data, uint16_t size);// send data in async mode
void PE_I2C_read(PE_I2C_Device_t *dev, uint8_t *data, uint16_t size);// read data in async mode

void PE_I2C_setMem(PE_I2C_Device_t *dev, uint16_t *addr, uint8_t addrSize, uint8_t *data, uint8_t size);// send data internal memory address
void PE_I2C_getMem(PE_I2C_Device_t *dev, uint16_t *addr, uint8_t addrSize, uint8_t *data, uint8_t size);// read data internal memory address

// Slave functions
void PE_I2C_listenTo(PE_I2C_Device_t *dev);// init slave mode with specific address + configure bus
void PE_I2C_onReceive();// call when master use send mode
void PE_I2C_onRequest();// call when master use read mode

// Interrupt handlers
void PE_I2C_TX_interrupt(PE_I2C_Device_t *dev);
void PE_I2C_RX_interrupt(PE_I2C_Device_t *dev);
void PE_I2C_ER_interrupt(PE_I2C_Device_t *dev);

//TODO callbacks

#ifdef __cplusplus
}
#endif

#endif //PE_I2C_H
