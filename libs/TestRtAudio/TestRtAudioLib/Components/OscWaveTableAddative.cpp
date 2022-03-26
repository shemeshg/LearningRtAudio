#include "OscWaveTableAddative.h"

namespace RtAudioNs
{
namespace Components
{

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



}}