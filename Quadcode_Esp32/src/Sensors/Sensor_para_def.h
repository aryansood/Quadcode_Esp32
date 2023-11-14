/*
Definition of the number of sensors used, and their typed, abstarcted from the real sensor hardware.
Link between the definitions and the physical sensors done in /Sensors/Sensor_data.h
*/
#pragma once
#include<Sensors/Sensors_entrypoint.h>
#include<Sensors/BMI088.h>
#include<Sensors/LIS2MDL.h>
#include<Sensors/LSM6DSM.h>
#include<Sensors/BMP388.h>

#define Num_acc 2
#define Num_gyro 2
#define Num_compass 1
#define Num_alt 1

class LSM6DSM_SENSOR LSM6DSM_S;

class BMI088_SENSOR BMI088_S;

class BMP388_SENSOR BMP388_S;

class LIS2MDL_SENSOR LIS2MDL_S;

struct Acc Acc_state[Num_acc];
struct Gyro Gyro_state[Num_gyro];
struct Altitude Alt_state[Num_alt];
struct Mag Mag_state[Num_compass];

