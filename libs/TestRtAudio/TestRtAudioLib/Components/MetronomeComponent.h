#pragma once
#include "OscWaveTableAddative.h"
#include "Envelopes/PercussiveEnvelope.h"
#include "PlayheadMarker.h"

namespace RtAudioNs
{
  namespace Components
  {
    class MetronomeComponent
    {
    public:
      MetronomeComponent(unsigned int _sampleRate, unsigned int _nBufferFrames, PlayheadMarker &_playheadMarker) : sampleRate{_sampleRate}, nBufferFrames{_nBufferFrames}, playheadMarker{_playheadMarker}
      {
        oscSineLow = std::make_unique<Components::OscWaveTableAddative>(sampleRate);
        oscSineLow->harmoniesLevels = harmoniesLevels;
        oscSineLow->gFrequency = lowFreq;

        oscSineHi = std::make_unique<Components::OscWaveTableAddative>(sampleRate);
        oscSineHi->harmoniesLevels = harmoniesLevels;
        oscSineHi->gFrequency = hiFreq;

        percussiveEnvelope = std::make_unique<Components::PercussiveEnvelope>();

        constexpr unsigned int bitPerSec = 60;
        constexpr float hiBitEvery = 0.5;

        playheadEvent.framesEvery = sampleRate * bitPerSec / playheadMarker.metronomParams.metronomBpm;
        playheadEvent.framesLen = (int)( (float)playheadEvent.framesEvery * hiBitEvery);
        playheadEvent.frameStart = 0;
        playheadEvent.repeatCount = -1;
      }

      void setupWaveTable()
      {
        oscSineLow->setupWaveTable();
        oscSineHi->setupWaveTable();
      }

      void render(std::vector<double> &channelData);

    private:
      std::unique_ptr<OscWaveTableAddative> oscSineLow;
      std::unique_ptr<OscWaveTableAddative> oscSineHi;
      std::unique_ptr<PercussiveEnvelope> percussiveEnvelope;

      std::vector<float> harmoniesLevels{1};

      const unsigned int sampleRate;
      unsigned int nBufferFrames;

      const float hiFreq = 1000;
      const float lowFreq = 500;
      PlayheadMarker &playheadMarker;
      PlayheadEvent playheadEvent{};
    };

  }
}
