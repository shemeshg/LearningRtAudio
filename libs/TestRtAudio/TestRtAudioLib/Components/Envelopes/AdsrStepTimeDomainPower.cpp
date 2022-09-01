#include "AdsrStepTimeDomainPower.h"
#include "../RangeUtils.h"

namespace RtAudioNs
{
  namespace Components
  {

    double AdsrStepTimeDomainPower::rescalePower(const double signedFromZeroToOne)
    {
      double scaled = rescaleRange(abs(signedFromZeroToOne), 0, 1, 1, maxCurvePower);
      if (signedFromZeroToOne < 0)
      {
        return 1.0 / scaled;
      }
      return scaled;
    }

    double AdsrStepTimeDomainPower::getPowSignedZerowToOne(const double val)
    {
      return pow((double)position * (1.0 / (double)totalFramesLen), rescalePower(val));
    }

  }}