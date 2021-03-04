//
// Created by master on 02.03.21.
//

#include "PE_PWM.h"

#include <stddef.h>

void PE_PWM_createTimer(PE_PWM_Timer_t *timer) {
    uint8_t index;

    timer->channelCount = 0;
    timer->counter      = 0;

    for (index = 0; index < PE_PWM_CHANNEL_PER_TIMER; index++) {
        timer->channelItems[index] = NULL;
    }
}

void PE_PWM_dispatchTick(PE_PWM_Timer_t *timer) {
    uint8_t index;

    // First set all channels high (if configured)
    if (timer->counter == 0) {
        for (index = 0; index < PE_PWM_CHANNEL_PER_TIMER; index++) {
            if (timer->channelItems[index] != NULL) {
                PE_PWM_setChannelPin1(timer->channelItems[index]->ID);
            }
        }
    }

    timer->counter++;

    // Loop through all channels, if tick match - set 0
    for (index = 0; index < PE_PWM_CHANNEL_PER_TIMER; index++) {
        if (timer->channelItems[index] != NULL && timer->channelItems[index]->ticks == timer->counter) {
            PE_PWM_setChannelPin0(timer->channelItems[index]->ID);
        }
    }
}

__attribute__((weak))
void PE_PWM_setChannelPin0(uint8_t id) {
    (void) id;
}

__attribute__((weak))
void PE_PWM_setChannelPin1(uint8_t id) {
    (void) id;
}