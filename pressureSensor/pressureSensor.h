/***
 * analog pressure sensor library - Header
 *
 * Copyright (C) 2020  Bence Takács
 */

#pragma once
/// Has to be executed on Arduino IDE > 1.6.7
#include <Arduino.h>
#include <filters.h>



using namespace IIR;

class PressureSensor {
public:

  /** \brief Pressure Sensor calss.
   *
   */
  PressureSensor();
  ~PressureSensor();
  void begin(int Pin);
  void calibration();
   void calibrationRaw();
  bool isCalibrated();
  double getPressure();
  double getPressureRaw();
  double setoffsetV(double offset);
  double setscale(double sc);
  double measurePressure();
  double offsetV = 0; 



private: 
  int analogPin = 0;
  double pressurembar = 0;   //default 64 
  double pressurembar_unfiltered;
  
  double calibration_step=0.1;
  int calibrated =0;
  int calibratedcount=0;
  double scale= 10/0.09;
  String sName = "sensor";
  int calibrationPreLoopforFilter =0;

  const float cutoff_freq   = 10.0;  //Cutoff frequency in Hz
  const float sampling_time = 0.0005; //Sampling time in seconds.
  IIR::ORDER  order  = IIR::ORDER::OD3; // Order (OD1 to OD4)

  Filter *f;

};
