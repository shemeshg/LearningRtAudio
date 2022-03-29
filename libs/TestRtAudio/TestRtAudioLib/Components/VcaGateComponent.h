#pragma once
#include <vector>
namespace RtAudioNs
{
  namespace Components
  {

    void vcaComponent(std::vector<double> &channelData,
                          std::vector<double> &addVoltageV,
                          std::vector<double> &attinuateMultiplier);

    class VcaContainer
    {
    public:
      float addVoltage = 0;
      float attinuateMultiplier = 1;
    };
  }
}