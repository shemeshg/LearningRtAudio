#include "SimpleAdsrComponent.h"
#include "GateConstants.h"

namespace RtAudioNs
{
  namespace Components
  {
    double AdsrStep::proccess(bool isReset, unsigned int totalFramesLen)
    {
      if (isReset)
      {
        position = 0;
        resetRetval();
        simpleAdsrStatus = currentStatus;
      }

      if (position >= totalFramesLen)
      {
        simpleAdsrStatus = beforeNextStatus;
      }

      updateReturnVal(totalFramesLen);

      position++;
      return returnVal;
    }

    void SimpleAdsrComponent::render(std::vector<double> &vGate, std::vector<double> &vOut)
    {
      for (unsigned int i = 0; i < vGate.size(); i++)
      {
        if (vGate[i] > gateThreshold)
        {
          if (simpleAdsrStatus == SimpleAdsrStatus::idle || simpleAdsrStatus == SimpleAdsrStatus::r)
          {
            vOut[i] = stepA.proccess(true, 44800);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::a)
          {
            vOut[i] = stepA.proccess(false, 44800);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::beforeD)
          {
            vOut[i] = stepD.proccess(true, 44800);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::d)
          {
            vOut[i] = stepD.proccess(false, 44800);
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
            simpleAdsrStatus == SimpleAdsrStatus::s 
          )
          {
            vOut[i] = stepR.proccess(true, 44800);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::r)
          {
            vOut[i] = stepR.proccess(false, 44800);
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