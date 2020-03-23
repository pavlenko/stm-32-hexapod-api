/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H
#define __TIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported function prototypes --------------------------------------------- */

void MX_TIM_PWM_Init(TIM_TypeDef *tim, TIM_HandleTypeDef *handle);

/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif //__TIM_H
