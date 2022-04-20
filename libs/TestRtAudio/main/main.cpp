#include <iostream>
#include "TestRtAudio.h"
#include "Components/CircularBuffer.h"

int main()
{
  RtAudioNs::Components::CircularBuffer c(5);
  std::vector<double> in{1,2,3,4,5},out{0,0,0,0,0}, feedback(5,0.0);
  std::vector<int> offst(5,2);
  c.render(in,out,offst,feedback);
  for (auto &v: out){
    std::cout<<v<<"*";
  }
  std::cout<<"\n";
  for (auto &v: c.vec){
    std::cout<<v<<"*";
  }
  std::cout<<"\n";
  if (1==1){return 0;}

  // TestRtAudio::coutListApis();
  RtAudioNs::TestRtAudio tra;
  tra.coutDevicesInfo();
  tra.setupStreamParameters(2, 2, 1024);
  tra.rtWaveTableCallback.setupPlayersAndControls();
  tra.rtWaveTableCallback.callbackToUi = [](std::vector<double> &v)
  {
    static int i = 0;
    if (!(++i % 50))
    {
      std::cout << "Called back from RTAudio: " << v[0] << " \n";
    }
  };
  tra.playWavTable();
  tra.rtWaveTableCallback.setDoScopelog(false);
  char input;
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