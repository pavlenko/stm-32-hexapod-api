#include "PE_SpiderV2.h"

#include <stddef.h>

PE_SpiderV2_State_t PE_SpiderV2_stateInit = {PE_SpiderV2_handlerInit_onEntering, NULL};
PE_SpiderV2_State_t PE_SpiderV2_stateIdle = {PE_SpiderV2_handlerIdle_onEntering, PE_SpiderV2_handlerIdle_onDispatch};

PE_SpiderV2_State_t PE_SpiderV2_stateMove1 = {PE_SpiderV2_handlerMove1_onEntering, NULL};
PE_SpiderV2_State_t PE_SpiderV2_stateMove2 = {PE_SpiderV2_handlerMove2_onEntering, NULL};
PE_SpiderV2_State_t PE_SpiderV2_stateMove3 = {PE_SpiderV2_handlerMove3_onEntering, NULL};
PE_SpiderV2_State_t PE_SpiderV2_stateMove4 = {PE_SpiderV2_handlerMove4_onEntering, NULL};
PE_SpiderV2_State_t PE_SpiderV2_stateMove5 = {PE_SpiderV2_handlerMove5_onEntering, NULL};
PE_SpiderV2_State_t PE_SpiderV2_stateMove6 = {PE_SpiderV2_handlerMove6_onEntering, NULL};
PE_SpiderV2_State_t PE_SpiderV2_stateMove7 = {PE_SpiderV2_handlerMove7_onEntering, NULL};
PE_SpiderV2_State_t PE_SpiderV2_stateMove8 = {PE_SpiderV2_handlerMove8_onEntering, NULL};

void PE_SpiderV2_handlerInit_onEntering(PE_SpiderV2_t *spider) {
    //TODO HP_calculateInit(&moving);
    spider->nextState = &PE_SpiderV2_stateIdle;
}

void PE_SpiderV2_handlerIdle_onEntering(PE_SpiderV2_t *spider) {
    //TODO HP_calculateIdle(&moving);
}

void PE_SpiderV2_handlerIdle_onDispatch(PE_SpiderV2_t *spider) {
    if (spider->remote.moveX != 0 || spider->remote.moveY != 0 || spider->remote.rotateZ != 0) {
        //TODO HP_calculateMovingLinear(&remote, &moving);
        //TODO HP_calculateMovingRotate(&remote, &moving);

        spider->nextState = &PE_SpiderV2_stateMove1;
    }
}

void PE_SpiderV2_handlerMove1_onEntering(PE_SpiderV2_t *spider) {
    spider->nextState = &PE_SpiderV2_stateMove2;
}

void PE_SpiderV2_handlerMove2_onEntering(PE_SpiderV2_t *spider) {
    spider->nextState = &PE_SpiderV2_stateMove3;
}

void PE_SpiderV2_handlerMove3_onEntering(PE_SpiderV2_t *spider) {
    spider->nextState = &PE_SpiderV2_stateMove4;
}

void PE_SpiderV2_handlerMove4_onEntering(PE_SpiderV2_t *spider) {
    spider->nextState = &PE_SpiderV2_stateMove5;
}

void PE_SpiderV2_handlerMove5_onEntering(PE_SpiderV2_t *spider) {
    spider->nextState = &PE_SpiderV2_stateMove6;
}

void PE_SpiderV2_handlerMove6_onEntering(PE_SpiderV2_t *spider) {
    spider->nextState = &PE_SpiderV2_stateMove7;
}

void PE_SpiderV2_handlerMove7_onEntering(PE_SpiderV2_t *spider) {
    spider->nextState = &PE_SpiderV2_stateMove8;
}

void PE_SpiderV2_handlerMove8_onEntering(PE_SpiderV2_t *spider) {
    spider->nextState = &PE_SpiderV2_stateMove1;
}

void PE_SpiderV2_initialize(PE_SpiderV2_t *spider) {
    spider->nextState = &PE_SpiderV2_stateInit;
}

void PE_SpiderV2_dispatch(PE_SpiderV2_t *spider) {
    if (spider->currState != spider->nextState) {
        spider->currState = spider->nextState;

        if (spider->currState && spider->currState->onEntering) {
            spider->currState->onEntering(spider);
        }
    }

    if (spider->currState && spider->currState->onDispatch) {
        spider->currState->onDispatch(spider);
    }
}