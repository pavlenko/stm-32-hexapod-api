/* Includes ------------------------------------------------------------------*/

#include <math.h>
#include "hexapod.h"

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

const float HP_BODY_RADIUS_X1 = 170;
const float HP_BODY_RADIUS_X4 = 680;

const float STEP_PART_X1 = 10;
const float STEP_PART_X2 = 20;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

Hexapod_t h;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void HP_calculateRotationCenter(HP_Remote_t *remote, HP_Status_t *status) {
    if (remote->moveX == 0 && remote->moveY == 0) {
        status->rotateZBy.x = 0;
        status->rotateZBy.y = 0;
    } else if (remote->moveX == 0) {
        status->rotateZBy.x = HP_BODY_RADIUS_X4 * ((float) remote->rotateZ);
        status->rotateZBy.y = 0;
    } else if (remote->moveY == 0) {
        status->rotateZBy.x = 0;
        status->rotateZBy.y = HP_BODY_RADIUS_X4 * ((float) remote->rotateZ);
    } else {
        float angle  = atan2f(remote->moveY, remote->moveX);
        float rotate = (float) remote->rotateZ * (float) M_PI_2;
        float result;

        if (angle >= 0) {
            result = angle - rotate;
        } else {
            result = angle + rotate;
        }

        status->rotateZBy.x = HP_BODY_RADIUS_X4 * cosf(result);
        status->rotateZBy.y = HP_BODY_RADIUS_X4 * sinf(result);
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

void hp_calculateInit() {
    h.legs[LEG_FL].tgt = (Point3D_t) {h.legs[LEG_FL].def.x, h.legs[LEG_FL].def.y, h.legs[LEG_FL].def.z};
    h.legs[LEG_FR].tgt = (Point3D_t) {h.legs[LEG_FR].def.x, h.legs[LEG_FR].def.y, h.legs[LEG_FR].def.z};
    h.legs[LEG_ML].tgt = (Point3D_t) {h.legs[LEG_ML].def.x, h.legs[LEG_ML].def.y, h.legs[LEG_ML].def.z};
    h.legs[LEG_MR].tgt = (Point3D_t) {h.legs[LEG_MR].def.x, h.legs[LEG_MR].def.y, h.legs[LEG_MR].def.z};
    h.legs[LEG_BL].tgt = (Point3D_t) {h.legs[LEG_BL].def.x, h.legs[LEG_BL].def.y, h.legs[LEG_BL].def.z};
    h.legs[LEG_BR].tgt = (Point3D_t) {h.legs[LEG_BR].def.x, h.legs[LEG_BR].def.y, h.legs[LEG_BR].def.z};
}

void hp_calculateIdle() {
    h.legs[LEG_FL].tgt = (Point3D_t) {h.legs[LEG_FL].def.x, h.legs[LEG_FL].def.y, h.height};
    h.legs[LEG_FR].tgt = (Point3D_t) {h.legs[LEG_FR].def.x, h.legs[LEG_FR].def.y, h.height};
    h.legs[LEG_ML].tgt = (Point3D_t) {h.legs[LEG_ML].def.x, h.legs[LEG_ML].def.y, h.height};
    h.legs[LEG_MR].tgt = (Point3D_t) {h.legs[LEG_MR].def.x, h.legs[LEG_MR].def.y, h.height};
    h.legs[LEG_BL].tgt = (Point3D_t) {h.legs[LEG_BL].def.x, h.legs[LEG_BL].def.y, h.height};
    h.legs[LEG_BR].tgt = (Point3D_t) {h.legs[LEG_BR].def.x, h.legs[LEG_BR].def.y, h.height};
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

/* Exported functions ------------------------------------------------------- */