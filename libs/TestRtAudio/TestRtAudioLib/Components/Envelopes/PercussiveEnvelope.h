#pragma once
#include <vector>
#include "AdsrStep.h"

namespace RtAudioNs
{
  namespace Components
  {

    class AdsrStepPrecussiveR : public AdsrStep
    {
    public:
      AdsrStepPrecussiveR(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStep(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}

      void updateReturnVal()
      {
        returnVal = returnVal * pow(0.01, (1.0 / (double)totalFramesLen));
      }
      void resetRetval()
      {
        returnVal = 1;
      }
    };

    class PercussiveEnvelope
    {

    public:
      void render(std::vector<double> &vGate, std::vector<double> &vOut);
      PercussiveEnvelope() : stepR(returnVal, simpleAdsrStatus, SimpleAdsrStatus::r, SimpleAdsrStatus::idle)
      {
      }

    private:
      double returnVal = 1;

      SimpleAdsrStatus simpleAdsrStatus = SimpleAdsrStatus::idle;

      AdsrStepPrecussiveR stepR;
      bool triggerReleased = true;
    };
  }

}