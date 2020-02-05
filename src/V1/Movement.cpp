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

Point3D_t mounts[LEG_COUNT] = {
        {.x = -85, .y = 147.2, .z = 0},
        {.x = 85, .y = 147.2, .z = 0},
        {.x = -170, .y = 0, .z = 0},
        {.x = 170, .y = 0, .z = 0},
        {.x = -85, .y = -147.2, .z = 0},
        {.x = 85, .y = -147.2, .z = 0},
};

static float SIN_60 = 0.866025403784;
static float COS_60 = 0.5;

static float heightInit = 0;
static float heightIdle = 60;

static float targetNear = 30;
static float targetIdle = 120;

static float stepSizeFull = 40;
static float stepSizeHalf = 20;
static float stepSizeQuat = 10;

void calculateInit() {
    float diffX = targetNear * COS_60;
    float diffY = targetNear * SIN_60;

    Point3D_t targets[6] = {
            {.x = mounts[LEG_F_L].x - diffX, .y = mounts[LEG_F_L].y + diffY, .z = mounts[LEG_F_L].z - heightInit},
            {.x = mounts[LEG_F_R].x + diffX, .y = mounts[LEG_F_R].y + diffY, .z = mounts[LEG_F_R].z - heightInit},
            {.x = mounts[LEG_M_L].x + targetNear, .y = mounts[LEG_M_L].y, .z = mounts[LEG_M_L].z - heightInit},
            {.x = mounts[LEG_M_R].x + targetNear, .y = mounts[LEG_M_R].y, .z = mounts[LEG_M_R].z - heightInit},
            {.x = mounts[LEG_B_L].x - diffX, .y = mounts[LEG_B_L].y - diffY, .z = mounts[LEG_B_L].z - heightInit},
            {.x = mounts[LEG_B_R].x + diffX, .y = mounts[LEG_B_R].y - diffY, .z = mounts[LEG_B_R].z - heightInit},
    };
}

void calculateIdle() {
    float diffX = targetIdle * COS_60;
    float diffY = targetIdle * SIN_60;

    Point3D_t targets[6] = {
            {.x = mounts[LEG_F_L].x - diffX, .y = mounts[LEG_F_L].y + diffY, .z = mounts[LEG_F_L].z - heightIdle},
            {.x = mounts[LEG_F_R].x + diffX, .y = mounts[LEG_F_R].y + diffY, .z = mounts[LEG_F_R].z - heightIdle},
            {.x = mounts[LEG_M_L].x + targetIdle, .y = mounts[LEG_M_L].y, .z = mounts[LEG_M_L].z - heightIdle},
            {.x = mounts[LEG_M_R].x + targetIdle, .y = mounts[LEG_M_R].y, .z = mounts[LEG_M_R].z - heightIdle},
            {.x = mounts[LEG_B_L].x - diffX, .y = mounts[LEG_B_L].y - diffY, .z = mounts[LEG_B_L].z - heightIdle},
            {.x = mounts[LEG_B_R].x + diffX, .y = mounts[LEG_B_R].y - diffY, .z = mounts[LEG_B_R].z - heightIdle},
    };
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
    if (control.rotateZ != 0) {
        if (control.moveX != 0 || control.moveY != 0) {
            //TODO rotate + move
        } else {
            //TODO rotate only
            float rotateByX = 0;
            float rotateByY = 0;
        }
    } else {
        //TODO move only
        float angle = atan(control.moveY / control.moveX);
        float coefX = cos(angle);
        float coefY = sin(angle);

        float diffX = targetIdle * COS_60;
        float diffY = targetIdle * SIN_60;

        Point3D_t targets[6] = {
                {.x = mounts[LEG_F_L].x - diffX + (stepSizeQuat * coefX), .y = mounts[LEG_F_L].y + diffY + (stepSizeQuat * coefY), .z = mounts[LEG_F_L].z - heightInit},
                {.x = mounts[LEG_F_R].x + diffX - (stepSizeQuat * coefX), .y = mounts[LEG_F_R].y + diffY - (stepSizeQuat * coefY), .z = mounts[LEG_F_R].z - heightIdle},
                {.x = mounts[LEG_M_L].x + targetIdle + (stepSizeQuat * coefX), .y = mounts[LEG_M_L].y + (stepSizeQuat * coefY), .z = mounts[LEG_M_L].z - heightInit},
                {.x = mounts[LEG_M_R].x + targetIdle - (stepSizeQuat * coefX), .y = mounts[LEG_M_R].y - (stepSizeQuat * coefY), .z = mounts[LEG_M_R].z - heightIdle},
                {.x = mounts[LEG_B_L].x - diffX + (stepSizeQuat * coefX), .y = mounts[LEG_B_L].y - diffY + (stepSizeQuat * coefY), .z = mounts[LEG_B_L].z - heightInit},
                {.x = mounts[LEG_B_R].x + diffX - (stepSizeQuat * coefX), .y = mounts[LEG_B_R].y - diffY - (stepSizeQuat * coefY), .z = mounts[LEG_B_R].z - heightIdle},
        };
    }

    //TODO FL, MR, BL: z = 0; xy -= step/4; FR, ML, BR: z = -60; xy += step/4
}
void calculateStep2() {
    //TODO FL, MR, BL: z = -60; xy -= step/2; FR, ML, BR: z = -60; xy += step/2
}
void calculateStep3() {
    //TODO FL, MR, BL: z = -60; xy -= step/4; FR, ML, BR: z = 0; xy += step/4
}
void calculateStep4() {
    //TODO FL, MR, BL: z = -60; xy -= 0; FR, ML, BR: z = 0; xy += 0
}
void calculateStep5() {
    //TODO FL, MR, BL: z = -60; xy += step/4; FR, ML, BR: z = 0; xy -= step/4
}
void calculateStep6() {
    //TODO FL, MR, BL: z = -60; xy += step/2; FR, ML, BR: z = -60; xy -= step/2
}
void calculateStep7() {
    //TODO FL, MR, BL: z = -0; xy += step/4; FR, ML, BR: z = -60; xy -= step/4
}
void calculateStep8() {
    //TODO FL, MR, BL: z = -0; xy += 0; FR, ML, BR: z = -60; xy -= 0
}
