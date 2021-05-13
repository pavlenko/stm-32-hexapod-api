#include "PE_SPI.h"

#include <stddef.h>

void PE_SPI_init(PE_SPI_Device_t *device)
{
    //TODO split master/slave definitions
    //TODO deselect
    //TODO set config
    //TODO call specific init implementation
}

void PE_SPI_send(PE_SPI_Device_t *device, uint8_t *data, uint16_t size)
{
    //TODO select slave device
    //TODO maybe configure SPI parameters?
    //TODO call send implementation
}

void PE_SPI_onTXComplete(PE_SPI_Device_t *device)
{
    //TODO update status
    //TODO clear slave device pointer
    //TODO unselect slave device
    //TODO maybe call user function?
}

void PE_SPI_onRXComplete(PE_SPI_Device_t *device)
{
    //TODO update status
    //TODO clear slave device pointer
    //TODO maybe call user function
}

__attribute__((weak))
void PE_SPI_wait(PE_SPI_Device_t *device)
{
    //TODO maybe call wait implementation instead of weak?
    //TODO maybe add timeout check?
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