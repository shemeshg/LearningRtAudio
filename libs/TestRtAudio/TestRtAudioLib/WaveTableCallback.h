#pragma once
#include <iostream>
#include <vector>
#include "RtAudio.h"
#include "Components/OscWaveTable2Addative.h"
#include "Components/RtGuiControl.h"
#include "Components/VcaGateComponent.h"
#include "Components/SwitchAmpComponent.h"
#include "Components/PlayWavFile.h"
#include "Components/FiltersComponent.h"
#include "Components/PlayheadMarker.h"
#include "Components/CircularBuffer.h"
#include "Components/Envelopes/SimpleAdsrComponent.h"
#include "Components/Envelopes/LinearAdsr.h"
#include "Components/Envelopes/ExponentialAdsr.h"
#include "Components/Envelopes/PercussiveEnvelope.h"
#include "Components/Envelopes/RampageEnvelope.h"
#include "Components/MetronomeComponent.h"
#include "Components/DebounceVca.h"
#include "Components/MidiComponent/MidiComponent.h"

namespace RtAudioNs
{ 
  class RtWaveTableCallback
  {
  public:
    std::vector<std::unique_ptr<Components::RtGuiControl>> rtGuiSliders;
    std::vector<std::unique_ptr<Components::OscWaveTable2Addative>> vecOsc2Sine;
    std::vector<std::unique_ptr<Components::VcaContainer>> vecVcas;
    std::vector<std::unique_ptr<Components::SwitchAmpComponent>> switchAmps;
    std::vector<std::unique_ptr<Components::PlayWavFile>> playWavfiles;
    std::vector<std::unique_ptr<Components::FiltersComponent>> filters;
    std::unique_ptr<Components::PlayheadMarker> playheadMarker;
    std::vector<Components::PlayheadEvent> playheadEvents;
    Components::FramesCounter frameCounter;
    std::unique_ptr<Components::CircularBuffer> circularBuffer;
    std::unique_ptr<Components::SimpleAdsrComponent> simpleAdsrComponent;
    std::unique_ptr<Components::LinearAdsrComponent> linearAdsr;
    std::unique_ptr<Components::ExponentialAdsr> exponentialAdsr;    
    std::unique_ptr<Components::PercussiveEnvelope> percussiveEnvelope;
    std::unique_ptr<Components::RampageEnvelope> rampageEnvelope;
    std::unique_ptr<Components::MetronomeComponent> metronomeComponent;
    std::unique_ptr<Components::MidiComponent> midiComponent;
    Components::DebounceVca debounceVca;

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