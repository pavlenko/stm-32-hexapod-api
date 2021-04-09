#include "PE_SpiderV2_geometry.h"

#include <math.h>
#include <stddef.h>

const float PE_SpiderV2_ROTATE_RADIUS = 680;

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

float PE_SpiderV2_calculateAngleByOppositeSide(float adjacentSideA, float adjacentSideB, float oppositeSide) {
    return acosf(
            (adjacentSideA * adjacentSideA + adjacentSideB * adjacentSideB - oppositeSide * oppositeSide) /
            (2 * adjacentSideA * adjacentSideB)
    );
}