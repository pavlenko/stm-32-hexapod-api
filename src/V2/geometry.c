/* Includes ------------------------------------------------------------------*/

#include "geometry.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

float convertDegreeToRadian(float value) {
    return ((float) M_PI) * value / 180;
}

float convertRadianToDegree(float value) {
    return value * 180 / ((float) M_PI);
}

float calculateSideByOppositeAngle(float adjacentSideA, float adjacentSideB, float oppositeAngle) {
    return sqrtf(
            adjacentSideA * adjacentSideA +
            adjacentSideB * adjacentSideB -
            2 * adjacentSideA * adjacentSideB * cosf(oppositeAngle)
    );
}

float calculateAngleByOppositeSide(float adjacentSideA, float adjacentSideB, float oppositeSide) {
    return acosf(
            (adjacentSideA * adjacentSideA + adjacentSideB * adjacentSideB - oppositeSide * oppositeSide) /
            (2 * adjacentSideA * adjacentSideB)
    );
}
