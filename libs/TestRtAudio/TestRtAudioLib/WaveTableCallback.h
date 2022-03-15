#pragma once
#include <iostream>
#include <vector>
#include "RtAudio.h"
#include "OscWaveTable.h"

class RtGuiSlider
{
public:
  float &val;
  float min;
  float max;
  float step;
  std::string name;

  RtGuiSlider(std::string name, float &val, float min, float max, float step) : 
      name(name), val(val), min(min), max(max), step(step)
  {
  }

  virtual void setVal(float v){
    val = v;
  }

};


class RtGuiSliderRefreshTableSetter: RtGuiSlider {
  public:
  OscWaveTable &owt;
  RtGuiSliderRefreshTableSetter(OscWaveTable &owt, std::string name, float &val, float min, float max, float step) : 
      RtGuiSlider{name, val, min, max, step},owt{owt}{

      }   
  void setVal(float v) override{
    val = v;
    owt.setupWaveTable();
  }         
};


class RtWaveTableCallback
{
public:
  std::vector<RtGuiSlider> rtGuiSlider;
  std::vector<std::unique_ptr<OscWaveTableSine>> Oscs;

  float detuneOscsAmount = 0;
  float detuneNoteNumber = 60;

  float detuneAmplitudeDb = -10;

  bool doScopelog=false;

  RtWaveTableCallback();

  ~RtWaveTableCallback();

  void scopeLog(double *buffer, unsigned int &nBufferFrames, int channels = 2, int rowsCount = 22050);

  int render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
             double &streamTime, RtAudioStreamStatus &status);
};
