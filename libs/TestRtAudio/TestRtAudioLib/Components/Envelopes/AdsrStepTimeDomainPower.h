#pragma once
#include "AdsrStep.h"

namespace RtAudioNs
{
  namespace Components
  {
    class AdsrStepTimeDomainPower: public AdsrStep {
      public:
        AdsrStepTimeDomainPower(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStep(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}

          unsigned int totalFramesLen = 44800;
      protected:

        unsigned int position = 0;      
        double getPowSignedZerowToOne(const double val);

      private:
        double rescalePower(const double signedFromZeroToOne);
        const double maxCurvePower = 5;
    };
  }}