#pragma once
#include <iostream>
#include <vector>
#include "RtAudio.h"
#include "Components/OscWaveTable2Addative.h"
#include "Components/RtGuiControl.h"
namespace RtAudioNs
{
 
  class RtWaveTableCallback
  {
  public:
    std::vector<std::unique_ptr<Components::RtGuiControl>> rtGuiSliders;
    std::vector<std::unique_ptr<Components::OscWaveTable2Addative>> Oscs;

    RtWaveTableCallback();

    ~RtWaveTableCallback();

    int render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
               double &streamTime, RtAudioStreamStatus &status);

    void setupStreamParameters(RtAudio &audio, int outDeviceId = -1, int inDeviceId = -1, unsigned int streamBufferFrames = 1024);
    void setupPlayersAndControls();

    RtAudio::StreamParameters streamOutParameters, streamInParameters;

    std::function<void(std::vector<double> &v)> callbackToUi = [](std::vector<double> &v) {};

    bool const &getDoScopelog() const { return doScopelog; }
    void setDoScopelog(bool val) { doScopelog = val; }

    unsigned int const &getSampleRate() const { return sampleRate; }
    unsigned int bufferFrames = 1024;

  private:
    void scopeLog(double *buffer, unsigned int &nBufferFrames, int channels, int rowsCount,
                  std::vector<unsigned int> colsToPrint, std::ostream &stream = std::cout);

    std::vector<double> getInput(double *inputBuffer, unsigned int &nBufferFrames, int channels, unsigned int inputToGet);

    void sendOutput(double *buffer, unsigned int &nBufferFrames, int channels,
                    std::vector<double> &outChannel, std::vector<unsigned int> colsToSend);



    unsigned int sampleRate = 48000;

    bool doScopelog = false;
  };
}