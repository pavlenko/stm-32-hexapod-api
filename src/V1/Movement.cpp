//
// Created by master on 29.01.20.
//

#include <cmath>
#include "Movement.hpp"

typedef struct Point3D_t {
    float x;
    float y;
    float z;
} Point3D_t;

typedef enum Legs_t {
    LEG_F_L,
    LEG_F_R,
    LEG_M_L,
    LEG_M_R,
    LEG_B_L,
    LEG_B_R,
    LEG_COUNT,
} Legs_t;

// Default mounts for legs (by radius 170mm)
//const Point3D_t mntFL = {.x = -85, .y = 147.2, .z = 0};
//const Point3D_t mntFR = {.x = 85, .y = 147.2, .z = 0};
//const Point3D_t mntML = {.x = -170, .y = 0, .z = 0};
//const Point3D_t mntMR = {.x = 170, .y = 0, .z = 0};
//const Point3D_t mntBL = {.x = -85, .y = -147.2, .z = 0};
//const Point3D_t mntBR = {.x = 85, .y = -147.2, .z = 0};

// Default destinations for init and idle steps (by radius 170mm + 100mm)
const Point3D_t dstFL = {.x = -135, .y = 233.83, .z = 0};
const Point3D_t dstFR = {.x = 135, .y = 233.83, .z = 0};
const Point3D_t dstML = {.x = -270, .y = 0, .z = 0};
const Point3D_t dstMR = {.x = 270, .y = 0, .z = 0};
const Point3D_t dstBL = {.x = -135, .y = -233.83, .z = 0};
const Point3D_t dstBR = {.x = 135, .y = -233.83, .z = 0};

//static float SIN_60 = 0.866025403784;
//static float COS_60 = 0.5;

//static float heightInit = 0;
static float heightIdle = 60;

//static float targetNear = 30;
//static float targetIdle = 120;

//static float stepSizeFull = 40;
static float stepX2 = 20;
static float stepX1 = 10;

void setTarget(Legs_t i, float x, float y, float z) {
    (void) i; (void) x; (void) y; (void) z;
}
void calculateInit() {
    setTarget(LEG_F_L, dstFL.x, dstFL.y, dstFL.z);
    setTarget(LEG_F_R, dstFR.x, dstFR.y, dstFR.z);
    setTarget(LEG_M_L, dstML.x, dstML.y, dstML.z);
    setTarget(LEG_M_R, dstMR.x, dstMR.y, dstMR.z);
    setTarget(LEG_B_L, dstBL.x, dstBL.y, dstBL.z);
    setTarget(LEG_B_R, dstBR.x, dstBR.y, dstBR.z);
}
void calculateIdle() {
    setTarget(LEG_F_L, dstFL.x, dstFL.y, -heightIdle);
    setTarget(LEG_F_R, dstFR.x, dstFR.y, -heightIdle);
    setTarget(LEG_M_L, dstML.x, dstML.y, -heightIdle);
    setTarget(LEG_M_R, dstMR.x, dstMR.y, -heightIdle);
    setTarget(LEG_B_L, dstBL.x, dstBL.y, -heightIdle);
    setTarget(LEG_B_R, dstBR.x, dstBR.y, -heightIdle);
}
/**
 *      b
 *      *
 *     / \
 *  C /   \ A
 *   /     \
 *  *-------*
 * a    B    c
 *
 * B^2 = A^2 + C^2 - 2*A*C*cos(b)
 *
 * cos(b) = (A^2 + C^2 - B^2) / (2 * A * C)
 */

//TODO if only move - just use direction for calculate
//TODO if only rotate - use center point for rotate
//TODO if rotate+move - use direction for resolve rotate point and use it for calculate (differential?????)

void calculateStep1() {
    //TODO FL, MR, BL: z = 0; xy -= step/4; FR, ML, BR: z = -60; xy += step/4
    float rotateByX = 0, rotateByY = 0;

    if (control.rotateZ != 0) {
        if (control.moveX != 0 || control.moveY != 0) {
            //TODO rotate + move
        } else {
            //TODO rotate only
            //float rotateByX = 0;
            //float rotateByY = 0;
        }
    } else {}

    // Find distance between rotate point & base dst point
    float l_dst2rot = hypotf(rotateByX - dstFL.x, rotateByY - dstFL.y);
    float l_tgt2rot = l_dst2rot;
    float l_dst2tgt = stepX1;

    // Find angle between dst2rot and tgt2rot sides: cos(b) = (A^2 + C^2 - B^2) / (2 * A * C)
    float a_diff = acosf((l_dst2rot * l_dst2rot + l_tgt2rot * l_tgt2rot - l_dst2tgt * l_dst2tgt) / (2 * l_dst2rot * l_tgt2rot));

    // Find angle between dst2rot and x axis
    float a_dst2x = acosf((rotateByX - dstFL.x) / l_dst2rot);

    // LEG target angle if ccw: deg = a_dst2x - angle, else deg = a_dst2x + angle, x = l_dst2rot * cos(deg), y = l_dst2rot * sin(deg)
    float deg = a_dst2x - a_diff;
    float x = l_dst2rot * cosf(deg);
    float y = l_dst2rot * sinf(deg);

    //TODO how to calculate LEG CCW/CW depends on rotate direction
    (void) x;
    (void) y;
    // End calc rotation

    // Move only (for now)
    float angle = atanf(control.moveY / control.moveX);
    float diffX = cosf(angle);
    float diffY = sinf(angle);

    setTarget(LEG_F_L, dstFL.x + (stepX1 * diffX), dstFL.y + (stepX1 * diffY), dstFL.z);
    setTarget(LEG_F_R, dstFR.x - (stepX1 * diffX), dstFR.y - (stepX1 * diffY), -heightIdle);
    setTarget(LEG_M_L, dstML.x + (stepX1 * diffX), dstML.y + (stepX1 * diffY), dstML.z);
    setTarget(LEG_M_R, dstMR.x - (stepX1 * diffX), dstMR.y - (stepX1 * diffY), -heightIdle);
    setTarget(LEG_B_L, dstBL.x + (stepX1 * diffX), dstBL.y + (stepX1 * diffY), dstBL.z);
    setTarget(LEG_B_R, dstBR.x - (stepX1 * diffX), dstBR.y - (stepX1 * diffY), -heightIdle);
}
void calculateStep2() {
    //TODO FL, MR, BL: z = -60; xy -= step/2; FR, ML, BR: z = -60; xy += step/2

    // Move only (for now)
    float angle = atanf(control.moveY / control.moveX);
    float diffX = cosf(angle);
    float diffY = sinf(angle);

    setTarget(LEG_F_L, dstFL.x + (stepX2 * diffX), dstFL.y + (stepX2 * diffY), -heightIdle);
    setTarget(LEG_F_R, dstFR.x - (stepX2 * diffX), dstFR.y - (stepX2 * diffY), -heightIdle);
    setTarget(LEG_M_L, dstML.x + (stepX2 * diffX), dstML.y + (stepX2 * diffY), -heightIdle);
    setTarget(LEG_M_R, dstMR.x - (stepX2 * diffX), dstMR.y - (stepX2 * diffY), -heightIdle);
    setTarget(LEG_B_L, dstBL.x + (stepX2 * diffX), dstBL.y + (stepX2 * diffY), -heightIdle);
    setTarget(LEG_B_R, dstBR.x - (stepX2 * diffX), dstBR.y - (stepX2 * diffY), -heightIdle);
}
void calculateStep3() {
    //TODO FL, MR, BL: z = -60; xy -= step/4; FR, ML, BR: z = 0; xy += step/4

    // Move only (for now)
    float angle = atan(control.moveY / control.moveX);
    float diffX = cos(angle);
    float diffY = sin(angle);

    setTarget(LEG_F_L, dstFL.x + (stepX1 * diffX), dstFL.y + (stepX1 * diffY), -heightIdle);
    setTarget(LEG_F_R, dstFR.x - (stepX1 * diffX), dstFR.y - (stepX1 * diffY), dstFR.z);
    setTarget(LEG_M_L, dstML.x + (stepX1 * diffX), dstML.y + (stepX1 * diffY), -heightIdle);
    setTarget(LEG_M_R, dstMR.x - (stepX1 * diffX), dstMR.y - (stepX1 * diffY), dstMR.z);
    setTarget(LEG_B_L, dstBL.x + (stepX1 * diffX), dstBL.y + (stepX1 * diffY), -heightIdle);
    setTarget(LEG_B_R, dstBR.x - (stepX1 * diffX), dstBR.y - (stepX1 * diffY), dstBR.z);
}
void calculateStep4() {
    //TODO FL, MR, BL: z = -60; xy -= 0; FR, ML, BR: z = 0; xy += 0

    // Move only (for now)
    setTarget(LEG_F_L, dstFL.x, dstFL.y, -heightIdle);
    setTarget(LEG_F_R, dstFR.x, dstFR.y, dstFR.z);
    setTarget(LEG_M_L, dstML.x, dstML.y, -heightIdle);
    setTarget(LEG_M_R, dstMR.x, dstMR.y, dstMR.z);
    setTarget(LEG_B_L, dstBL.x, dstBL.y, -heightIdle);
    setTarget(LEG_B_R, dstBR.x, dstBR.y, dstBR.z);
}
void calculateStep5() {
    //TODO FL, MR, BL: z = -60; xy += step/4; FR, ML, BR: z = 0; xy -= step/4

    // Move only (for now)
    float angle = atan(control.moveY / control.moveX);
    float diffX = cos(angle);
    float diffY = sin(angle);

    setTarget(LEG_F_L, dstFL.x - (stepX1 * diffX), dstFL.y - (stepX1 * diffY), -heightIdle);
    setTarget(LEG_F_R, dstFR.x + (stepX1 * diffX), dstFR.y + (stepX1 * diffY), dstFR.z);
    setTarget(LEG_M_L, dstML.x - (stepX1 * diffX), dstML.y - (stepX1 * diffY), -heightIdle);
    setTarget(LEG_M_R, dstMR.x + (stepX1 * diffX), dstMR.y + (stepX1 * diffY), dstMR.z);
    setTarget(LEG_B_L, dstBL.x - (stepX1 * diffX), dstBL.y - (stepX1 * diffY), -heightIdle);
    setTarget(LEG_B_R, dstBR.x + (stepX1 * diffX), dstBR.y + (stepX1 * diffY), dstBR.z);
}
void calculateStep6() {
    //TODO FL, MR, BL: z = -60; xy += step/2; FR, ML, BR: z = -60; xy -= step/2

    // Move only (for now)
    float angle = atan(control.moveY / control.moveX);
    float diffX = cos(angle);
    float diffY = sin(angle);

    setTarget(LEG_F_L, dstFL.x - (stepX2 * diffX), dstFL.y - (stepX2 * diffY), -heightIdle);
    setTarget(LEG_F_R, dstFR.x + (stepX2 * diffX), dstFR.y + (stepX2 * diffY), -heightIdle);
    setTarget(LEG_M_L, dstML.x - (stepX2 * diffX), dstML.y - (stepX2 * diffY), -heightIdle);
    setTarget(LEG_M_R, dstMR.x + (stepX2 * diffX), dstMR.y + (stepX2 * diffY), -heightIdle);
    setTarget(LEG_B_L, dstBL.x - (stepX2 * diffX), dstBL.y - (stepX2 * diffY), -heightIdle);
    setTarget(LEG_B_R, dstBR.x + (stepX2 * diffX), dstBR.y + (stepX2 * diffY), -heightIdle);
}
void calculateStep7() {
    //TODO FL, MR, BL: z = -0; xy += step/4; FR, ML, BR: z = -60; xy -= step/4

    // Move only (for now)
    float angle = atan(control.moveY / control.moveX);
    float diffX = cos(angle);
    float diffY = sin(angle);

    setTarget(LEG_F_L, dstFL.x - (stepX1 * diffX), dstFL.y - (stepX1 * diffY), dstFL.z);
    setTarget(LEG_F_R, dstFR.x + (stepX1 * diffX), dstFR.y + (stepX1 * diffY), -heightIdle);
    setTarget(LEG_M_L, dstML.x - (stepX1 * diffX), dstML.y - (stepX1 * diffY), dstML.z);
    setTarget(LEG_M_R, dstMR.x + (stepX1 * diffX), dstMR.y + (stepX1 * diffY), -heightIdle);
    setTarget(LEG_B_L, dstBL.x - (stepX1 * diffX), dstBL.y - (stepX1 * diffY), dstBL.z);
    setTarget(LEG_B_R, dstBR.x + (stepX1 * diffX), dstBR.y + (stepX1 * diffY), -heightIdle);
}
void calculateStep8() {
    //TODO FL, MR, BL: z = -0; xy += 0; FR, ML, BR: z = -60; xy -= 0

    // Move only (for now)
    setTarget(LEG_F_L, dstFL.x, dstFL.y, dstFL.z);
    setTarget(LEG_F_R, dstFR.x, dstFR.y, -heightIdle);
    setTarget(LEG_M_L, dstML.x, dstML.y, dstML.z);
    setTarget(LEG_M_R, dstMR.x, dstMR.y, -heightIdle);
    setTarget(LEG_B_L, dstBL.x, dstBL.y, dstBL.z);
    setTarget(LEG_B_R, dstBR.x, dstBR.y, -heightIdle);
}
