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

void hp_calculateLegTarget(Leg_n n, float step, float height) {
    // Calculate leg rotation radius
    float rotationRadius = hypotf(h.rotateZBy.x - h.legs[n].def.x, h.rotateZBy.y - h.legs[n].def.y);

    // Calculate leg rotation angle
    float rotationAngle = calculateAngleByOppositeSide(rotationRadius, rotationRadius, step);

    // Calculate basic angle
    float basicAngle = acosf((h.rotateZBy.x - h.legs[n].def.x) / rotationRadius);

    float resultAngle = step < 0 ? basicAngle - rotationAngle : basicAngle + rotationAngle;//TODO result value sign must depends on step var sign

    h.legs[n].tgt = (Point3D_t) {rotationRadius * cosf(resultAngle), rotationRadius * sinf(resultAngle), -height};//TODO check result
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

/* Exported functions ------------------------------------------------------- */