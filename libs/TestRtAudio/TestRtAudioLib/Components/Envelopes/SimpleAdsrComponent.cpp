#include "SimpleAdsrComponent.h"
#include "Components/GateConstants.h"


namespace RtAudioNs
{
  namespace Components
  {


    void SimpleAdsrComponent::render(std::vector<double> &vGate, std::vector<double> &vOut)
    {
      stepA.lineCurved = 0.2; //This is zero to one, see in header constant 5 as max power.
      stepD.lineCurved = - 0.2;
      stepR.lineCurved = 0.4;


      for (unsigned int i = 0; i < vGate.size(); i++)
      {
        if (vGate[i] > gateThreshold)
        {
          if (simpleAdsrStatus == SimpleAdsrStatus::idle || simpleAdsrStatus == SimpleAdsrStatus::r)
          {
            vOut[i] = stepA.proccess(true);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::a)
          {
            vOut[i] = stepA.proccess(false);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::beforeD)
          {
            vOut[i] = stepD.proccess(true);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::d)
          {
            vOut[i] = stepD.proccess(false);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::s)
          {
            vOut[i] = sustainLevel;
          }
        }
        else
        {
          if (simpleAdsrStatus == SimpleAdsrStatus::a ||
              simpleAdsrStatus == SimpleAdsrStatus::beforeD ||
              simpleAdsrStatus == SimpleAdsrStatus::d ||
              simpleAdsrStatus == SimpleAdsrStatus::s)
          {
            vOut[i] = stepR.proccess(true);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::r)
          {
            vOut[i] = stepR.proccess(false);
          }
          else
          {
            simpleAdsrStatus = SimpleAdsrStatus::idle;
            vOut[i] = 0;
          }
        }
      }
    }

  }
}