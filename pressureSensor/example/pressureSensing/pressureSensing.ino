#include <pressureSensor.h>

PressureSensor sensorA;
void setup() {
 
  sensorA.begin(A7);
  Serial.begin(115200);
  Serial.println("Started");

  sensorA.setoffsetV(2736.83);
  while(!sensorA.isCalibrated())   // calibration of sensor 
  {
    sensorA.calibration();
    Serial.print(sensorA.getPressure());
    Serial.println();
  }
   
}

void loop() {
  
   Serial.print(1);
    Serial.print(",");
   Serial.print(sensorA.getPressure());
   Serial.println();
  
}