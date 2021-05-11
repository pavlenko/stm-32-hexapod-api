#ifndef PE_SPI_H
#define PE_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//TODO SS pin abstraction
//TODO transmit/receive logic with interrupt based and blocking modes
//TODO separate configuration structure?
//TODO master/slave mode? maybe separate types
//TODO interrupt like callbacks?

typedef struct PE_SPI_Device_s {
    uint8_t *txBuffer;
    volatile uint16_t txBufferTotal;
    uint16_t txBufferCount;
    uint8_t *rxBuffer;
    volatile uint16_t rxBufferTotal;
    uint16_t rxBufferCount;
} PE_SPI_Device_t;

void PE_SPI_onTXComplete(PE_SPI_Device_t *spi);
void PE_SPI_onRXComplete(PE_SPI_Device_t *spi);

#ifdef __cplusplus
}
#endif

#endif //PE_SPI_H
