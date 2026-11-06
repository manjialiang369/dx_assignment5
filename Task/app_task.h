
#ifndef APP_TASK_H
#define APP_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

void led_task_init(void);
void ins_task_init(void);
void motor_task_init(void);
void power_task_init(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_H */
