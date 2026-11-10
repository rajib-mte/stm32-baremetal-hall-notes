
#ifndef MPU6050_H
#define MPU6050_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

/* MPU6050 I2C Address */
#define MPU6050_ADDR        (0x68 << 1)

/* MPU6050 Registers */
#define MPU6050_WHO_AM_I    0x75
#define MPU6050_PWR_MGMT_1  0x6B
#define MPU6050_SMPLRT_DIV  0x19
#define MPU6050_CONFIG      0x1A
#define MPU6050_GYRO_CONFIG 0x1B
#define MPU6050_ACCEL_CONFIG 0x1C
#define MPU6050_DATA_REG    0x3B

/* MPU6050 Data Structure */
typedef struct
{
    int16_t Accel_X_RAW;
    int16_t Accel_Y_RAW;
    int16_t Accel_Z_RAW;

    int16_t Gyro_X_RAW;
    int16_t Gyro_Y_RAW;
    int16_t Gyro_Z_RAW;

    int16_t Temp_RAW;

    float Ax;
    float Ay;
    float Az;

    float Gx;
    float Gy;
    float Gz;

    float Temperature;

} MPU6050_t;

/* Function Prototypes */

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c);

HAL_StatusTypeDef MPU6050_Read_All(
    I2C_HandleTypeDef *hi2c,
    MPU6050_t *Data
);

HAL_StatusTypeDef MPU6050_Read_WhoAmI(
    I2C_HandleTypeDef *hi2c,
    uint8_t *id
);

#endif
