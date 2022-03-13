#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "RtAudio.h"

class RtGuiSlider
{
public:
  float &val;
  float min;
  float max;
  float step;
  std::string name;
  RtGuiSlider(std::string name, float &val, float min, float max, float step) :name(name), val(val), min(min), max(max), step(step)
  {
  }
};

class RtWaveTableCallback
{
public:
  int gWavetableLength; // The length of the buffer in frames
  float *gWavetable;    // Buffer that holds the wavetable

  float gAmplitudeDb = -20;   // Amplitude of the playback
  float gFrequency = 220.0; // Frequency (TODO: not implemented yet)
  const int gChannelsCount = 2;

  std::vector<RtGuiSlider> rtGuiSlider;

  RtWaveTableCallback(int gWavetableLength);
 

  ~RtWaveTableCallback();

  void scopeLog(double *buffer, unsigned int &nBufferFrames, int channels = 2, int rowsCount = 2000);

  int render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
             double &streamTime, RtAudioStreamStatus &status);

  void setupSine();

  void setupTriangle();

private:
  float getLinearInterpolation(double gReadPointer, int chid);
};


