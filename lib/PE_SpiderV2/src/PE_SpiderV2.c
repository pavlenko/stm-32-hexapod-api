#include "PE_SpiderV2.h"

void PE_SpiderV2_dispatch(PE_SpiderV2_t *spider) {
    if (spider->currState != spider->nextState) {
        spider->currState = spider->nextState;

        if (spider->currState && spider->currState->onEntering) {
            spider->currState->onEntering();
        }
    }

    if (spider->currState && spider->currState->onDispatch) {
        spider->currState->onDispatch();
    }
}