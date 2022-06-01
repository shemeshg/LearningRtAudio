#include "MetronomeComponent.h"
#include "VcaGateComponent.h"

namespace RtAudioNs
{
  namespace Components
  {

    void MetronomeComponent::render(std::vector<double> &channelData){
      std::vector<double> allzero(nBufferFrames, 0);
  
      
      if  (playheadMarker.getMarkerBufferBarNumUpper() == 0) {
        oscSineHi->render(channelData, allzero);
      } else {
        oscSineLow->render(channelData, allzero);
      }

      std::vector<double> playHeadTriggerIn(nBufferFrames, 0);
      std::vector<double> playHeadResetIn(nBufferFrames, 0);
      playheadEvent.render(playHeadTriggerIn, playHeadResetIn);

      std::vector<double> envelopeOutVca(nBufferFrames, 0);
      percussiveEnvelope->render(playHeadTriggerIn, envelopeOutVca);

      Components::vcaComponent(channelData, allzero , envelopeOutVca);

      
      return;
      
    }

  }}