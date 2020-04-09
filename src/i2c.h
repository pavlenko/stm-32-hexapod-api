#ifndef __I2C_H
#define __I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void MX_I2C2_Init(uint16_t address);

void MX_I2C2_dispatch();

#ifdef __cplusplus
}
#endif

#endif //__I2C_H
