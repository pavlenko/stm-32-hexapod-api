#include "PE_SpiderV2.h"

void PE_SpiderV2_dispatch(PE_SpiderV2_t *spider, uint32_t millis) {
    if (millis - spider->millis < 20) {
        return;
    }

    spider->millis = millis;

    if (spider->prevState != spider->nextState) {
        spider->prevState = spider->nextState;

        if (spider->prevState->onEntering) {
            spider->prevState->onEntering();
        }
    }

    if (spider->prevState->onDispatch) {
        spider->prevState->onDispatch();
    }
}