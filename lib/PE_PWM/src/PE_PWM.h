//
// Created by master on 02.03.21.
//

#ifndef STM_32_HEXAPOD_API_PE_PWM_H
#define STM_32_HEXAPOD_API_PE_PWM_H

#include <stdint.h>

#define PE_PWM_CHANNEL_PER_TIMER 8

typedef struct PE_PWM_Channel_s {
    uint8_t ID;
    uint16_t ticks;
} PE_PWM_Channel_t;

typedef PE_PWM_Channel_t *PE_PWM_Channel_p;

typedef struct PE_PWM_Timer_s {
    volatile uint16_t counter;
    uint8_t channelCount;
    PE_PWM_Channel_p channelItems[PE_PWM_CHANNEL_PER_TIMER];
} PE_PWM_Timer_t;

void PE_PWM_createTimer(PE_PWM_Timer_t *timer);
void PE_PWM_dispatchTick(PE_PWM_Timer_t *timer);

void PE_PWM_setChannelPin0(uint8_t id);
void PE_PWM_setChannelPin1(uint8_t id);

#endif //STM_32_HEXAPOD_API_PE_PWM_H
