//
// Created by lenovo on 2026/11/5.
//
#include "LED.h"

typedef struct {
    GPIO_TypeDef *port;
    uint16_t      pin;
} bsp_led_map_t;


static const bsp_led_map_t led_map[BSP_LED_NUM] = {
    {LED_R_GPIO_Port, LED_R_Pin},
    {LED_G_GPIO_Port, LED_G_Pin},
    {LED_B_GPIO_Port, LED_B_Pin},
};

static inline int led_id_valid(BSP_LED_ID id)
{
    /* 强转 unsigned 同时挡住负数，避免 id < 0 时越界访问 led_map */
    return (unsigned)id < (unsigned)BSP_LED_NUM;
}

void BSP_LED_Init(void)
{
    GPIO_InitTypeDef gpio = {0};
    uint16_t         mask = 0;

    __HAL_RCC_GPIOH_CLK_ENABLE();

    for (uint32_t i = 0; i < (uint32_t)BSP_LED_NUM; i++) {
        HAL_GPIO_WritePin(led_map[i].port, led_map[i].pin, GPIO_PIN_SET);
        mask |= led_map[i].pin;
    }

    gpio.Pin   = mask;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOH, &gpio);
}

void BSP_LED_On(BSP_LED_ID id)
{
    if (!led_id_valid(id)) return;
    HAL_GPIO_WritePin(led_map[id].port, led_map[id].pin, GPIO_PIN_RESET);
}

void BSP_LED_Off(BSP_LED_ID id)
{
    if (!led_id_valid(id)) return;
    HAL_GPIO_WritePin(led_map[id].port, led_map[id].pin, GPIO_PIN_SET);
}

void BSP_LED_Toggle(BSP_LED_ID id)
{
    if (!led_id_valid(id)) return;
    HAL_GPIO_TogglePin(led_map[id].port, led_map[id].pin);
}

void BSP_LED_AllOff(void)
{
    for (uint32_t i = 0; i < (uint32_t)BSP_LED_NUM; i++) {
        HAL_GPIO_WritePin(led_map[i].port, led_map[i].pin, GPIO_PIN_SET);
    }
}
