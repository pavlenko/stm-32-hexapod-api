#ifndef PE_SPIDER_V2_MAIN_H
#define PE_SPIDER_V2_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "PE_SpiderV2_common.h"

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

PE_SpiderV2_Status_t PE_SpiderV2_initialize(PE_SpiderV2_t *spider);
void PE_SpiderV2_refreshMs(PE_SpiderV2_t *spider, uint32_t millis);

void PE_SpiderV2_refreshOnEntering(PE_SpiderV2_t *spider);
void PE_SpiderV2_refreshOnDispatch(PE_SpiderV2_t *spider);
void PE_SpiderV2_refreshOnComplete(PE_SpiderV2_t *spider);

extern const uint32_t PE_SpiderV2_DELAY_MS_INIT;
extern const uint32_t PE_SpiderV2_DELAY_MS_MOVE;

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
