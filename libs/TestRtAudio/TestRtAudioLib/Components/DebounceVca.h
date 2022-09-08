#pragma once
#include <vector>

namespace {
  constexpr double defautlNoiseAmount = 0.05;
  constexpr int defaultKeepStateConst = 1000; 

}

namespace RtAudioNs
{
  namespace Components
  {
    class DebounceVca
    {
    public:
      void process(std::vector<double> &channelData, std::vector<double> &out_vector);
   
    private:
      double noiseAmount = defautlNoiseAmount;
      int keepStateConst = defaultKeepStateConst; 
      
      enum MOVE_TO
      {
        UP,
        DOWN,
        UNCHANGED
      };
      double currentVal=0;

      MOVE_TO _moveTo = MOVE_TO::UNCHANGED;
    };
  }
}