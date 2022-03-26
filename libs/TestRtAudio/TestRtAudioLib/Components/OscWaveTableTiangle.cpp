#include "OscWaveTableTiangle.h"
namespace RtAudioNs
{
namespace Components
{
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

}}