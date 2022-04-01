#pragma once
#include <vector>
#include "GateConstants.h"

namespace RtAudioNs
{
  namespace Components
  {


    void vcaComponent(std::vector<double> &channelData,
                          std::vector<double> &addAmp,
                          std::vector<double> &multAmp);                          

    class VcaContainer
    {
    public:
      float addAmp = 0;
      float multAmp = 1;
    };

    void gateComponent(std::vector<double> &channelData,
                          std::vector<double> &gateIn);                          

    class GateContainer
    {
    public:
      float gateIn = 0;
    };



    

  }
}