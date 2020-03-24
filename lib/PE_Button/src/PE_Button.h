//
// Created by master on 24.03.20.
//

#ifndef STM_32_HEXAPOD_API_PE_BUTTON_H
#define STM_32_HEXAPOD_API_PE_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef PE_BUTTON_USE_HOLD_SINGULAR
#define PE_BUTTON_USE_HOLD_SINGULAR
#endif

#ifndef PE_BUTTON_USE_HOLD_REPEATED
#define PE_BUTTON_USE_HOLD_REPEATED
#endif

#ifndef PE_BUTTON_TIMEOUT_DEBRIEF
#define PE_BUTTON_TIMEOUT_DEBRIEF 20U
#endif

#ifndef PE_BUTTON_TIMEOUT_HOLD_SINGULAR
#define PE_BUTTON_TIMEOUT_HOLD_SINGULAR 800U
#endif

#ifndef PE_BUTTON_TIMEOUT_HOLD_REPEATED
#define PE_BUTTON_TIMEOUT_HOLD_REPEATED 1200U
#endif

#ifndef PE_BUTTON_TIMEOUT_REPEAT
#define PE_BUTTON_TIMEOUT_REPEAT 200U
#endif

//TODO maybe use common callbacks
typedef void (*PE_Button_Handler_t) ();

//TODO button counters & status
typedef struct PE_Button_Key_s {
    PE_Button_Handler_t onPress;
    PE_Button_Handler_t onRelease;
#if defined(PE_BUTTON_USE_HOLD_SINGULAR)
    PE_Button_Handler_t onHoldSingular;
#endif
#if defined(PE_BUTTON_USE_HOLD_REPEATED)
    PE_Button_Handler_t onHoldRepeated;
#endif
} PE_Button_Key_t;

#ifdef __cplusplus
}
#endif

#endif //STM_32_HEXAPOD_API_PE_BUTTON_H
