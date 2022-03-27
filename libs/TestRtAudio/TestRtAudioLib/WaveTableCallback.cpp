#include <cassert>
#include "WaveTableCallback.h"
#include "RangeUtils.h"
#include "Components/OscWaveTableAddative.h"
#include <string>
using namespace RtAudioNs;

RtWaveTableCallback::RtWaveTableCallback()
{
}

void RtWaveTableCallback::setupPlayersAndControls()
{

  auto oscSine = std::make_unique<Components::OscWaveTableAddative>(sampleRate);
  oscSine->setupWaveTable();
  auto oscSine2 = std::make_unique<Components::OscWaveTableAddative>(sampleRate);
  oscSine2->setupWaveTable();

  // it is RtGuiSliderRefreshTableSetter to prevent aliassing on harmonics, 
  // Maybe think how to do that, based on setter automaticlly,
  // but then we will have to manage MaxFrequency to restrigger RefreshTable
  std::unique_ptr<Components::RtGuiControl> rs1(new Components::RtGuiSliderRefreshTableSetter(*oscSine, "Note Number", detuneNoteNumber, 21, 108, 1));
  std::unique_ptr<Components::RtGuiControl> rs2(new Components::RtGuiSlider("Amplitude Db", detuneAmplitudeDb, -40, 0, 0.1));
  std::unique_ptr<Components::RtGuiControl> rs3(new Components::RtGuiSlider("detuneOscs", detuneOscsAmount, 0, 100, 0.1));

  rtGuiSliders.push_back(std::move(rs1));
  rtGuiSliders.push_back(std::move(rs2));
  rtGuiSliders.push_back(std::move(rs3));

  /*
  for (unsigned int i = 0; i < oscSine->harmoniesLevels.size(); i++)
  {
    std::unique_ptr<RtGuiControl> hm1(new RtGuiSliderRefreshTableSetter(*oscSine, "harminic " + std::to_string(i), oscSine->harmoniesLevels.at(i), -1, 1, 0.00001));
    hm1->setVal(pow(0.5,i));
    rtGuiSlider.push_back(std::move(hm1));
  }
  */

  Oscs.push_back(std::move(oscSine));
  Oscs.push_back(std::move(oscSine2));
}

RtWaveTableCallback::~RtWaveTableCallback()
{
}

void RtWaveTableCallback::sendOutput(double *buffer, unsigned int &nBufferFrames, int channels,
                                     std::vector<double> &outChannel, std::vector<unsigned int> colsToSend)
{
  for (int frameCount = 0; frameCount < nBufferFrames; frameCount++)
  {
    for (auto &colToSend : colsToSend)
    {
      buffer[frameCount * channels + colToSend] = outChannel[frameCount];
    }
  }
}

std::vector<double> RtWaveTableCallback::getInput(double *inBuffer, unsigned int &nBufferFrames, int channels, unsigned int inputToGet)
{
  std::vector<double> inChannel(nBufferFrames, 0);

  for (int frameCount = 0; frameCount < nBufferFrames; frameCount++)
  {
    inChannel[frameCount] = inBuffer[frameCount * channels + inputToGet];
  }

  return inChannel;
}

void RtWaveTableCallback::scopeLog(double *buffer, unsigned int &nBufferFrames, int channels, int rowsCount,
                                   std::vector<unsigned int> colsToPrint,
                                   std::ostream &stream)
{
  static int i = 0;
  int bufferPosition = 0;
  if (i < rowsCount)
  {

    for (int frameCount = 0; frameCount < nBufferFrames && i < rowsCount; frameCount++)
    {
      stream << i;
      for (int ch = 0; ch < channels; ch++)
      {
        if (std::count(colsToPrint.begin(), colsToPrint.end(), ch))
        {
          stream << "," << buffer[bufferPosition++];
        }
      }
      stream << "\n";
      i++;
    }
  }
}



int RtWaveTableCallback::render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
                                double &streamTime, RtAudioStreamStatus &status)
{

  double *outBuffer = (double *)outputBuffer;
  double *inBuffer = (double *)inputBuffer;

  

  std::vector<double> outChannel01(nBufferFrames, 0);
  std::vector<double> outOscContiousPitch(nBufferFrames, 1);
                        //=getInput(inBuffer, nBufferFrames, streamInParameters.nChannels, 2);

  if (status)
    std::cout << "Stream underflow detected!" << std::endl;

  float detuneFrequency = midiNoteToFrequency(detuneNoteNumber);

  Oscs.at(0)->gFrequency = detuneFrequency + detuneOscsAmount;
  Oscs.at(0)->gAmplitudeDb = detuneAmplitudeDb;

  Oscs.at(0)->render(outChannel01, outOscContiousPitch);

  if (Oscs.size() == 2)
  {
    Oscs.at(1)->gFrequency = detuneFrequency - detuneOscsAmount;
    Oscs.at(1)->gAmplitudeDb = detuneAmplitudeDb;
    Oscs.at(1)->render(outChannel01, outOscContiousPitch);
  }

  // I choose channel 2 to avoid feedback
  std::vector<double> inChannel1 = getInput(inBuffer, nBufferFrames, streamInParameters.nChannels, 2);
  callbackToUi(inChannel1);
  //std::transform(outChannel01.begin(), outChannel01.end(), inChannel1.begin(),outChannel01.begin(),  [](double i, double j)
  //               { return i * j ; });
  


  sendOutput(outBuffer, nBufferFrames, streamOutParameters.nChannels, outChannel01, {0,1});
  //sendOutput(outBuffer, nBufferFrames, streamOutParameters.nChannels, inChannel1, {2});
  if (doScopelog)
  {
    scopeLog(outBuffer, nBufferFrames, streamOutParameters.nChannels, 20250, {0, 1});
  }

  return 0;
}

void RtWaveTableCallback::setupStreamParameters(RtAudio &audio, int outDeviceId, int inDeviceId, unsigned int streamBufferFrames)
{
  if (outDeviceId == -1)
  {
    outDeviceId = audio.getDefaultOutputDevice();
  }

  if (inDeviceId == -1)
  {
    inDeviceId = audio.getDefaultInputDevice();
  }

  streamOutParameters.deviceId = outDeviceId;

  RtAudio::DeviceInfo info = audio.getDeviceInfo(outDeviceId);
  streamOutParameters.nChannels = info.outputChannels; //4; 
  streamOutParameters.firstChannel = 0;

  streamInParameters.deviceId = inDeviceId;
  streamInParameters.nChannels = info.inputChannels;
  streamInParameters.firstChannel = 0;

  sampleRate = info.preferredSampleRate;
  bufferFrames=streamBufferFrames;

}
