//
// Created by master on 29.01.20.
//

#include <hexapod.h>
#include <PE_SpiderV2.h>
#include "main.h"

PE_SpiderV2_t spider;

int main()
{
    HP_initialize();

    uint32_t millis = 0;

    while (true) {
        HP_dispatch(millis);
        PE_SpiderV2_dispatch(&spider, millis);
        millis++;
    }
}
