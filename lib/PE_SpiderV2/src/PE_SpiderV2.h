#ifndef PE_SPIDER_V2_MAIN_H
#define PE_SPIDER_V2_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum PE_SpiderV2_LegMode_s {
    PE_SPIDER_V2_LEG_MODE_GROUNDED,
    PE_SPIDER_V2_LEG_MODE_FLOATING,
} PE_SpiderV2_LegMode_t;

typedef enum PE_SpiderV2_LegPos_s {
    PE_SPIDER_V2_LEG_POS_FL,
    PE_SPIDER_V2_LEG_POS_FR,
    PE_SPIDER_V2_LEG_POS_ML,
    PE_SPIDER_V2_LEG_POS_MR,
    PE_SPIDER_V2_LEG_POS_BL,
    PE_SPIDER_V2_LEG_POS_BR,
} PE_SpiderV2_LegPos_t;

typedef struct PE_SpiderV2_Leg_s PE_SpiderV2_Leg_t;
typedef struct PE_SpiderV2_s PE_SpiderV2_t;

typedef struct PE_SpiderV2_Point2D_s {
    float x;
    float y;
} PE_SpiderV2_Point2D_t;

typedef struct PE_SpiderV2_Point3D_s {
    float x;
    float y;
    float z;
} PE_SpiderV2_Point3D_t;

typedef struct PE_SpiderV2_Remote_s {
    float moveX;
    float moveY;
    int8_t rotateZ;
} PE_SpiderV2_Remote_t;

typedef struct PE_SpiderV2_Moving_s {
    uint16_t height;
    float moveByX;
    float moveByY;
    PE_SpiderV2_Point2D_t rotateZBy;
} PE_SpiderV2_Moving_t;

typedef void (*PE_SpiderV2_StateHandler_t) (PE_SpiderV2_t *spider);
typedef void (*PE_SpiderV2_Calculate_t) (PE_SpiderV2_Moving_t *moving, PE_SpiderV2_Leg_t *leg, float step, PE_SpiderV2_LegMode_t mode);

typedef struct PE_SpiderV2_State_s {
    PE_SpiderV2_StateHandler_t onEntering;
    PE_SpiderV2_StateHandler_t onDispatch;
} PE_SpiderV2_State_t;

typedef struct PE_SpiderV2_Leg_s {
    float cLength;
    float fLength;
    float tLength;
    PE_SpiderV2_Point3D_t mnt;
    PE_SpiderV2_Point3D_t src;
    PE_SpiderV2_Point3D_t dst;
    float cDegree;
    float fDegree;
    float tDegree;
} PE_SpiderV2_Leg_t;

typedef struct PE_SpiderV2_s {
    uint32_t delayMs;
    uint32_t startMs;
    PE_SpiderV2_Leg_t legs[6];
    PE_SpiderV2_Remote_t remote;
    PE_SpiderV2_Moving_t moving;
    PE_SpiderV2_State_t *currState;
    PE_SpiderV2_State_t *nextState;
    PE_SpiderV2_Calculate_t calculate;
} PE_SpiderV2_t;

void PE_SpiderV2_calculateMovingLinear(PE_SpiderV2_Remote_t *remote, PE_SpiderV2_Moving_t *moving);
void PE_SpiderV2_calculateMovingRotate(PE_SpiderV2_Remote_t *remote, PE_SpiderV2_Moving_t *moving);
void PE_SpiderV2_calculateTargetLinear(PE_SpiderV2_Moving_t *moving, PE_SpiderV2_Leg_t *leg, float step, PE_SpiderV2_LegMode_t mode);
void PE_SpiderV2_calculateTargetRotate(PE_SpiderV2_Moving_t *moving, PE_SpiderV2_Leg_t *leg, float step, PE_SpiderV2_LegMode_t mode);

void PE_SpiderV2_calculateDegree(PE_SpiderV2_Leg_t *leg);

void PE_SpiderV2_handlerInit_onEntering(PE_SpiderV2_t *spider);
void PE_SpiderV2_handlerIdle_onEntering(PE_SpiderV2_t *spider);
void PE_SpiderV2_handlerIdle_onDispatch(PE_SpiderV2_t *spider);

void PE_SpiderV2_handlerMove1_onEntering(PE_SpiderV2_t *spider);
void PE_SpiderV2_handlerMove2_onEntering(PE_SpiderV2_t *spider);
void PE_SpiderV2_handlerMove3_onEntering(PE_SpiderV2_t *spider);
void PE_SpiderV2_handlerMove4_onEntering(PE_SpiderV2_t *spider);
void PE_SpiderV2_handlerMove5_onEntering(PE_SpiderV2_t *spider);
void PE_SpiderV2_handlerMove6_onEntering(PE_SpiderV2_t *spider);
void PE_SpiderV2_handlerMove7_onEntering(PE_SpiderV2_t *spider);
void PE_SpiderV2_handlerMove8_onEntering(PE_SpiderV2_t *spider);

void PE_SpiderV2_initialize(PE_SpiderV2_t *spider);
void PE_SpiderV2_dispatchMs(PE_SpiderV2_t *spider, uint32_t millis);
void PE_SpiderV2_onDispatch(PE_SpiderV2_t *spider);

extern const float PE_SpiderV2_ROTATE_RADIUS;

extern const float PE_SpiderV2_STEP_PART_X1;
extern const float PE_SpiderV2_STEP_PART_X2;

extern PE_SpiderV2_State_t PE_SpiderV2_stateInit;
extern PE_SpiderV2_State_t PE_SpiderV2_stateIdle;

extern PE_SpiderV2_State_t PE_SpiderV2_stateMove1;
extern PE_SpiderV2_State_t PE_SpiderV2_stateMove2;
extern PE_SpiderV2_State_t PE_SpiderV2_stateMove3;
extern PE_SpiderV2_State_t PE_SpiderV2_stateMove4;
extern PE_SpiderV2_State_t PE_SpiderV2_stateMove5;
extern PE_SpiderV2_State_t PE_SpiderV2_stateMove6;
extern PE_SpiderV2_State_t PE_SpiderV2_stateMove7;
extern PE_SpiderV2_State_t PE_SpiderV2_stateMove8;

#ifdef __cplusplus
}
#endif

#endif //PE_SPIDER_V2_MAIN_H
