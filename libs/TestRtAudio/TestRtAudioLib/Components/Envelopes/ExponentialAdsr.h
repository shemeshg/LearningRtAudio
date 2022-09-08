#pragma once
#include <vector>
#include <cmath>
#include "AdsrStep.h"
#include "AdsrRender.h"

namespace RtAudioNs
{
  namespace Components
  {

    class AdsrStepExp : public AdsrStep
    {
    public:
      AdsrStepExp(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStep(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}

    protected:
      void rampToMultiplier(double currentVal, double targetValue, double overshootRatio,
                              double time, double sampeRate)
      {
        _currentVal = currentVal;
        double distanceToTarget = targetValue - currentVal;
        asymptote = currentVal + distanceToTarget * overshootRatio;
        expVal = currentVal - asymptote;

        double tou = -1.0 * time / log(1.0 - 1.0 / overshootRatio);

        multiplier = pow(exp(-1.0 / tou), 1.0 / sampeRate);
      }

      double incrementCurrentVal()
      {
        _currentVal = asymptote + expVal;
        return _currentVal;
      }

      void incrementExpVal()
      {
        expVal = expVal * multiplier;        
      }

    private:
      double expVal = 0 ;
      double multiplier = 0;
      double asymptote = 0;
      double _currentVal = 0;
    };

    namespace  {
    constexpr double AcurrentVal=0;
    constexpr double AtargetValue = 0.8;
    constexpr double AovershootRatio=1.01;
    constexpr double Atime=2.0;
    constexpr double sampeRate = 48800;

    constexpr double DcurrentVal=0.8;
    constexpr double DovershootRatio=1.1;
    constexpr double Dtime=1.0;

    constexpr double RtargetValue = 0;
    constexpr double RovershootRatio=1.1;
    constexpr double Rtime=1.0;

    constexpr double AdsrSustainLevel = 0.7;
    };

    class EAdsrStepA : public AdsrStepExp
    {
    public:
      EAdsrStepA(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStepExp(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus) {
          }

      void updateReturnVal() override
      {
        double &returnVal = getReturnVal();
        returnVal = incrementCurrentVal();         
        incrementExpVal();
      }
      void resetRetval() override
      {
        double &returnVal = getReturnVal();
        rampToMultiplier(AcurrentVal, AtargetValue, AovershootRatio, Atime, sampeRate);
        returnVal = 0;
      }
      bool moveNextStateCondition() override
      {
        double &returnVal = getReturnVal();
        return returnVal >= AtargetValue;
      }

    };

    class EAdsrStepD : public AdsrStepExp
    {
    public:
      EAdsrStepD(
          double &_sustainLevel,
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStepExp(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus),
                                                sustainLevel{_sustainLevel} {}

      void updateReturnVal() override
      {
        double &returnVal = getReturnVal();
        returnVal = incrementCurrentVal();
        incrementExpVal();
      }
      void resetRetval() override
      {
        double &returnVal = getReturnVal();
        returnVal = DcurrentVal;
        rampToMultiplier(DcurrentVal, sustainLevel, DovershootRatio, Dtime, sampeRate);
      }
      bool moveNextStateCondition() override
      {
        double &returnVal = getReturnVal();
        return returnVal <= sustainLevel;
      }

    private:
      double &sustainLevel;
    };

    class EAdsrStepR : public AdsrStepExp
    {
    public:
      EAdsrStepR(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStepExp(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus){}

      void updateReturnVal() override
      {
        double &returnVal = getReturnVal();
        if (returnVal > 0)
        {
          returnVal = incrementCurrentVal();
          incrementExpVal();
        }
        else
        {
          returnVal = 0;
        }
      }
      void resetRetval() override
      {
        double &returnVal = getReturnVal();
        sustainLevel = returnVal;
        rampToMultiplier(sustainLevel, RtargetValue, RovershootRatio, Rtime, sampeRate);
      }
      bool moveNextStateCondition() override
      {
        double &returnVal = getReturnVal();
        return returnVal == 0;
      }

    private:
      double sustainLevel = 0;
    };

    class ExponentialAdsr
    {
    public:
      ExponentialAdsr() : adsrRender(stepA, stepD, stepR, sustainLevel, simpleAdsrStatus),
                          stepA(returnVal, simpleAdsrStatus, SimpleAdsrStatus::a, SimpleAdsrStatus::beforeD),
                          stepD(sustainLevel, returnVal, simpleAdsrStatus, SimpleAdsrStatus::d, SimpleAdsrStatus::s),
                          stepR(returnVal, simpleAdsrStatus, SimpleAdsrStatus::r, SimpleAdsrStatus::idle)
      {
      }

      AdsrRender adsrRender;

    protected:
      double sustainLevel = AdsrSustainLevel;

    private:
      double returnVal = 0;

      SimpleAdsrStatus simpleAdsrStatus = SimpleAdsrStatus::idle;

      EAdsrStepA stepA;
      EAdsrStepD stepD;
      EAdsrStepR stepR;
    };
  }
}
