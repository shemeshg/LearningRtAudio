#include "OscWaveTableSine.h"
namespace RtAudioNs
{
namespace Components
{

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

}}