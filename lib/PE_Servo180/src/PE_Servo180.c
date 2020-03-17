#include "PE_Servo180.h"

#include <stdio.h>

typedef struct {
    uint8_t active;
    uint16_t ticks;
} servo_t;

typedef struct {
    int8_t servoN;
    servo_t *servos;
    volatile uint16_t *counter;
    volatile uint16_t *compare;
} channel_t;

static uint16_t _TICKS_PER_MICROSECOND = 1;
static uint16_t _REFRESH_INTERVAL      = 20000;
static uint8_t _SERVOS_PER_CHANNEL     = 0;

#define usToTicks(_us)    (_TICKS_PER_MICROSECOND * _us)     // converts microseconds to tick
#define ticksToUs(_ticks) (((unsigned)_ticks) / _TICKS_PER_MICROSECOND ) // converts from ticks back to microseconds

channel_t channels[5] = {
        {0, NULL}
};

inline void PE_Servo180_ISR(uint8_t channelN) {
    channel_t channel = channels[channelN];

    if (channel.servoN < 0) {
        *(channel.counter) = 0;
    } else if (channel.servos[channel.servoN].active) {
        PE_Servo180_pinClr(channelN, channel.servoN);
    }

    channel.servoN++;

    if (channel.servoN < _SERVOS_PER_CHANNEL) {
        *(channel.compare) = *(channel.counter) + channel.servos[channel.servoN].ticks;

        if (channel.servos[channel.servoN].active) {
            PE_Servo180_pinSet(channelN, channel.servoN);
        }
    } else {
        uint16_t refresh = usToTicks(_REFRESH_INTERVAL);

        if (*(channel.counter) < (refresh + 4)) {
            *(channel.compare) = refresh;
        } else {
            *(channel.compare) = *(channel.counter) + 4;
        }
    }
}

void inline PE_Servo180_pinSet(uint8_t channel, uint8_t motor) {
    (void) channel;
    (void) motor;
}

void inline PE_Servo180_pinClr(uint8_t channel, uint8_t motor) {
    (void) channel;
    (void) motor;
}

// Weak function default implementation fol allow override
__attribute__((weak)) void EX_weak_function() {}