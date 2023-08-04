#include <Wire.h>

//Register specification for sensor LIS2MDL

//Offset configuration registers
#define LIS2MDL_OFFSET_X_REG_L  0x45
#define LIS2MDL_OFFSET_X_REG_H  0x46
#define LIS2MDL_OFFSET_Y_REG_L  0x47
#define LIS2MDL_OFFSET_Y_REG_H  0x48
#define LIS2MDL_OFFSET_Z_REG_L  0x49
#define LIS2MDL_OFFSET_Z_REG_H  0x4A

//Configuration registers
#define LIS2MDL_WHO_AM_I    0x4F     
#define LIS2MDL_CFG_REG_A   0x60
#define LIS2MDL_CFG_REG_B   0x61
#define LIS2MDL_CFG_REG_C   0x62
#define LIS2MDL_STATUS_REG  0x67

//Magnetometer registers
#define LIS2MDL_OUTX_L_REG  0x68
#define LIS2MDL_OUTX_H_REG  0x69
#define LIS2MDL_OUTY_L_REG  0x6A
#define LIS2MDL_OUTY_H_REG  0x6B
#define LIS2MDL_OUTZ_L_REG  0x6C
#define LIS2MDL_OUTZ_H_REG  0x6D

//Output data rate
#define LIS2MDL_ODR_10  0X00
#define LIS2MDL_ODR_20  0X01
#define LIS2MDL_ODR_50  0X02
#define LIS2MDL_ODR_100 0X03


#define LIS2MDL_ADDRESS 0x1E

struct LIS2MDL_DATA
{
    int Mag_X;
    int Mag_Y;
    int Mag_Z;
    double Mag_X_R;
    double Mag_Y_R;
    double Mag_Z_R;
};

void LIS2MDL_SETUP()
{
    Wire.beginTransmission(LIS2MDL_ADDRESS);
    Wire.write(LIS2MDL_CFG_REG_A);
    Wire.write(0x8C);
    Wire.endTransmission();
}

void LIS2MDL_RESET()
{
    Wire.beginTransmission(LIS2MDL_ADDRESS);
    Wire.write(LIS2MDL_CFG_REG_A);
    Wire.write(0xAC);
    Wire.endTransmission();
    delay(1);
}

void LIS2MDL_MAG_RAW(LIS2MDL_DATA* LIS2MDL_DATA_X)
{
    Wire.beginTransmission(LIS2MDL_ADDRESS);
    Wire.write(LIS2MDL_OUTX_L_REG);
    Wire.endTransmission();
    Wire.requestFrom(LIS2MDL_ADDRESS,6);
    LIS2MDL_DATA_X->Mag_X = (Wire.read());
    LIS2MDL_DATA_X->Mag_X = Wire.read()<<8 | LIS2MDL_DATA_X->Mag_X;
    LIS2MDL_DATA_X->Mag_Y = Wire.read();
    LIS2MDL_DATA_X->Mag_Y = Wire.read()<<8 | LIS2MDL_DATA_X->Mag_Y;
    LIS2MDL_DATA_X->Mag_Z = Wire.read();
    LIS2MDL_DATA_X->Mag_Z = Wire.read()<<8 | LIS2MDL_DATA_X->Mag_Z;
}

void LIS2MDL_MAG()
{

}
//Do the self test in the future 