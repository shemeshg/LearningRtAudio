#include <cassert>
#include <iostream>
#include "OscWaveTable.h"
#include "RangeUtils.h"

namespace RtAudioNs
{
  namespace Components
  {

    OscWaveTable::OscWaveTable(unsigned int sampleRate) : sampleRate{sampleRate}
    {
      gWavetable = (float *)std::calloc(gWavetableLength * 2, sizeof(float));
      assert(gWavetable);
    }

    OscWaveTable::~OscWaveTable()
    {
      free(gWavetable);
      gWavetable = NULL;
    }

    int OscWaveTable::render(std::vector<double> &channelData, std::vector<double> &cvPitchChange)
    {
      double *buffer = &channelData[0];
      unsigned int nBufferFrames = channelData.size();
      int bufferPosition = 0;

      for (unsigned int i = 0; i < nBufferFrames; i++)
      {
        double val = 0;
        val = getLinearInterpolation();
        buffer[bufferPosition] += val;
        bufferPosition++;
        gReadPointer = nextGReadPointer(gFrequency * cvPitchChange[i]);
      }
      return 0;
    }

    float OscWaveTable::getLinearInterpolation()
    {
      const int currentGReadPointer = (int)gReadPointer;
      float currentGReadRemainder = gReadPointer - (int)gReadPointer;
      int nextGReadPointerInt = currentGReadPointer + 1 >= gWavetableLength ? 0 : currentGReadPointer + 1;

      float ch = this->gWavetable[currentGReadPointer] +
                 currentGReadRemainder *
                     (this->gWavetable[nextGReadPointerInt] - this->gWavetable[currentGReadPointer]);

      return ch;
    }
  }
}