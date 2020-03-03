#include "PE_SpiderV2.h"

#include <math.h>
#include <stddef.h>

const float PE_SpiderV2_ROTATE_RADIUS = 680;

const float PE_SpiderV2_STEP_PART_X1 = 10;
const float PE_SpiderV2_STEP_PART_X2 = 20;

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

float PE_SpiderV2_calculateAngleByOppositeSide(float adjacentSideA, float adjacentSideB, float oppositeSide);

void PE_SpiderV2_calculateMovingLinear(PE_SpiderV2_remote_t *remote, PE_SpiderV2_moving_t *moving) {
    if (remote->moveX == 0 && remote->moveY == 0) {
        moving->moveByX = 0;
        moving->moveByY = 0;
    } else {
        float angle = atan2f(remote->moveY, remote->moveX);

        moving->moveByX = cosf(angle);
        moving->moveByY = sinf(angle);
    }
}

void PE_SpiderV2_calculateMovingRotate(PE_SpiderV2_remote_t *remote, PE_SpiderV2_moving_t *moving) {
    if (remote->moveX == 0 && remote->moveY == 0) {
        moving->rotateZBy.x = 0;
        moving->rotateZBy.y = 0;
    } else if (remote->moveX == 0) {
        moving->rotateZBy.x = PE_SpiderV2_ROTATE_RADIUS * ((float) remote->rotateZ);
        moving->rotateZBy.y = 0;
    } else if (remote->moveY == 0) {
        moving->rotateZBy.x = 0;
        moving->rotateZBy.y = PE_SpiderV2_ROTATE_RADIUS * ((float) remote->rotateZ);
    } else {
        float angle  = atan2f(remote->moveY, remote->moveX);
        float rotate = (float) remote->rotateZ * (float) M_PI_2;
        float result;

        if (angle >= 0) {
            result = angle - rotate;
        } else {
            result = angle + rotate;
        }

        moving->rotateZBy.x = PE_SpiderV2_ROTATE_RADIUS * cosf(result);
        moving->rotateZBy.y = PE_SpiderV2_ROTATE_RADIUS * sinf(result);
    }
}

void PE_SpiderV2_calculateTargetLinear(PE_SpiderV2_t *spider, PE_SpiderV2_LegPos_t leg, float step, PE_SpiderV2_LegMode_t mode) {
    spider->legTargets[leg].x = spider->legSources[leg].x + spider->moving.moveByX * step;
    spider->legTargets[leg].y = spider->legSources[leg].y + spider->moving.moveByY * step;

    if (mode == PE_SPIDER_V2_LEG_MODE_FLOATING) {
        spider->legTargets[leg].z = spider->legSources[leg].z;
    } else {
        spider->legTargets[leg].z = spider->legSources[leg].z + ((float) -spider->moving.height);
    }
}

void PE_SpiderV2_calculateTargetRotate(PE_SpiderV2_t *spider, PE_SpiderV2_LegPos_t leg, float step, PE_SpiderV2_LegMode_t mode) {
    // Calculate leg rotation radius
    float radius = hypotf(
        spider->moving.rotateZBy.x - spider->legSources[leg].x,
        spider->moving.rotateZBy.y - spider->legSources[leg].y
    );

    // Calculate leg rotation angle
    float stepAngle = PE_SpiderV2_calculateAngleByOppositeSide(radius, radius, step);

    // Calculate basic angle
    float baseAngle = acosf((spider->moving.rotateZBy.x - spider->legSources[leg].x) / radius);

    // Calculate result angle
    float diffAngle;
    if (step < 0) {
        diffAngle = baseAngle - stepAngle;
    } else {
        diffAngle = baseAngle + stepAngle;
    }

    spider->legTargets[leg].x = spider->legSources[leg].x + step * sinf(diffAngle);
    spider->legTargets[leg].y = spider->legSources[leg].y + step * cosf(diffAngle);

    if (mode == PE_SPIDER_V2_LEG_MODE_FLOATING) {
        spider->legTargets[leg].z = spider->legSources[leg].z;
    } else {
        spider->legTargets[leg].z = spider->legSources[leg].z + ((float) -spider->moving.height);
    }
}

void PE_SpiderV2_handlerInit_onEntering(PE_SpiderV2_t *spider) {
    //TODO HP_calculateInit(&moving);
    spider->nextState = &PE_SpiderV2_stateIdle;
}

void PE_SpiderV2_handlerIdle_onEntering(PE_SpiderV2_t *spider) {
    //TODO HP_calculateIdle(&moving);
}

void PE_SpiderV2_handlerIdle_onDispatch(PE_SpiderV2_t *spider) {
    if (spider->remote.moveX != 0 || spider->remote.moveY != 0 || spider->remote.rotateZ != 0) {
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
    //TODO HP_calculateStep1(&moving);
    spider->nextState = &PE_SpiderV2_stateMove2;
}

void PE_SpiderV2_handlerMove2_onEntering(PE_SpiderV2_t *spider) {
    //TODO HP_calculateStep2(&moving);
    spider->nextState = &PE_SpiderV2_stateMove3;
}

void PE_SpiderV2_handlerMove3_onEntering(PE_SpiderV2_t *spider) {
    //TODO HP_calculateStep3(&moving);
    if (spider->remote.moveX == 0 && spider->remote.moveY == 0 && spider->remote.rotateZ == 0) {
        spider->nextState = &PE_SpiderV2_stateIdle;
    } else {
        spider->nextState = &PE_SpiderV2_stateMove4;
    }
}

void PE_SpiderV2_handlerMove4_onEntering(PE_SpiderV2_t *spider) {
    //TODO HP_calculateStep4(&moving);
    PE_SpiderV2_calculateMovingLinear(&spider->remote, &spider->moving);
    PE_SpiderV2_calculateMovingRotate(&spider->remote, &spider->moving);
    spider->nextState = &PE_SpiderV2_stateMove5;
}

void PE_SpiderV2_handlerMove5_onEntering(PE_SpiderV2_t *spider) {
    //TODO HP_calculateStep5(&moving);
    spider->nextState = &PE_SpiderV2_stateMove6;
}

void PE_SpiderV2_handlerMove6_onEntering(PE_SpiderV2_t *spider) {
    //TODO HP_calculateStep6(&moving);
    spider->nextState = &PE_SpiderV2_stateMove7;
}

void PE_SpiderV2_handlerMove7_onEntering(PE_SpiderV2_t *spider) {
    //TODO HP_calculateStep7(&moving);
    if (spider->remote.moveX == 0 && spider->remote.moveY == 0 && spider->remote.rotateZ == 0) {
        spider->nextState = &PE_SpiderV2_stateIdle;
    } else {
        spider->nextState = &PE_SpiderV2_stateMove8;
    }
}

void PE_SpiderV2_handlerMove8_onEntering(PE_SpiderV2_t *spider) {
    //TODO HP_calculateStep8(&moving);
    PE_SpiderV2_calculateMovingLinear(&spider->remote, &spider->moving);
    PE_SpiderV2_calculateMovingRotate(&spider->remote, &spider->moving);
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

float PE_SpiderV2_calculateAngleByOppositeSide(float adjacentSideA, float adjacentSideB, float oppositeSide) {
    return acosf(
            (adjacentSideA * adjacentSideA + adjacentSideB * adjacentSideB - oppositeSide * oppositeSide) /
            (2 * adjacentSideA * adjacentSideB)
    );
}
