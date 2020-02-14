//
// Created by master on 29.01.20.
//

#include <V1/Movement.hpp>
#include <V2/hexapod.h>
#include "main.h"

int main()
{
    HP_initialize();

    uint32_t millis = 0;

    while (true) {
        HP_dispatch(millis);
        millis++;
    }
}
