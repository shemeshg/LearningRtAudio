#pragma once
#include <vector>
namespace RtAudioNs
{
  namespace Components
  {
    class SwitchNHoldComponent
    {
      double currentVal = 0;
      SwitchNHoldComponent(){
      }

      void render(std::vector<double> &vIn, std::vector<double> &vOut);

    };
  }
}