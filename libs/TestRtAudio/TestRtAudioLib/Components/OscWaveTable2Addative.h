#pragma once
#include "OscWaveTableAddative.h"

namespace RtAudioNs
{
  namespace Components
  {

    class OscWaveTable2Addative : public ItfSetupWaveTable
    {
    public:
      OscWaveTable2Addative(unsigned int sampleRate);
      void setupWaveTable() override;
      std::unique_ptr<OscWaveTableAddative> oscSine1;
      std::unique_ptr<OscWaveTableAddative> oscSine2;

      float detuneOscsAmount = 0;
      float detuneNoteNumber = 60;
      float detuneAmplitudeDb = -10;

      int render(std::vector<double> &channelData, std::vector<double> &cvPitchChange);
    };

  }
}