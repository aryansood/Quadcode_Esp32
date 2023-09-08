#include <Wire.h>
#include <Arduino.h>
#define BMP388_CMD      0x7E
#define BMP388_CONFIG   0x1F
#define BMP388_ODR      0x1D
#define BMP388_OSR      0x1C
#define BMP388_PWR_CTRL 0x1B
#define BMP388_IF_CONF  0x1A 
#define BMP388_INT_CTRL 0x19      
#define BMP388_CHIP_ID  0x00
#define BMP388_STATUS   0x03
#define BMP388_ERR_REG  0x02

//Fifo configuration registers
#define BMP388_FIFO_CONFIG_1    0x17
#define BMP388_FIFO_CONFIG_2    0x18
#define BMP388_FIFO_WTM_1       0x16 
#define BMP388_FIFO_WTM_0       0x15

//Fifo read register
#define BMP388_FIFO_DATA        0x14 
#define BMP388_FIFO_LENGTH_1    0x13
#define BMP388_FIFO_LENGTH_0    0x12

//Pressure registers
#define BMP388_DATA_0   0x04 //0_7
#define BMP388_DATA_1   0x05 //8_15
#define BMP388_DATA_2   0x06 //16_23

//Odr values
#define BMP388_ODR_200  0x00
#define BMP388_ODR_100  0x01
#define BMP388_ODR_50   0x02
#define BMP388_ODR_25   0x03

//Oversampling values
#define BMP388_OSR_1    0X00
#define BMP388_OSR_2    0X01
#define BMP388_OSR_4    0X02
#define BMP388_OSR_8    0X03
#define BMP388_OSR_16   0X04
#define BMP388_OSR_32   0X05

//Address for calibration parameters
#define BMP388_CALI_START 0x31

#define BMP388_ADDRESS 0x76
//#define BMP388_ADDRESS 0x77

struct CALIBRATION_PARAMETERS
{
    uint16_t PAR_T1_R;
    uint16_t PAR_T2_R;
    int8_t PAR_T3_R;
    int16_t PAR_P1_R;
    int16_t PAR_P2_R;
    int8_t PAR_P3_R;
    int8_t PAR_P4_R;
    uint16_t PAR_P5_R;
    uint16_t PAR_P6_R;
    int8_t PAR_P7_R;
    int8_t PAR_P8_R;
    int16_t PAR_P9_R;
    int8_t PAR_P10_R;
    int8_t PAR_P11_R;
    
    float CALI_PARA_T[3];
    float CALI_PARA_P[11];
};

struct BMP388_DATA
{
    int Pressure;
    double Pressure_real;
};

struct CALIBRATION_PARAMETERS CALI_PARA;

void BMP388_SETUP()
{
    Wire.beginTransmission(BMP388_ADDRESS);
    Wire.write(BMP388_ODR);
    Wire.write(BMP388_ODR_200);
    Wire.endTransmission();

    Wire.beginTransmission(BMP388_ADDRESS);
    Wire.write(BMP388_OSR);
    Wire.write(BMP388_OSR_16);
    Wire.endTransmission();
}

void BMP388_RESET()
{
    Wire.beginTransmission(BMP388_ADDRESS);
    Wire.write(BMP388_CMD);
    Wire.write(0xB6);
    Wire.endTransmission();
    delay(1);
}

void BMP388_PRESS_RAW(BMP388_DATA* BMP388_DATA_X)
{
    Wire.beginTransmission(BMP388_ADDRESS);
    Wire.write(BMP388_DATA_0);
    Wire.endTransmission();
    Wire.requestFrom(BMP388_ADDRESS,3);
    BMP388_DATA_X->Pressure = Wire.read();
    BMP388_DATA_X->Pressure = (Wire.read()<<7) | BMP388_DATA_X->Pressure;
    BMP388_DATA_X->Pressure = (Wire.read()<<15)| BMP388_DATA_X->Pressure;
}

void BMP388_CALIBRATION_PARAMETERS(CALIBRATION_PARAMETERS* BMP388_CALI_DATA)
{
    Wire.beginTransmission(BMP388_ADDRESS);
    Wire.write(BMP388_CALI_START);
    Wire.endTransmission();
    Wire.requestFrom(BMP388_ADDRESS,21);
    //TEMPERATURE CALI PARAMETERS
    BMP388_CALI_DATA->PAR_T1_R = Wire.read();
    BMP388_CALI_DATA->PAR_T1_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_T1_R;
    BMP388_CALI_DATA->PAR_T2_R = Wire.read();
    BMP388_CALI_DATA->PAR_T2_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_T2_R;
    BMP388_CALI_DATA->PAR_T3_R = Wire.read();
    BMP388_CALI_DATA->PAR_T3_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_T3_R;
    //PRESSURE CALI PARAMETERS
    BMP388_CALI_DATA->PAR_P1_R = Wire.read();
    BMP388_CALI_DATA->PAR_P1_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P1_R;
    BMP388_CALI_DATA->PAR_P2_R = Wire.read();
    BMP388_CALI_DATA->PAR_P2_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P2_R;
    BMP388_CALI_DATA->PAR_P3_R = Wire.read();
    BMP388_CALI_DATA->PAR_P3_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P3_R;
    BMP388_CALI_DATA->PAR_P4_R = Wire.read();
    BMP388_CALI_DATA->PAR_P4_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P4_R;
    BMP388_CALI_DATA->PAR_P5_R = Wire.read();
    BMP388_CALI_DATA->PAR_P5_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P5_R;
    BMP388_CALI_DATA->PAR_P6_R = Wire.read();
    BMP388_CALI_DATA->PAR_P6_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P6_R;
    BMP388_CALI_DATA->PAR_P7_R = Wire.read();
    BMP388_CALI_DATA->PAR_P7_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P7_R;
    BMP388_CALI_DATA->PAR_P8_R = Wire.read();
    BMP388_CALI_DATA->PAR_P8_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P8_R;
    BMP388_CALI_DATA->PAR_P9_R = Wire.read();
    BMP388_CALI_DATA->PAR_P9_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P9_R;
    BMP388_CALI_DATA->PAR_P10_R = Wire.read();
    BMP388_CALI_DATA->PAR_P10_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P10_R;
    BMP388_CALI_DATA->PAR_P10_R = Wire.read();
    BMP388_CALI_DATA->PAR_P10_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P10_R;
    BMP388_CALI_DATA->PAR_P11_R = Wire.read();
    BMP388_CALI_DATA->PAR_P11_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P11_R;

}

void BMP388_TEMP_CALIBRATION()
{
    
}

void BMP388_PRESS_CALIBRATION()
{

}

//Do the self test in the future 

void BMP388_PRESS_TEST(BMP388_DATA* BMP388_DATA_X)
{
    BMP388_PRESS_RAW(BMP388_DATA_X);
    Serial.print("Pressure_Raw: ");
    Serial.print(BMP388_DATA_X->Pressure);
    Serial.println();
}