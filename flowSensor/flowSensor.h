/***
 * flowSensor library - Header
 *
 * Copyright (C) 2020  Bence Takács
 */

#pragma once
/// Has to be executed on Arduino IDE > 1.6.7
#include <Arduino.h>
#include <filters.h>
#include <pressureSensor.h>



using namespace IIR;

class FlowSensor {
public:

  /** \brief Pressure Sensor calss.
   *
   */
  FlowSensor();
  ~FlowSensor();
  void begin(int pin);
  void calibration();
  bool isCalibrated();
  double getFlow();
  double setoffsetF(double offset);
  double setK(double sc);
  double setK(double mK, double pK);

  PressureSensor *pressureSensor;
double offsetF = 0;

private: 
  int analogPin = 0;
  double flow = 0;   //default 64 
  double flowUnfiltered;
  
  double calibration_step=0.1;
  int calibrated =0;
  int calibratedcount=0;
  double minusk = 2;
  double plusk = 2;
  String sName = "sensor";
  int calibrationPreLoopforFilter =0;

  const float cutoff_freq   = 10.0;  //Cutoff frequency in Hz
  const float sampling_time = 0.0005; //Sampling time in seconds.
  IIR::ORDER  order  = IIR::ORDER::OD3; // Order (OD1 to OD4)

  Filter *f;

  

};
