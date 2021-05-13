#include "PE_SPI.h"

int main(void)
{
    PE_SPI_Device_t spi;

    char data = "Hello World!";
    while (1) {
        PE_SPI_send(&spi, (uint8_t *) data, sizeof(data), 1000);
        PE_SPI_wait(&spi);
    }
}