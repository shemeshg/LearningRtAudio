#pragma once
#include "AdsrStep.h"

namespace RtAudioNs
{
  namespace Components
  {
    class AdsrStepTimeDomainPower: public AdsrStep {
      public:
        AdsrStepTimeDomainPower(
          double &_returnVal,
          SimpleAdsrStatus &_simpleAdsrStatus,
          SimpleAdsrStatus _currentStatus,
          SimpleAdsrStatus _beforeNextStatus) : AdsrStep(_returnVal, _simpleAdsrStatus, _currentStatus, _beforeNextStatus) {}

           
      protected:
        unsigned int getTotalFramesLen(){
          return totalFramesLen;
        }

        unsigned int &getPosition(){
          return position;
        } 

        double getPowSignedZerowToOne(const double val);
        
      private:
        unsigned int position = 0; 
        const unsigned int totalFramesLen = 44800;
        
        double rescalePower(const double signedFromZeroToOne);
        const double maxCurvePower = 5;
    };
  }}