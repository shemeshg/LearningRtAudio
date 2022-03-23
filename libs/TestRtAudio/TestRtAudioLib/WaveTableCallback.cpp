#include <cassert>
#include "WaveTableCallback.h"
#include "RangeUtils.h"
#include <string>

RtWaveTableCallback::RtWaveTableCallback()
{


}


 void RtWaveTableCallback::setupPlayersAndControls(){
  
  auto oscSine = std::make_unique<OscWaveTableAddative>(sampleRate, streamOutParameters.nChannels);
  oscSine->sendToChannels={0,1};
  auto oscSine2 = std::make_unique<OscWaveTableAddative>(sampleRate, streamOutParameters.nChannels);

  std::unique_ptr<RtGuiControl> rs1(new RtGuiSliderRefreshTableSetter(*oscSine,"Note Number", detuneNoteNumber, 21, 108, 1));
  std::unique_ptr<RtGuiControl> rs2(new RtGuiSlider("Amplitude Db", detuneAmplitudeDb, -40, 0, 0.1));
  std::unique_ptr<RtGuiControl> rs3(new RtGuiSlider("detuneOscs", detuneOscsAmount, 0, 100, 0.1));

  // step=0 is no quantizing
  std::unique_ptr<RtDcInControlBase>  rs4(new RtDcInControl(streamInParameters.nChannels, detuneOscsAmount,1,-1,1,0)); 

  rtGuiSliders.push_back(std::move(rs1));
  rtGuiSliders.push_back(std::move(rs2));
  rtGuiSliders.push_back(std::move(rs3));

  rtDcInControls.push_back(std::move(rs4));

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

void RtWaveTableCallback::scopeLog(double *buffer, unsigned int &nBufferFrames, int channels, int rowsCount, 
        std::vector<unsigned int> colsToPrint,
        std::ostream& stream )
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
        if (std::count(colsToPrint.begin(), colsToPrint.end(), ch)) {
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

  for (auto const& e : std::as_const(rtDcInControls)) {
    e->setValIfRequired(inBuffer,nBufferFrames);
  }

  if (status)
    std::cout << "Stream underflow detected!" << std::endl;

  float detuneFrequency = midiNoteToFrequency(detuneNoteNumber);

  Oscs.at(0)->gFrequency = detuneFrequency + detuneOscsAmount;
  Oscs.at(0)->gAmplitudeDb = detuneAmplitudeDb;

  Oscs.at(0)->render(outBuffer, nBufferFrames, OscWaveTable::RenderMode::setBuffer);

  if (Oscs.size() == 2)
  {
    Oscs.at(1)->gFrequency = detuneFrequency - detuneOscsAmount;
    Oscs.at(1)->gAmplitudeDb = detuneAmplitudeDb;
    Oscs.at(1)->render(outBuffer, nBufferFrames, OscWaveTable::RenderMode::addBuffer);
  }

  if (doScopelog)
  {
    scopeLog(outBuffer, nBufferFrames, streamOutParameters.nChannels, 20250, {0,1});
  }

  return 0;
}


  void RtWaveTableCallback::setupStreamParameters(RtAudio &audio, int outDeviceId, int inDeviceId){
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
    streamOutParameters.nChannels = 2; //info.outputChannels
    streamOutParameters.firstChannel = 0;

    streamInParameters.deviceId = inDeviceId;
    streamInParameters.nChannels = 2; //info.inputChannels
    streamInParameters.firstChannel = 0;

    sampleRate = info.preferredSampleRate;    
  }