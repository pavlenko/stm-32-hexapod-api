#ifndef PE_SPIDER_V2_GEOMETRY_H
#define PE_SPIDER_V2_GEOMETRY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "PE_SpiderV2_common.h"

void PE_SpiderV2_calculateMovingLinear(PE_SpiderV2_Remote_t *remote, PE_SpiderV2_Moving_t *moving);

void PE_SpiderV2_calculateMovingRotate(PE_SpiderV2_Remote_t *remote, PE_SpiderV2_Moving_t *moving);

void PE_SpiderV2_calculateTargetLinear(PE_SpiderV2_Moving_t *moving, PE_SpiderV2_Leg_t *leg, float step, PE_SpiderV2_LegMode_t mode);

void PE_SpiderV2_calculateTargetRotate(PE_SpiderV2_Moving_t *moving, PE_SpiderV2_Leg_t *leg, float step, PE_SpiderV2_LegMode_t mode);

void PE_SpiderV2_calculateDegree(PE_SpiderV2_Leg_t *leg);

#ifdef __cplusplus
}
#endif

#endif //PE_SPIDER_V2_GEOMETRY_H
