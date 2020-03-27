/***
 * ventillationControl library - Header
 *
 * Copyright (C) 2020  Bence Takács
 */

#pragma once
/// Has to be executed on Arduino IDE > 1.6.7
#include <Arduino.h>
#include <PID_v1.h>
#include <AccelStepper.h>


class ventControl {
public:

  /** \brief Filter class.
   *
   */
  ventControl();
  ~ventControl();
  bool begin();
  bool  ventControlLoopP(double input , double setpoint );
  bool  ventControlLoopF(double input , double setpoint );
  bool runhoming();
  bool runMotor();
  bool pidTuningP();
  bool pidTuningF();
  int steppin = 19;
  int dirpin  = 18;
  int endswitchpin = 5;
 

  
  int calibrated = false; 
  int homing =1;
  int ishoming= false; 
  int homingSuccess= false;
  int stepperNullPosition = 280;

  double Setpoint, Input, Output;
  //Specify the links and initial tuning parameters
  double pKp=1.8, pKi=6, pKd=0.01;   /* pressure control  double Kp=1.8, Ki=6, Kd=0.01;*/
  PID *myPIDp;

  double fKp=0.08, fKi=6.0, fKd=0.0;   /* pressure control  double Kp=1.8, Ki=6, Kd=0.01;*/
  PID *myPIDf;
  
  AccelStepper *stepperX;
};
