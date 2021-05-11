#ifndef PE_SPI_H
#define PE_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//TODO enum
#define PE_SPI_MODE0 0b00
#define PE_SPI_MODE1 0b01
#define PE_SPI_MODE2 0b10
#define PE_SPI_MODE3 0b11

//TODO enum
#define PE_SPI_MSB_FIRST 0U
#define PE_SPI_LSB_FIRST 1U

//TODO SS pin abstraction
//TODO transmit/receive logic with interrupt based and blocking modes
//TODO separate configuration structure?
//TODO master/slave mode? maybe separate types
//TODO interrupt like callbacks?

typedef struct PE_SPI_Config_s {
    uint32_t baud;
    uint8_t bitOrder;
    uint8_t dataMode;
} PE_SPI_Config_t;

typedef struct PE_SPI_Device_s {
    uint8_t *txBuffer;
    volatile uint16_t txBufferTotal;
    uint16_t txBufferCount;
    uint8_t *rxBuffer;
    volatile uint16_t rxBufferTotal;
    uint16_t rxBufferCount;
} PE_SPI_Device_t;

void PE_SPI_send(PE_SPI_Device_t *device, uint8_t *data, uint16_t size);
void PE_SPI_read(PE_SPI_Device_t *device, uint8_t *data, uint16_t size);

void PE_SPI_onTXComplete(PE_SPI_Device_t *spi);
void PE_SPI_onRXComplete(PE_SPI_Device_t *spi);

void PE_SPI_select(PE_SPI_Device_t *spi);

#ifdef __cplusplus
}
#endif

#endif //PE_SPI_H
