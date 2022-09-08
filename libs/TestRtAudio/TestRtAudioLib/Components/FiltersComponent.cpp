#include "FiltersComponent.h"
#include "RangeUtils.h"
#include <vector>

namespace RtAudioNs
{
  namespace Components
  {

    void FiltersComponent::process_fc(std::vector<double> &channelData, std::vector<double> &fc_vector)
    {
       constexpr  double fromHz=50, toHz=10000;
      for (unsigned int i = 0; i < channelData.size(); i++)
      {
          fc_vector[i] = constrainRange(fc_vector[i], 0.0, 1.0);          
          setFc((int)rescaleRange(fc_vector[i], 0.0, 1.0, fromHz, toHz));
          
          channelData[i] = filter->process(channelData[i]);       
      }
    }
  }
}
