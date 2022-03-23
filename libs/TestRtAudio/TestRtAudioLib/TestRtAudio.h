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
  void stopStream();
  void playWavTable();
  void setupStreamParameters(int outDeviceId = -1, int inDeviceId = -1)
  {
    rtWaveTableCallback.setupStreamParameters(audio, outDeviceId, inDeviceId);
  }

  RtWaveTableCallback rtWaveTableCallback = RtWaveTableCallback();

private:
  RtAudio audio;
  std::string const nativeFormatStr(RtAudioFormat const &i);
  void playRtAudioCallback(RtAudioCallback callback, void *userData);
};
