#include "PE_SpiderV2.h"

//TODO maybe remove millis from dispatch
void PE_SpiderV2_dispatch(PE_SpiderV2_t *spider, uint32_t millis) {
    if (millis - spider->millis < 20) {
        return;
    }

    spider->millis = millis;

    if (spider->prevState != spider->nextState) {
        spider->prevState = spider->nextState;

        if (spider->prevState && spider->prevState->onEntering) {
            spider->prevState->onEntering();
        }
    }

    if (spider->prevState && spider->prevState->onDispatch) {
        spider->prevState->onDispatch();
    }
}