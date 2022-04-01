#include "VcaGateComponent.h"

namespace RtAudioNs
{
  namespace Components
  {
    void vcaComponent(std::vector<double> &channelData,
                      std::vector<double> &addAmp,
                      std::vector<double> &multAmp)
    {
      for (unsigned int i = 0; i < channelData.size(); i++)
      {
        channelData[i] = (channelData[i] + addAmp[i]) * multAmp[i];
      }
    }

    void gateComponent(std::vector<double> &channelData,
                       std::vector<double> &gateIn)
    {
      for (unsigned int i = 0; i < channelData.size(); i++)
      {
        channelData[i] = gateIn[i] < gateThreshold ? 0 : channelData[i];
      }
    }


  }
}