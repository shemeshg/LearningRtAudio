#pragma once
#include <iostream>
#include <vector>
#include "RtAudio.h"
#include "OscWaveTable.h"

class RtGuiControl
{
public:
  float &val;
  float min;
  float max;
  float step;
  std::string name;

  RtGuiControl(std::string name, float &val, float min, float max, float step) : name(name), val(val), min(min), max(max), step(step)
  {
  }

  virtual ~RtGuiControl() {}

  void virtual setVal(float v) = 0;
};

class RtGuiSlider : public RtGuiControl
{
public:
  RtGuiSlider(std::string name, float &val, float min, float max, float step) : RtGuiControl{name, val, min, max, step}
  {
  }

  void setVal(float v) override
  {
    val = v;
  }
};

class RtGuiSliderRefreshTableSetter : public RtGuiControl
{
public:
  OscWaveTable &owt;
  RtGuiSliderRefreshTableSetter(OscWaveTable &owt, std::string name, float &val, float min, float max, float step) : RtGuiControl{name, val, min, max, step}, owt{owt}
  {
  }

  void setVal(float v) override
  {
    val = v;
    owt.setupWaveTable();
  }
};

class RtWaveTableCallback
{
public:
  std::vector<std::unique_ptr<RtGuiControl>> rtGuiSliders;
  std::vector<std::unique_ptr<OscWaveTable>> Oscs;

  float detuneOscsAmount = 0;
  float detuneNoteNumber = 60;

  float detuneAmplitudeDb = -10;

  bool doScopelog = false;

  RtWaveTableCallback();

  ~RtWaveTableCallback();

  void scopeLog(double *buffer, unsigned int &nBufferFrames, int channels, int rowsCount,
                std::vector<unsigned int> colsToPrint, std::ostream &stream = std::cout);

  int render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
             double &streamTime, RtAudioStreamStatus &status);

  void setupStreamParameters(RtAudio &audio, int outDeviceId = -1, int inDeviceId = -1);
  void setupPlayersAndControls();
  unsigned int bufferFrames = 64;
  unsigned int sampleRate = 48000;
  RtAudio::StreamParameters streamOutParameters, streamInParameters;
};
