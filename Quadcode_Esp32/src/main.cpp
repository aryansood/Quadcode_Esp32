#include<Arduino.h>
#include<Sensors/Sensor_setup.h>
#include<Comm/calibration_serial.h>
#include<freertos/FreeRTOS.h>

int i = 0;
void setup() {
  Wire.begin();
  Sensor_init();
  Serial.begin(9600);
}

void loop() {
  Send_telem();
  delay(100);
}
