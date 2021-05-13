#include "PE_SPI.h"
#include "stm32f1xx.h"

SPI_HandleTypeDef hSPI1;
PE_SPI_Device_t spi;

int main(void) {
    uint8_t data[16];
    while (1) {
        PE_SPI_read(&spi, (uint8_t *) data, sizeof(data), 1000);
        PE_SPI_wait(&spi);
        //TODO Do something with received data
    }
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi == &hSPI1) {
        PE_SPI_onRXComplete(&spi);
    }
}

void SPI1_IRQHandler() {
    HAL_SPI_IRQHandler(&hSPI1);
}