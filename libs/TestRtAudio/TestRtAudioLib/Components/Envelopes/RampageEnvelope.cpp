#include "RampageEnvelope.h"
#include <cmath>

namespace RtAudioNs
{
  namespace Components
  {
    void RampageEnvelope::render(std::vector<double> &inVector,
                                 std::vector<double> &outVector,
                                 std::vector<double> &attackTime, //in seconds
                                 std::vector<double> &decayTime //in seconds
                                 )
    {

      for (unsigned int i = 0; i < inVector.size(); i++)
      {

        const double attachCoef = pow(exp(-1 / attackTime[i]), 1.0 / sampleRate);
        const double decayCoef = pow(exp(-1 / decayTime[i]), 1.0 / sampleRate);
        const double absIn = abs(inVector[i]);
        const double coef =  absIn> lastEnvelopeSample ? attachCoef : decayCoef;

        outVector[i] = coef * lastEnvelopeSample + (1 - coef) * absIn;
        lastEnvelopeSample = outVector[i];
      }
    }
  }

}
