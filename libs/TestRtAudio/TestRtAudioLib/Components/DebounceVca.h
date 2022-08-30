#pragma once
#include <vector>

namespace RtAudioNs
{
  namespace Components
  {
    class DebounceVca
    {
    public:
      void process(std::vector<double> &channelData, std::vector<double> &out_vector);

      double noiseAmount = 0.05;
      int keepStateConst = 1000;
    private:
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