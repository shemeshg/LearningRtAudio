#include <cassert>
#include "WaveTableCallback.h"
#include "Components/OscWaveTable2Addative.h"
#include "Components/VcaGateComponent.h"
#include "Components/SwitchAmpComponent.h"
#include <string>
using namespace RtAudioNs;

RtWaveTableCallback::RtWaveTableCallback()
{
}

void RtWaveTableCallback::setupPlayersAndControls()
{
  playheadMarker = std::make_unique<Components::PlayheadMarker>(sampleRate, bufferFrames);

  metronomeComponent = std::make_unique<Components::MetronomeComponent>(sampleRate, bufferFrames, *playheadMarker.get());
  metronomeComponent->setupWaveTable();

  simpleAdsrComponent = std::make_unique<Components::SimpleAdsrComponent>();
  linearAdsr = std::make_unique<Components::LinearAdsrComponent>();
  exponentialAdsr = std::make_unique<Components::ExponentialAdsr>();
  percussiveEnvelope = std::make_unique<Components::PercussiveEnvelope>();
  

  Components::PlayheadEvent phe{};
  phe.getFramesEvery() = sampleRate * 4; // 1 sec
  constexpr float framesLenInSec=0.2;
  phe.getFramesLen() = (int)((float)sampleRate * framesLenInSec); // 1 sec
  phe.getFrameStart() = 0;
  phe.getRepeatCount() = -1;
  playheadEvents.push_back(std::move(phe));

  auto osc2Sine = std::make_unique<Components::OscWaveTable2Addative>(sampleRate);
  osc2Sine->setupWaveTable();
  auto vca1 = std::make_unique<Components::VcaContainer>();
  constexpr float defaultMultAmp = -20;
  vca1->multAmp = defaultMultAmp;

  auto filter = std::make_unique<Components::FiltersComponent>(
      Components::FiltersComponent::FILTER_TYPE::FILTER_FO_LPF,
      sampleRate);

  auto playWavfile = std::make_unique<Components::PlayWavFile>("//Volumes//TEMP//DeleteME//tmp/sampleWav.wav");
  playWavfile->openFile();

  constexpr int secPerMin = 60;
  circularBuffer = std::make_unique<Components::CircularBuffer>(sampleRate * secPerMin); // 1 Min

  rampageEnvelope = std::make_unique<Components::RampageEnvelope>(sampleRate);

  midiComponent = std::make_unique<Components::MidiComponent>();
  midiComponent->refrehInPorts();
  midiComponent->printInPorts();
  midiComponent->openInPort(1);

  // it is RtGuiSliderRefreshTableSetter to prevent aliassing on harmonics,
  // Maybe think how to do that, based on setter automaticlly,
  // but then we will have to manage MaxFrequency to restrigger RefreshTable
  constexpr double minNoteNumber=21;
  constexpr double maxNoteNumber=108;
  std::unique_ptr<Components::RtGuiControl> rs1(new Components::RtGuiSliderRefreshTableSetter(*osc2Sine, "Note Number", osc2Sine->getDetuneNoteNumber(),
                                                                             minNoteNumber, maxNoteNumber, 1));
  constexpr double minDbLevel = -40;
  constexpr double sliderStep = 0.1;
  std::unique_ptr<Components::RtGuiControl> rs2(new Components::RtGuiSlider("Amplitude Db", vca1->multAmp, minDbLevel, 0, sliderStep));
  constexpr double maxDetuneAmount = 100;
  std::unique_ptr<Components::RtGuiControl> rs3(new Components::RtGuiSlider("detuneOscs", osc2Sine->getDetuneOscsAmount(), 0, maxDetuneAmount, sliderStep));

  rtGuiSliders.push_back(std::move(rs1));
  rtGuiSliders.push_back(std::move(rs2));
  rtGuiSliders.push_back(std::move(rs3));

  auto sac = std::make_unique<Components::SwitchAmpComponent>();
  std::vector<double> sacOption1(bufferFrames, 0);
  constexpr double switchLevel2 = 0.2;
  std::vector<double> sacOption2(bufferFrames, switchLevel2);
  constexpr double switchLevel3 = 0.4;
  std::vector<double> sacOption3(bufferFrames, switchLevel3);
  sac->getOutVals().push_back(std::move(sacOption1));
  sac->getOutVals().push_back(std::move(sacOption2));
  sac->getOutVals().push_back(std::move(sacOption3));
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
  filters.push_back(std::move(filter));
}



void RtWaveTableCallback::sendOutput(double *buffer, unsigned int &nBufferFrames, unsigned int channels,
                                     std::vector<double> &outChannel, std::vector<unsigned int> colsToSend)
{
  for (unsigned int frameCount = 0; frameCount < nBufferFrames; frameCount++)
  {
    for (auto &colToSend : colsToSend)
    {
      buffer[frameCount * channels + colToSend] = outChannel[frameCount]; //NOLINT
    }
  }
}

std::vector<double> RtWaveTableCallback::getInput(double *inBuffer, unsigned int &nBufferFrames, unsigned int channels, unsigned int inputToGet)
{
  std::vector<double> inChannel(nBufferFrames, 0);

  for (unsigned int frameCount = 0; frameCount < nBufferFrames; frameCount++)
  {
    inChannel[frameCount] = inBuffer[frameCount * channels + inputToGet]; //NOLINT
  }

  return inChannel;
}

void RtWaveTableCallback::scopeLog(double *buffer, unsigned int &nBufferFrames, unsigned int channels, int rowsCount,
                                   std::vector<unsigned int> colsToPrint,
                                   std::ostream &stream)
{
  static int i = 0;
  int bufferPosition = 0;
  if (i < rowsCount)
  {

    for (unsigned int frameCount = 0; frameCount < nBufferFrames && i < rowsCount; frameCount++)
    {
      stream << i;
      for (unsigned int ch = 0; ch < channels; ch++)
      {
        if (std::count(colsToPrint.begin(), colsToPrint.end(), ch))
        {
          stream << "," << buffer[bufferPosition++]; //NOLINT
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
  (void)streamTime;
  double *outBuffer = (double *)outputBuffer; //NOLINT
  double *inBuffer = (double *)inputBuffer; //NOLINT

  std::vector<double> outChannel01(nBufferFrames, 0);
  // std::vector<double> outOscContiousPitch(nBufferFrames, 0);

  if (status)
    std::cout << "Stream underflow detected!" << std::endl;

  std::vector<double>
      inChannel3 = getInput(inBuffer, nBufferFrames, streamInParameters.nChannels, 2);

  midiComponent->getMessage(1);
  //std::vector<double>
  //    inChannel4 = getInput(inBuffer, nBufferFrames, streamInParameters.nChannels, 3);
  //std::vector<int> delayOffset(nBufferFrames, 0);     
  //std::transform(inChannel4.begin(), inChannel4.end(), delayOffset.begin(),  [this](double toN )
  //              { return rescaleRange(toN, 0.0, 1.0, sampleRate / 1000, sampleRate); });

  //std::vector<int> delayOffset(nBufferFrames, sampleRate);
  //std::vector<double> delayFeedback(nBufferFrames, 0.3);
  //circularBuffer->render(inChannel3, outChannel01, delayOffset, delayFeedback);


  //simpleAdsrComponent->render(inChannel3, outChannel01);
  //linearAdsr->render(inChannel3, outChannel01);
  //exponentialAdsr->render(inChannel3, outChannel01);

  //std::vector<double> attackVec(nBufferFrames, 0.001);
  //std::vector<double> decayVec(nBufferFrames, 1);

  //rampageEnvelope->render(inChannel3, outChannel01, attackVec, decayVec);
  //metronomeComponent->render(outChannel01);

  // std::vector<double>
  //     inChannel4 = getInput(inBuffer, nBufferFrames, streamInParameters.nChannels, 3);

  // callbackToUi(outChannel01);

  // std::vector<double> vca1add(nBufferFrames, vecVcas[0]->addAmp);
  // Components::vcaComponent(outChannel01, vca1add, inChannel2);
  // Components::gateComponent(outChannel01, inChannel3);
  // outChannel01 = playWavfiles[0]->getVectorStream(nBufferFrames)[0]; //render all
  // outChannel01 = playWavfiles[0]->render(testGate, testReset)[0]; // render partially

  // outChannel01 = inChannel2;
  // filters[0]->process_fc(outChannel01, inChannel3);
  
  //noiseAmount = create step every ...; keepStateConst = keep voltage constant for n buffers;
  // The steps needs to be smoothed using Rampage...
  //debounceVca.process(inChannel3, outChannel01);

  sendOutput(outBuffer, nBufferFrames, streamOutParameters.nChannels, outChannel01, {0, 1});
  if (doScopelog)
  {
    constexpr int rowCount =20250;
    scopeLog(outBuffer, nBufferFrames, streamOutParameters.nChannels, rowCount, {0, 1});
  }

  playheadMarker->incrementMarkerNext();
  return 0;
}

void RtWaveTableCallback::setupStreamParameters(RtAudio &audio, int outDeviceId, int inDeviceId, unsigned int streamBufferFrames)
{
  if (outDeviceId == -1)
  {
    outDeviceId = (int)audio.getDefaultOutputDevice();
  }

  if (inDeviceId == -1)
  {
    inDeviceId = (int)audio.getDefaultInputDevice();
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
