#include <iostream>
#include "TestRtAudio.h"
#include "RangeUtils.h"

int main()
{
  /*
  // TestRtAudio::coutListApis();
  TestRtAudio tra;
  
  tra.playWavTable(2);
  char input;
  // std::cout << "\nPlaying ... press <enter> to quit.\n";
  std::cin.get(input);  
  //tra.rtWaveTableCallback.rtGuiSlider.at(0).val = 440;
  //std::cin.get(input);
  tra.stopStream();
  */
  CustomMidiScale c;
  //std::cout<<midiNoteToFrequency(60)<<" "<<midiNoteToFrequency(45)<<" "<<midiNoteToFrequency(77)<<"\n";
  //std::cout<<c.midiNoteToFrequency(60)<<" "<<c.midiNoteToFrequency(45)<<" "<<c.midiNoteToFrequency(77)<<"\n";
  std::cout<<midiNoteToFrequency(50)<<" "<<c.midiNoteToFrequency(50)<<"\n";
  std::cout<<midiNoteToFrequency(50.2)<<" "<<c.midiNoteToFrequency(50.2)<<"\n";
  std::cout<<midiNoteToFrequency(50.4)<<" "<<c.midiNoteToFrequency(50.4)<<"\n";
  std::cout<<midiNoteToFrequency(50.8)<<" "<<c.midiNoteToFrequency(50.8)<<"\n";
  return 0;
}