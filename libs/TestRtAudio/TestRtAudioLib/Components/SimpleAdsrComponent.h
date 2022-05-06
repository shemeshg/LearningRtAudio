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
      AdsrStep(SimpleAdsrStatus &_simpleAdsrStatus, 
              SimpleAdsrStatus _currentStatus, 
              SimpleAdsrStatus _beforeNextStatus) : 
              simpleAdsrStatus{_simpleAdsrStatus}, 
              currentStatus{_currentStatus}, 
              beforeNextStatus{_beforeNextStatus} {}

      double returnVal = 0;
      virtual void updateReturnVal(unsigned int totalFramesLen) = 0;
      virtual void resetRetval() = 0;

    private:
      unsigned int position = 0;
      SimpleAdsrStatus &simpleAdsrStatus, currentStatus, beforeNextStatus;
    };

    class AdsrStepA : public AdsrStep
    {
    public:
      AdsrStepA(SimpleAdsrStatus &_simpleAdsrStatus, 
                SimpleAdsrStatus _currentStatus, 
                SimpleAdsrStatus _beforeNextStatus) : 
                AdsrStep(_simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}

      void updateReturnVal(unsigned int totalFramesLen)
      {
        returnVal += 1.0/(double)totalFramesLen;
      }
      void resetRetval(){
        returnVal = 0;
      }
    };

    class AdsrStepD : public AdsrStep
    {
    public:
      AdsrStepD(SimpleAdsrStatus &_simpleAdsrStatus, 
                SimpleAdsrStatus _currentStatus, 
                SimpleAdsrStatus _beforeNextStatus) : 
                AdsrStep(_simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}
                
      void updateReturnVal(unsigned int totalFramesLen)
      {
        returnVal -= (1.0-sustainLevel) /(double)totalFramesLen;
      }
      void resetRetval(){
        returnVal = 1;
      }
    private:
      double sustainLevel = 0.7;
    };

    class AdsrStepR : public AdsrStep
    {
    public:
      AdsrStepR(SimpleAdsrStatus &_simpleAdsrStatus, 
                SimpleAdsrStatus _currentStatus, 
                SimpleAdsrStatus _beforeNextStatus) : 
                AdsrStep(_simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}
                
      void updateReturnVal(unsigned int totalFramesLen)
      {
        if (returnVal > 0) {
          returnVal -= (sustainLevel) /(double)totalFramesLen;
        } else {
          returnVal = 0;
        }
        
      }
      void resetRetval(){
        //returnVal = sustainLevel;
      }
    private:
      double sustainLevel = 0.7;
    };

    class SimpleAdsrComponent
    {
    public:
      void render(std::vector<double> &vGate, std::vector<double> &vOut);
      SimpleAdsrComponent() : stepA(simpleAdsrStatus, SimpleAdsrStatus::a, SimpleAdsrStatus::beforeD),
                              stepD(simpleAdsrStatus, SimpleAdsrStatus::d, SimpleAdsrStatus::s),
                              stepR(simpleAdsrStatus, SimpleAdsrStatus::r, SimpleAdsrStatus::idle)
      {

      }

    private:
      SimpleAdsrStatus simpleAdsrStatus = SimpleAdsrStatus::idle;

      AdsrStepA stepA;
      AdsrStepD stepD;
      AdsrStepR stepR;
    };
  }
}