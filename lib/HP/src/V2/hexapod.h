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
/* Exported types ------------------------------------------------------------*/

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
    Point2D_t rotateZBy;
} HP_Status_t;

typedef struct {
    Point3D_t mnt;
    Point3D_t def;
    Point3D_t tgt;
} Leg_t;

typedef struct {
    Leg_t legs[6];
    uint8_t height;
    float moveX;
    float moveY;
    int8_t rotateZ;
    Point2D_t rotateZBy;
} Hexapod_t;

/* Exported macro ------------------------------------------------------------*/
/* Exported function prototypes --------------------------------------------- */

void HP_calculateRotationCenter(HP_Remote_t *remote, HP_Status_t *status);

void hp_calculateInit();
void hp_calculateIdle();
void hp_calculateStep1();
void hp_calculateStep2();
void hp_calculateStep3();
void hp_calculateStep4();
void hp_calculateStep5();
void hp_calculateStep6();
void hp_calculateStep7();
void hp_calculateStep8();

/* Exported variables --------------------------------------------------------*/

extern Hexapod_t h;

#ifdef __cplusplus
}
#endif

#endif //HEXAPOD_H
