#include <cassert>
#include "WaveTableCallback.h"
#include "RangeUtils.h"



RtWaveTableCallback::RtWaveTableCallback()
{
  auto oscSine = std::make_unique<OscWaveTableSine>();
  auto oscSine2 = std::make_unique<OscWaveTableSine>();
 
  RtGuiSlider rs("Note Number", detuneNoteNumber, 21, 108, 1);
  RtGuiSlider rs2("Amplitude Db", detuneAmplitudeDb, -40, 0, 0.1);
  RtGuiSlider rs3("detuneOscs", detuneOscsAmount, 0, 100, 0.1);
  
  Oscs.push_back(std::move(oscSine));
  Oscs.push_back(std::move(oscSine2));

  rtGuiSlider.push_back(std::move(rs));
  rtGuiSlider.push_back(std::move(rs2));
  rtGuiSlider.push_back(std::move(rs3));
}



RtWaveTableCallback::~RtWaveTableCallback()
{
}

void RtWaveTableCallback::scopeLog(double *buffer, unsigned int &nBufferFrames, int channels, int rowsCount)
{
  static int i = 0;
  int bufferPosition = 0;
  if (i < rowsCount)
  {

    for (int frameCount = 0; frameCount < nBufferFrames && i < rowsCount; frameCount++)
    {
      std::cout << i;
      for (int ch = 0; ch < channels; ch++)
      {
        std::cout << "," << buffer[bufferPosition++];
      }
      std::cout << "\n";
      i++;
    }
  }
}

int RtWaveTableCallback::render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
                                double &streamTime, RtAudioStreamStatus &status)
{

  double *buffer = (double *)outputBuffer;

  if (status)
    std::cout << "Stream underflow detected!" << std::endl;

  float detuneFrequency = midiNoteToFrequency(detuneNoteNumber);
  Oscs.at(0)->gFrequency = detuneFrequency + detuneOscsAmount;
  Oscs.at(0)->gAmplitudeDb = detuneAmplitudeDb;
  
  Oscs.at(1)->gFrequency = detuneFrequency - detuneOscsAmount;
  Oscs.at(1)->gAmplitudeDb = detuneAmplitudeDb;

  Oscs.at(0)->render(buffer, nBufferFrames, OscWaveTable::RenderMode::setBuffer);
  Oscs.at(1)->render(buffer, nBufferFrames, OscWaveTable::RenderMode::addBuffer);

  // scopeLog(buffer, nBufferFrames);
  return 0;
}

