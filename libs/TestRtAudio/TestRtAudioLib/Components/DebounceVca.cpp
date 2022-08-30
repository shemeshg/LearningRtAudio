#include "DebounceVca.h"
namespace RtAudioNs
{
  namespace Components
  {
    void DebounceVca::process(std::vector<double> &channelData, std::vector<double> &out_vector)
    {
      
      static int keepStateForCounter = keepStateConst;
      for (unsigned int i = 0; i < channelData.size(); i++)
      {
        if (keepStateForCounter != 0)
        {
          keepStateForCounter--;
        };

        if (channelData[i] > currentVal + noiseAmount)
        {
          if (keepStateForCounter == 0 && _moveTo != MOVE_TO::UP)
          {
            _moveTo = MOVE_TO::UP;
          }
        }
        else if (channelData[i] < (currentVal - noiseAmount))
        {
          if (keepStateForCounter == 0 && _moveTo != MOVE_TO::DOWN)
          {
            _moveTo = MOVE_TO::DOWN;
          }
        }


        if (_moveTo == MOVE_TO::UP || _moveTo == MOVE_TO::DOWN)
        {
          currentVal = channelData[i];
          _moveTo = MOVE_TO::UNCHANGED;
          keepStateForCounter = keepStateConst;          
        }
        out_vector[i] = currentVal;
      }
    }
  }
}