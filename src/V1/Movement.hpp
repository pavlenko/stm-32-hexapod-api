//
// Created by master on 29.01.20.
//

#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <cstdint>

typedef struct {
    float moveX;
    float moveY;
    int8_t rotateX;
    int8_t rotateZ;
} control_t;

static control_t control;

static const uint32_t delay = 20;
static uint32_t latest;

static uint8_t step = 0;

static const float STEP_SIZE_X1_FULL = 30.0;
static const float STEP_SIZE_X1_PART = 7.5;

static const float STEP_SIZE_X2_FULL = 40.0;
static const float STEP_SIZE_X2_PART = 10.0;

static const float STEP_SIZE_X3_FULL = 60.0;
static const float STEP_SIZE_X3_PART = 15.0;

typedef enum Status {
    STATUS_IDLE,
    STATUS_MOVE,
} Status_t;

static Status_t status = STATUS_IDLE;

typedef enum Speed {
    Speed_X1,
    Speed_X2,
    Speed_X3,
    Speed_X4,
} Speed_t;

static Speed_t currSpeed = Speed_X1;// Private
static Speed_t nextSpeed = Speed_X1;// Public, may be set via some method

void dispatch(uint32_t millis) {
    // Delay logic
    if (millis - latest < delay) {
        return;
    }

    latest = millis;

    //TODO speed = step length * 1|2|3

    // algorithm step logic
    switch (step) {
        case 0:
            // Change speed (copy to private value for prevent change in other places)
            currSpeed = nextSpeed;

            if (status != STATUS_IDLE) {
                status = STATUS_IDLE;
                //TODO calculate positions
            }

            // Check if any control signal exists and if true - go to next step
            if (control.moveX != 0 || control.moveY != 0 || control.rotateX != 0 || control.rotateZ != 0) {
                // Go to move step
                step   = 1;
                status = STATUS_MOVE;
            }
            break;
        case 1:
            //TODO calculate positions

            // Go to next step
            step = 2;
            break;
        case 2:
            //TODO calculate positions

            // Go to next step
            step = 3;
            break;
        case 3:
            //TODO calculate positions

            if (control.moveX == 0 && control.moveY == 0 && control.rotateX == 0 && control.rotateZ == 0) {
                // Go to init step
                step = 0;
            } else {
                // Go to next step
                step = 4;
            }
            break;
        case 4:
            // Change speed (copy to private value for prevent change in other places)
            currSpeed = nextSpeed;

            //TODO calculate positions

            // Go to next step
            step = 5;
            break;
        case 5:
            //TODO calculate positions

            // Go to next step
            step = 6;
            break;
        case 6:
            //TODO calculate positions

            // Go to next step
            step = 7;
            break;
        case 7:
            //TODO calculate positions

            if (control.moveX == 0 && control.moveY == 0 && control.rotateX == 0 && control.rotateZ == 0) {
                // Go to init step
                step = 0;
            } else {
                // Go to next step
                step = 8;
            }
            break;
        case 8:
            // Change speed (copy to private value for prevent change in other places)
            currSpeed = nextSpeed;

            //TODO calculate positions

            // Go to next step
            step = 1;
            break;
    }
}

#endif //MOVEMENT_HPP
