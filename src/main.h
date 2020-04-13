#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32f1xx.h"

#include <PE_nRF24L01.h>
#include <PE_Button.h>
#include <PE_Servo180.h>
#include <PE_SpiderV2.h>
#include "led.h"

extern I2C_HandleTypeDef I2C2_Handle;
extern SPI_HandleTypeDef SPIn;
extern PE_nRF24_t nRF24;

extern TIM_HandleTypeDef TIM2_Handle;
extern TIM_HandleTypeDef TIM3_Handle;
extern TIM_HandleTypeDef TIM4_Handle;

extern PE_Servo180_Timer_t timer1;
extern PE_Servo180_Timer_t timer2;
extern PE_Servo180_Timer_t timer3;

extern PE_Servo180_Motor_t motor01;
extern PE_Servo180_Motor_t motor02;
extern PE_Servo180_Motor_t motor03;
extern PE_Servo180_Motor_t motor04;
extern PE_Servo180_Motor_t motor05;
extern PE_Servo180_Motor_t motor06;
extern PE_Servo180_Motor_t motor07;
extern PE_Servo180_Motor_t motor08;
extern PE_Servo180_Motor_t motor09;
extern PE_Servo180_Motor_t motor10;
extern PE_Servo180_Motor_t motor11;
extern PE_Servo180_Motor_t motor12;
extern PE_Servo180_Motor_t motor13;
extern PE_Servo180_Motor_t motor14;
extern PE_Servo180_Motor_t motor15;
extern PE_Servo180_Motor_t motor16;
extern PE_Servo180_Motor_t motor17;
extern PE_Servo180_Motor_t motor18;

extern PE_SpiderV2_t spiderV2;

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void Error_Handler(const char *, int);

#ifdef __cplusplus
}
#endif

#endif //MAIN_H
