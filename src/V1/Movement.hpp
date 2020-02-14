//
// Created by master on 29.01.20.
//

#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <cstdint>

/*
enum class Power {
    OFF,
    ON,
};

static Power power;

static const uint32_t DELAY_DEFAULT = 20;

static uint32_t delay = DELAY_DEFAULT;
static uint32_t latest;

static const float STEP_SIZE_X1_FULL = 30.0;
static const float STEP_SIZE_X1_PART = 7.5;

static const float STEP_SIZE_X2_FULL = 40.0;
static const float STEP_SIZE_X2_PART = 10.0;

static const float STEP_SIZE_X3_FULL = 60.0;
static const float STEP_SIZE_X3_PART = 15.0;

typedef enum Step_e {
    STEP_IDLE,
    STEP_MOVE_1,
    STEP_MOVE_2,
    STEP_MOVE_3,
    STEP_MOVE_4,
    STEP_MOVE_5,
    STEP_MOVE_6,
    STEP_MOVE_7,
    STEP_MOVE_8,
} Step_t;

static Step_t step = STEP_IDLE;

typedef enum Status_e {
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

enum class State {
    BOOTING,
    WAITING,
    MOVING,
    CONFIGURE,
    SHUTDOWN,
};

static State state;

static bool mustShutdown;

void initialize() {
    // Set power enable pin to ON state (this must be a set GPIO port pin value)
    power = Power::ON;
}

void dispatch(uint32_t millis) {
    // Delay logic
    if (millis - latest < delay) {
        return;
    }

    latest = millis;

    //TODO speed = step length * 1|2|3

    switch (state) {
        case State::BOOTING:
            //TODO set standby positions

            // Go to next state
            state = State::WAITING;
            break;
        case State::WAITING:
            //TODO set idle positions, once

            // Go to next state
            if (control.moveX != 0 || control.moveY != 0 || control.rotateX != 0 || control.rotateZ != 0) {
                state = State::MOVING;
            } else if (mustShutdown) {
                state = State::SHUTDOWN;
            }
            break;
        case State::MOVING:
            //TODO process moving steps
            break;
        case State::CONFIGURE:
            //TODO process configure
            break;
        case State::SHUTDOWN:
            //TODO set standby positions, once

            // Disable power
            power = Power::OFF;
            break;
    }

    // algorithm step logic
    switch (step) {
        case STEP_IDLE:
            // Change speed (copy to private value for prevent change in other places)
            currSpeed = nextSpeed;

            if (status != STATUS_IDLE) {
                status = STATUS_IDLE;
                //TODO calculate positions
            }

            // Check if any control signal exists and if true - go to next step
            if (control.moveX != 0 || control.moveY != 0 || control.rotateX != 0 || control.rotateZ != 0) {
                // Go to move step
                step   = STEP_MOVE_1;
                status = STATUS_MOVE;
            }
            break;
        case STEP_MOVE_1:
            //TODO calculate positions

            // Go to next step
            step = STEP_MOVE_2;
            break;
        case STEP_MOVE_2:
            //TODO calculate positions

            // Go to next step
            step = STEP_MOVE_3;
            break;
        case STEP_MOVE_3:
            //TODO calculate positions

            if (control.moveX == 0 && control.moveY == 0 && control.rotateX == 0 && control.rotateZ == 0) {
                // Go to init step
                step = STEP_IDLE;
            } else {
                // Go to next step
                step = STEP_MOVE_4;
            }
            break;
        case STEP_MOVE_4:
            // Change speed (copy to private value for prevent change in other places)
            currSpeed = nextSpeed;

            //TODO calculate positions

            // Go to next step
            step = STEP_MOVE_5;
            break;
        case STEP_MOVE_5:
            //TODO calculate positions

            // Go to next step
            step = STEP_MOVE_6;
            break;
        case STEP_MOVE_6:
            //TODO calculate positions

            // Go to next step
            step = STEP_MOVE_7;
            break;
        case STEP_MOVE_7:
            //TODO calculate positions

            if (control.moveX == 0 && control.moveY == 0 && control.rotateX == 0 && control.rotateZ == 0) {
                // Go to init step
                step = STEP_IDLE;
            } else {
                // Go to next step
                step = STEP_MOVE_8;
            }
            break;
        case STEP_MOVE_8:
            // Change speed (copy to private value for prevent change in other places)
            currSpeed = nextSpeed;

            //TODO calculate positions

            // Go to next step
            step = STEP_MOVE_1;
            break;
    }
}
*/

void calculateInit();
void calculateIdle();
void calculateStep1();
void calculateStep2();
void calculateStep3();
void calculateStep4();
void calculateStep5();
void calculateStep6();
void calculateStep7();
void calculateStep8();

#endif //MOVEMENT_HPP
