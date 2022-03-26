#include "TestRtAudio.h"
#include "waveTable.h"

using namespace RtAudioNs;

TestRtAudio::TestRtAudio(RtAudio::Api api, RtAudioErrorCallback &&errorCallback) : audio{api, std::move(errorCallback)}
{
}

TestRtAudio::~TestRtAudio()
{
  if (audio.isStreamOpen())
    audio.closeStream();
}

void TestRtAudio::coutListApis()
{
  std::vector<RtAudio::Api> apis;
  RtAudio ::getCompiledApi(apis);

  std::cout << "\nCompiled APIs:\n";
  for (size_t i = 0; i < apis.size(); i++)
    std::cout << "  " << i << ". " << RtAudio::getApiDisplayName(apis[i])
              << " (" << RtAudio::getApiName(apis[i]) << ")" << std::endl;

  return;
}

void TestRtAudio::coutDevicesInfo()
{
  std::cout << "API: " << RtAudio::getApiDisplayName(audio.getCurrentApi()) << "\n";
  // Determine the number of devices available
  unsigned int devices = audio.getDeviceCount();
  // Scan through devices for various capabilities
  RtAudio::DeviceInfo info;
  for (unsigned int i = 0; i < devices; i++)
  {
    info = audio.getDeviceInfo(i);
    if (info.probed == true)
    {
      // Print, for example, the maximum number of output channels for each device
      std::cout << "  device: " << i << "\n";
      std::cout << "    probed: " << info.probed << "\n";
      std::cout << "    name: " << info.name << "\n";

      std::cout << "    outputChannels: " << info.outputChannels << "\n";
      std::cout << "    inputChannels: " << info.inputChannels << "\n";
      std::cout << "    duplexChannels: " << info.duplexChannels << "\n";
      std::cout << "    isDefaultOutput: " << info.isDefaultOutput << "\n";
      std::cout << "    isDefaultInput: " << info.isDefaultInput << "\n";

      std::cout << "    sampleRates:";
      for (int sampleRate : info.sampleRates)
      {
        std::cout << " " << sampleRate;
      }
      std::cout << "\n";

      std::cout << "    preferredSampleRate: " << info.preferredSampleRate << "\n";
      std::cout << "    nativeFormats: " << nativeFormatStr(info.nativeFormats) << "\n";
      std::cout << "\n";
    }
  }
  return;
}

void TestRtAudio::playRtAudioCallback(RtAudioCallback callback, void *userData)
{
  RtWaveTableCallback *userDataCasted = (RtWaveTableCallback *)userData;

  try
  {

    audio.openStream(&userDataCasted->streamOutParameters, &userDataCasted->streamInParameters, RTAUDIO_FLOAT64,
                     userDataCasted->getSampleRate(), &userDataCasted->bufferFrames, callback, userData);
    audio.startStream();
  }
  catch (RtAudioError &e)
  {
    e.printMessage();
    exit(0);
  }
}

void TestRtAudio::stopStream()
{
  try
  {
    // Stop the stream
    audio.stopStream();
  }
  catch (RtAudioError &e)
  {
    e.printMessage();
  }
}

void TestRtAudio::playWavTable()
{
  playRtAudioCallback(&waveTable, (void *)&rtWaveTableCallback);
}

std::string const TestRtAudio::nativeFormatStr(RtAudioFormat const &i)
{
  if (i & RTAUDIO_SINT8)
    return " 8-bit int";
  else if (i & RTAUDIO_SINT16)
    return "16-bit int";
  else if (i & RTAUDIO_SINT24)
    return "24-bit int";
  else if (i & RTAUDIO_SINT32)
    return "32-bit int";
  else if (i & RTAUDIO_FLOAT32)
    return "32-bit float";
  else if (i & RTAUDIO_FLOAT64)
    return "64-bit float";
  else
    return "No natively supported data formats(?)!";
}
