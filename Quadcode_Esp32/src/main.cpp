#include<Arduino.h>
#include<Sensors/Sensor_setup.h>
#include<Telemetry/calibration_serial.h>
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
