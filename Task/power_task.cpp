
#include "CAN_bsp.h"
#include "app_task.h"

#define POWER_CAN_ID   0x301

typedef struct {
    uint16_t voltage_mv;
    int16_t  current_ma;
} power_data_t;

static power_data_t power_data;

static void power_callback(can_device_receive *can_receive, uint8_t *data)
{
    (void)can_receive;

    power_data.voltage_mv = (uint16_t)((data[0] << 8) | data[1]);
    power_data.current_ma = (int16_t)((data[2] << 8) | data[3]);
}

static void power_task(void *argument)
{
    (void)argument;

    static can_device_receive power_rx(&hcan1, POWER_CAN_ID, power_callback);

    for (;;) {
        
        osDelay(10);
    }
}

extern "C" void power_task_init(void)
{
    static const osThreadAttr_t attr = {
        .name       = "Power_Task",
        .stack_size = 256 * 4,
        .priority   = (osPriority_t)osPriorityNormal,
    };

    osThreadNew(power_task, NULL, &attr);
}