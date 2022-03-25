#pragma once
#include <iostream>
#include <vector>
#include "RtAudio.h"
#include "OscWaveTable.h"

class RtGuiControl
{
public:
  RtGuiControl(std::string name, float &val, float min, float max, float step) : name(name), val(val), min(min), max(max), step(step)
  {
  }

  virtual ~RtGuiControl() {}

  void virtual setVal(float v) = 0;
  float const &getVal() const { return val; }
  std::string const &getName() const { return name; }
  float const &getMin() const { return min; }
  float const &getMax() const { return max; }
  float const &getStep() const { return step; }

protected:
  float &val;
  float min;
  float max;
  float step;
  std::string name;
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

  void sendOutput(double *buffer, unsigned int &nBufferFrames, int channels,
                  std::vector<double> &outChannel, std::vector<unsigned int> colsToSend);

  std::vector<double> getInput(double *inputBuffer, unsigned int &nBufferFrames, int channels, unsigned int inputToGet);

  int render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
             double &streamTime, RtAudioStreamStatus &status);

  void setupStreamParameters(RtAudio &audio, int outDeviceId = -1, int inDeviceId = -1, unsigned int streamBufferFrames = 1024);
  void setupPlayersAndControls();
  unsigned int bufferFrames = 1024;
  unsigned int sampleRate = 48000;
  RtAudio::StreamParameters streamOutParameters, streamInParameters;

  std::function<void(std::vector<double> &v)> callbackToUi = [](std::vector<double> &v) {};
};
