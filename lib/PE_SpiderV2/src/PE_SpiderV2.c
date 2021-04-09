#include "PE_SpiderV2.h"
#include "PE_SpiderV2_geometry.h"

#include <stddef.h>

const uint32_t PE_SpiderV2_DELAY_MS_INIT = 2000;
const uint32_t PE_SpiderV2_DELAY_MS_MOVE = 125;//250|125|62.5

const float PE_SpiderV2_STEP_PART_X1 = 15;
const float PE_SpiderV2_STEP_PART_X2 = 30;

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
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FL], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FR], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_ML], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_MR], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BL], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BR], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);

    if (spider->remote.off == 0) {
        spider->delayMs   = PE_SpiderV2_DELAY_MS_INIT;
        spider->nextState = &PE_SpiderV2_stateIdle;
    }
}

void PE_SpiderV2_handlerIdle_onEntering(PE_SpiderV2_t *spider) {
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FL], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FR], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_ML], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_MR], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BL], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    PE_SpiderV2_calculateTargetLinear(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BR], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);

    spider->delayMs = PE_SpiderV2_DELAY_MS_MOVE;
}

void PE_SpiderV2_handlerIdle_onDispatch(PE_SpiderV2_t *spider) {
    if (spider->remote.off == 1) {
        spider->delayMs   = PE_SpiderV2_DELAY_MS_MOVE * 4;
        spider->nextState = &PE_SpiderV2_stateInit;
    } else if (spider->remote.moveX != 0 || spider->remote.moveY != 0 || spider->remote.rotateZ != 0) {
        PE_SpiderV2_calculateMovingLinear(&spider->remote, &spider->moving);
        PE_SpiderV2_calculateMovingRotate(&spider->remote, &spider->moving);

        if (spider->remote.rotateZ != 0) {
            spider->calculate = PE_SpiderV2_calculateTargetRotate;
        } else {
            spider->calculate = PE_SpiderV2_calculateTargetLinear;
        }

        spider->nextState = &PE_SpiderV2_stateMove1;
    }
}

void PE_SpiderV2_handlerMove1_onEntering(PE_SpiderV2_t *spider) {
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FL], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FR], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_ML], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_MR], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BL], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BR], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);

    spider->nextState = &PE_SpiderV2_stateMove2;
}

void PE_SpiderV2_handlerMove2_onEntering(PE_SpiderV2_t *spider) {
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FL], PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FR], -PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_ML], PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_MR], -PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BL], PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BR], -PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);

    spider->nextState = &PE_SpiderV2_stateMove3;
}

void PE_SpiderV2_handlerMove3_onEntering(PE_SpiderV2_t *spider) {
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FL], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FR], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_ML], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_MR], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BL], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BR], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);

    if (spider->remote.off == 1 || (spider->remote.moveX == 0 && spider->remote.moveY == 0 && spider->remote.rotateZ == 0)) {
        spider->nextState = &PE_SpiderV2_stateIdle;
    } else {
        spider->nextState = &PE_SpiderV2_stateMove4;
    }
}

void PE_SpiderV2_handlerMove4_onEntering(PE_SpiderV2_t *spider) {
    PE_SpiderV2_calculateMovingLinear(&spider->remote, &spider->moving);
    PE_SpiderV2_calculateMovingRotate(&spider->remote, &spider->moving);

    if (spider->remote.rotateZ != 0) {
        spider->calculate = PE_SpiderV2_calculateTargetRotate;
    } else {
        spider->calculate = PE_SpiderV2_calculateTargetLinear;
    }

    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FL], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FR], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_ML], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_MR], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BL], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BR], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);

    spider->nextState = &PE_SpiderV2_stateMove5;
}

void PE_SpiderV2_handlerMove5_onEntering(PE_SpiderV2_t *spider) {
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FL], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FR], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_ML], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_MR], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BL], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BR], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);

    spider->nextState = &PE_SpiderV2_stateMove6;
}

void PE_SpiderV2_handlerMove6_onEntering(PE_SpiderV2_t *spider) {
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FL], -PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FR], PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_ML], -PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_MR], PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BL], -PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BR], PE_SpiderV2_STEP_PART_X2, PE_SPIDER_V2_LEG_MODE_GROUNDED);

    spider->nextState = &PE_SpiderV2_stateMove7;
}

void PE_SpiderV2_handlerMove7_onEntering(PE_SpiderV2_t *spider) {
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FL], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FR], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_ML], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_MR], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BL], -PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BR], PE_SpiderV2_STEP_PART_X1, PE_SPIDER_V2_LEG_MODE_GROUNDED);

    if (spider->remote.off == 1 || (spider->remote.moveX == 0 && spider->remote.moveY == 0 && spider->remote.rotateZ == 0)) {
        spider->nextState = &PE_SpiderV2_stateIdle;
    } else {
        spider->nextState = &PE_SpiderV2_stateMove8;
    }
}

void PE_SpiderV2_handlerMove8_onEntering(PE_SpiderV2_t *spider) {
    PE_SpiderV2_calculateMovingLinear(&spider->remote, &spider->moving);
    PE_SpiderV2_calculateMovingRotate(&spider->remote, &spider->moving);

    if (spider->remote.rotateZ != 0) {
        spider->calculate = PE_SpiderV2_calculateTargetRotate;
    } else {
        spider->calculate = PE_SpiderV2_calculateTargetLinear;
    }

    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FL], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_FR], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_ML], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_MR], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BL], 0, PE_SPIDER_V2_LEG_MODE_FLOATING);
    spider->calculate(&spider->moving, &spider->legs[PE_SPIDER_V2_LEG_POS_BR], 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);

    spider->nextState = &PE_SpiderV2_stateMove1;
}

PE_SpiderV2_Status_t PE_SpiderV2_initialize(PE_SpiderV2_t *spider) {
    uint8_t index;

    for (index = 0; index < 6; index++) {
        if (spider->legs[index].cLength == 0 || spider->legs[index].fLength == 0 || spider->legs[index].tLength == 0) {
            return PE_SPIDER_V2_STATUS_FAILURE;
        }

        //TODO check possibility of destination
    }

    spider->delayMs   = 0;
    spider->nextState = &PE_SpiderV2_stateInit;

    spider->remote = (PE_SpiderV2_Remote_t) {0, 0, 0, 0};

    return PE_SPIDER_V2_STATUS_SUCCESS;
}

void PE_SpiderV2_refreshMs(PE_SpiderV2_t *spider, uint32_t millis) {
    if (millis - spider->startMs < spider->delayMs) {
        return;
    }

    spider->startMs = millis;

    if (spider->currState != spider->nextState) {
        spider->currState = spider->nextState;

        if (spider->currState && spider->currState->onEntering) {
            PE_SpiderV2_refreshOnEntering(spider);
            spider->currState->onEntering(spider);
        }
    }

    if (spider->currState && spider->currState->onDispatch) {
        PE_SpiderV2_refreshOnDispatch(spider);
        spider->currState->onDispatch(spider);
    }

    PE_SpiderV2_refreshOnComplete(spider);
}

__attribute__((weak))
void PE_SpiderV2_refreshOnEntering(PE_SpiderV2_t *spider) {
    (void) spider;
}

__attribute__((weak))
void PE_SpiderV2_refreshOnDispatch(PE_SpiderV2_t *spider) {
    (void) spider;
}

__attribute__((weak))
void PE_SpiderV2_refreshOnComplete(PE_SpiderV2_t *spider) {
    (void) spider;
}
