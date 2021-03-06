#include "SwitchNHoldComponent.h"
#include "GateConstants.h"

namespace RtAudioNs
{
  namespace Components
  {
    void SwitchNHoldComponent::render(std::vector<double> &vIn, std::vector<double> &vTrigger, std::vector<double> &vOut){
      for (unsigned int i = 0; i < vIn.size(); i++){
        if (vTrigger[i] > gateThreshold){currentVal = vIn[i];}
        vOut[i]=currentVal;
      }
    }
  }}