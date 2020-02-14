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
void HP_moveStep1();
void HP_moveStep2();
void HP_moveStep3();
void HP_moveStep4();
void HP_moveStep5();
void HP_moveStep6();
void HP_moveStep7();
void HP_moveStep8();

/* Private functions ---------------------------------------------------------*/

void HP_calculateRotationCenter(HP_Remote_t *remote, HP_Status_t *status) {
    if (remote->moveX == 0 && remote->moveY == 0) {
        status->rotateZBy.x = 0;
        status->rotateZBy.y = 0;
    } else if (remote->moveX == 0) {
        status->rotateZBy.x = HP_ROTATE_RADIUS * ((float) remote->rotateZ);
        status->rotateZBy.y = 0;
    } else if (remote->moveY == 0) {
        status->rotateZBy.x = 0;
        status->rotateZBy.y = HP_ROTATE_RADIUS * ((float) remote->rotateZ);
    } else {
        float angle  = atan2f(remote->moveY, remote->moveX);
        float rotate = (float) remote->rotateZ * (float) M_PI_2;
        float result;

        if (angle >= 0) {
            result = angle - rotate;
        } else {
            result = angle + rotate;
        }

        status->rotateZBy.x = HP_ROTATE_RADIUS * cosf(result);
        status->rotateZBy.y = HP_ROTATE_RADIUS * sinf(result);
    }
}

void HP_calculateLinear(HP_Remote_t *remote, HP_Status_t *status) {
    if (remote->moveX == 0 && remote->moveY == 0) {
        status->moveByX = 0;
        status->moveByY = 0;
    } else {
        float angle = atan2f(remote->moveY, remote->moveX);

        status->moveByX = cosf(angle);
        status->moveByY = sinf(angle);
    }
}

void HP_calculateTargetLinear(HP_Status_t *status, HP_Leg_t *leg, float step, HP_LegMode_t mode) {
    leg->tgt.x = leg->def.x + status->moveByX * step;
    leg->tgt.y = leg->def.y + status->moveByY * step;

    if (mode == LEG_MODE_FLOATING) {
        leg->tgt.z = leg->def.z;
    } else {
        leg->tgt.z = leg->def.z + ((float) -status->height);
    }
}

void HP_calculateTargetRotate(HP_Status_t *status, HP_Leg_t *leg, float step, HP_LegMode_t mode) {
    // Calculate leg rotation radius
    float radius = hypotf(status->rotateZBy.x - leg->def.x, status->rotateZBy.y - leg->def.y);

    // Calculate leg rotation angle
    float stepAngle = calculateAngleByOppositeSide(radius, radius, step);

    // Calculate basic angle
    float baseAngle = acosf((status->rotateZBy.x - leg->def.x) / radius);

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
        leg->tgt.z = leg->def.z + ((float) -status->height);
    }
}

void HP_calculateInit(HP_Status_t *status) {
    HP_calculateTargetLinear(status, &h.legs[LEG_FL], 0, LEG_MODE_FLOATING);
    HP_calculateTargetLinear(status, &h.legs[LEG_FR], 0, LEG_MODE_FLOATING);
    HP_calculateTargetLinear(status, &h.legs[LEG_ML], 0, LEG_MODE_FLOATING);
    HP_calculateTargetLinear(status, &h.legs[LEG_MR], 0, LEG_MODE_FLOATING);
    HP_calculateTargetLinear(status, &h.legs[LEG_BL], 0, LEG_MODE_FLOATING);
    HP_calculateTargetLinear(status, &h.legs[LEG_BR], 0, LEG_MODE_FLOATING);
}

void HP_calculateIdle(HP_Status_t *status) {
    HP_calculateTargetLinear(status, &h.legs[LEG_FL], 0, LEG_MODE_GROUNDED);
    HP_calculateTargetLinear(status, &h.legs[LEG_FR], 0, LEG_MODE_GROUNDED);
    HP_calculateTargetLinear(status, &h.legs[LEG_ML], 0, LEG_MODE_GROUNDED);
    HP_calculateTargetLinear(status, &h.legs[LEG_MR], 0, LEG_MODE_GROUNDED);
    HP_calculateTargetLinear(status, &h.legs[LEG_BL], 0, LEG_MODE_GROUNDED);
    HP_calculateTargetLinear(status, &h.legs[LEG_BR], 0, LEG_MODE_GROUNDED);
}

void HP_calculateStep1(HP_Status_t *status) {
    h.calculate(status, &h.legs[LEG_FL], STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_FR], -STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_ML], STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_MR], -STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_BL], STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_BR], -STEP_PART_X1, LEG_MODE_GROUNDED);
}

void HP_calculateStep2(HP_Status_t *status) {
    h.calculate(status, &h.legs[LEG_FL], STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_FR], -STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_ML], STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_MR], -STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_BL], STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_BR], -STEP_PART_X2, LEG_MODE_GROUNDED);
}

void HP_calculateStep3(HP_Status_t *status) {
    h.calculate(status, &h.legs[LEG_FL], STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_FR], -STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_ML], STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_MR], -STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_BL], STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_BR], -STEP_PART_X1, LEG_MODE_FLOATING);
}

void HP_calculateStep4(HP_Status_t *status) {
    h.calculate(status, &h.legs[LEG_FL], 0, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_FR], 0, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_ML], 0, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_MR], 0, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_BL], 0, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_BR], 0, LEG_MODE_FLOATING);
}

void HP_calculateStep5(HP_Status_t *status) {
    h.calculate(status, &h.legs[LEG_FL], -STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_FR], STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_ML], -STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_MR], STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_BL], -STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_BR], STEP_PART_X1, LEG_MODE_FLOATING);
}

void HP_calculateStep6(HP_Status_t *status) {
    h.calculate(status, &h.legs[LEG_FL], -STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_FR], STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_ML], -STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_MR], STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_BL], -STEP_PART_X2, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_BR], STEP_PART_X2, LEG_MODE_GROUNDED);
}

void HP_calculateStep7(HP_Status_t *status) {
    h.calculate(status, &h.legs[LEG_FL], -STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_FR], STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_ML], -STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_MR], STEP_PART_X1, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_BL], -STEP_PART_X1, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_BR], STEP_PART_X1, LEG_MODE_GROUNDED);
}

void HP_calculateStep8(HP_Status_t *status) {
    h.calculate(status, &h.legs[LEG_FL], 0, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_FR], 0, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_ML], 0, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_MR], 0, LEG_MODE_GROUNDED);
    h.calculate(status, &h.legs[LEG_BL], 0, LEG_MODE_FLOATING);
    h.calculate(status, &h.legs[LEG_BR], 0, LEG_MODE_GROUNDED);
}

uint32_t startAt = 0;

typedef void (*HP_Handler_t) ();

typedef struct HP_State_s {
    HP_Handler_t onEntering;
    HP_Handler_t onDispatch;
} HP_State_t;

HP_State_t HP_init = {HP_handlerInit_onEntering, NULL};

HP_State_t *_prevState;
HP_State_t *_nextState;

HP_Handler_t _onEntering;
HP_Handler_t _onDispatch;

HP_Remote_t remote;
HP_Status_t status;

void HP_handlerInit_onEntering() {
    HP_calculateInit(&status);

    _onEntering = HP_handlerIdle_onEntering;
    _onDispatch = HP_handlerIdle_onDispatch;
}

void HP_handlerIdle_onEntering() {
    HP_calculateIdle(&status);
}

void HP_handlerIdle_onDispatch() {
    if (remote.moveX != 0 || remote.moveY != 0 || remote.rotateZ != 0) {
        HP_calculateLinear(&remote, &status);
        HP_calculateRotationCenter(&remote, &status);

        _onEntering = HP_moveStep1;
        _onDispatch = NULL;
    }
}

void HP_moveStep1() {
    HP_calculateStep1(&status);
    _onEntering = HP_moveStep2;
}

void HP_moveStep2() {
    HP_calculateStep2(&status);
    _onEntering = HP_moveStep3;
}

void HP_moveStep3() {
    //TODO change state depends on remote
    HP_calculateStep3(&status);
    _onEntering = HP_moveStep4;
}

void HP_moveStep4() {
    //TODO recalculate linear & rotate
    HP_calculateStep4(&status);
    _onEntering = HP_moveStep5;
}

void HP_moveStep5() {
    HP_calculateStep5(&status);
    _onEntering = HP_moveStep6;
}

void HP_moveStep6() {
    HP_calculateStep6(&status);
    _onEntering = HP_moveStep7;
}

void HP_moveStep7() {
    //TODO change state depends on remote
    HP_calculateStep7(&status);
    _onEntering = HP_moveStep8;
}

void HP_moveStep8() {
    //TODO recalculate linear & rotate
    HP_calculateStep8(&status);
    _onEntering = HP_moveStep1;
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