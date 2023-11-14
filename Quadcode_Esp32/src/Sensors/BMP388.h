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
#define BMP388_PRESSURE_DATA_0   0x04 //0_7
#define BMP388_PRESSURE_DATA_1   0x05 //8_15
#define BMP388_PRESSURE_DATA_2   0x06 //16_23

//Temperature registers
#define BMP388_TEMPERATURE_DATA_0   0x07 //0_7
#define BMP388_TEMPERATURE_DATA_1   0x08 //8_15
#define BMP388_TEMPERATURE_DATA_2   0x09 //16_23

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

//Definition of powers of 2
#define POW_5 1<<5
#define POW_6 1<<6
#define POW_7 1<<7
#define POW_8 1<<8
#define POW_14 1<<14
#define POW_15 1<<15
#define POW_16 1<<16
#define POW_18 1<<18
#define POW_20 1<<20
#define POW_29 1<<29
#define POW_30 1<<30

#define STANDARD_SEA_LEVEL_PRESSURE_PA 101325


class BMP388_SENSOR{
public:
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

        double CALI_PARA_T[4];
        double CALI_PARA_P[12];
    };

    struct BMP388_DATA
    {
        u_int32_t Pressure;
        u_int32_t Temperature;
        double Pressure_real;
        double Temperature_real;
    };

    struct CALIBRATION_PARAMETERS* BMP388_CALI_DATA;
    struct BMP388_DATA* BMP388_DATA_X;
    int merda = 10;
    double se_press;

    BMP388_SENSOR() {
        BMP388_CALI_DATA = new CALIBRATION_PARAMETERS;
        BMP388_DATA_X = new BMP388_DATA;
    }

    void BMP388_SETUP()
    {
        Wire.beginTransmission(BMP388_ADDRESS);
        Wire.write(BMP388_PWR_CTRL);
        Wire.write(0);
        Wire.endTransmission();
        delay(1000);

        Wire.beginTransmission(BMP388_ADDRESS);
        Wire.write(BMP388_PWR_CTRL);
        Wire.write((3<<3) | 3);
        Wire.endTransmission();
        
        Wire.beginTransmission(BMP388_ADDRESS);
        Wire.write(BMP388_OSR);
        Wire.write(BMP388_OSR_16);
        Wire.endTransmission();

        Wire.beginTransmission(BMP388_ADDRESS);
        Wire.write(BMP388_ODR);
        Wire.write(BMP388_ODR_200);
        Wire.endTransmission();
    }

    void BMP388_SETUP_TEMP()
    {
        Wire.beginTransmission(BMP388_ADDRESS);
        Wire.write(BMP388_PWR_CTRL);
        Wire.write((3<<3) | 3);
        Wire.endTransmission();
    }

    void Bmp388_RESET()
    {
        Wire.beginTransmission(BMP388_ADDRESS);
        Wire.write(BMP388_CMD);
        Wire.write(0xB6);
        Wire.endTransmission();
        delay(1);
    }

    void BMP388_PRESS_RAW()
    {
        BMP388_SETUP_TEMP();
        Wire.beginTransmission(BMP388_ADDRESS);
        Wire.write(BMP388_PRESSURE_DATA_0);
        Wire.endTransmission();
        Wire.requestFrom(BMP388_ADDRESS,3);
        BMP388_DATA_X->Pressure = Wire.read();
        BMP388_DATA_X->Pressure = (Wire.read()<<8) | BMP388_DATA_X->Pressure;
        BMP388_DATA_X->Pressure = (Wire.read()<<16)| BMP388_DATA_X->Pressure;

    }

    void BMP388_TEMP_RAW()
    {
        Wire.beginTransmission(BMP388_ADDRESS);
        Wire.write(BMP388_TEMPERATURE_DATA_0);
        Wire.endTransmission();
        Wire.requestFrom(BMP388_ADDRESS,3);
        BMP388_DATA_X->Temperature = Wire.read();
        BMP388_DATA_X->Temperature = (Wire.read()<<8) | BMP388_DATA_X->Temperature;
        BMP388_DATA_X->Temperature = (Wire.read()<<16)| BMP388_DATA_X->Temperature;
    }

   
    void BMP388_CALIBRATION_PARAMETERS()
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
        //PRESSURE CALI PARAMETERS
        BMP388_CALI_DATA->PAR_P1_R = Wire.read();
        BMP388_CALI_DATA->PAR_P1_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P1_R;

        BMP388_CALI_DATA->PAR_P2_R = Wire.read();
        BMP388_CALI_DATA->PAR_P2_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P2_R;

        BMP388_CALI_DATA->PAR_P3_R = Wire.read();

        BMP388_CALI_DATA->PAR_P4_R = Wire.read();

        BMP388_CALI_DATA->PAR_P5_R = Wire.read();
        BMP388_CALI_DATA->PAR_P5_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P5_R;

        BMP388_CALI_DATA->PAR_P6_R = Wire.read();
        BMP388_CALI_DATA->PAR_P6_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P6_R;

        BMP388_CALI_DATA->PAR_P7_R = Wire.read();
        
        BMP388_CALI_DATA->PAR_P8_R = Wire.read();
        
        BMP388_CALI_DATA->PAR_P9_R = Wire.read();
        BMP388_CALI_DATA->PAR_P9_R = (Wire.read()<<8) | BMP388_CALI_DATA->PAR_P9_R;

        BMP388_CALI_DATA->PAR_P10_R = Wire.read();
        
        BMP388_CALI_DATA->PAR_P11_R = Wire.read();
        
        //Double convertion pressure
        BMP388_CALI_DATA->CALI_PARA_T[1] = double(BMP388_CALI_DATA->PAR_T1_R)*double(POW_8);
        BMP388_CALI_DATA->CALI_PARA_T[2] = double(BMP388_CALI_DATA->PAR_T2_R)/double(POW_30);
        BMP388_CALI_DATA->CALI_PARA_T[3] = double(BMP388_CALI_DATA->PAR_T3_R)/double(POW_18);
        BMP388_CALI_DATA->CALI_PARA_T[3] = double(BMP388_CALI_DATA->CALI_PARA_T[3])/double(POW_30);

        //Double convertion temperature
        BMP388_CALI_DATA->CALI_PARA_P[1] = double(BMP388_CALI_DATA->PAR_P1_R-(16384))/double(POW_20);
        BMP388_CALI_DATA->CALI_PARA_P[2] = double(BMP388_CALI_DATA->PAR_P2_R-(16384))/double(POW_29);
        BMP388_CALI_DATA->CALI_PARA_P[3] = double(BMP388_CALI_DATA->PAR_P3_R)/double(POW_16);
        BMP388_CALI_DATA->CALI_PARA_P[3] = double(BMP388_CALI_DATA->CALI_PARA_P[3])/double(POW_16);

        BMP388_CALI_DATA->CALI_PARA_P[4] = double(BMP388_CALI_DATA->PAR_P4_R)/double(POW_7);
        BMP388_CALI_DATA->CALI_PARA_P[4] = double(BMP388_CALI_DATA->CALI_PARA_P[4])/double(POW_30);
        BMP388_CALI_DATA->CALI_PARA_P[5] = double(BMP388_CALI_DATA->PAR_P5_R)*double(8);
        BMP388_CALI_DATA->CALI_PARA_P[6] = double(BMP388_CALI_DATA->PAR_P6_R)/double(POW_6);

        BMP388_CALI_DATA->CALI_PARA_P[7] = double(BMP388_CALI_DATA->PAR_P7_R)/double(POW_8);
        BMP388_CALI_DATA->CALI_PARA_P[8] = double(BMP388_CALI_DATA->PAR_P8_R)/double(POW_15);
        BMP388_CALI_DATA->CALI_PARA_P[9] = double(BMP388_CALI_DATA->PAR_P9_R)/double(POW_16);
        BMP388_CALI_DATA->CALI_PARA_P[9] = double(BMP388_CALI_DATA->CALI_PARA_P[9])/double(POW_16);
        BMP388_CALI_DATA->CALI_PARA_P[9] = double(BMP388_CALI_DATA->CALI_PARA_P[9])/double(POW_16);

        BMP388_CALI_DATA->CALI_PARA_P[10] = double(BMP388_CALI_DATA->PAR_P10_R)/double(POW_16);
        BMP388_CALI_DATA->CALI_PARA_P[10] = double(BMP388_CALI_DATA->CALI_PARA_P[10])/double(POW_16);
        BMP388_CALI_DATA->CALI_PARA_P[10] = double(BMP388_CALI_DATA->CALI_PARA_P[10])/double(POW_16);
        BMP388_CALI_DATA->CALI_PARA_P[11] = double(BMP388_CALI_DATA->PAR_P11_R)/double(POW_30);
        BMP388_CALI_DATA->CALI_PARA_P[11] = double(BMP388_CALI_DATA->CALI_PARA_P[11])/double(POW_30);
        BMP388_CALI_DATA->CALI_PARA_P[11] = double(BMP388_CALI_DATA->CALI_PARA_P[11])/double(POW_5);
        
    }

    void BMP388_TEMP_CALIBRATION()
    {
        double partial_data1;
        double partial_data2;
        
        double data_converted;

        partial_data1 = double(BMP388_DATA_X->Temperature-BMP388_CALI_DATA->CALI_PARA_T[1]);
        partial_data2 = double(partial_data1*BMP388_CALI_DATA->CALI_PARA_T[2]);
        data_converted = partial_data2 + (partial_data1*partial_data1)*BMP388_CALI_DATA->CALI_PARA_T[3];
        BMP388_DATA_X->Temperature_real = data_converted;
    }

    void BMP388_PRESS_CALIBRATION()
    {
        double comp_press;
        double partial_data1;
        double partial_data2;
        double partial_data3;
        double partial_data4;
        double partial_out1;
        double partial_out2; 

        partial_data1 = BMP388_CALI_DATA->CALI_PARA_P[6]*BMP388_DATA_X->Temperature_real;
        partial_data2 = BMP388_CALI_DATA->CALI_PARA_P[7]*(BMP388_DATA_X->Temperature_real*BMP388_DATA_X->Temperature_real);
        partial_data3 = BMP388_CALI_DATA->CALI_PARA_P[8]*(BMP388_DATA_X->Temperature_real*BMP388_DATA_X->Temperature_real*BMP388_DATA_X->Temperature_real);
        partial_out1  = BMP388_CALI_DATA->CALI_PARA_P[5]+ partial_data1 + partial_data2 + partial_data3;

        partial_data1 = BMP388_CALI_DATA->CALI_PARA_P[2]*BMP388_DATA_X->Temperature_real;
        partial_data2 = BMP388_CALI_DATA->CALI_PARA_P[3]*(BMP388_DATA_X->Temperature_real*BMP388_DATA_X->Temperature_real);
        partial_data3 = BMP388_CALI_DATA->CALI_PARA_P[4]*(BMP388_DATA_X->Temperature_real*BMP388_DATA_X->Temperature_real*BMP388_DATA_X->Temperature_real);
        partial_out2  = double(BMP388_DATA_X->Pressure)*(BMP388_CALI_DATA->CALI_PARA_P[1]+ partial_data1 + partial_data2 + partial_data3);

        partial_data1 = double(BMP388_DATA_X->Pressure) * double(BMP388_DATA_X->Pressure);
        partial_data2 = BMP388_CALI_DATA->CALI_PARA_P[9] + BMP388_CALI_DATA->CALI_PARA_P[10] * BMP388_DATA_X->Temperature_real;
        partial_data3 = partial_data1 * partial_data2;
        partial_data4 = partial_data3 + (double(BMP388_DATA_X->Pressure) * double(BMP388_DATA_X->Pressure) * double(BMP388_DATA_X->Pressure)) * BMP388_CALI_DATA->CALI_PARA_P[11];
        comp_press = partial_out1 + partial_out2 + partial_data4;
        BMP388_DATA_X->Pressure_real = comp_press;

    }

    void BMP388_PRESS_ALT_CALIBRATION()
    {
        int num_measure = 1000;
        float pres_average = 0;
        for(int i = 0;i<num_measure;i++)
        {
            BMP388_PRESS_RAW();
        BMP388_TEMP_RAW();
        BMP388_TEMP_CALIBRATION();
        BMP388_PRESS_CALIBRATION();
            
            pres_average += BMP388_DATA_X->Pressure_real;
        }
        pres_average = pres_average/float(num_measure);
        se_press = (pres_average / pow(1.0 - (double(68.0) / 44307.7), 5.255302));
        //Alt_state[0].Pressure_offset = pres_average;
    }

    void BMP388_PRESS_ALT_CONVERT()
    {
        //Alt_state[0].Altitude = BMP388_DATA_X->Pressure_real-se_press+STANDARD_SEA_LEVEL_PRESSURE_PA;
        //Alt_state[0].Altitude = (1.0 - pow(Alt_state[0].Altitude / double(STANDARD_SEA_LEVEL_PRESSURE_PA), 0.190284)) * 44307.7;
    };

    void Get_data()
    {

    };

    void BMP388_ALT_TEST()
    {
        BMP388_PRESS_RAW();
        BMP388_TEMP_RAW();
        BMP388_TEMP_CALIBRATION();
        BMP388_PRESS_CALIBRATION();
        BMP388_PRESS_ALT_CONVERT();
        //Serial.print(Alt_state[0].Altitude);
        Serial.println();
    }
};