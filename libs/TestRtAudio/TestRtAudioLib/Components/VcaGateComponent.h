#pragma once
#include <vector>
namespace RtAudioNs
{
  namespace Components
  {
    const double gateThreshold = 0.3;

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

    class SnhContainer {
      public:
      std::vector<double> currentState;
      SnhContainer(unsigned int frameSize,double lastVal);
      void render(std::vector<double> &gateIn, std::vector<double> &gateOut);
      private:
        unsigned int _frameSize; 
        double _lastVal=0.0;
    };

    

  }
}