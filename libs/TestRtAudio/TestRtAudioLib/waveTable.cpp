#include "waveTable.h"
#include "WaveTableCallback.h"


int waveTable(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
              double streamTime, RtAudioStreamStatus status, void *userData)
{

  RtAudioNs::RtWaveTableCallback *userDataCasted = static_cast<RtAudioNs::RtWaveTableCallback *>(userData);
  return userDataCasted->render(outputBuffer, inputBuffer, nBufferFrames, streamTime, status);
}
