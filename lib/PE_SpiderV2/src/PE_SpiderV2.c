#include "PE_SpiderV2.h"

#include <math.h>
#include <stddef.h>

const uint32_t PE_SpiderV2_DELAY_MS_INIT = 2000;
const uint32_t PE_SpiderV2_DELAY_MS_MOVE = 125;//250|125|62.5

const float PE_SpiderV2_ROTATE_RADIUS = 680;

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

float PE_SpiderV2_calculateAngleByOppositeSide(float adjacentSideA, float adjacentSideB, float oppositeSide);

void PE_SpiderV2_calculateMovingLinear(PE_SpiderV2_Remote_t *remote, PE_SpiderV2_Moving_t *moving) {
    if (remote->moveX == 0 && remote->moveY == 0) {
        moving->moveByX = 0;
        moving->moveByY = 0;
    } else {
        float angle = atan2f(remote->moveY, remote->moveX);

        moving->moveByX = cosf(angle);
        moving->moveByY = sinf(angle);
    }
}

void PE_SpiderV2_calculateMovingRotate(PE_SpiderV2_Remote_t *remote, PE_SpiderV2_Moving_t *moving) {
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

void PE_SpiderV2_calculateTargetLinear(PE_SpiderV2_Moving_t *moving, PE_SpiderV2_Leg_t *leg, float step, PE_SpiderV2_LegMode_t mode) {
    leg->dst.x = leg->src.x + moving->moveByX * step;
    leg->dst.y = leg->src.y + moving->moveByY * step;

    if (mode == PE_SPIDER_V2_LEG_MODE_FLOATING) {
        leg->dst.z = leg->src.z;
    } else {
        leg->dst.z = leg->src.z + ((float) -moving->height);
    }

    PE_SpiderV2_calculateDegree(leg);
}

void PE_SpiderV2_calculateTargetRotate(PE_SpiderV2_Moving_t *moving, PE_SpiderV2_Leg_t *leg, float step, PE_SpiderV2_LegMode_t mode) {
    // Calculate leg rotation radius
    float radius = hypotf(
        moving->rotateZBy.x - leg->src.x,
        moving->rotateZBy.y - leg->src.y
    );

    // Calculate leg rotation angle
    float stepAngle = PE_SpiderV2_calculateAngleByOppositeSide(radius, radius, step);

    // Calculate basic angle
    float baseAngle = acosf((moving->rotateZBy.x - leg->src.x) / radius);

    // Calculate result angle
    float diffAngle;
    if (step < 0) {
        diffAngle = baseAngle - stepAngle;
    } else {
        diffAngle = baseAngle + stepAngle;
    }

    leg->dst.x = leg->src.x + step * sinf(diffAngle);
    leg->dst.y = leg->src.y + step * cosf(diffAngle);

    if (mode == PE_SPIDER_V2_LEG_MODE_FLOATING) {
        leg->dst.z = leg->src.z;
    } else {
        leg->dst.z = leg->src.z + ((float) -moving->height);
    }

    PE_SpiderV2_calculateDegree(leg);
}

void PE_SpiderV2_calculateDegree(PE_SpiderV2_Leg_t *leg) {
    PE_SpiderV2_Point3D_t local = {leg->dst.x - leg->mnt.x, leg->dst.y - leg->mnt.y, leg->dst.z - leg->mnt.z};

    // Calculate horizontal distance mount - target
    float h_distance = hypotf(local.x, local.y);

    // Calculate horizontal distance coxa - target
    float c_distance = h_distance - leg->cLength;

    // Calculate vertical distance in millimeters
    float v_distance;
    if (c_distance > leg->fLength + leg->tLength) {
        c_distance = leg->fLength + leg->tLength;
        v_distance = 0;
    } else {
        v_distance = hypotf(c_distance, local.z);
    }

    // Calculate femur add angle from z to v_distance axis in radians
    float f_add_angle = fabsf(atanf(c_distance / local.z));

    // Calculate coxa angle
    leg->cDegree = atanf(local.y / local.x) + (float) M_PI_2;

    if (v_distance > 0) {
        // Calculate femur angle in radians
        leg->fDegree = PE_SpiderV2_calculateAngleByOppositeSide(leg->fLength, v_distance, leg->tLength) + f_add_angle;

        // Calculate tiba angle in radians
        leg->tDegree = PE_SpiderV2_calculateAngleByOppositeSide(leg->tLength, leg->fLength, v_distance);
    } else {
        // Calculate femur angle in radians IF not possible to reach target
        leg->fDegree = f_add_angle;

        // Calculate tiba angle in radians IF not possible to reach target
        leg->tDegree = (float) M_PI;
    }
}

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

float PE_SpiderV2_calculateAngleByOppositeSide(float adjacentSideA, float adjacentSideB, float oppositeSide) {
    return acosf(
            (adjacentSideA * adjacentSideA + adjacentSideB * adjacentSideB - oppositeSide * oppositeSide) /
            (2 * adjacentSideA * adjacentSideB)
    );
}
