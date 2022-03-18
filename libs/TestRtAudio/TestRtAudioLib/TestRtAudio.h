#pragma once

#include "RtAudio.h"
#include "RtAudioError.h"
#include "WaveTableCallback.h"

class TestRtAudio
{
public:
  TestRtAudio(RtAudio::Api api = RtAudio::Api::UNSPECIFIED, RtAudioErrorCallback &&errorCallback = 0);


  ~TestRtAudio();

  static void coutListApis();

  void coutDevicesInfo();

  void playRtAudioCallback(RtAudioCallback callback, void *userData);

  void stopStream();

  RtWaveTableCallback rtWaveTableCallback = RtWaveTableCallback();
  void playWavTable();

  void setupStreamParameters(int deviceId = -1){
    rtWaveTableCallback.setupStreamParameters(audio,deviceId);
  }

private:
  

  RtAudio audio;
  
  std::string const nativeFormatStr(RtAudioFormat const &i);
};
