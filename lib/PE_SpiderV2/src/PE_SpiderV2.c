#include "PE_SpiderV2.h"

#include <stddef.h>

PE_SpiderV2_State_t PE_SpiderV2_stateInit = {PE_SpiderV2_handlerInit_onEntering, NULL};
PE_SpiderV2_State_t PE_SpiderV2_stateIdle = {PE_SpiderV2_handlerIdle_onEntering, PE_SpiderV2_handlerIdle_onDispatch};

void PE_SpiderV2_handlerInit_onEntering(PE_SpiderV2_t *spider) {
    (void) spider;//TODO
}

void PE_SpiderV2_handlerIdle_onEntering(PE_SpiderV2_t *spider) {
    (void) spider;//TODO
}

void PE_SpiderV2_handlerIdle_onDispatch(PE_SpiderV2_t *spider) {
    (void) spider;//TODO
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