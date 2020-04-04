#include "nRF24.h"

void MX_nRF24_Init(PE_nRF24_t *handle) {
    PE_nRF24_Config_t config;

    config.rfChannel    = 2;
    config.payloadWidth = 1;
    config.crcScheme    = PE_nRF24_CRC_SCHEME_1BYTE;
    config.txPower      = PE_nRF24_TX_POWER_18dBm;
    config.dataRate     = PE_nRF24_DATA_RATE__250KBPS;
    config.retryCount   = PE_nRF24_RETRY_COUNT__1;
    config.retryDelay   = PE_nRF24_RETRY_DELAY_1000us;
    config.addressWidth = PE_nRF24_ADDR_WIDTH_5BIT;
    config.addressRX    = (uint8_t *) PE_nRF24_TEST_ADDRESS;
    config.addressTX    = (uint8_t *) PE_nRF24_TEST_ADDRESS;

    if (PE_nRF24L01_initialize(handle, &config) != PE_nRF24_RESULT_OK) {
        Error_Handler(__FILE__, __LINE__);
    }
}

//TODO move integration function here
