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
    gWavetable[n * gChannelsCount] =     
      harmoniesLevels[0] * sin(fondamental * 1) +
      harmoniesLevels[1] * sin(fondamental * 2) +
      harmoniesLevels[2] * sin(fondamental * 3) +
      harmoniesLevels[3] * sin(fondamental * 4);
    
    

    for (unsigned int i = 1; i < gChannelsCount; i++)
    {
      gWavetable[n * gChannelsCount + i] = gWavetable[n * gChannelsCount];
    }
  }
}

void OscWaveTableSine::setupWaveTable()
{
  for (unsigned int n = 0; n < gWavetableLength; n++)
  {
    const float fondamental = (2.0 * M_PI) * ((float)n / (float)gWavetableLength);

    gWavetable[n * gChannelsCount] = sin(fondamental);
    /*
    0.5 * sin(fondamental) +
        pow(0.5, 2) * sin(fondamental * 2) +
        pow(0.5, 3) * sin(fondamental * 3) +
        pow(0.5, 4) * sin(fondamental * 4);
        */

    for (unsigned int i = 1; i < gChannelsCount; i++)
    {
      gWavetable[n * gChannelsCount + i] = gWavetable[n * gChannelsCount];
    }
  }
}

void OscWaveTableTiangle::setupWaveTable()
{
  // Generate a triangle waveform (ramp from -1 to 1, then 1 to -1)
  // and store it in the buffer. Notice: generating the wavetable does
  // not depend on the audio sample rate (why not?)

  for (unsigned int n = 0; n < gWavetableLength / 2; n++)
  {
    gWavetable[n * gChannelsCount] = -1.0 + 4.0 * (float)n / (float)gWavetableLength;
    for (unsigned int i = 1; i < gChannelsCount; i++)
    {
      gWavetable[n * gChannelsCount + i] = gWavetable[n * gChannelsCount];
    }
  }
  for (unsigned int n = gWavetableLength / 2; n < gWavetableLength; n++)
  {
    gWavetable[n * gChannelsCount] = 1.0 - 4.0 * (float)(n - gWavetableLength / 2) / (float)gWavetableLength;
    for (unsigned int i = 1; i < gChannelsCount; i++)
    {
      gWavetable[n * gChannelsCount + i] = gWavetable[n * gChannelsCount];
    }
  }
}

OscWaveTable::OscWaveTable()
{
  gWavetable = (float *)std::calloc(gWavetableLength * 2, sizeof(float));
  assert(gWavetable);
}

OscWaveTable::~OscWaveTable()
{
  free(gWavetable);
  gWavetable = NULL;
}

int OscWaveTable::render(double *buffer, unsigned int &nBufferFrames, RenderMode renderMode)
{
  int bufferPosition = 0;
  float _gAmplitude = gAmplitude();

  for (unsigned int i = 0; i < nBufferFrames; i++)
  {
    for (unsigned chIdx = 0; chIdx < gChannelsCount; chIdx++)
    {
      if (renderMode == RenderMode::setBuffer)
      {
        buffer[bufferPosition] = _gAmplitude * getLinearInterpolation(chIdx);
      }
      else
      {
        buffer[bufferPosition] += _gAmplitude * getLinearInterpolation(chIdx);
      }

      bufferPosition++;
    }

    gReadPointer = nextGReadPointer();
  }
  return 0;
}

float OscWaveTable::getLinearInterpolation(int chid)
{
  const int currentGReadPointer = (int)gReadPointer;
  float currentGReadRemainder = gReadPointer - (int)gReadPointer;
  int nextGReadPointerInt = currentGReadPointer + 1 >= gWavetableLength ? 0 : currentGReadPointer + 1;

  float ch = this->gWavetable[currentGReadPointer * gChannelsCount + chid] +
             currentGReadRemainder *
                 (this->gWavetable[nextGReadPointerInt * gChannelsCount + chid] - this->gWavetable[currentGReadPointer * gChannelsCount + chid]);

  return ch;
}
