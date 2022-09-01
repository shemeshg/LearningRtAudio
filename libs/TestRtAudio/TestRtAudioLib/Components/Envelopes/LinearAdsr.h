#pragma once
#include <vector>
#include <cmath>
#include "AdsrStep.h"

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

      void updateReturnVal()
      {
        returnVal = returnVal + incrementStep;
      }
      void resetRetval()
      {
        returnVal = 0;
      }
      bool moveNextStateCondition()
      {
        return returnVal == 1;
      }
      double incrementStep = 0.02;
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

      void updateReturnVal()
      {
        returnVal = returnVal + incrementStep;
      }
      void resetRetval()
      {
        returnVal = 1;
      }
      bool moveNextStateCondition()
      {
        return returnVal == sustainLevel;
      }
      
      double incrementStep = -0.02;
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
          SimpleAdsrStatus _beforeNextStatus) : AdsrStep(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}

      void updateReturnVal()
      {
        if (returnVal > 0)
        {
          returnVal = returnVal + incrementStep;
        }
        else
        {
          returnVal = 0;
        }

      }
      void resetRetval()
      {
        sustainLevel = returnVal;
      }
      bool moveNextStateCondition()
      {
        return returnVal == 0;
      }

      double incrementStep = -0.02;
      

    private:
      double sustainLevel = 0;
    };

    
    class LinearAdsrComponent
    {
    public:
      void render(std::vector<double> &vGate, std::vector<double> &vOut);
      LinearAdsrComponent() : stepA(returnVal, simpleAdsrStatus, SimpleAdsrStatus::a, SimpleAdsrStatus::beforeD),
                              stepD(sustainLevel, returnVal, simpleAdsrStatus, SimpleAdsrStatus::d, SimpleAdsrStatus::s),
                              stepR(returnVal, simpleAdsrStatus, SimpleAdsrStatus::r, SimpleAdsrStatus::idle)
      {
      }

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