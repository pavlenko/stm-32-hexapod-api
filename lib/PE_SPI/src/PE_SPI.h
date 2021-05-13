#ifndef PE_SPI_H
#define PE_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef enum {
    PE_SPI_DATA_MODE_0 = 0x0U,
    PE_SPI_DATA_MODE_1 = 0x1U,
    PE_SPI_DATA_MODE_2 = 0x2U,
    PE_SPI_DATA_MODE_3 = 0x3U,
} PE_SPI_DataMode_t;

typedef enum {
    PE_SPI_MSB_FIRST = 0x0U,
    PE_SPI_LSB_FIRST = 0x1U,
} PE_SPI_BitOrder_t;

typedef enum {
    PE_SPI_STATUS_OK    = 0x0U,
    PE_SPI_STATUS_ERROR = 0x1U,
    /*TODO other statuses*/
} PE_SPI_Status_t;

//TODO SS pin abstraction
//TODO transmit/receive logic with interrupt based and blocking modes
//TODO separate configuration structure?
//TODO master/slave mode? maybe separate types
//TODO interrupt like callbacks?

typedef struct PE_SPI_Device_s {
    uint32_t baudRate;
    PE_SPI_BitOrder_t bitOrder;
    PE_SPI_DataMode_t dataMode;
    uint8_t *txBuffer;
    volatile uint16_t txTotal;
    volatile uint16_t txCount;
} PE_SPI_Device_t;

typedef struct PE_SPI_Driver_s {
    void *hw;
    PE_SPI_Device_t *device;
    PE_SPI_Status_t status;
} PE_SPI_Driver_t;

/**
 * @param driver
 * @param hw
 * @return
 */
PE_SPI_Status_t PE_SPI_initDriver(PE_SPI_Driver_t *driver, void *hw);

/**
 * @param device
 * @param baudRate
 * @param bitOrder
 * @param dataMode
 * @return
 */
PE_SPI_Status_t PE_SPI_initDevice(PE_SPI_Device_t *device, uint32_t baudRate, PE_SPI_BitOrder_t bitOrder, PE_SPI_DataMode_t dataMode);

// tx, tx, tx, ...
PE_SPI_Status_t PE_SPI_transmit(PE_SPI_Driver_t *driver, PE_SPI_Device_t *device, uint8_t *data, uint16_t size);

// rx, rx, rx, ...
PE_SPI_Status_t PE_SPI_receive(PE_SPI_Driver_t *driver, PE_SPI_Device_t *device, uint8_t *data, uint16_t size);

// tx, rx, tx, rx, ...
PE_SPI_Status_t PE_SPI_transfer(PE_SPI_Driver_t *driver, PE_SPI_Device_t *device, uint8_t *txData, uint8_t *rxData, uint16_t size);

void PE_SPI_send(PE_SPI_Device_t *device, uint8_t *data, uint16_t size);
void PE_SPI_wait(PE_SPI_Device_t *device);

void PE_SPI_onTXComplete(PE_SPI_Device_t *device);
void PE_SPI_onRXComplete(PE_SPI_Device_t *device);

void PE_SPI_chipSelectSet(PE_SPI_Device_t *device);
void PE_SPI_chipSelectClr(PE_SPI_Device_t *device);

#ifdef __cplusplus
}
#endif

#endif //PE_SPI_H
