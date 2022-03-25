#include <cassert>
#include <iostream>
#include "OscWaveTable.h"

void OscWaveTable::setupWaveTable()
{
  return;
}

void OscWaveTableAddative::setupWaveTable()
{
  for (unsigned int n = 0; n < gWavetableLength; n++)
  {

    const float fondamental = (2.0 * M_PI) * ((float)n / (float)gWavetableLength);
    gWavetable[n] = harmoniesLevels[0] * sin(fondamental * 1);

    for (unsigned int i = 1; i < harmoniesLevels.size(); i++)
    {
      if (((float)gFrequency * (i + 1)) > (sampleRate / 2))
      {
        break;
      }
      gWavetable[n] += harmoniesLevels[i] * sin(fondamental * (i + 1));
    }
  }
}

void OscWaveTableSine::setupWaveTable()
{
  for (unsigned int n = 0; n < gWavetableLength; n++)
  {
    const float fondamental = (2.0 * M_PI) * ((float)n / (float)gWavetableLength);

    gWavetable[n] = sin(fondamental);
    /*
    0.5 * sin(fondamental) +
        pow(0.5, 2) * sin(fondamental * 2) +
        pow(0.5, 3) * sin(fondamental * 3) +
        pow(0.5, 4) * sin(fondamental * 4);
        */
  }
}

void OscWaveTableTiangle::setupWaveTable()
{
  // Generate a triangle waveform (ramp from -1 to 1, then 1 to -1)
  // and store it in the buffer. Notice: generating the wavetable does
  // not depend on the audio sample rate (why not?)

  for (unsigned int n = 0; n < gWavetableLength / 2; n++)
  {
    gWavetable[n] = -1.0 + 4.0 * (float)n / (float)gWavetableLength;
  }
  for (unsigned int n = gWavetableLength / 2; n < gWavetableLength; n++)
  {
    gWavetable[n] = 1.0 - 4.0 * (float)(n - gWavetableLength / 2) / (float)gWavetableLength;
  }
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
