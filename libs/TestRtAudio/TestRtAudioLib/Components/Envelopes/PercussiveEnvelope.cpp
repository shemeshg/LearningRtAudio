#include "PercussiveEnvelope.h"
#include "Components/GateConstants.h"
#include <iostream>

namespace RtAudioNs
{
  namespace Components
  {

    void PercussiveEnvelope::render(std::vector<double> &vGate, std::vector<double> &vOut)
    {
      

      for (unsigned int i = 0; i < vGate.size(); i++)
      {

        if (vGate[i] > gateThreshold)
        {
          if (triggerReleased)
          {

            vOut[i] = stepR.proccess(true);
            triggerReleased = false;
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::r)
          {
            vOut[i] = stepR.proccess(false);
          }
        }
        else
        {
          triggerReleased = true;
          if (simpleAdsrStatus == SimpleAdsrStatus::r)
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