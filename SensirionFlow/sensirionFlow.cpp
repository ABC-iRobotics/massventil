/***
 * sensirion Flow sensor FSM3300 library - Implementation
 *
 * Copyright (C) 2020  Bence Takács
 */

#include "sensirionFlow.h"
#include <Wire.h>





// CONSTRUCTOR AND DESTRUCTOR * * * * * * * * * * * * * * *

SFM3300::SFM3300()
{
    f=new Filter(cutoff_freq, sampling_time, order);
}

SFM3300::~SFM3300() { }

// PUBLIC METHODS * * * * * * * * * * * * * * * * * * * * *

bool SFM3300::begin(uint8_t address) {
  Wire.begin();
   delay(100);

  sensorAddress = address;
  Wire.beginTransmission(byte(sensorAddress)); // transmit to device #064 (0x40)
  Wire.write(byte(0x20));      //
  Wire.write(byte(0x00));      //
  Wire.endTransmission();
  delay(1000);

  Wire.beginTransmission(byte(sensorAddress)); // transmit to device #064 (0x40)
  Wire.write(byte(0x30));      //
  Wire.write(byte(0xde));      //
  Wire.endTransmission(); 

  delay(5);
  Wire.requestFrom(sensorAddress, 3); 
  dataArr[0] = Wire.read(); // first received byte stored here
  dataArr[1] = Wire.read(); // second received byte stored here
  dataArr[2] = Wire.read(); // third received byte stored here
  Wire.endTransmission();
   //CRC required
  scaleFactor = (dataArr[0]<<8)+dataArr[1];
    Serial.println(scaleFactor);
    delay(1000);
  delay(5);

  Wire.beginTransmission(byte(sensorAddress)); // transmit to device #064 (0x40)
  Wire.write(byte(0x30));      //
  Wire.write(byte(0xdf));      //
  Wire.endTransmission(); 

  delay(5);
  Wire.requestFrom(sensorAddress, 3); 
  dataArr[0] = Wire.read(); // first received byte stored here
  dataArr[1] = Wire.read(); // second received byte stored here
  dataArr[2] = Wire.read(); // third received byte stored here
  Wire.endTransmission();
   //CRC required
  offset = (dataArr[0]<<8)+dataArr[1];
}
bool SFM3300::startMeasuring()
{
  Wire.beginTransmission(byte(sensorAddress)); // transmit to device #064 (0x40)
  Wire.write(byte(0x10));      //
  Wire.write(byte(0x00));      //
  Wire.endTransmission(); 
  lasTimeofMeasuring=micros();
}
int SFM3300::readMeasuredFlowRow()
{
   Wire.requestFrom(sensorAddress, 3); 
  dataArr[0] = Wire.read(); // first received byte stored here
  dataArr[1] = Wire.read(); // second received byte stored here
  dataArr[2] = Wire.read(); // third received byte stored here
  Wire.endTransmission();
  //CRC required 
  return (dataArr[0]<<8)+dataArr[1];
}
double SFM3300::readFlow()  // unit slm
{
   Wire.requestFrom(sensorAddress, 3); 
  dataArr[0] = Wire.read(); // first received byte stored here
  dataArr[1] = Wire.read(); // second received byte stored here
  dataArr[2] = Wire.read(); // third received byte stored here
  Wire.endTransmission();
  //CRC required 
  return ((dataArr[0]<<8)+dataArr[1]- offset)/scaleFactor;
}
void SFM3300::measureFlow()
{
  flow_unfiltered= readFlow() ;
  flow = f->filterIn(flow_unfiltered);
}
double SFM3300::readMeasuredFlow() 
{
  return flow;
}

double SFM3300::readMeasuredVolume()
{
  return volume;
}
void SFM3300::resetMeasuredVolume()
{
   volume=0;
}
bool SFM3300::measureVolume()  // unit slm
{
      long timeofMeasuringPeriod = micros()-lasTimeofMeasuring;
      
      volume+= (readFlow()/60.0) * (timeofMeasuringPeriod/1000000.0);
      lasTimeofMeasuring=micros();
      return true;
}