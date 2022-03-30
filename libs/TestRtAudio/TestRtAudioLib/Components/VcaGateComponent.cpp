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
                       std::vector<double> &gateIn,
                       std::vector<double> &gateThreshold)
    {
      for (unsigned int i = 0; i < channelData.size(); i++)
      {
        channelData[i] = gateIn[i] < gateThreshold[i] ? 0 : channelData[i];
      }
    }

    SnhContainer::SnhContainer(unsigned int frameSize): _frameSize{frameSize},currentState(frameSize,0) {}

    void SnhContainer::render(std::vector<double> &gateIn, std::vector<double> &gateThreshold, std::vector<double> &gateOut){
      for (unsigned int i = 0; i < gateIn.size(); i++){
        if (gateIn[i]>gateThreshold[i]){
          lastVal = gateIn[i];
        }
        gateOut[i]=lastVal;
      }
    }

  }
}