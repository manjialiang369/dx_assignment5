//
// Created by lenovo on 2026/11/5.
//

#ifndef DX_ASSIGNMENT5_FREERTOS_LED_H
#define DX_ASSIGNMENT5_FREERTOS_LED_H

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BSP_LED_R = 0,
    BSP_LED_G = 1,
    BSP_LED_B = 2,
    BSP_LED_NUM
} BSP_LED_ID;

void BSP_LED_Init(void);

void BSP_LED_On(BSP_LED_ID id);
void BSP_LED_Off(BSP_LED_ID id);
void BSP_LED_Toggle(BSP_LED_ID id);

void BSP_LED_AllOff(void);

#ifdef __cplusplus
}
#endif

#endif //DX_ASSIGNMENT5_FREERTOS_LED_H
