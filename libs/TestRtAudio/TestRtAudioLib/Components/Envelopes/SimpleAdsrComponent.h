#pragma once
#include <vector>
#include <cmath>
#include "AdsrStepTimeDomainPower.h"
#include "AdsrRender.h"

namespace RtAudioNs
{
  namespace Components
  {
    class AdsrStepA : public AdsrStepTimeDomainPower
    {
    public:
      AdsrStepA(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : 
            AdsrStepTimeDomainPower(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus),
            returnVal{_returnVal} {}

      void updateReturnVal()
      {
        returnVal = getPowSignedZerowToOne(lineCurved);
        position++;
      }
      void resetRetval()
      {
        position = 0;
        returnVal = 0;
      }
      bool moveNextStateCondition() {
        return position >= totalFramesLen;
      }
      double lineCurved = 0;

      private:
        double &returnVal;
    };

    class AdsrStepD : public AdsrStepTimeDomainPower
    {
    public:
      AdsrStepD(
          double &_sustainLevel,
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStepTimeDomainPower(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus),
                                                sustainLevel{_sustainLevel},
                                                returnVal{_returnVal}  {}

      void updateReturnVal()
      {
        returnVal = (1.0 - sustainLevel) * (1.0 - getPowSignedZerowToOne(lineCurved)) + sustainLevel;
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
      double lineCurved = 0;
    private:
      double &sustainLevel;
      double &returnVal;
    };

    class AdsrStepR : public AdsrStepTimeDomainPower
    {
    public:
      AdsrStepR(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : 
            AdsrStepTimeDomainPower(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus),
            returnVal{_returnVal}  {}

      void updateReturnVal()
      {
        if (returnVal > 0)
        {
          returnVal = sustainLevel * (1.0 - getPowSignedZerowToOne(lineCurved));
        }
        else
        {
          returnVal = 0;
        }
        position++;
      }
      void resetRetval()
      {
        position = 0;
        sustainLevel = returnVal;
      }
      bool moveNextStateCondition() {
        return position >= totalFramesLen;
      }

      double lineCurved = 0; 

    private:
      double sustainLevel = 0;
      double &returnVal;
    };

    class SimpleAdsrComponent
    {
    public:
      void render(std::vector<double> &vGate, std::vector<double> &vOut);
      SimpleAdsrComponent() : stepA(returnVal, simpleAdsrStatus, SimpleAdsrStatus::a, SimpleAdsrStatus::beforeD),
                              stepD(sustainLevel, returnVal, simpleAdsrStatus, SimpleAdsrStatus::d, SimpleAdsrStatus::s),
                              stepR(returnVal, simpleAdsrStatus, SimpleAdsrStatus::r, SimpleAdsrStatus::idle),
                              adsrRender(stepA, stepD, stepR, sustainLevel, simpleAdsrStatus)
      {
        stepA.lineCurved = 0.2; //This is zero to one, see in header constant 5 as max power.
        stepD.lineCurved = - 0.2;
        stepR.lineCurved = 0.4;
        stepA.totalFramesLen = 44800; //This is the buffer len(time)
        stepD.totalFramesLen = 44800;
        stepR.totalFramesLen = 44800;
      }

      double sustainLevel = 0.7;
      AdsrRender adsrRender;
    private:
      double returnVal = 0;

      SimpleAdsrStatus simpleAdsrStatus = SimpleAdsrStatus::idle;

      

      AdsrStepA stepA;
      AdsrStepD stepD;
      AdsrStepR stepR;
    };
  }
}