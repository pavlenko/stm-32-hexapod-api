#ifndef PE_I2C_DEVICE_H
#define PE_I2C_DEVICE_H

class PE_I2C_Device {
public:
    uint8_t *rxBufferData;
    uint8_t rxBufferCount;
    uint8_t rxBufferTotal;
    uint8_t *txBufferData;
    uint8_t txBufferCount;
    uint8_t txBufferTotal;
};

#endif //PE_I2C_DEVICE_H
