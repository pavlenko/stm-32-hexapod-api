#ifndef PE_SPIDER_V2_MAIN_H
#define PE_SPIDER_V2_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct PE_SpiderV2_t PE_SpiderV2_t;

typedef struct PE_SpiderV2_Point2D_t {
    float x;
    float y;
} PE_SpiderV2_Point2D_t;

typedef struct PE_SpiderV2_Point3D_t {
    float x;
    float y;
    float z;
} PE_SpiderV2_Point3D_t;

typedef struct PE_SpiderV2_remote_t {
    float moveX;
    float moveY;
    int8_t rotateZ;
} PE_SpiderV2_remote_t;

typedef struct PE_SpiderV2_moving_t {
    uint16_t height;
    float moveByX;
    float moveByY;
    PE_SpiderV2_Point2D_t rotateZBy;
} PE_SpiderV2_moving_t;

typedef void (*PE_SpiderV2_StateHandler_t) ();

typedef struct PE_SpiderV2_State_t {
    PE_SpiderV2_StateHandler_t onEntering;
    PE_SpiderV2_StateHandler_t onDispatch;
} PE_SpiderV2_State_t;

typedef struct PE_SpiderV2_t {
    PE_SpiderV2_remote_t remote;
    PE_SpiderV2_moving_t moving;
    PE_SpiderV2_State_t *prevState;
    PE_SpiderV2_State_t *nextState;
} PE_SpiderV2_t;

#ifdef __cplusplus
}
#endif

#endif //PE_SPIDER_V2_MAIN_H
