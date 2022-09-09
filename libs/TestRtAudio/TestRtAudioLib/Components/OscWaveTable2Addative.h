#pragma once
#include "RangeUtils.h"
#include "OscWaveTableAddative.h"

namespace RtAudioNs
{
  namespace Components
  {
    namespace {
        constexpr float midiMiddleC = 60;
        constexpr float harmonyLevel0 = 0.5;
    }

    class OscWaveTable2Addative : public ItfSetupWaveTable
    {
    public:
      OscWaveTable2Addative(unsigned int sampleRate);
      void setupWaveTable() override;






      
      int render(std::vector<double> &channelData, std::vector<double> &cvPitchChange);

      float &getDetuneOscsAmount(){
          return detuneOscsAmount;
      }

      float &getDetuneNoteNumber(){
      return detuneNoteNumber;
    }

      private:
        // Levels 0..1 NOT DBs
        std::vector<float> harmoniesLevels{harmonyLevel0, 0, 0, 0, 0, 0, 0, 0};
        float detuneOscsAmount = 0;
        float detuneNoteNumber = midiMiddleC;

        std::unique_ptr<OscWaveTableAddative> oscSine1;
        std::unique_ptr<OscWaveTableAddative> oscSine2;
        CustomMidiScale customMidiScale;
    };

  }
}
