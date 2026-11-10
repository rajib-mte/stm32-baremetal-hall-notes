
#include "MPU6050.h"

/* Write one byte to MPU6050 register */
static HAL_StatusTypeDef MPU6050_Write_Reg(
    I2C_HandleTypeDef *hi2c,
    uint8_t reg,
    uint8_t data)
{
    return HAL_I2C_Mem_Write(
        hi2c,
        MPU6050_ADDR,
        reg,
        I2C_MEMADD_SIZE_8BIT,
        &data,
        1,
        100
    );
}

/* Read multiple bytes from MPU6050 */
static HAL_StatusTypeDef MPU6050_Read_Reg(
    I2C_HandleTypeDef *hi2c,
    uint8_t reg,
    uint8_t *data,
    uint16_t len)
{
    return HAL_I2C_Mem_Read(
        hi2c,
        MPU6050_ADDR,
        reg,
        I2C_MEMADD_SIZE_8BIT,
        data,
        len,
        100
    );
}

/* Read WHO_AM_I register */
HAL_StatusTypeDef MPU6050_Read_WhoAmI(
    I2C_HandleTypeDef *hi2c,
    uint8_t *id)
{
    return MPU6050_Read_Reg(
        hi2c,
        MPU6050_WHO_AM_I,
        id,
        1
    );
}

/* Initialize MPU6050 */
HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t id;

    /* Check device identity */
    if (MPU6050_Read_WhoAmI(hi2c, &id) != HAL_OK)
        return HAL_ERROR;

    if (id != 0x68)
        return HAL_ERROR;

    /* Wake up MPU6050 */
    if (MPU6050_Write_Reg(
        hi2c, MPU6050_PWR_MGMT_1, 0x00) != HAL_OK)
        return HAL_ERROR;

    HAL_Delay(100);

    /* Sample rate: 1 kHz / (1 + 7) = 125 Hz */
    if (MPU6050_Write_Reg(
        hi2c, MPU6050_SMPLRT_DIV, 0x07) != HAL_OK)
        return HAL_ERROR;

    /* Digital Low Pass Filter */
    if (MPU6050_Write_Reg(
        hi2c, MPU6050_CONFIG, 0x03) != HAL_OK)
        return HAL_ERROR;

    /* Gyroscope: +/- 250 degrees/sec */
    if (MPU6050_Write_Reg(
        hi2c, MPU6050_GYRO_CONFIG, 0x00) != HAL_OK)
        return HAL_ERROR;

    /* Accelerometer: +/- 2g */
    if (MPU6050_Write_Reg(
        hi2c, MPU6050_ACCEL_CONFIG, 0x00) != HAL_OK)
        return HAL_ERROR;

    return HAL_OK;
}

/* Read accelerometer, gyroscope and temperature */
HAL_StatusTypeDef MPU6050_Read_All(
    I2C_HandleTypeDef *hi2c,
    MPU6050_t *Data)
{
    uint8_t buffer[14];

    if (MPU6050_Read_Reg(
        hi2c,
        MPU6050_DATA_REG,
        buffer,
        14) != HAL_OK)
    {
        return HAL_ERROR;
    }

    /* Raw Accelerometer Data */
    Data->Accel_X_RAW =
        (int16_t)(buffer[0] << 8 | buffer[1]);

    Data->Accel_Y_RAW =
        (int16_t)(buffer[2] << 8 | buffer[3]);

    Data->Accel_Z_RAW =
        (int16_t)(buffer[4] << 8 | buffer[5]);

    /* Raw Temperature Data */
    Data->Temp_RAW =
        (int16_t)(buffer[6] << 8 | buffer[7]);

    /* Raw Gyroscope Data */
    Data->Gyro_X_RAW =
        (int16_t)(buffer[8] << 8 | buffer[9]);

    Data->Gyro_Y_RAW =
        (int16_t)(buffer[10] << 8 | buffer[11]);

    Data->Gyro_Z_RAW =
        (int16_t)(buffer[12] << 8 | buffer[13]);

    /* Convert Accelerometer: +/- 2g */
    Data->Ax = Data->Accel_X_RAW / 16384.0f;
    Data->Ay = Data->Accel_Y_RAW / 16384.0f;
    Data->Az = Data->Accel_Z_RAW / 16384.0f;

    /* Convert Gyroscope: +/- 250 dps */
    Data->Gx = Data->Gyro_X_RAW / 131.0f;
    Data->Gy = Data->Gyro_Y_RAW / 131.0f;
    Data->Gz = Data->Gyro_Z_RAW / 131.0f;

    /* Convert Temperature: Celsius */
    Data->Temperature =
        (Data->Temp_RAW / 340.0f) + 36.53f;

    return HAL_OK;
}
