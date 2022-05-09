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

      unsigned int totalFramesLen = 44800;
    protected:
      unsigned int position = 0;      
      double getPowSignedZerowToOne(const double val);

    private:
      SimpleAdsrStatus &simpleAdsrStatus, currentStatus, beforeNextStatus;
      double rescalePower(const double signedFromZeroToOne);
      const double maxCurvePower = 5;

    };

  }}