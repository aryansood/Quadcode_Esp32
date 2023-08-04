#include <Arduino.h>
#include <Wire.h>
#include<Sensors/LSM6DSM.h>
#include<Sensors/LIS2MDL.h>
#include<Sensors/BMI088.h>
#include<Sensors/BMP388.h>

LSM6DSM_DATA LSM6DSM_DATA_R;


void setup() {
  Wire.begin();
  LSM6DSM_SETUP();
  Serial.begin(9600);
}

void loop() {
   LSM6DSM_GYRO_RAW(&LSM6DSM_DATA_R);
   LSM6DSM_ACC_RAW(&LSM6DSM_DATA_R);
   LSM6DSM_ACC_GYRO(&LSM6DSM_DATA_R);
   Serial.print("Acc_x");
   Serial.println();
   Serial.print(LSM6DSM_DATA_R.Acc_X_R);
   Serial.println();
   Serial.print("Acc_y");
   Serial.println();
   Serial.print(LSM6DSM_DATA_R.Acc_Y_R);
   Serial.println();
   Serial.print("Acc_z");
   Serial.println();
   Serial.print(LSM6DSM_DATA_R.Acc_Z_R);
   Serial.println();
   delay(500);
}
