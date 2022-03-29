#include "VcaGateComponent.h"

namespace RtAudioNs
{
  namespace Components
  {
    void vcaComponent(std::vector<double> &channelData,
                          std::vector<double> &addVoltageV,
                          std::vector<double> &attinuateMultiplier)
    {
      for (unsigned int i = 0; i < channelData.size(); i++)
      {
        channelData[i] = (channelData[i] + addVoltageV[i]) * attinuateMultiplier[i];        
      }
    }


  }}