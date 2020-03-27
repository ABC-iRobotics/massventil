/***
 * flowSensor library - Implementation
 *
 * Copyright (C) 2020  Bence Takács
 */


#include "flowSensor.h"
#include <filters.h>
#include <pressureSensor.h>


// CONSTRUCTOR AND DESTRUCTOR * * * * * * * * * * * * * * *

FlowSensor::FlowSensor()
{
 f=new Filter(cutoff_freq, sampling_time, order);
 pressureSensor = new PressureSensor();

}

FlowSensor::~FlowSensor() { }

// PUBLIC METHODS * * * * * * * * * * * * * * * * * * * * *

void FlowSensor::begin(int pin) {
    
    pressureSensor->begin(pin);
}
long double calibratingFlow = 0;
void FlowSensor::calibration()
  {
      double pressurembar = pressureSensor->getPressure();
          if(pressurembar<0)
                  {
                    flowUnfiltered= (- minusk * sqrt(-pressurembar) );
                  }
                  else
                  {
                    flowUnfiltered = (plusk* sqrt(pressurembar));
                  }
                  flow = f->filterIn(flowUnfiltered);
     
                if(calibrationPreLoopforFilter<1000)
                {
                  calibrationPreLoopforFilter++;
                  return;
                }

                if(calibratedcount<5000)
                {
                  calibratingFlow+=flow;
                  calibratedcount++;
                }
                else
                {
                  offsetF = calibratingFlow /5000.0; 
                  calibrated = true;
                }
                

               
                          
                       
}


bool FlowSensor::isCalibrated()
{
  return calibrated;
}
double FlowSensor::getFlow()
{
  double pressurembar = pressureSensor->getPressure();
          if(pressurembar<0)
                  {
                    flowUnfiltered= (- minusk * sqrt(-pressurembar) ) ;
                  }
                  else
                  {
                    flowUnfiltered = (plusk* sqrt(pressurembar));
                  }
                  flow = f->filterIn(flowUnfiltered);
                  return flow;
}
double FlowSensor::setoffsetF(double offset)
{
    offsetF=offset;
}
double FlowSensor::setK(double mK, double pK)
{
    minusk=mK;
    plusk=pK;
}