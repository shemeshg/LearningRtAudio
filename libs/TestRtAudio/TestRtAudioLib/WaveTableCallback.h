#pragma once
#include <cmath>
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
  RtGuiSlider(std::string name, float &val, float min, float max, float step) : name(name), val(val), min(min), max(max), step(step)
  {
  }
};


class RtWaveTableCallback
{
public:
  std::vector<RtGuiSlider> rtGuiSlider;
  std::vector<std::unique_ptr<OscWaveTableSine>> Oscs;

  float detuneOscsAmount = 0;
  float detunePitch = 0;

  float detuneAmplitudeDb = -10;

  RtWaveTableCallback();

  ~RtWaveTableCallback();

  void scopeLog(double *buffer, unsigned int &nBufferFrames, int channels = 2, int rowsCount = 2000);

  int render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
             double &streamTime, RtAudioStreamStatus &status);
};
