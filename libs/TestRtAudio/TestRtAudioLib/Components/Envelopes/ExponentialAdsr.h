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

    class EAdsrStepA : public AdsrStepExp
    {
    public:
      EAdsrStepA(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : returnVal{_returnVal},AdsrStepExp(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus) {
          }

      void updateReturnVal()
      {
        returnVal = incrementCurrentVal();         
        incrementExpVal();
      }
      void resetRetval()
      {
        rampToMultiplier(0, 0.8, 1.01, 2.0, 48800);
        returnVal = 0;
      }
      bool moveNextStateCondition()
      {
        return returnVal >= 0.8;
      }

      private:
        double &returnVal;
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
                                                returnVal{_returnVal},
                                                sustainLevel{_sustainLevel} {}

      void updateReturnVal()
      {
        returnVal = incrementCurrentVal();
        incrementExpVal();
      }
      void resetRetval()
      {
        returnVal = 0.8;
        rampToMultiplier(0.8, sustainLevel, 1.1, 1, 48800);
      }
      bool moveNextStateCondition()
      {
        return returnVal <= sustainLevel;
      }

    private:
      double &sustainLevel;
      double &returnVal;

    };

    class EAdsrStepR : public AdsrStepExp
    {
    public:
      EAdsrStepR(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStepExp(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus),
                                                returnVal{_returnVal} {}

      void updateReturnVal()
      {
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
      void resetRetval()
      {
        sustainLevel = returnVal;
        rampToMultiplier(sustainLevel, 0, 1.1, 1, 48800);
      }
      bool moveNextStateCondition()
      {
        return returnVal == 0;
      }

    private:
      double sustainLevel = 0;
      double &returnVal;
    };

    class ExponentialAdsr
    {
    public:
      ExponentialAdsr() : stepA(returnVal, simpleAdsrStatus, SimpleAdsrStatus::a, SimpleAdsrStatus::beforeD),
                          stepD(sustainLevel, returnVal, simpleAdsrStatus, SimpleAdsrStatus::d, SimpleAdsrStatus::s),
                          stepR(returnVal, simpleAdsrStatus, SimpleAdsrStatus::r, SimpleAdsrStatus::idle),
                          adsrRender(stepA, stepD, stepR, sustainLevel, simpleAdsrStatus)
      {
      }

      AdsrRender adsrRender;

    protected:
      double sustainLevel = 0.7;

    private:
      double returnVal = 0;

      SimpleAdsrStatus simpleAdsrStatus = SimpleAdsrStatus::idle;

      EAdsrStepA stepA;
      EAdsrStepD stepD;
      EAdsrStepR stepR;
    };
  }
}