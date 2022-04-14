#include "PlayheadMarker.h"

namespace RtAudioNs
{
  namespace Components
  {
    PlayheadMarker::PlayheadMarker(unsigned int _sampleRate, unsigned int _nBufferFrames) : sampleRate(_sampleRate), nBufferFrames(_nBufferFrames)
    {
    }

    void PlayheadEvent::render(std::vector<double> &triggerIn, std::vector<double> &triggerResetIn)
    {
      for (unsigned int i = 0; i < triggerIn.size(); i++)
      {

        if ((markerBufferFrames - frameStart) > 0  && 
            ((markerBufferFrames - frameStart) % framesEvery == 0) &&
            (repeatCount > 0 || repeatCount == -1))
        {
          triggerResetIn[i] = 1;
          framesRemainedToPLay = framesLen;
          if (repeatCount > 0){repeatCount--;}
        } else {
          triggerResetIn[i] = 0;
        }

        if (framesRemainedToPLay > 0)
        {
          triggerIn[i] = 1;
          framesRemainedToPLay--;
        }
        else
        {
          triggerIn[i] = 0;
        }

        markerBufferFrames++;
      }
    }
  }
}