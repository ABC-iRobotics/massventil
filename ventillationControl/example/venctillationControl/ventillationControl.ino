#include <sensirionFlow.h>


SFM3300 flowSensor;
void setup() {
  // put your setup code here, to run once:
  flowSensor.begin(0x40);     
  flowSensor.startMeasuring();

  Serial.begin(115200);
  Serial.println("Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  flowSensor.measureVolume();   // must call frequently, if it is possible in main loop, period time is measured in method. 
  Serial.print(flowSensor.readMeasuredFlow());
  Serial.print(",");
  Serial.print(flowSensor.readMeasuredVolume(),6);
  Serial.println();
}