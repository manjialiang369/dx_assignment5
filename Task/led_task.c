
#include "cmsis_os.h"
#include "main.h"
#include "app_task.h"
#include "LED.h"

#define LED_INTERVAL_MS   200
#define LED_TASK_STACK    128

static const BSP_LED_ID led_flow[BSP_LED_NUM] = {
    BSP_LED_R,
    BSP_LED_G,
    BSP_LED_B,
};

static void led_task(void *argument)
{
    (void)argument;

    uint32_t idx = 0;

    for (;;)
    {
        BSP_LED_AllOff();
        BSP_LED_On(led_flow[idx]);
        osDelay(LED_INTERVAL_MS);

        idx++;
        if (idx >= BSP_LED_NUM)
        {
            idx = 0;
        }
    }
}

void led_task_init(void)
{
    static const osThreadAttr_t attr = {
        .name       = "led_task",
        .stack_size = LED_TASK_STACK * 4,
        .priority   = (osPriority_t)osPriorityNormal,
    };

    BSP_LED_Init();
    BSP_LED_AllOff();

    osThreadNew(led_task, NULL, &attr);
}
