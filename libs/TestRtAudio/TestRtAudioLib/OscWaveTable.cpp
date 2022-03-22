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
    gWavetable[n * nOutChannels] = harmoniesLevels[0] * sin(fondamental * 1); 
      
    for(unsigned int i=1;i<harmoniesLevels.size();i++){
      if (((float)gFrequency * (i+ 1) )> (sampleRate/ 2)){        
        break;
      }
      gWavetable[n * nOutChannels] +=  harmoniesLevels[i] * sin(fondamental * (i+ 1));
    }  
    
    
    

    for (unsigned int i = 1; i < nOutChannels; i++)
    {
      gWavetable[n * nOutChannels + i] = gWavetable[n * nOutChannels];
    }
  }
}

void OscWaveTableSine::setupWaveTable()
{
  for (unsigned int n = 0; n < gWavetableLength; n++)
  {
    const float fondamental = (2.0 * M_PI) * ((float)n / (float)gWavetableLength);

    gWavetable[n * nOutChannels] = sin(fondamental);
    /*
    0.5 * sin(fondamental) +
        pow(0.5, 2) * sin(fondamental * 2) +
        pow(0.5, 3) * sin(fondamental * 3) +
        pow(0.5, 4) * sin(fondamental * 4);
        */

    for (unsigned int i = 1; i < nOutChannels; i++)
    {
      gWavetable[n * nOutChannels + i] = gWavetable[n * nOutChannels];
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
    gWavetable[n * nOutChannels] = -1.0 + 4.0 * (float)n / (float)gWavetableLength;
    for (unsigned int i = 1; i < nOutChannels; i++)
    {
      gWavetable[n * nOutChannels + i] = gWavetable[n * nOutChannels];
    }
  }
  for (unsigned int n = gWavetableLength / 2; n < gWavetableLength; n++)
  {
    gWavetable[n * nOutChannels] = 1.0 - 4.0 * (float)(n - gWavetableLength / 2) / (float)gWavetableLength;
    for (unsigned int i = 1; i < nOutChannels; i++)
    {
      gWavetable[n * nOutChannels + i] = gWavetable[n * nOutChannels];
    }
  }
}

OscWaveTable::OscWaveTable(unsigned int sampleRate,unsigned int nOutChannels):sampleRate{sampleRate},nOutChannels{nOutChannels}
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
    for (unsigned chIdx = 0; chIdx < nOutChannels; chIdx++)
    {
      double val = 0;

      if ( std::count(sendToChannels.begin(), sendToChannels.end(), chIdx)  ){
        val = _gAmplitude * getLinearInterpolation(chIdx);
      }
      
      if (renderMode == RenderMode::setBuffer)
      {
        buffer[bufferPosition] = val;
      }
      else
      {
        buffer[bufferPosition] += val;
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

  float ch = this->gWavetable[currentGReadPointer * nOutChannels + chid] +
             currentGReadRemainder *
                 (this->gWavetable[nextGReadPointerInt * nOutChannels + chid] - this->gWavetable[currentGReadPointer * nOutChannels + chid]);

  return ch;
}
