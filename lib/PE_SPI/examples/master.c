#include "PE_SPI.h"
#include "stm32f1xx.h"

SPI_HandleTypeDef hSPI1;
PE_SPI_Device_t spi;

int main(void) {
    char data = "Hello World!";
    while (1) {
        PE_SPI_send(&spi, (uint8_t *) data, sizeof(data), 1000);
        PE_SPI_wait(&spi);
    }
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi == &hSPI1) {
        PE_SPI_onTXComplete(&spi);
    }
}

void SPI1_IRQHandler() {
    HAL_SPI_IRQHandler(&hSPI1);
}