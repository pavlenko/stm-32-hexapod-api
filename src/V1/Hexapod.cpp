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

void Hexapod::initialize() {
    ModeFSM.initialize(&MODE_BOOTING);
}

void Hexapod::dispatch(uint32_t millis) {
    // Delay logic
    if (millis - updated < 20) {
        return;
    }

    updated = millis;

    ModeFSM.dispatch();
}
