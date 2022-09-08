#pragma once
#include <vector>
namespace RtAudioNs
{
  namespace Components
  {
    // Switch between inputs(vector of vector) on every trigger of
    // render(std::vector<double> &vTriggerNext
    class SwitchAmpComponent
    {


    public:
      SwitchAmpComponent()
      {
      }

      void render(std::vector<double> &vTriggerNext, std::vector<double> &vOut);

     std::vector<std::vector<double>> &getOutVals(){
      return outVals;
     }

    private:
      std::vector<std::vector<double>> outVals;
      unsigned int currentValIdx = 0;
      enum SwitchStatus
      {
        on_stop,
        on_start
      };
      SwitchStatus switchStatus = on_stop;      
    };
  }
}