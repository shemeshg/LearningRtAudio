#pragma once
#include <cmath>

namespace RtAudioNs
{
  namespace Components
  {
    enum SimpleAdsrStatus
    {
      idle,
      a,
      beforeD,
      d,
      s,
      r
    };

    class AdsrStep
    {
    public:
      double proccess(bool isReset);
      AdsrStep(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : returnVal{_returnVal},
                                                simpleAdsrStatus{_simpleAdsrStatus},
                                                currentStatus{_currentStatus},
                                                beforeNextStatus{_beforeNextStatus} {}

      double &returnVal;
      virtual void updateReturnVal() = 0;
      virtual void resetRetval() = 0;
      virtual bool moveNextStateCondition() = 0;
      


    private:
      SimpleAdsrStatus &simpleAdsrStatus, currentStatus, beforeNextStatus;


    };

  }}