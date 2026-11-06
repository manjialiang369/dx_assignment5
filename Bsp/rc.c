//
// Created by lenovo on 2026/11/5.
//

#include "rc.h"
#include "main.h"
#include "usart.h"
extern DMA_HandleTypeDef hdma_usart3_rx;
rc_t    rc;
uint8_t dbus_buf[RC_FRAME_LEN];

static void rc_decode(void) {
    rc.ch[0] = (dbus_buf[0] | (dbus_buf[1] << 8)) & 0x07FF;
    rc.ch[1] = ((dbus_buf[1] >> 3) | (dbus_buf[2] << 5)) & 0x07FF;
    rc.ch[2] = ((dbus_buf[2] >> 6) | (dbus_buf[3] << 2) | (dbus_buf[4] << 10)) & 0x07FF;
    rc.ch[3] = ((dbus_buf[4] >> 1) | (dbus_buf[5] << 7)) & 0x07FF;

    rc.s1 = (dbus_buf[5] >> 6) & 0x03;
    rc.s2 = (dbus_buf[5] >> 4) & 0x03;
}

void RC_Init(void){
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart3, dbus_buf, RC_FRAME_LEN);
}

void RC_IDLE_Handler(void)
{
    if ((__HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE) == RESET) ||
        (__HAL_UART_GET_IT_SOURCE(&huart3, UART_IT_IDLE) == RESET)) {
        return;
        }

    __HAL_UART_CLEAR_IDLEFLAG(&huart3);
    HAL_UART_DMAStop(&huart3);

    if ((RC_FRAME_LEN - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx)) == RC_FRAME_LEN) {
        rc_decode();
    }

    __HAL_DMA_SET_COUNTER(&hdma_usart3_rx, RC_FRAME_LEN);
    HAL_UART_Receive_DMA(&huart3, dbus_buf, RC_FRAME_LEN);
}