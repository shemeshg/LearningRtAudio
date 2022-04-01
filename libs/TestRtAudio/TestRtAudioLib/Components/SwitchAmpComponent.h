#pragma once
#include <vector>
namespace RtAudioNs
{
  namespace Components
  {
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

      void render(std::vector<double> &vIn, std::vector<double> &vOut);
    };
  }
}