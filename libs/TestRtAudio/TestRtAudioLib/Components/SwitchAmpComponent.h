#pragma once
#include <vector>
namespace RtAudioNs
{
  namespace Components
  {
    // Switch between inputs(vector of vector) on every trigger of 
    // render(std::vector<double> &vTriggerNext
    class SwitchAmpComponent
    {
      enum SwitchStatus
      {
        on_stop,
        on_start
      };
      SwitchStatus switchStatus = on_stop;

    public:
      std::vector<std::vector<double>> outVals;
      unsigned int currentValIdx = 0;
      SwitchAmpComponent()
      {
      }

      void render(std::vector<double> &vTriggerNext, std::vector<double> &vOut);
    };
  }
}