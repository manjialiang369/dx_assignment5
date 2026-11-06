//
// Created by lenovo on 2026/11/4.
//

#ifndef DX_ASSIGNMENT5_FREERTOS_RC_H
#define DX_ASSIGNMENT5_FREERTOS_RC_H

#include "stm32f4xx_hal.h"
#define RC_FRAME_LEN 18
typedef struct {
    uint16_t ch[4];
    uint8_t  s1, s2;
} rc_t;
extern rc_t    rc;
extern uint8_t dbus_buf[RC_FRAME_LEN];
void RC_Init(void);
void RC_IDLE_Handler(void);

#endif //DX_ASSIGNMENT5_FREERTOS_RC_H
