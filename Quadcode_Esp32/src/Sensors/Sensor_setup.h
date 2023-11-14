#pragma once
#include <Sensors/Sensor_para_def.h>

void Sensor_init()
{
     LSM6DSM_S.LSM6DSM_SETUP();
     BMI088_S.BMI088_SETUP();
     LIS2MDL_S.LIS2MDL_SETUP();
}