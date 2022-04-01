#pragma once
#include <vector>
namespace RtAudioNs
{
  namespace Components
  {
    class SwitchNHoldComponent
    {
      double currentVal = 0;
      SwitchAmpComponent(){
      }

      void render(std::vector<double> &vIn, std::vector<double> &vOut);

    }
  }
}