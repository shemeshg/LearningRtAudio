#include "PlayheadMarker.h"

namespace RtAudioNs
{
  namespace Components
  {
    PlayheadMarker::PlayheadMarker(unsigned int _sampleRate, unsigned int _nBufferFrames) : sampleRate(_sampleRate), nBufferFrames(_nBufferFrames)
    {
    }

  }
}