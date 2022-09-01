// Follow the original signal envelope
#pragma once
#include <vector>

namespace RtAudioNs
{
  namespace Components
  {
    class RampageEnvelope
    {
    public:
      RampageEnvelope(unsigned int _sampleRate) : sampleRate{_sampleRate} {}
      void render(std::vector<double> &inVector,
                  std::vector<double> &outVector,
                  std::vector<double> &attackTime,
                  std::vector<double> &decayTime);

    private:
      unsigned int sampleRate;
      double lastEnvelopeSample = 0;
    };
  }
}