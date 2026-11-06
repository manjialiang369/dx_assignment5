

#include "cmsis_os.h"
#include "ins_task.h"

static void ins_task_entry(void *argument)
{
    (void)argument;

    INS_Init();

    uint32_t tick = osKernelGetTickCount();
    for (;;) {
        INS_Task();
        tick += 1;
        osDelayUntil(tick);
    }
}

void ins_task_init(void)
{
    static const osThreadAttr_t attr = {
        .name       = "INS_Task",
        .stack_size = 1024 * 4,
        .priority   = (osPriority_t)osPriorityAboveNormal,
    };

    osThreadNew(ins_task_entry, NULL, &attr);
}
