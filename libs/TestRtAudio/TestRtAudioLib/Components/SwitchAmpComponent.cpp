#include "SwitchAmpComponent.h"
#include "GateConstants.h"
#include <iostream>
namespace RtAudioNs
{
  namespace Components
  {

    void SwitchAmpComponent::render(std::vector<double> &vTriggerNext, std::vector<double> &vOut){
      for (unsigned int i = 0; i < vTriggerNext.size(); i++){
        if (switchStatus==on_stop && vTriggerNext[i] > gateThreshold){
          currentValIdx++;
          switchStatus=on_start;
          if (currentValIdx == outVals.size()){currentValIdx = 0;}
        } else if  (switchStatus==on_start && vTriggerNext[i] < gateThreshold){
          switchStatus=on_stop;
        } 
        vOut[i] = outVals[currentValIdx][i];
      }
    }
  }
}