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

typedef struct PE_SpiderV2_remote_s {
    float moveX;
    float moveY;
    int8_t rotateZ;
} PE_SpiderV2_remote_t;

typedef struct PE_SpiderV2_moving_s {
    uint16_t height;
    float moveByX;
    float moveByY;
    PE_SpiderV2_Point2D_t rotateZBy;
} PE_SpiderV2_moving_t;

typedef void (*PE_SpiderV2_StateHandler_t) ();

typedef struct PE_SpiderV2_State_s {
    PE_SpiderV2_StateHandler_t onEntering;
    PE_SpiderV2_StateHandler_t onDispatch;
} PE_SpiderV2_State_t;

typedef struct PE_SpiderV2_s {
    PE_SpiderV2_Point2D_t legMounts[6];
    PE_SpiderV2_Point3D_t legSources[6];
    PE_SpiderV2_Point3D_t legTargets[6];
    PE_SpiderV2_remote_t remote;
    PE_SpiderV2_moving_t moving;
    PE_SpiderV2_State_t *prevState;
    PE_SpiderV2_State_t *nextState;
    uint32_t millis;
} PE_SpiderV2_t;

void PE_SpiderV2_dispatch(PE_SpiderV2_t *spider, uint32_t millis);

#ifdef __cplusplus
}
#endif

#endif //PE_SPIDER_V2_MAIN_H
