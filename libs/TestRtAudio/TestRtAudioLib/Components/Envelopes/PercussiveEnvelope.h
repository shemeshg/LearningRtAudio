#pragma once
#include <vector>
#include "AdsrStepTimeDomainPower.h"

namespace RtAudioNs
{
  namespace Components
  {

    class AdsrStepPrecussiveR : public AdsrStepTimeDomainPower
    {
    public:
      AdsrStepPrecussiveR(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : 
                AdsrStepTimeDomainPower(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus),
                returnVal{_returnVal}
                           {}

      void updateReturnVal()
      {
        returnVal = returnVal * pow(0.01, (1.0 / (double)totalFramesLen));
        position++;
      }
      void resetRetval()
      {
        position = 0;
        returnVal = 1;
      }

      bool moveNextStateCondition() {
        return position >= totalFramesLen;
      }

      private:
        double &returnVal;
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