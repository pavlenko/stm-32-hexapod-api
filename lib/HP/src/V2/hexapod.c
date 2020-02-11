/* Includes ------------------------------------------------------------------*/

#include <math.h>
#include "hexapod.h"

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

const float BODY_RADIUS_X1 = 170;
const float BODY_RADIUS_X4 = 680;

const float STEP_PART_X1 = 10;
const float STEP_PART_X2 = 20;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

Hexapod_t h;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void HP_calculateRotationCenter(HP_Remote_t *remote, HP_Status_t *status) {

}

void hp_calculateRotationCenter() {
    if (h.moveX == 0 && h.moveY == 0) {
        h.rotateZBy.x = 0;
        h.rotateZBy.y = 0;
    } else if (h.moveX == 0) {
        h.rotateZBy.x = BODY_RADIUS_X4 * ((float) h.rotateZ);
        h.rotateZBy.y = 0;
    } else if (h.moveY == 0) {
        h.rotateZBy.x = 0;
        h.rotateZBy.y = BODY_RADIUS_X4 * ((float) h.rotateZ);
    } else {
        float direction = atanf(h.moveY / h.moveX) + ((float) h.rotateZ * (float) M_PI_2);

        h.rotateZBy.x = BODY_RADIUS_X4 * cosf(direction);
        h.rotateZBy.y = BODY_RADIUS_X4 * sinf(direction);
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