#pragma once
#include <vector>
#include <cmath>
#include "AdsrStep.h"
#include "AdsrRender.h"

namespace RtAudioNs
{
  namespace Components
  {
    class LAdsrStepA : public AdsrStep
    {
    public:
      LAdsrStepA(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStep(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}

      void updateReturnVal() override
      {
        double &returnVal = getReturnVal();
        returnVal = returnVal + incrementStep;
      }
      void resetRetval() override
      {
        double &returnVal = getReturnVal();
        returnVal = 0;
      }
      bool moveNextStateCondition() override
      {
        double &returnVal = getReturnVal();
        return returnVal >= maxAStepLevel;
      }
      

    private:
      const double incrementStep = 0.00002;
      const double maxAStepLevel = 0.8;

    };

    class LAdsrStepD : public AdsrStep
    {
    public:
      LAdsrStepD(
          double &_sustainLevel,
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStep(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus),
                                                sustainLevel{_sustainLevel} {}

      void updateReturnVal() override
      {
        double &returnVal = getReturnVal();
        returnVal = returnVal + incrementStep;
      }
      void resetRetval() override
      {
        double &returnVal = getReturnVal();
        returnVal = 1;
      }
      bool moveNextStateCondition() override
      {
        double &returnVal = getReturnVal();
        return returnVal <= sustainLevel;
      }

      double incrementStep = -0.0002;

    private:
      double &sustainLevel;
    };

    class LAdsrStepR : public AdsrStep
    {
    public:
      LAdsrStepR(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) :  AdsrStep(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}

      void updateReturnVal() override
      {
        double &returnVal = getReturnVal();
        if (returnVal > 0)
        {
          returnVal = returnVal + incrementStep;
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
      }
      bool moveNextStateCondition() override
      {
        double &returnVal = getReturnVal();
        return returnVal == 0;
      }

      double incrementStep = -0.0002;

    private:
      double sustainLevel = 0;
    };

    class LinearAdsrComponent
    {
    public:
      LinearAdsrComponent() : stepA(returnVal, simpleAdsrStatus, SimpleAdsrStatus::a, SimpleAdsrStatus::beforeD),
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

      LAdsrStepA stepA;
      LAdsrStepD stepD;
      LAdsrStepR stepR;
    };
  }
}