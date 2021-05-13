#include "PE_SPI.h"

#include <stddef.h>

void PE_SPI_init(PE_SPI_Device_t *device)
{
    //TODO split master/slave definitions
    //TODO deselect
    //TODO set config
    //TODO call specific init implementation
}

void PE_SPI_send(PE_SPI_Device_t *device, uint8_t *data, uint16_t size, uint32_t timeout)
{
    PE_SPI_select(device);
}

__attribute__((weak))
void PE_SPI_wait(PE_SPI_Device_t *device)
{
    (void) device;
}

__attribute__((weak))
void PE_SPI_chipSelectSet(PE_SPI_Device_t *device)
{
    (void) device;
}

__attribute__((weak))
void PE_SPI_chipSelectClr(PE_SPI_Device_t *device)
{
    (void) device;
}