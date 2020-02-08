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

const float PI = (float) M_PI;

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
static inline float deg2rad(float value);

/**
 * Convert angle value from radians to degrees
 *
 * @param value
 * @return
 */
static inline float rad2deg(float value);

//TODO helper functions for calculate geometry: theorem of cosinus, etc

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //GEOMETRY_H
