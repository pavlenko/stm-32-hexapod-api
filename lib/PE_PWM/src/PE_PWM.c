//
// Created by master on 02.03.21.
//

#include "PE_PWM.h"

#include <stddef.h>

void PE_PWM_dispatchTick(PE_PWM_Timer_t *timer) {
    uint8_t i;

    // First set all channels high (if configured)
    if (timer->counter == 0) {
        for (i = 0; i < PE_PWM_CHANNEL_PER_TIMER; i++) {
            if (timer->items[timer->index] != NULL) {
                PE_PWM_setChannelPin1(timer->items[timer->index]->ID);
            }
        }
    }

    timer->counter++;

    // Loop through all channels, if tick match - set 0, else - set 1
    for (i = 0; i < PE_PWM_CHANNEL_PER_TIMER; i++) {
        if (timer->items[timer->index] != NULL) {
            if (timer->items[timer->index]->ticks == timer->counter) {
                PE_PWM_setChannelPin0(timer->items[timer->index]->ID);
            } else {
                PE_PWM_setChannelPin1(timer->items[timer->index]->ID);
            }
        }
    }
}