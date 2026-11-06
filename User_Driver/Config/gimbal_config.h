
#ifndef GIMBAL_CONFIG_H
#define GIMBAL_CONFIG_H

/* =====  INS / EKF 参数 ===== */
#define CFG_CPU_FREQ_MHZ         168U      /* CPU 主频，仅用于 DWT_Init 的计时基准 */
#define CFG_INS_ACCEL_LPF        0.0085f   /* 运动加速度一阶低通时间常数[s]（α=dt/(τ+dt)，τ≈8.5ms ⇒ 约 19Hz） */
#define CFG_EKF_Q1               10.0f     /* 四元数过程噪声：越大越信陀螺积分（机动快、噪声也大） */
#define CFG_EKF_Q2               0.001f    /* 陀螺零偏过程噪声：越小零偏估计越稳 */
#define CFG_EKF_R                10000000.0f /* 加速度计量测噪声 R：很大 ⇒ 基本不信加速度计（只防长期漂移） */
#define CFG_EKF_LAMBDA           1.0f      /* 渐消因子：1.0 = 不渐消（例程用 0.9996 增强抗发散） */
#define CFG_EKF_ACC_LPF          0.0f      /* EKF 内部加速度低通：0 = 不滤波（噪声已由大 R 压住） */
#define CFG_EKF_CHI2_TOL_DEG     20.0f     /* 卡方检验容许的重力向量夹角[°]：阈值由它和 R 反算，超限即判发散/拒绝该次量测 */


/* =====  IMU 安装与标度修正（只作用于陀螺：加速度计不乘 scale）===== */
#define CFG_IMU_SCALE_X          1.0f    /* 陀螺 X 轴标度因数 */
#define CFG_IMU_SCALE_Y          1.0f    /* 陀螺 Y 轴标度因数 */
#define CFG_IMU_SCALE_Z          1.0f    /* 陀螺 Z 轴标度因数 */
#define CFG_IMU_YAW_OFFSET_DEG   0.0f
#define CFG_IMU_PITCH_OFFSET_DEG 0.0f
#define CFG_IMU_ROLL_OFFSET_DEG  0.0f


#endif /* GIMBAL_CONFIG_H */
