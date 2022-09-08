#pragma once
#include <vector>
#include "AdsrStep.h"

namespace RtAudioNs
{
  namespace Components
  {

    class AdsrRender
    {
    public:
      AdsrRender(AdsrStep &stepA, AdsrStep &stepD, AdsrStep &stepR, 
        double &sustainLevel, SimpleAdsrStatus &simpleAdsrStatus) : stepA{stepA}, stepD{stepD}, stepR{stepR}, sustainLevel{sustainLevel}, simpleAdsrStatus{simpleAdsrStatus}
      {
      }
      void render(std::vector<double> &vGate, std::vector<double> &vOut);

    private:
      double &sustainLevel;
      SimpleAdsrStatus &simpleAdsrStatus;
      AdsrStep &stepA;
      AdsrStep &stepD;
      AdsrStep &stepR;
    };

  }}