#include <cassert>
#include <iostream>
#include "OscWaveTable.h"

namespace RtAudioNs
{
  namespace Components
  {
    void OscWaveTable::setupWaveTable()
    {
      return;
    }


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
      float _gAmplitude = gAmplitude();

      for (unsigned int i = 0; i < nBufferFrames; i++)
      {
        double val = 0;
        val = _gAmplitude * getLinearInterpolation();
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