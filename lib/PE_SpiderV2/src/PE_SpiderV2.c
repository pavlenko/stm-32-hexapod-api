#include "PE_SpiderV2.h"

//TODO maybe remove millis from dispatch
void PE_SpiderV2_dispatch(PE_SpiderV2_t *spider, uint32_t millis) {
    if (millis - spider->millis < 20) {
        return;
    }

    spider->millis = millis;

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