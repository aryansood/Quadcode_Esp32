#include <Wire.h>
#include <Arduino.h>

#define LSM6DSM_FIFO_CTRL1  0x06
#define LSM6DSM_FIFO_CTRL2  0x07
#define LSM6DSM_FIFO_CTRL3  0x08
#define LSM6DSM_FIFO_CTRL4  0x09
#define LSM6DSM_FIFO_CTRL5  0x0A 
#define LSM6DSM_WHO_AM_I    0x0F

//Control registers of acc and gyro
#define LSM6DSM_CTRL1_XL    0x10
#define LSM6DSM_CTRL2_G     0x11
#define LSM6DSM_CTRL3_C     0x12
#define LSM6DSM_CTRL4_C     0x13
#define LSM6DSM_CTRL5_C     0x14
#define LSM6DSM_CTRL6_C     0x15
#define LSM6DSM_CTRL7_G     0x16
#define LSM6DSM_CTRL8_XL    0x17
#define LSM6DSM_CTRL9_XL    0x18
#define LSM6DSM_CTRL10_C    0x19

//Gyroscope registers
#define LSM6DSM_OUTX_L_G    0x22
#define LSM6DSM_OUTX_H_G    0x23
#define LSM6DSM_OUTY_L_G    0x24
#define LSM6DSM_OUTY_H_G    0x25
#define LSM6DSM_OUTZ_L_G    0x26
#define LSM6DSM_OUTZ_H_G    0x27

//Accelerometer registers
#define LSM6DSM_OUTX_L_XL   0x28
#define LSM6DSM_OUTX_H_XL   0x29
#define LSM6DSM_OUTY_L_XL   0x2A
#define LSM6DSM_OUTY_L_XL   0x2B
#define LSM6DSM_OUTZ_L_XL   0x2C
#define LSM6DSM_OUTZ_H_XL   0x2D

//Fifo status registers
#define LSM6DSM_FIFO_STATUS1    0x3A
#define LSM6DSM_FIFO_STATUS2    0x3B
#define LSM6DSM_FIFO_STATUS3    0x3C
#define LSM6DSM_FIFO_STATUS4    0x3D

//Fifo data output registers
#define LSM6DSM_FIFO_DATA_OUT_L 0x3E
#define LSM6DSM_FIFO_DATA_OUT_H 0x3F
#define LIS2MDL
#define LIS2MDL
#define LIS2MDL

//Accelerometer offset correction registers
#define LSM6DSM_X_OFS_USR   0x73
#define LSM6DSM_Y_OFS_USR   0x74
#define LSM6DSM_Y_OFS_USR   0x75

//Accelerometer odr rate selection
#define ACC_ODR_12_5    0X01      
#define ACC_ODR_26      0x02
#define ACC_ODR_52      0x03
#define ACC_ODR_104     0x04
#define ACC_ODR_208     0x05
#define ACC_ODR_416     0x06
#define ACC_ODR_833     0x07
#define ACC_ODR_1660    0x08
#define ACC_ODR_3330    0x09
#define ACC_ODR_6660    0x0A

//Accelerometer Sensitivity
#define ACC_SEN_2   0x00  
#define ACC_SEN_16  0x01
#define ACC_SEN_4   0x02
#define ACC_SEN_8   0x03

//Angular odr rate selection
#define GYRO_ODR_12_5    0X01      
#define GYRO_ODR_26      0x02
#define GYRO_ODR_52      0x03
#define GYRO_ODR_104     0x04
#define GYRO_ODR_208     0x05
#define GYRO_ODR_416     0x06
#define GYRO_ODR_833     0x07
#define GYRO_ODR_1660    0x08
#define GYRO_ODR_3330    0x09
#define GYRO_ODR_6660    0x0A

//Gyroscope sensitivity
#define GYRO_SEN_250     0x00  
#define GYRO_SEN_500     0x01
#define GYRO_SEN_1000    0x02
#define GYRO_SEN_2000    0x03

//Address selection
 #define LSM6DSM_ADDRESS 0x6A
//#define LSM6DSM_ADDRESS 0x6B

class LSM6DSM_SENSOR {
public:
    struct LSM6DSM_DATA
    {
        int16_t Acc_X;
        int16_t Acc_Y;
        int16_t Acc_Z;
        int16_t Gyro_X;
        int16_t Gyro_Y;
        int16_t Gyro_Z;
        double Acc_X_R;
        double Acc_Y_R;
        double Acc_Z_R;
        double Gyro_X_R;
        double Gyro_Y_R;
        double Gyro_Z_R;
    };

    LSM6DSM_DATA* LSM6DSM_DATA_X;

    LSM6DSM_SENSOR() {
        LSM6DSM_DATA_X = new LSM6DSM_DATA;
    }

    void LSM6DSM_SETUP()
    {
        Wire.beginTransmission(LSM6DSM_ADDRESS);
        Wire.write(LSM6DSM_CTRL1_XL);
        Wire.write(ACC_ODR_6660<<4 | ACC_SEN_2<<2);
        Wire.endTransmission();

        Wire.beginTransmission(LSM6DSM_ADDRESS);
        Wire.write(LSM6DSM_CTRL2_G);
        Wire.write(GYRO_ODR_6660<<4 | GYRO_SEN_500<<2);
        Wire.endTransmission();
    }

    void LSM6DSM_RESET()
    {
        Wire.beginTransmission(LSM6DSM_ADDRESS);
        Wire.write(LSM6DSM_CTRL3_C);
        Wire.write(0x01);
        Wire.endTransmission();
        delay(1000);
        Wire.beginTransmission(LSM6DSM_ADDRESS);
        Wire.write(LSM6DSM_CTRL3_C);
        Wire.write(0x01<<7);
        Wire.endTransmission();
        delay(1000);
    }

    void LSM6DSM_GYRO_RAW()
    {
        Wire.beginTransmission(LSM6DSM_ADDRESS);
        Wire.write(LSM6DSM_OUTX_L_G);
        Wire.endTransmission();
        Wire.requestFrom(LSM6DSM_ADDRESS,6);
        LSM6DSM_DATA_X->Gyro_X = (Wire.read())+(Wire.read()<<8);
        LSM6DSM_DATA_X->Gyro_X = Wire.read()<<8 | LSM6DSM_DATA_X->Gyro_X;
        LSM6DSM_DATA_X->Gyro_Y = Wire.read();
        LSM6DSM_DATA_X->Gyro_Y = Wire.read()<<8 | LSM6DSM_DATA_X->Gyro_Y;
        LSM6DSM_DATA_X->Gyro_Z = Wire.read();
        LSM6DSM_DATA_X->Gyro_Z = Wire.read()<<8 | LSM6DSM_DATA_X->Gyro_Z;
    }

    void LSM6DSM_ACC_RAW()
    {
        Wire.beginTransmission(LSM6DSM_ADDRESS);
        Wire.write(LSM6DSM_OUTX_L_XL);
        Wire.endTransmission();
        Wire.requestFrom(LSM6DSM_ADDRESS,6);
        LSM6DSM_DATA_X->Acc_X = (Wire.read());
        LSM6DSM_DATA_X->Acc_X = Wire.read()<<8 | LSM6DSM_DATA_X->Acc_X;
        LSM6DSM_DATA_X->Acc_Y = Wire.read();
        LSM6DSM_DATA_X->Acc_Y = Wire.read()<<8 | LSM6DSM_DATA_X->Acc_Y;
        LSM6DSM_DATA_X->Acc_Z = Wire.read();
        LSM6DSM_DATA_X->Acc_Z = Wire.read()<<8 | LSM6DSM_DATA_X->Acc_Z;
    }

    void LSM6DSM_ACC_GYRO()
    {
        
        LSM6DSM_DATA_X->Acc_X_R = float(LSM6DSM_DATA_X->Acc_X)*2.f/32768.f;
        LSM6DSM_DATA_X->Acc_Y_R = float(LSM6DSM_DATA_X->Acc_Y)*2.f/32768.f;
        LSM6DSM_DATA_X->Acc_Z_R = float(LSM6DSM_DATA_X->Acc_Z)*2.f/32768.f;
        LSM6DSM_DATA_X->Gyro_X_R = float(LSM6DSM_DATA_X->Gyro_X)*500.f/32768.f;
        LSM6DSM_DATA_X->Gyro_Y_R = float(LSM6DSM_DATA_X->Gyro_Y)*500.f/32768.f;
        LSM6DSM_DATA_X->Gyro_Z_R = float(LSM6DSM_DATA_X->Gyro_Z)*500.f/32768.f;
    }
    //Do the self test in the future 

    void LSM6DSM_TEST()
    {
        LSM6DSM_GYRO_RAW();
        LSM6DSM_ACC_RAW();
        LSM6DSM_ACC_GYRO();
        Serial.print("Acc_x: ");
        Serial.print(LSM6DSM_DATA_X->Acc_X_R);
        Serial.print("Acc_y: ");
        Serial.print(LSM6DSM_DATA_X->Acc_Y_R);
        Serial.print("Acc_z: ");
        Serial.print(LSM6DSM_DATA_X->Acc_Z_R);
        Serial.println();
    }
};