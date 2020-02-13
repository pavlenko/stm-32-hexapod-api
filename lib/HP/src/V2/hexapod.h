/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HEXAPOD_H
#define HEXAPOD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "geometry.h"

/* Exported constants --------------------------------------------------------*/

extern const float HP_BODY_RADIUS_X1;
extern const float HP_BODY_RADIUS_X4;

/* Exported types ------------------------------------------------------------*/

typedef enum HP_LegMode_e {
    LEG_MODE_GROUNDED,
    LEG_MODE_FLOATING,
} HP_LegMode_t;

typedef enum {
    LEG_FL,
    LEG_FR,
    LEG_ML,
    LEG_MR,
    LEG_BL,
    LEG_BR,
} Leg_n;

typedef struct {
    float moveX;
    float moveY;
    int8_t rotateZ;
} HP_Remote_t;

typedef struct {
    uint16_t height;
    float moveByX;
    float moveByY;
    Point2D_t rotateZBy;
} HP_Status_t;

typedef struct {
    Point3D_t mnt;
    Point3D_t def;
    Point3D_t tgt;
} HP_Leg_t;

typedef void (*HP_calculate_t) (HP_Status_t *status, HP_Leg_t *leg, float step, HP_LegMode_t mode);

typedef struct {
    HP_Leg_t legs[6];
    uint8_t height;
    HP_calculate_t calculate;
} Hexapod_t;

/* Exported macro ------------------------------------------------------------*/
/* Exported function prototypes --------------------------------------------- */

void HP_calculateRotationCenter(HP_Remote_t *remote, HP_Status_t *status);
void HP_calculateLinear(HP_Remote_t *remote, HP_Status_t *status);
void HP_calculateTargetLinear(HP_Status_t *status, HP_Leg_t *leg, float step, HP_LegMode_t mode);
void HP_calculateTargetRotate(HP_Status_t *status, HP_Leg_t *leg, float step, HP_LegMode_t mode);

void hp_calculateInit();
void hp_calculateIdle();
void HP_calculateStep1(HP_Status_t *status);
void HP_calculateStep2(HP_Status_t *status);
void HP_calculateStep3(HP_Status_t *status);
void HP_calculateStep4(HP_Status_t *status);
void HP_calculateStep5(HP_Status_t *status);
void HP_calculateStep6(HP_Status_t *status);
void HP_calculateStep7(HP_Status_t *status);
void HP_calculateStep8(HP_Status_t *status);

/* Exported variables --------------------------------------------------------*/

extern Hexapod_t h;

#ifdef __cplusplus
}
#endif

#endif //HEXAPOD_H
