#pragma once
#include <vector>
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
      double proccess(bool isReset, unsigned int totalFramesLen);
      AdsrStep(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : returnVal{_returnVal},
                                                simpleAdsrStatus{_simpleAdsrStatus},
                                                currentStatus{_currentStatus},
                                                beforeNextStatus{_beforeNextStatus} {}

      double &returnVal;
      virtual void updateReturnVal(unsigned int totalFramesLen) = 0;
      virtual void resetRetval() = 0;

    protected:
      unsigned int position = 0;      
      double getPowSignedZerowToOne(const double val, const unsigned int totalFramesLen);

    private:
      SimpleAdsrStatus &simpleAdsrStatus, currentStatus, beforeNextStatus;
      double rescalePower(const double signedFromZeroToOne);
      const double maxCurvePower = 5;

    };

    class AdsrStepA : public AdsrStep
    {
    public:
      AdsrStepA(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStep(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}

      void updateReturnVal(unsigned int totalFramesLen)
      {
        returnVal = getPowSignedZerowToOne(0.2, totalFramesLen);
      }
      void resetRetval()
      {
        returnVal = 0;
      }
    };

    class AdsrStepD : public AdsrStep
    {
    public:
      AdsrStepD(
          double &_sustainLevel,
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStep(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus),
                                                sustainLevel{_sustainLevel} {}

      void updateReturnVal(unsigned int totalFramesLen)
      {
        // returnVal -= (1.0 - sustainLevel) / (double)totalFramesLen;
        returnVal = (1.0 - sustainLevel) * (1.0 - getPowSignedZerowToOne(-0.2, totalFramesLen)) + sustainLevel;
      }
      void resetRetval()
      {
        returnVal = 1;
      }

    private:
      double &sustainLevel;
    };

    class AdsrStepR : public AdsrStep
    {
    public:
      AdsrStepR(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStep(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}

      void updateReturnVal(unsigned int totalFramesLen)
      {
        if (returnVal > 0)
        {
          returnVal = sustainLevel * (1.0 - getPowSignedZerowToOne(0.2, totalFramesLen));
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

    private:
      double sustainLevel = 0;
    };

    class SimpleAdsrComponent
    {
    public:
      void render(std::vector<double> &vGate, std::vector<double> &vOut);
      SimpleAdsrComponent() : stepA(returnVal, simpleAdsrStatus, SimpleAdsrStatus::a, SimpleAdsrStatus::beforeD),
                              stepD(sustainLevel, returnVal, simpleAdsrStatus, SimpleAdsrStatus::d, SimpleAdsrStatus::s),
                              stepR(returnVal, simpleAdsrStatus, SimpleAdsrStatus::r, SimpleAdsrStatus::idle)
      {
      }

      double sustainLevel = 0.7;

    private:
      double returnVal = 0;

      SimpleAdsrStatus simpleAdsrStatus = SimpleAdsrStatus::idle;

      AdsrStepA stepA;
      AdsrStepD stepD;
      AdsrStepR stepR;
    };
  }
}