#include <cassert>
#include <iostream>
#include "OscWaveTable.h"


namespace RtAudioNs
{
  namespace Components
  {

    OscWaveTable::OscWaveTable(unsigned int sampleRate) : sampleRate{sampleRate}
    {
           gWavetable.assign(gWavetableLength * 2,0);
    }



    int OscWaveTable::render(std::vector<double> &channelData, std::vector<double> &cvPitchChange)
    {

      unsigned int nBufferFrames = channelData.size();
      int bufferPosition = 0;

      for (unsigned int i = 0; i < nBufferFrames; i++)
      {
        double val = 0;
        val = getLinearInterpolation();
        channelData[bufferPosition] += val;
        bufferPosition++;
        constexpr double frequencyPower10Pitch = 10;
        gReadPointer = nextGReadPointer(gFrequency * pow(2, cvPitchChange[i] * frequencyPower10Pitch));
      }
      return 0;
    }

    double OscWaveTable::getLinearInterpolation()
    {
      const int currentGReadPointer = (int)gReadPointer;
      double currentGReadRemainder = gReadPointer - (int)gReadPointer;
      int nextGReadPointerInt = currentGReadPointer + 1 >= gWavetableLength ? 0 : currentGReadPointer + 1;

      double ch = this->gWavetable[currentGReadPointer] +
                 currentGReadRemainder *
                     (this->gWavetable[nextGReadPointerInt] - this->gWavetable[currentGReadPointer]);

      return ch;
    }
  }
}
