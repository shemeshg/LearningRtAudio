#include "OscWaveTable2Addative.h"
#include "RangeUtils.h"
#include <iostream>

namespace RtAudioNs
{
  namespace Components
  {
    OscWaveTable2Addative::OscWaveTable2Addative(unsigned int sampleRate)
    {
      oscSine1 = std::make_unique<Components::OscWaveTableAddative>(sampleRate);
      oscSine2 = std::make_unique<Components::OscWaveTableAddative>(sampleRate);
    }

    void OscWaveTable2Addative::setupWaveTable()
    {
      oscSine1->setupWaveTable();
      oscSine2->setupWaveTable();
    }

    int OscWaveTable2Addative::render(std::vector<double> &channelData, std::vector<double> &cvPitchChange)
    {
      float detuneFrequency = (float)customMidiScale.cMidiNoteToFrequency(detuneNoteNumber);
      oscSine1->harmoniesLevels = harmoniesLevels;
      oscSine1->gFrequency = detuneFrequency + detuneOscsAmount;
      oscSine1->render(channelData, cvPitchChange);
      
      oscSine2->harmoniesLevels = harmoniesLevels;
      oscSine2->gFrequency = detuneFrequency - detuneOscsAmount;
      oscSine2->render(channelData, cvPitchChange);
      return 0;
    }
  }
}