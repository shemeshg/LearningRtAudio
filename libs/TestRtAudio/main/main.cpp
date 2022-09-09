#include <iostream>
#include "TestRtAudio.h"


int main()
{
  // TestRtAudio::coutListApis();
  RtAudioNs::TestRtAudio tra;
  tra.coutDevicesInfo();
  const int outDev=2,inDev=2, bufferFrames=1024;
  tra.setupStreamParameters(outDev, inDev, bufferFrames);
  tra.rtWaveTableCallback.setupPlayersAndControls();
  tra.rtWaveTableCallback.getCallbackToUi() = [](std::vector<double> &v)
  {
    static int i = 0;
    constexpr int  modFrames=50;
    if (!(++i % modFrames))
    {
      std::cout << "Called back from RTAudio: " << v[0] << " \n";
    }
  };
  tra.playWavTable();
  tra.rtWaveTableCallback.setDoScopelog(false);
  char input=' ';
  std::cout << "\nPlaying ... press <enter> to quit.\n";
  std::cin.get(input);
  // tra.rtWaveTableCallback.rtGuiSlider.at(0)->setVal(440);
  // std::cin.get(input);
  tra.stopStream();

  /*
   CustomMidiScale c;
   std::cout<<midiNoteToFrequency(51) - midiNoteToFrequency(50.8)<<" "<<c.cMidiNoteToFrequency(51) - c.cMidiNoteToFrequency(50.8)<<"\n";
   std::cout<<midiNoteToFrequency(51.2) - midiNoteToFrequency(51)<<" "<<c.cMidiNoteToFrequency(51.2) - c.cMidiNoteToFrequency(51)<<"\n";
   std::cout<<midiNoteToFrequency(51.4) - midiNoteToFrequency(51.2)<<" "<<c.cMidiNoteToFrequency(51.4) - c.cMidiNoteToFrequency(51.2)<<"\n";
   */

  return 0;
}
