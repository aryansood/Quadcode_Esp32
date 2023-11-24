/*
Send data for calibration, basic version
*/
#pragma once
#include<Sensors/Sensor_data.h>
#include<Arduino.h>

void Send_telem()
{
    Get_Data_Sen();
    Serial.printf("Acc_0: ");
    Serial.print(Acc_state[0].Acc_x);
    Serial.print(Acc_state[0].Acc_y);
    Serial.print(Acc_state[0].Acc_z);
    Serial.println();
    Serial.printf("Gyro_0: ");
    Serial.print(Gyro_state[0].Gyro_x);
    Serial.print(Gyro_state[0].Gyro_y);
    Serial.print(Gyro_state[0].Gyro_z);
    Serial.println();
    Serial.printf("Acc_1: ");
    Serial.print(Acc_state[1].Acc_x);
    Serial.print(Acc_state[1].Acc_y);
    Serial.print(Acc_state[1].Acc_z);
    Serial.println();
    Serial.printf("Gyro_1: ");
    Serial.print(Gyro_state[1].Gyro_x);
    Serial.print(Gyro_state[1].Gyro_y);
    Serial.print(Gyro_state[1].Gyro_z);
    Serial.println();
    Serial.printf("Mag_1: ");
    Serial.print(Mag_state[0].Mag_x);
    Serial.print(Mag_state[0].Mag_x);
    Serial.print(Mag_state[0].Mag_x);
    Serial.println();
}
