/*
Get the data from the physical sensors and link to the abstract structure of the sensor functions
*/
#pragma once
#include <Sensors/Sensor_para_def.h>

void Get_Data_Sen()
{
    LSM6DSM_S.Get_data();
    BMI088_S.Get_data();
    LIS2MDL_S.Get_data();

    Acc_state[0].Acc_x = LSM6DSM_S.LSM6DSM_DATA_X->Acc_X_R;
    Acc_state[0].Acc_y = LSM6DSM_S.LSM6DSM_DATA_X->Acc_Y_R;
    Acc_state[0].Acc_z = LSM6DSM_S.LSM6DSM_DATA_X->Acc_Z_R;
    Gyro_state[0].Gyro_x = LSM6DSM_S.LSM6DSM_DATA_X->Gyro_X_R;
    Gyro_state[0].Gyro_x = LSM6DSM_S.LSM6DSM_DATA_X->Gyro_Y_R;
    Gyro_state[0].Gyro_x = LSM6DSM_S.LSM6DSM_DATA_X->Gyro_Z_R;

    Acc_state[1].Acc_x = BMI088_S.BMI088_DATA_X->Acc_X_R;
    Acc_state[1].Acc_y = BMI088_S.BMI088_DATA_X->Acc_Y_R;
    Acc_state[1].Acc_z = BMI088_S.BMI088_DATA_X->Acc_Z_R;
    Gyro_state[1].Gyro_x = BMI088_S.BMI088_DATA_X->Gyro_X_R;
    Gyro_state[1].Gyro_x = BMI088_S.BMI088_DATA_X->Gyro_Y_R;
    Gyro_state[1].Gyro_x = BMI088_S.BMI088_DATA_X->Gyro_Z_R;

    Mag_state[0].Mag_x = LIS2MDL_S.LIS2MDL_DATA_X->Mag_X_R;
    Mag_state[0].Mag_y = LIS2MDL_S.LIS2MDL_DATA_X->Mag_Y_R;
    Mag_state[0].Mag_z = LIS2MDL_S.LIS2MDL_DATA_X->Mag_Z_R;
}