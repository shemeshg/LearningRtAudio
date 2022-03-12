#include <iostream>
#include "TestRtAudio.h"

int main()
{
  // TestRtAudio::coutListApis();
  TestRtAudio tra;
  // tra.coutDevicesInfo();
  //  tra.playSin(2);
  //  tra.playWavFile();
  tra.rtWaveTableCallback.setupSine();
  tra.playWavTable(2);
  char input;
  // std::cout << "\nPlaying ... press <enter> to quit.\n";
  std::cin.get(input);
  //tra.rtWaveTableCallback.gFrequency = 440;
  tra.rtWaveTableCallback.rtGuiSlider.at(0).val = 440;
  std::cin.get(input);
  tra.stopStream();
  return 0;
}