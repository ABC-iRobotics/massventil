/***
 * ventillationControl library - Implementation
 *
 * Copyright (C) 2020  Bence Takács
 */

#include "ventillationControl.h"




// CONSTRUCTOR AND DESTRUCTOR * * * * * * * * * * * * * * *

ventControl::ventControl()
{
    myPIDp = new PID(&Input, &Output, &Setpoint, pKp, pKi, pKd, DIRECT);
    myPIDf = new PID(&Input, &Output, &Setpoint, fKp, fKi, fKd, DIRECT);
    stepperX = new AccelStepper(1, steppin, dirpin);
}

ventControl::~ventControl() { }

// PUBLIC METHODS * * * * * * * * * * * * * * * * * * * * *

bool ventControl::begin() {
  pinMode(endswitchpin,INPUT);
  pinMode(steppin,OUTPUT);
  pinMode(dirpin,OUTPUT);

  stepperX->setMaxSpeed(6000);      // Set Max Speed of Stepper (Slower to get better accuracy)
  stepperX->setAcceleration(100000.0);
  stepperX->setSpeed(300);
  myPIDp->SetMode(AUTOMATIC);
  myPIDp->SetOutputLimits(-200,200);
  myPIDf->SetMode(AUTOMATIC);
  myPIDf->SetOutputLimits(-200,200);
}
bool ventControl::runMotor()
{
  stepperX->run();
}
bool ventControl::ventControlLoopP(double input, double setpoint)
{
              Input = input;
              Setpoint=setpoint;
              myPIDp->Compute();
              stepperX->moveTo(Output); 
}
bool ventControl::ventControlLoopF(double input, double setpoint)
{
              Input = input;
              Setpoint=setpoint;
              myPIDf->Compute();
              stepperX->moveTo(Output); 
}
bool ventControl::runhoming()
{
  ishoming = true;
  homingSuccess= false; 

     if(homing<5)stepperX->runSpeed();
      else stepperX->run();

      if(homing==1)
      {
          
          if(digitalRead(endswitchpin)==0)
            {   
              homing=2; 
              delay(100); 
              stepperX->setSpeed(-300);
            }
      }
      else if(homing==2)
      {
        if(digitalRead(endswitchpin)==1)
        {   
          homing=3;
          delay(100);
          stepperX->setSpeed(30);
        }
      }
      else if(homing==3)
      {
          if(digitalRead(endswitchpin)==0)
          {      
            homing=4;
            delay(100);
            stepperX->setSpeed(0);
          }
      }
      else if(homing==4)
      {
        homing=5;
        stepperX->setCurrentPosition(stepperNullPosition);    
      }
      else if(homing==5)
      {
        homing=6;
        stepperX->moveTo(0);
      }
      else if(homing==6)
      {
        if(stepperX->currentPosition()==0)
        {
          homing=1;
          ishoming=false;
          homingSuccess = true;
        }
         
      }
    return 0;

}
bool ventControl::pidTuningP()
{
  myPIDp->SetTunings(pKp,pKi,pKd);
}
bool ventControl::pidTuningF()

{
  myPIDf->SetTunings(fKp,fKi,fKd);
}