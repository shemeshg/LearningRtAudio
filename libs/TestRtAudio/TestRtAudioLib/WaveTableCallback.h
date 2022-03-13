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
  RtGuiSlider(std::string name, float &val, float min, float max, float step) : name(name), val(val), min(min), max(max), step(step)
  {
  }
};

class OscWaveTable
{
public:
  int gWavetableLength = 512; // The length of the buffer in frames
  float *gWavetable;          // Buffer that holds the wavetable

  float gAmplitudeDb = -10; // Amplitude of the playback
  float gFrequency = 220.0; // Frequency (TODO: not implemented yet)
  const int gChannelsCount = 2;

  double gReadPointer = 0;

  float gAmplitude()
  {
    return pow(10.0, gAmplitudeDb / 20.0);
  }

  double phaseStep()
  {
    return gWavetableLength * (gFrequency / 44100.0);
  }

  float nextGReadPointer()
  {
    float p = gReadPointer + phaseStep();
    if (p >= gWavetableLength)
    {
      p -= gWavetableLength;
    }
    return p;
  }

  OscWaveTable();
  virtual void setupWaveTable() = 0;
  virtual ~OscWaveTable();

  float getLinearInterpolation(int chid);

  enum RenderMode { setBuffer, addBuffer };

  int render(double *buffer ,  unsigned int &nBufferFrames, RenderMode renderMode );

  
};

class OscWaveTableSine : public OscWaveTable
{
  public:
  OscWaveTableSine() : OscWaveTable() {}
  void setupWaveTable() override;
};

class OscWaveTableTiangle : public OscWaveTable
{
  public:
  OscWaveTableTiangle() : OscWaveTable() {}
  void setupWaveTable() override;
};

class RtWaveTableCallback
{
public:
  std::vector<RtGuiSlider> rtGuiSlider;
  std::vector<std::unique_ptr<OscWaveTableSine>> Oscs;
  
  float detuneOscsAmount = 0;
  float detuneFrequency = 400;
  float detuneAmplitudeDb = -10;

  RtWaveTableCallback();

  ~RtWaveTableCallback();

  void scopeLog(double *buffer, unsigned int &nBufferFrames, int channels = 2, int rowsCount = 2000);

  int render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
             double &streamTime, RtAudioStreamStatus &status);
};
