//
// Created by master on 02.02.20.
//

#include "Hexapod.hpp"

void MODE_BOOTING_onEntering(PE_FSM &fsm);
void MODE_WAITING_onEntering(PE_FSM &fsm);
void MODE_WAITING_onDispatch(PE_FSM &fsm);
void MODE_MOVING_onDispatch(PE_FSM &fsm);
void MODE_CONFIGURE_onEntering(PE_FSM &fsm);
void MODE_SHUTDOWN_onEntering(PE_FSM &fsm);
void MODE_SHUTDOWN_onDispatch(PE_FSM &fsm);

PE_FSMState MODE_BOOTING   = PE_FSMState(MODE_BOOTING_onEntering, nullptr);
PE_FSMState MODE_WAITING   = PE_FSMState(MODE_WAITING_onEntering, MODE_WAITING_onDispatch);
PE_FSMState MODE_MOVING    = PE_FSMState(nullptr, MODE_MOVING_onDispatch);
PE_FSMState MODE_CONFIGURE = PE_FSMState(MODE_CONFIGURE_onEntering, nullptr);
PE_FSMState MODE_SHUTDOWN  = PE_FSMState(MODE_SHUTDOWN_onEntering, MODE_SHUTDOWN_onDispatch);

PE_FSM ModeFSM = PE_FSM();

void MOVE_STEP1_onEntering(PE_FSM &fsm);
void MOVE_STEP2_onEntering(PE_FSM &fsm);
void MOVE_STEP3_onEntering(PE_FSM &fsm);
void MOVE_STEP4_onEntering(PE_FSM &fsm);
void MOVE_STEP5_onEntering(PE_FSM &fsm);
void MOVE_STEP6_onEntering(PE_FSM &fsm);
void MOVE_STEP7_onEntering(PE_FSM &fsm);
void MOVE_STEP8_onEntering(PE_FSM &fsm);

PE_FSMState MOVE_STEP1 = PE_FSMState(MOVE_STEP1_onEntering, nullptr);
PE_FSMState MOVE_STEP2 = PE_FSMState(MOVE_STEP2_onEntering, nullptr);
PE_FSMState MOVE_STEP3 = PE_FSMState(MOVE_STEP3_onEntering, nullptr);
PE_FSMState MOVE_STEP4 = PE_FSMState(MOVE_STEP4_onEntering, nullptr);
PE_FSMState MOVE_STEP5 = PE_FSMState(MOVE_STEP5_onEntering, nullptr);
PE_FSMState MOVE_STEP6 = PE_FSMState(MOVE_STEP6_onEntering, nullptr);
PE_FSMState MOVE_STEP7 = PE_FSMState(MOVE_STEP7_onEntering, nullptr);
PE_FSMState MOVE_STEP8 = PE_FSMState(MOVE_STEP8_onEntering, nullptr);

PE_FSM MoveFSM = PE_FSM();

typedef struct {
    float moveX;
    float moveY;
    int8_t rotateX;
    int8_t rotateZ;
    bool mustShutdown;
} control_t;

enum class Power {
    OFF,
    ON,
};

static Power power;

static control_t control;

typedef enum Speed {
    Speed_X1,
    Speed_X2,
    Speed_X3,
    Speed_X4,
} Speed_t;

static Speed_t currSpeed = Speed_X1;// Private
static Speed_t nextSpeed = Speed_X1;// Public, may be set via some method

void MODE_BOOTING_onEntering(PE_FSM &fsm) {
    // Disable power
    power = Power::ON;

    //TODO set standby positions

    // Go to next state
    ModeFSM.transitionTo(&MODE_WAITING);
}

void MODE_WAITING_onEntering(PE_FSM &fsm) {
    //TODO set idle positions, once
}

void MODE_WAITING_onDispatch(PE_FSM &fsm) {
    // Go to next state
    if (control.moveX != 0 || control.moveY != 0 || control.rotateX != 0 || control.rotateZ != 0) {
        ModeFSM.transitionTo(&MODE_MOVING);
    } else if (control.mustShutdown) {
        ModeFSM.transitionTo(&MODE_SHUTDOWN);
    }
}

void MODE_MOVING_onDispatch(PE_FSM &fsm) {
    //TODO process moving steps
}

void MODE_CONFIGURE_onEntering(PE_FSM &fsm) {
    //TODO process configure
}

void MODE_SHUTDOWN_onEntering(PE_FSM &fsm) {
    //TODO set standby positions, once
}

void MODE_SHUTDOWN_onDispatch(PE_FSM &fsm) {
    // Disable power
    power = Power::OFF;
}

void MOVE_STEP1_onEntering(PE_FSM &fsm) {
    //TODO calculate positions

    // Go to next state
    fsm.transitionTo(&MOVE_STEP2);
}

void MOVE_STEP2_onEntering(PE_FSM &fsm) {
    //TODO calculate positions

    // Go to next state
    fsm.transitionTo(&MOVE_STEP3);
}

void MOVE_STEP3_onEntering(PE_FSM &fsm) {
    //TODO calculate positions

    // Go to next state
    if (control.moveX == 0 && control.moveY == 0 && control.rotateX == 0 && control.rotateZ == 0) {
        // Go to init step
        ModeFSM.transitionTo(&MODE_WAITING);
    } else {
        // Go to next step
        fsm.transitionTo(&MOVE_STEP4);
    }
}

void MOVE_STEP4_onEntering(PE_FSM &fsm) {
    // Change speed (copy to private value for prevent change in other places)
    currSpeed = nextSpeed;

    //TODO calculate positions

    // Go to next state
    fsm.transitionTo(&MOVE_STEP5);
}

void MOVE_STEP5_onEntering(PE_FSM &fsm) {
    //TODO calculate positions

    // Go to next state
    fsm.transitionTo(&MOVE_STEP6);
}

void MOVE_STEP6_onEntering(PE_FSM &fsm) {
    //TODO calculate positions

    // Go to next state
    fsm.transitionTo(&MOVE_STEP7);
}

void MOVE_STEP7_onEntering(PE_FSM &fsm) {
    //TODO calculate positions

    if (control.moveX == 0 && control.moveY == 0 && control.rotateX == 0 && control.rotateZ == 0) {
        // Go to init step
        ModeFSM.transitionTo(&MODE_WAITING);
    } else {
        // Go to next state
        fsm.transitionTo(&MOVE_STEP8);
    }
}

void MOVE_STEP8_onEntering(PE_FSM &fsm) {
    // Change speed (copy to private value for prevent change in other places)
    currSpeed = nextSpeed;

    //TODO calculate positions

    // Go to next state
    fsm.transitionTo(&MOVE_STEP1);
}
