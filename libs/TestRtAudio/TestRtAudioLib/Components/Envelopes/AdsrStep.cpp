#include "AdsrStep.h"
#include "Components/RangeUtils.h"

namespace RtAudioNs
{
  namespace Components
  {



    double AdsrStep::proccess(bool isReset)
    {
      if (isReset)
      {        
        resetRetval();
        simpleAdsrStatus = currentStatus;
      }

      if ( moveNextStateCondition() )
      {
        simpleAdsrStatus = beforeNextStatus;
      }

      updateReturnVal();

      return returnVal;
    }


  }}