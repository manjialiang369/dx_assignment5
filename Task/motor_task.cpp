
#include "DJI_motor_driver.h"
#include "app_task.h"


#define MOTOR_ID          1
#define MOTOR_AMPLITUDE   1.0f
#define MOTOR_FREQ_HZ     0.2f


static void motor_task(void *argument)
{
    (void)argument;
    static DJI_motor motor(&hcan1, nullptr, MOTOR_ID, DJI_M3508);
    motor.posPid.pid_reset(0.02f, 0.1f, 0.3f, 0.0f, 0.0f);
    const float w = 6.2831853f * MOTOR_FREQ_HZ;
    uint32_t start = osKernelGetTickCount();

    for (;;) {
        float t      = (osKernelGetTickCount() - start) * 0.001f;
        float target = -MOTOR_AMPLITUDE * cosf(w * t);
        motor.motor_set_rounds(target);
        osDelay(2);
    }
}

extern "C" void motor_task_init(void)
{
    static const osThreadAttr_t attr = {
        .name       = "Motor_Task",
        .stack_size = 512 * 4,
        .priority   = (osPriority_t)osPriorityHigh,
    };

    osThreadNew(motor_task, NULL, &attr);
}