#include "Arduino.h"
#include "Motors_Control/Dshot.h"
#include "Sensors/LSM6DSM.h"
#include "Sensors/BMI088.h"
#include "Sensors/BMP388.h"
#include "Sensors/LIS2MDL.h"

LSM6DSM_DATA LSM6DSM_DATA_real;

BMI088_DATA BMI088_DATA_real;

BMP388_DATA BMP388_DATA_real;

LIS2MDL_DATA LIS2MDL_DATA_real;

void setup()
{
    Wire.begin();
    //LSM6DSM_SETUP();
    //BMI088_SETUP();
    BMP388_SETUP();
    //LIS2MDL_SETUP();
    Serial.begin(9600);
}

void loop()
{
    //LSM6DSM_TEST(&LSM6DSM_DATA_real);
    //BMI088_TEST(&BMI088_DATA_real);
    BMP388_PRESS_TEST(&BMP388_DATA_real);
    //LIS2MDL_MAG_TEST(&LIS2MDL_DATA_real);
    delay(1000);
}