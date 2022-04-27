#pragma once
#include <vector>

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
      double proccess(bool isReset, unsigned int totalFramesLen);
      AdsrStep(SimpleAdsrStatus &_simpleAdsrStatus, SimpleAdsrStatus _currentStatus, SimpleAdsrStatus _beforeNextStatus) : 
        simpleAdsrStatus{_simpleAdsrStatus}, currentStatus{_currentStatus}, beforeNextStatus{_beforeNextStatus} {}

      double returnVal=0;
    private:
      unsigned int position = 0;
      SimpleAdsrStatus &simpleAdsrStatus, currentStatus, beforeNextStatus;
      
    };

    class SimpleAdsrComponent
    {
    public:
      void render(std::vector<double> &vGate, std::vector<double> &vOut);
      SimpleAdsrComponent() : 
      stepA(simpleAdsrStatus, SimpleAdsrStatus::a, SimpleAdsrStatus::beforeD),
      stepD(simpleAdsrStatus, SimpleAdsrStatus::d, SimpleAdsrStatus::s),
      stepR(simpleAdsrStatus, SimpleAdsrStatus::r, SimpleAdsrStatus::idle)
      {
        stepA.returnVal = 0.9;
        stepD.returnVal = 0.7;
        stepR.returnVal = 0.2;
      }

    private:
      SimpleAdsrStatus simpleAdsrStatus = SimpleAdsrStatus::idle;

      AdsrStep stepA, stepD, stepR;

    };
  }
}