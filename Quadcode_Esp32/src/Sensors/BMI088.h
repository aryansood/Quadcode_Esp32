#include<Wire.h>
#include <Arduino.h>
//Register specification for sensor BMI088 

//Accelerometer registers map

//Control registers
#define BMI088_ACC_SOFTRESET    0x7E 
#define BMI088_ACC_PWR_CTRL     0x7D
#define BMI088_ACC_PWR_CONF     0x7C
#define BMI088_ACC_SELF_TEST    0x6D
#define BMI088_ACC_RANGE        0x41
#define BMI088_ACC_CONF         0x40
#define BMI088_ACC_STATUS       0x03
#define BMI088_ACC_ERR_REG      0x02
#define BMI088_ACC_CHIP_ID      0x00

//Fifo configuration registers
#define BMI088_ACC_FIFO_CONFIG_1    0x49
#define BMI088_ACC_FIFO_CONFIG_0    0x48
#define BMI088_ACC_FIFO_WTM_1       0x47
#define BMI088_ACC_FIFO_WTM_0       0x46
#define BMI088_ACC_FIFO_DOWNS       0x45

//Fifo read registers
#define BMI088_ACC_FIFO_DATA        0x26
#define BMI088_ACC_FIFO_LENGTH_1    0x25
#define BMI088_ACC_FIFO_LENGTH_0    0x24

//Accelerometer read registers
#define BMI088_ACC_X_LSB    0x12
#define BMI088_ACC_X_MSB    0x13
#define BMI088_ACC_Y_LSB    0x14
#define BMI088_ACC_Y_MSB    0x15
#define BMI088_ACC_Z_LSB    0x16
#define BMI088_ACC_Z_MSB    0x17

 
//Gyroscope registers map

//Control registers
#define BMI088_GYRO_LPM1        0x11        
#define BMI088_GYRO_BANDWIDTH   0x10
#define BMI088_GYRO_RANGE       0x0F
#define BMI088_GYRO_CHIP_ID     0x00
#define BMI088_GYRO_SOFTRESET   0x14

//Fifo configuration registers


//Gyroscope read registers
#define BMI088_GYRO_RATE_X_LSB   0x02
#define BMI088_GYRO_RATE_X_MSB   0x03
#define BMI088_GYRO_RATE_Y_LSB   0x04
#define BMI088_GYRO_RATE_Y_MSB   0x05
#define BMI088_GYRO_RATE_Z_LSB   0x06
#define BMI088_GYRO_RATE_Z_MSB   0x07


//Accelerometer Odr
#define BMI088_ACC_ODR_1600 0x0C
#define BMI088_ACC_ODR_800  0x0B
#define BMI088_ACC_ODR_400  0x0A
#define BMI088_ACC_ODR_200  0x09
#define BMI088_ACC_ODR_100  0x08

//Accelerometer Sampling
#define BMI088_ACC_BWP_OSR4 0x08
#define BMI088_ACC_BWP_OSR2 0x09
#define BMI088_ACC_BWP_OSR1 0x0A

//Accelerometer Sensitivity
#define BMI088_ACC_RANGE_3  0x00
#define BMI088_ACC_RANGE_6  0x01
#define BMI088_ACC_RANGE_12 0x02
#define BMI088_ACC_RANGE_24 0x03

//Gyroscope Sensitivity
#define BMI088_GYRO_RANGE_2000  0x00
#define BMI088_GYRO_RANGE_1000  0x01
#define BMI088_GYRO_RANGE_500   0x02
#define BMI088_GYRO_RANGE_250   0x03
#define BMI088_GYRO_RANGE_125   0x04

//Gyroscope Odr
#define BMI088_GYRO_ODR_2000_532    0x00
#define BMI088_GYRO_ODR_2000_230    0x01
#define BMI088_GYRO_ODR_1000        0x02
#define BMI088_GYRO_ODR_400         0x03
#define BMI088_GYRO_ODR_200_23      0x04
#define BMI088_GYRO_ODR_100_12      0x05
#define BMI088_GYRO_ODR_200_64      0x06
#define BMI088_GYRO_ODR_100_32      0x07

#define BMI088_ADDRESS_ACC  0x18
//#define BMI088_ADDRESS_ACC  0x19
#define BMI088_ADDRESS_GYRO 0x68
//#define BMI088_ADDRESS_GYRO 0x69

class BMI088_SENSOR
{
public:
    struct BMI088_DATA
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

    BMI088_DATA* BMI088_DATA_X;

    BMI088_SENSOR()
    {
        BMI088_DATA_X = new BMI088_DATA;
    }

    void BMI088_SETUP()
    {
        //Acc setup
        Wire.beginTransmission(BMI088_ADDRESS_ACC);
        Wire.write(BMI088_ACC_CONF);
        Wire.write(BMI088_ACC_BWP_OSR2<<4 | BMI088_ACC_ODR_1600);
        Wire.endTransmission();

        Wire.beginTransmission(BMI088_ADDRESS_ACC);
        Wire.write(BMI088_ACC_RANGE);
        Wire.write(BMI088_ACC_RANGE_3);
        Wire.endTransmission();

        Wire.beginTransmission(BMI088_ADDRESS_ACC);
        Wire.write(BMI088_ACC_PWR_CONF);
        Wire.write(0x00);
        Wire.endTransmission();

        Wire.beginTransmission(BMI088_ADDRESS_ACC);
        Wire.write(BMI088_ACC_PWR_CTRL);
        Wire.write(0x04);
        Wire.endTransmission();

        //Gyro Setup
        Wire.beginTransmission(BMI088_ADDRESS_GYRO);
        Wire.write(BMI088_GYRO_RANGE);
        Wire.write(BMI088_GYRO_RANGE_2000);
        Wire.endTransmission();

        Wire.beginTransmission(BMI088_ADDRESS_GYRO);
        Wire.write(BMI088_GYRO_BANDWIDTH);
        Wire.write(BMI088_GYRO_ODR_2000_230);
        Wire.endTransmission();

        Wire.beginTransmission(BMI088_ADDRESS_GYRO);
        Wire.write(BMI088_GYRO_LPM1);
        Wire.write(0x00);
        Wire.endTransmission();
    }

    void BMI088_RESET()
    {
        Wire.beginTransmission(BMI088_ADDRESS_ACC);
        Wire.write(BMI088_ACC_SOFTRESET);
        Wire.write(0xB6);
        Wire.endTransmission();
        delay(1000);
        Wire.beginTransmission(BMI088_ADDRESS_GYRO);
        Wire.write(BMI088_GYRO_SOFTRESET);
        Wire.write(0xB6);
        Wire.endTransmission();
    }

    void BMI088_ACC_RAW()
    {
        Wire.beginTransmission(BMI088_ADDRESS_ACC);
        Wire.write(BMI088_ACC_X_LSB);
        Wire.endTransmission();
        Wire.requestFrom(BMI088_ADDRESS_ACC,6);
        BMI088_DATA_X->Acc_X = (Wire.read());
        BMI088_DATA_X->Acc_X = Wire.read()<<8 | BMI088_DATA_X->Acc_X;
        BMI088_DATA_X->Acc_Y = Wire.read();
        BMI088_DATA_X->Acc_Y = Wire.read()<<8 | BMI088_DATA_X->Acc_Y;
        BMI088_DATA_X->Acc_Z = Wire.read();
        BMI088_DATA_X->Acc_Z = Wire.read()<<8 | BMI088_DATA_X->Acc_Z;
    }


    void BMI088_GYRO_RAW()
    {
        Wire.beginTransmission(BMI088_ADDRESS_GYRO);
        Wire.write(BMI088_GYRO_RATE_X_LSB);
        Wire.endTransmission();
        Wire.requestFrom(BMI088_ADDRESS_GYRO,6);
        BMI088_DATA_X->Gyro_X = (Wire.read());
        BMI088_DATA_X->Gyro_X = Wire.read()<<8 | BMI088_DATA_X->Gyro_X;
        BMI088_DATA_X->Gyro_Y = Wire.read();
        BMI088_DATA_X->Gyro_Y = Wire.read()<<8 | BMI088_DATA_X->Gyro_Y;
        BMI088_DATA_X->Gyro_Z = Wire.read();
        BMI088_DATA_X->Gyro_Z = Wire.read()<<8 | BMI088_DATA_X->Gyro_Z;
    }



    void BMI088_ACC_GYRO()
    {
        
        BMI088_DATA_X->Acc_X_R = float(BMI088_DATA_X->Acc_X)/float(10920);
        BMI088_DATA_X->Acc_Y_R = float(BMI088_DATA_X->Acc_Y)/float(10920);
        BMI088_DATA_X->Acc_Z_R = float(BMI088_DATA_X->Acc_Z)/float(10920);
        BMI088_DATA_X->Gyro_X_R = float(BMI088_DATA_X->Gyro_X)/float(16.384);
        BMI088_DATA_X->Gyro_Y_R = float(BMI088_DATA_X->Gyro_Y)/float(16.384);
        BMI088_DATA_X->Gyro_Z_R = float(BMI088_DATA_X->Gyro_Z)/float(16.384);
    }

    void Get_data()
    {
        BMI088_GYRO_RAW();
        BMI088_ACC_RAW();
        BMI088_ACC_GYRO();
    }; 

    void BMI088_TEST()
    {
        BMI088_GYRO_RAW();
        BMI088_ACC_RAW();
        BMI088_ACC_GYRO();
        Serial.print("Gyro_x: ");
        Serial.print(BMI088_DATA_X->Gyro_X_R);
        Serial.print("Gyro_y: ");
        Serial.print(BMI088_DATA_X->Gyro_Y_R);
        Serial.print("Gyro_z: ");
        Serial.print(BMI088_DATA_X->Gyro_Z_R);
        Serial.println();
    }
};