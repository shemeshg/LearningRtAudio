#include "OscWaveTableAddative.h"

namespace RtAudioNs
{
namespace Components
{

    void OscWaveTableAddative::setupWaveTable()
    {
      for (int n = 0; n < getGWavetableLength(); n++)
      {

        const float fondamental = (float)(2.0 * M_PI) * ((float)n / (float)getGWavetableLength());
        getGWavetable()[n] = harmoniesLevels[0] * sin(fondamental * 1);

        constexpr float chInfile = 2;
        for (unsigned int i = 1; i < harmoniesLevels.size(); i++)
        {
          if (((float)getGFrequency() * ((float)i + 1)) > ((float)getSampleRate() / chInfile))
          {
            break;
          }
          getGWavetable()[n] += harmoniesLevels[i] * sin(fondamental * ((float)i + 1));
        }
      }
    }



}}
