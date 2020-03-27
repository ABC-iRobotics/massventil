/***
 * analog pressure sensor library - Implementation
 *
 * Copyright (C) 2020  Bence Takács
 */


#include "pressureSensor.h"
#include <filters.h>



// CONSTRUCTOR AND DESTRUCTOR * * * * * * * * * * * * * * *

PressureSensor::PressureSensor()
{
 f=new Filter(cutoff_freq, sampling_time, order);
}

PressureSensor::~PressureSensor() { }

// PUBLIC METHODS * * * * * * * * * * * * * * * * * * * * *

void PressureSensor::begin(int Pin) {
    analogPin= Pin; 
    pinMode(analogPin,INPUT);
   
}

void PressureSensor::calibration() {

    if(calibrationPreLoopforFilter<500)
    {
      calibrationPreLoopforFilter++;
      return;}

    if(abs(pressurembar)<0.1)
          {calibration_step=0.0001;
          }     
          else if(abs(pressurembar)<0.5)
          {calibration_step=0.001;
          }
          else if(abs(pressurembar)<3.0)
          {calibration_step=0.1;
          }

          if(pressurembar>0.05)
          {
            offsetV+=calibration_step;
          }
          else if (pressurembar<-0.05)
          {
          offsetV-=calibration_step; 
          }   
          else
          {
            if(abs(pressurembar)<=0.05)
              { 
                calibratedcount++ ;
                if(calibratedcount>2000)
                {
                  calibrated = true;
                }
                }
                else
                {
                  calibratedcount=0;
                }
          }
}



bool PressureSensor::isCalibrated()
{
  return calibrated;
}
double PressureSensor::measurePressure()
{
  pressurembar_unfiltered= ((((((double)(analogRead(analogPin))-offsetV)*0.0008056640625)))) * (scale) ;
  pressurembar = f->filterIn(pressurembar_unfiltered);
}
double PressureSensor::getPressure()
{
  return pressurembar;
}
double PressureSensor::getPressureRaw()
{
  pressurembar_unfiltered=analogRead(analogPin)-offsetV;
  pressurembar = f->filterIn(pressurembar_unfiltered);
  return pressurembar_unfiltered;
}

double PressureSensor::setoffsetV(double offset)
{
    offsetV=offset;
}
double PressureSensor::setscale(double sc)
{
    scale=sc;
}