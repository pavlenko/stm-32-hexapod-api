#include "../src/PE_I2C.h"

PE_I2C_Device_t device1;
PE_I2C_Device_t device2;

PE_I2C_Driver_t driver;

int main (void) {
    uint8_t data[10];

    PE_I2C_send(device1, &data, 10);
}

int main2 (void) {
    //TODO maybe better
    I2C1->open(device1);// Set internal device pointer for lock
    I2C1->send(&data, 10);// Send data and maybe lock here
    I2C1->wait();// wait for completion
    I2C1->stop();// free lock & clear pointer to device
}