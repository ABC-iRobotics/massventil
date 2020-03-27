/***
 * sensirion Flow sensor FSM3300 library - Header
 *
 * Copyright (C) 2020  Bence Takács
 */

#pragma once
/// Has to be executed on Arduino IDE > 1.6.7
#include <Arduino.h>
#include <filters.h>

/*  TO DO 
 CRC check
 
 public/private variables methotsd 
*/


class SFM3300 {
public:

  /** \brief Filter class.
   *
   */
  SFM3300();
  ~SFM3300();
  bool begin(uint8_t address);
  bool startMeasuring();
  int readMeasuredFlowRow();
  void measureFlow();
  double readFlow();
  double readMeasuredFlow();
  double readMeasuredVolume();
  void resetMeasuredVolume();
  bool measureVolume();


  uint8_t sensorAddress = 64;   //default 64 

  double volume =0;
  long lasTimeofMeasuring;
  uint8_t dataArr[3];
  uint16_t scaleFactor=0;
  uint16_t offset =0;
  double flow_unfiltered;
  double flow;
  
  const float cutoff_freq   = 10.0;  //Cutoff frequency in Hz
  const float sampling_time = 0.0005; //Sampling time in seconds.
  IIR::ORDER  order  = IIR::ORDER::OD3; // Order (OD1 to OD4)

Filter *f;

};
