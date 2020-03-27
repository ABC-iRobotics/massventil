#include <sensirionFlow.h>

 
#include <flowSensor.h>


FlowSensor flowSensor;
SFM3300 sensirionSensor;
void setup() {
  // put your setup code here, to run once:
  
  flowSensor.begin(A7);     
  delay(1000);
  Serial.begin(115200);
  flowSensor.pressureSensor->setoffsetV(2736.83);
  while(!flowSensor.pressureSensor->isCalibrated())   // calibration of sensor 
  {
    flowSensor.pressureSensor->calibrationRaw();
    Serial.print(flowSensor.pressureSensor->getPressureRaw(),4);
    
    Serial.println();
    delayMicroseconds(500);
  }
  flowSensor.setK(80,80);  
  sensirionSensor.begin(0x40);     
  sensirionSensor.startMeasuring();

  
  Serial.println("Started");

  
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.print(1);
    Serial.print(",");
    Serial.print(flowSensor.pressureSensor->getPressureRaw(),4);
    Serial.print(",");
    Serial.print(sensirionSensor.readMeasuredFlow());
    Serial.print(",");
   Serial.print(flowSensor.getFlow());
   Serial.println();
   delayMicroseconds(500);
}