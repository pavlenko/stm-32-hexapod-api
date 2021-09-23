#ifndef PE_I2C_DRIVER_H
#define PE_I2C_DRIVER_H

#include <stddef.h>
#include <stdint.h>

//TODO device
//TODO status
//TODO lock
//TODO callbacks?
class PE_I2C_Driver {
private:
    void *hw;
    uint32_t speed;
    void *device;
    uint8_t status;
public:
    PE_I2C_Driver();

    void open(void *device);// configure bus
    void wait();// wait operation completed
    void stop();// un-configure device (need?)

    void send(uint8_t *data, uint16_t size);// send data in async mode
    void read(uint8_t *data, uint16_t size);// read data in async mode

    void setMem(uint16_t *addr, uint8_t addrSize, uint8_t *data, uint8_t size);// send data internal memory address
    void getMem(uint16_t *addr, uint8_t addrSize, uint8_t *data, uint8_t size);// read data internal memory address
};

#endif //PE_I2C_DRIVER_H
