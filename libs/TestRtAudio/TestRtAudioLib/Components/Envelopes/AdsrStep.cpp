#include "AdsrStep.h"
#include "Components/RangeUtils.h"

namespace RtAudioNs
{
  namespace Components
  {

    double AdsrStep::rescalePower(const double signedFromZeroToOne)
    {
      double scaled = rescaleRange(abs(signedFromZeroToOne), 0, 1, 1, maxCurvePower);
      if (signedFromZeroToOne < 0)
      {
        return 1.0 / scaled;
      }
      return scaled;
    }

    double AdsrStep::getPowSignedZerowToOne(const double val)
    {
      return pow((double)position * (1.0 / (double)totalFramesLen), rescalePower(val));
    }

    double AdsrStep::proccess(bool isReset)
    {
      if (isReset)
      {
        position = 0;
        resetRetval();
        simpleAdsrStatus = currentStatus;
      }

      if (position >= totalFramesLen)
      {
        simpleAdsrStatus = beforeNextStatus;
      }

      updateReturnVal();

      position++;
      return returnVal;
    }


  }}