#include <iostream>
#include "TestRtAudio.h"
#include "RangeUtils.h"

int main()
{
 
  // TestRtAudio::coutListApis();
  TestRtAudio tra;
  tra.setupStreamParameters(2);
  tra.playWavTable();
  tra.rtWaveTableCallback.doScopelog=false;
  char input;
  std::cout << "\nPlaying ... press <enter> to quit.\n";
  std::cin.get(input);  
  tra.rtWaveTableCallback.rtGuiSlider.at(0)->setVal(440);
  std::cin.get(input);
  tra.stopStream();
 
 /*
  CustomMidiScale c;
  std::cout<<midiNoteToFrequency(51) - midiNoteToFrequency(50.8)<<" "<<c.cMidiNoteToFrequency(51) - c.cMidiNoteToFrequency(50.8)<<"\n";
  std::cout<<midiNoteToFrequency(51.2) - midiNoteToFrequency(51)<<" "<<c.cMidiNoteToFrequency(51.2) - c.cMidiNoteToFrequency(51)<<"\n";
  std::cout<<midiNoteToFrequency(51.4) - midiNoteToFrequency(51.2)<<" "<<c.cMidiNoteToFrequency(51.4) - c.cMidiNoteToFrequency(51.2)<<"\n";
  */

  return 0;
}