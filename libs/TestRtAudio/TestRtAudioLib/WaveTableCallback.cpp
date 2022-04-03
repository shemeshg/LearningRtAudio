#include <cassert>
#include "WaveTableCallback.h"
#include "Components/OscWaveTable2Addative.h"
#include "Components/VcaGateComponent.h"
#include "Components/SwitchAmpComponent.h"
#include "Components/RangeUtils.h" 
#include <string>
using namespace RtAudioNs;

RtWaveTableCallback::RtWaveTableCallback()
{
}

void RtWaveTableCallback::setupPlayersAndControls()
{

  auto osc2Sine = std::make_unique<Components::OscWaveTable2Addative>(sampleRate);
  osc2Sine->setupWaveTable();
  auto vca1 = std::make_unique<Components::VcaContainer>();
  vca1->multAmp = -20;

  auto playWavfile = std::make_unique<Components::PlayWavFile>("//Volumes//TEMP//DeleteME//tmp/sampleWav.wav");
  playWavfile->openFile();
  

  // it is RtGuiSliderRefreshTableSetter to prevent aliassing on harmonics,
  // Maybe think how to do that, based on setter automaticlly,
  // but then we will have to manage MaxFrequency to restrigger RefreshTable
  std::unique_ptr<Components::RtGuiControl> rs1(new Components::RtGuiSliderRefreshTableSetter(*osc2Sine, "Note Number", osc2Sine->detuneNoteNumber, 21, 108, 1));
  std::unique_ptr<Components::RtGuiControl> rs2(new Components::RtGuiSlider("Amplitude Db", vca1->multAmp, -40, 0, 0.1));
  std::unique_ptr<Components::RtGuiControl> rs3(new Components::RtGuiSlider("detuneOscs", osc2Sine->detuneOscsAmount, 0, 100, 0.1));

  rtGuiSliders.push_back(std::move(rs1));
  rtGuiSliders.push_back(std::move(rs2));
  rtGuiSliders.push_back(std::move(rs3));

  auto sac = std::make_unique<Components::SwitchAmpComponent>();
  std::vector<double> sacOption1(bufferFrames, 0);
  std::vector<double> sacOption2(bufferFrames, 0.2);
  std::vector<double> sacOption3(bufferFrames, 0.4);
  sac->outVals.push_back(std::move(sacOption1));
  sac->outVals.push_back(std::move(sacOption2));
  sac->outVals.push_back(std::move(sacOption3));
  /*
  for (unsigned int i = 0; i < Osc2Sine->harmoniesLevels.size(); i++)
  {
    std::unique_ptr<RtGuiControl> hm1(new RtGuiSliderRefreshTableSetter(*oscSine, "harminic " + std::to_string(i), oscSine->harmoniesLevels.at(i), -1, 1, 0.00001));
    hm1->setVal(pow(0.5,i));
    rtGuiSlider.push_back(std::move(hm1));
  }
  */



  vecVcas.push_back(std::move(vca1));
  vecOsc2Sine.push_back(std::move(osc2Sine));
  switchAmps.push_back(std::move(sac));
  playWavfiles.push_back(std::move(playWavfile));
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


  if (status)
    std::cout << "Stream underflow detected!" << std::endl;

  std::vector<double>
      inChannel2 = getInput(inBuffer, nBufferFrames, streamInParameters.nChannels, 2);
  std::vector<double>
      inChannel3 = getInput(inBuffer, nBufferFrames, streamInParameters.nChannels, 3);

  switchAmps[0]->render(inChannel3,outOscContiousPitch);
  vecOsc2Sine.at(0)->render(outChannel01, outOscContiousPitch);

  // callbackToUi(outChannel01);

  std::vector<double> vca1add(nBufferFrames, vecVcas[0]->addAmp);
  Components::vcaComponent(outChannel01, vca1add, inChannel2);
  //Components::gateComponent(outChannel01, inChannel3);
  //outChannel01 = playWavfiles[0]->getVectorStream(nBufferFrames)[0];
  outChannel01 = playWavfiles[0]->render(inChannel2,inChannel2)[0];

  sendOutput(outBuffer, nBufferFrames, streamOutParameters.nChannels, outChannel01, {0, 1});
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
  streamOutParameters.nChannels = info.outputChannels; // 4;
  streamOutParameters.firstChannel = 0;

  streamInParameters.deviceId = inDeviceId;
  streamInParameters.nChannels = info.inputChannels;
  streamInParameters.firstChannel = 0;

  sampleRate = info.preferredSampleRate;
  bufferFrames = streamBufferFrames;
}
