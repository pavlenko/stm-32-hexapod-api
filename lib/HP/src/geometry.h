/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef GEOMETRY_H
#define GEOMETRY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <math.h>

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct Point2D {
    float x;
    float y;
} Point2D_t;

typedef struct Point3D {
    float x;
    float y;
    float z;
} Point3D_t;

/* Exported macro ------------------------------------------------------------*/

/* Exported function prototypes --------------------------------------------- */

/**
 * Convert angle value from degrees to radians
 *
 * @param value
 * @return
 */
float convertDegreeToRadian(float value);

/**
 * Convert angle value from radians to degrees
 *
 * @param value
 * @return
 */
float convertRadianToDegree(float value);

/**
 * Calculate side by opposite angle based on cosine formula
 *
 * Formula: C = sqrt(A*A + B*B - 2*A*B*cos(c))
 *
 * @param adjacentSideA
 * @param adjacentSideB
 * @param oppositeAngle
 * @return
 */
float calculateSideByOppositeAngle(float adjacentSideA, float adjacentSideB, float oppositeAngle);

/**
 * Calculate angle by opposite side based on cosine formula
 *
 * Formula: c = acos((A*A + B*B - C*C) / (2*A*B))
 *
 * @param adjacentSideA
 * @param adjacentSideB
 * @param oppositeSide
 * @return
 */
float calculateAngleByOppositeSide(float adjacentSideA, float adjacentSideB, float oppositeSide);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //GEOMETRY_H
