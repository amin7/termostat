#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "PID_AutoTune_v0.h"


PID_ATune::PID_ATune(double* Input, double* Output, double in_max_error) :
    in_max_error_(in_max_error)
{
	input = Input;
	output = Output;
	controlType =0 ; //default to PI
	noiseBand = 0.5;
  running = false;
	SetLookbackSec(10);
	lastTime = millis();
	
}
void PID_ATune::SetOutputRange(double min, double max) {
  out_min_ = min;
  out_max_ = max;
}

void PID_ATune::Start(double setpoint) {
  //initialize working variables the first time around
  peakType = 0;
  peakCount = 0;
  justchanged = false;
  setpoint_ = setpoint;
  running = true;
  if (in_max_error_ < setpoint_) {
    Serial.println("in_max_error_<setpoint_");
    return;
  }
  *output = out_max_;
  mode_ = mode_starting;
  
}


void PID_ATune::Cancel()
{
  mode_ = mode_off;
  *output = out_min_;
} 

 
int PID_ATune::Runtime()
{
  const auto refVal = *input;
  if (!(mode_starting == mode_
      || mode_run == mode_)) {
    return 0;
  }

  if (in_max_error_ < refVal) {
    Serial.println("in_max_error_ < refVal,stoped");
    mode_ = mode_err;
    *output = out_min_;
    return 1;
  }

  unsigned long now = millis();
	if (now < lastTime)
    return 0;

  if (peakCount > 9)
      {
    running = false;
    FinishUp();
    return 1;
  }
  lastTime = now + sampleTime;

  if ((refVal < setpoint_ + noiseBand)
      && (refVal > setpoint_ - noiseBand)
      && (mode_starting == mode_)
      ) {
    //we are in mesured window, start
    absMax = refVal;
    absMin = refVal;
    mode_ = mode_run;
  }

  if (mode_run != mode_) {
    return 0;
  }

  if (refVal > absMax)
    absMax = refVal;
  if (refVal < absMin)
    absMin = refVal;
	
	
	//oscillate the output base on the input's relation to the setpoint
	
	if (refVal > setpoint_ + noiseBand)
    *output = out_min_;
  else if (refVal < setpoint_ - noiseBand)
    *output = out_max_;
	
	
  //bool isMax=true, isMin=true;
  isMax=true;isMin=true;
  //id peaks
  for(int i=nLookBack-1;i>=0;i--)
  {
    double val = lastInputs[i];
    if(isMax) isMax = refVal>val;
    if(isMin) isMin = refVal<val;
    lastInputs[i+1] = lastInputs[i];
  }
  lastInputs[0] = refVal;  
  if(nLookBack<9)
  {  //we don't want to trust the maxes or mins until the inputs array has been filled
	return 0;
	}
  
  if(isMax)
  {
    if(peakType==0)peakType=1;
    if(peakType==-1)
    {
      peakType = 1;
      justchanged=true;
      peak2 = peak1;
    }
    peak1 = now;
    peaks[peakCount] = refVal;
   
  }
  else if(isMin)
  {
    if(peakType==0)peakType=-1;
    if(peakType==1)
    {
      peakType=-1;
      peakCount++;
      justchanged=true;
    }
    
    if(peakCount<10)peaks[peakCount] = refVal;
  }
  
  if(justchanged && peakCount>2)
  { //we've transitioned.  check if we can autotune based on the last peaks
    double avgSeparation = (abs(peaks[peakCount-1]-peaks[peakCount-2])+abs(peaks[peakCount-2]-peaks[peakCount-3]))/2;
    if( avgSeparation < 0.05*(absMax-absMin))
    {
      FinishUp();
	  return 1;
	 
    }
  }
   justchanged=false;
	return 0;
}
void PID_ATune::FinishUp()
{
  *output = out_min_;
  //we can generate tuning parameters!
  Ku = 4 * (2 * (out_max_ - out_min_)) / ((absMax - absMin) * 3.14159);
  Pu = (double) (peak1 - peak2) / 1000;
  mode_ = mode_done;
}

double PID_ATune::GetKp()
{
	return controlType==1 ? 0.6 * Ku : 0.4 * Ku;
}

double PID_ATune::GetKi()
{
	return controlType==1? 1.2*Ku / Pu : 0.48 * Ku / Pu;  // Ki = Kc/Ti
}

double PID_ATune::GetKd()
{
	return controlType==1? 0.075 * Ku * Pu : 0;  //Kd = Kc * Td
}

void PID_ATune::SetControlType(int Type) //0=PI, 1=PID
{
	controlType = Type;
}
int PID_ATune::GetControlType()
{
	return controlType;
}
	
void PID_ATune::SetNoiseBand(double Band)
{
	noiseBand = Band;
}

double PID_ATune::GetNoiseBand()
{
	return noiseBand;
}

void PID_ATune::SetLookbackSec(int value)
{
    if (value<1) value = 1;
	
	if(value<25)
	{
		nLookBack = value * 4;
		sampleTime = 250;
	}
	else
	{
		nLookBack = 100;
		sampleTime = value*10;
	}
}

int PID_ATune::GetLookbackSec()
{
	return nLookBack * sampleTime / 1000;
}
