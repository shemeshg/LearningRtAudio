#include "SwitchNHoldComponent.h"

namespace RtAudioNs
{
  namespace Components
  {
    void SwitchAmpComponent::render(std::vector<double> &vIn, std::vector<double> &vOut){
      for (unsigned int i = 0; i < vIn.size(); i++){
        if (vIn[i] > gateThreshold){currentVal = vIn[i];}
        vOut[i]=currentVal;
      }
  }}