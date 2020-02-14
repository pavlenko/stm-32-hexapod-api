/* Includes ------------------------------------------------------------------*/

#include <math.h>
#include <stddef.h>
#include "hexapod.h"

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

const float HP_ROTATE_RADIUS = 680;

const float STEP_PART_X1 = 10;
const float STEP_PART_X2 = 20;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

Hexapod_t h;

/* Private function prototypes -----------------------------------------------*/

void HP_handlerInit_onEntering();
void HP_handlerIdle_onEntering();
void HP_handlerIdle_onDispatch();
void HP_handlerMoveStep1_onEntering();
void HP_handlerMoveStep2_onEntering();
void HP_handlerMoveStep3_onEntering();
void HP_handlerMoveStep4_onEntering();
void HP_handlerMoveStep5_onEntering();
void HP_handlerMoveStep6_onEntering();
void HP_handlerMoveStep7_onEntering();
void HP_handlerMoveStep8_onEntering();

HP_State_t HP_stateInit      = {HP_handlerInit_onEntering, NULL};
HP_State_t HP_stateIdle      = {HP_handlerIdle_onEntering, HP_handlerIdle_onDispatch};
HP_State_t HP_stateMoveStep1 = {HP_handlerMoveStep1_onEntering, NULL};
HP_State_t HP_stateMoveStep2 = {HP_handlerMoveStep2_onEntering, NULL};
HP_State_t HP_stateMoveStep3 = {HP_handlerMoveStep3_onEntering, NULL};
HP_State_t HP_stateMoveStep4 = {HP_handlerMoveStep4_onEntering, NULL};
HP_State_t HP_stateMoveStep5 = {HP_handlerMoveStep5_onEntering, NULL};
HP_State_t HP_stateMoveStep6 = {HP_handlerMoveStep6_onEntering, NULL};
HP_State_t HP_stateMoveStep7 = {HP_handlerMoveStep7_onEntering, NULL};
HP_State_t HP_stateMoveStep8 = {HP_handlerMoveStep8_onEntering, NULL};

/* Private functions ---------------------------------------------------------*/

void HP_calculateMovingRotate(HP_Remote_t *remote, HP_Moving_t *moving) {
    if (remote->moveX == 0 && remote->moveY == 0) {
        moving->rotateZBy.x = 0;
        moving->rotateZBy.y = 0;
    } else if (remote->moveX == 0) {
        moving->rotateZBy.x = HP_ROTATE_RADIUS * ((float) remote->rotateZ);
        moving->rotateZBy.y = 0;
    } else if (remote->moveY == 0) {
        moving->rotateZBy.x = 0;
        moving->rotateZBy.y = HP_ROTATE_RADIUS * ((float) remote->rotateZ);
    } else {
        float angle  = atan2f(remote->moveY, remote->moveX);
        float rotate = (float) remote->rotateZ * (float) M_PI_2;
        float result;

        if (angle >= 0) {
            result = angle - rotate;
        } else {
            result = angle + rotate;
        }

        moving->rotateZBy.x = HP_ROTATE_RADIUS * cosf(result);
        moving->rotateZBy.y = HP_ROTATE_RADIUS * sinf(result);
    }
}

void HP_calculateMovingLinear(HP_Remote_t *remote, HP_Moving_t *moving) {
    if (remote->moveX == 0 && remote->moveY == 0) {
        moving->moveByX = 0;
        moving->moveByY = 0;
    } else {
        float angle = atan2f(remote->moveY, remote->moveX);

        moving->moveByX = cosf(angle);
        moving->moveByY = sinf(angle);
    }
}

void HP_calculateTargetLinear(HP_Moving_t *moving, HP_Leg_t *leg, float step, HP_LegMode_t mode) {
    leg->tgt.x = leg->def.x + moving->moveByX * step;
    leg->tgt.y = leg->def.y + moving->moveByY * step;

    if (mode == LEG_MODE_FLOATING) {
        leg->tgt.z = leg->def.z;
    } else {
        leg->tgt.z = leg->def.z + ((float) -moving->height);
    }
}

void HP_calculateTargetRotate(HP_Moving_t *moving, HP_Leg_t *leg, float step, HP_LegMode_t mode) {
    // Calculate leg rotation radius
    float radius = hypotf(moving->rotateZBy.x - leg->def.x, moving->rotateZBy.y - leg->def.y);

    // Calculate leg rotation angle
    float stepAngle = calculateAngleByOppositeSide(radius, radius, step);

    // Calculate basic angle
    float baseAngle = acosf((moving->rotateZBy.x - leg->def.x) / radius);

    // Calculate result angle
    float diffAngle;
    if (step < 0) {
        diffAngle = baseAngle - stepAngle;
    } else {
        diffAngle = baseAngle + stepAngle;
    }

    leg->tgt.x = leg->def.x + step * sinf(diffAngle);
    leg->tgt.y = leg->def.y + step * cosf(diffAngle);

    if (mode == LEG_MODE_FLOATING) {
        leg->tgt.z = leg->def.z;
    } else {
        leg->tgt.z = leg->def.z + ((float) -moving->height);
    }
}

void HP_calculateInit(HP_Moving_t *moving) {
    HP_calculateTargetLinear(moving, &h.legs[LEG_FL], 0, LEG_MODE_FLOATING);
    HP_calculateTargetLinear(moving, &h.legs[LEG_FR], 0, LEG_MODE_FLOATING);
    HP_calculateTargetLinear(moving, &h.legs[LEG_ML], 0, LEG_MODE_FLOATING);
    HP_calculateTargetLinear(moving, &h.legs[LEG_MR], 0, LEG_MODE_FLOATING);
    HP_calculateTargetLinear(moving, &h.legs[LEG_BL], 0, LEG_MODE_FLOATING);
    HP_calculateTargetLinear(moving, &h.legs[LEG_BR], 0, LEG_MODE_FLOATING);
}

void HP_calculateIdle(HP_Moving_t *moving) {
    HP_calculateTargetLinear(moving, &h.legs[LEG_FL], 0, LEG_MODE_GROUNDED);
    HP_calculateTargetLinear(moving, &h.legs[LEG_FR], 0, LEG_MODE_GROUNDED);
    HP_calculateTargetLinear(moving, &h.legs[LEG_ML], 0, LEG_MODE_GROUNDED);
    HP_calculateTargetLinear(moving, &h.legs[LEG_MR], 0, LEG_MODE_GROUNDED);
    HP_calculateTargetLinear(moving, &h.legs[LEG_BL], 0, LEG_MODE_GROUNDED);
    HP_calculateTargetLinear(moving, &h.legs[LEG_BR], 0, LEG_MODE_GROUNDED);
}

void HP_calculateStep1(HP_Moving_t *moving) {
    h.calculate(moving, &h.legs[LEG_FL], STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_FR], -STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_ML], STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_MR], -STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_BL], STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_BR], -STEP_PART_X1, LEG_MODE_GROUNDED);
}

void HP_calculateStep2(HP_Moving_t *moving) {
    h.calculate(moving, &h.legs[LEG_FL], STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_FR], -STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_ML], STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_MR], -STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_BL], STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_BR], -STEP_PART_X2, LEG_MODE_GROUNDED);
}

void HP_calculateStep3(HP_Moving_t *moving) {
    h.calculate(moving, &h.legs[LEG_FL], STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_FR], -STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_ML], STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_MR], -STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_BL], STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_BR], -STEP_PART_X1, LEG_MODE_FLOATING);
}

void HP_calculateStep4(HP_Moving_t *moving) {
    h.calculate(moving, &h.legs[LEG_FL], 0, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_FR], 0, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_ML], 0, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_MR], 0, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_BL], 0, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_BR], 0, LEG_MODE_FLOATING);
}

void HP_calculateStep5(HP_Moving_t *moving) {
    h.calculate(moving, &h.legs[LEG_FL], -STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_FR], STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_ML], -STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_MR], STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_BL], -STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_BR], STEP_PART_X1, LEG_MODE_FLOATING);
}

void HP_calculateStep6(HP_Moving_t *moving) {
    h.calculate(moving, &h.legs[LEG_FL], -STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_FR], STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_ML], -STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_MR], STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_BL], -STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_BR], STEP_PART_X2, LEG_MODE_GROUNDED);
}

void HP_calculateStep7(HP_Moving_t *moving) {
    h.calculate(moving, &h.legs[LEG_FL], -STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_FR], STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_ML], -STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_MR], STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_BL], -STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_BR], STEP_PART_X1, LEG_MODE_GROUNDED);
}

void HP_calculateStep8(HP_Moving_t *moving) {
    h.calculate(moving, &h.legs[LEG_FL], 0, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_FR], 0, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_ML], 0, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_MR], 0, LEG_MODE_GROUNDED);
    h.calculate(moving, &h.legs[LEG_BL], 0, LEG_MODE_FLOATING);
    h.calculate(moving, &h.legs[LEG_BR], 0, LEG_MODE_GROUNDED);
}

uint32_t startAt = 0;

HP_State_t HP_init = {HP_handlerInit_onEntering, NULL};

HP_State_t *_prevState;
HP_State_t *_nextState;

HP_Handler_t _onEntering;
HP_Handler_t _onDispatch;

HP_Remote_t remote;
HP_Moving_t moving;

void HP_handlerInit_onEntering() {
    HP_calculateInit(&moving);

    _onEntering = HP_handlerIdle_onEntering;
    _onDispatch = HP_handlerIdle_onDispatch;
}

void HP_handlerIdle_onEntering() {
    HP_calculateIdle(&moving);
}

void HP_handlerIdle_onDispatch() {
    if (remote.moveX != 0 || remote.moveY != 0 || remote.rotateZ != 0) {
        HP_calculateMovingLinear(&remote, &moving);
        HP_calculateMovingRotate(&remote, &moving);

        _onEntering = HP_handlerMoveStep1_onEntering;
        _onDispatch = NULL;
    }
}

void HP_handlerMoveStep1_onEntering() {
    HP_calculateStep1(&moving);
    _onEntering = HP_handlerMoveStep2_onEntering;
}

void HP_handlerMoveStep2_onEntering() {
    HP_calculateStep2(&moving);
    _onEntering = HP_handlerMoveStep3_onEntering;
}

void HP_handlerMoveStep3_onEntering() {
    //TODO change state depends on remote
    HP_calculateStep3(&moving);
    _onEntering = HP_handlerMoveStep4_onEntering;
}

void HP_handlerMoveStep4_onEntering() {
    //TODO recalculate linear & rotate
    HP_calculateStep4(&moving);
    _onEntering = HP_handlerMoveStep5_onEntering;
}

void HP_handlerMoveStep5_onEntering() {
    HP_calculateStep5(&moving);
    _onEntering = HP_handlerMoveStep6_onEntering;
}

void HP_handlerMoveStep6_onEntering() {
    HP_calculateStep6(&moving);
    _onEntering = HP_handlerMoveStep7_onEntering;
}

void HP_handlerMoveStep7_onEntering() {
    //TODO change state depends on remote
    HP_calculateStep7(&moving);
    _onEntering = HP_handlerMoveStep8_onEntering;
}

void HP_handlerMoveStep8_onEntering() {
    //TODO recalculate linear & rotate
    HP_calculateStep8(&moving);
    _onEntering = HP_handlerMoveStep1_onEntering;
}

void HP_initialize() {
    _nextState = &HP_init;

    _onEntering = HP_handlerInit_onEntering;
}

void HP_dispatch(uint32_t millis) {
    // Timings
    if (millis - startAt < 20) {
        return;
    }

    startAt = millis;

    if (_prevState != _nextState) {
        _prevState = _nextState;

        if (_prevState->onEntering) {
            _prevState->onEntering();
        }
    }

    if (_prevState->onDispatch) {
        _prevState->onDispatch();
    }

    // Handle singular callback
    if (_onEntering) {
        _onEntering();
        _onEntering = NULL;
    }

    // Handle periodic callback
    if (_onDispatch) {
        _onDispatch();
    }
}

/* Exported functions ------------------------------------------------------- */