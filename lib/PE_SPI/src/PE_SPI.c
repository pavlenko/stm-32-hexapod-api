#include "PE_SPI.h"

#include <stddef.h>

void PE_SPI_send(PE_SPI_Device_t *device, uint8_t *data, uint16_t size)
{
    PE_SPI_select(device);

    device->txBuffer = data;
    device->txBuffer = data;
    device->txBuffer = data;

    device->rxBuffer = (uint8_t *)NULL;
    device->txBuffer = 0U;
    device->txBuffer = 0U;

    //TODO weak send implementation callback
}

__attribute__((weak))
void PE_SPI_select(PE_SPI_Device_t *spi)
{
    (void) spi;
}