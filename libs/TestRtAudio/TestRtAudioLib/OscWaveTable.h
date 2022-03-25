#pragma once
#include <cmath>
#include <vector>

class OscWaveTable
{
public:
  int gWavetableLength = 512; // The length of the buffer in frames
  unsigned int sampleRate;


  float gAmplitudeDb = -10; // Amplitude of the playback
  float gFrequency = 220.0; // Frequency 
  

  OscWaveTable(unsigned int sampleRate);
  virtual void setupWaveTable() = 0;
  virtual ~OscWaveTable();
  enum RenderMode
  {
    setBuffer,
    addBuffer
  };

  int render(std::vector<double> &channelData, std::vector<double> &cvPitchChange);

protected:
  float *gWavetable; // Buffer that holds the wavetable
private:
  double gReadPointer = 0;

  float gAmplitude()
  {
    return pow(10.0, gAmplitudeDb / 20.0);
  }

  double phaseStep(const double &frequency )
  {
    return gWavetableLength * (frequency / sampleRate);
  }

  float nextGReadPointer(const double &frequency )
  {
    float p = gReadPointer + phaseStep(frequency);
    if (p >= gWavetableLength)
    {
      p -= gWavetableLength;
    }
    return p;
  }

  float getLinearInterpolation();
};

class OscWaveTableSine : public OscWaveTable
{
public:
  OscWaveTableSine(unsigned int sampleRate) : OscWaveTable(sampleRate) {
    setupWaveTable();
  }
  void setupWaveTable() override;
};

class OscWaveTableAddative : public OscWaveTable
{
public:
  // Levels 0..1 NOT DBs
  std::vector<float> harmoniesLevels{0.5,0,0,0,0,0,0,0};

  OscWaveTableAddative(unsigned int sampleRate) : OscWaveTable(sampleRate){
    setupWaveTable();
  }
  void setupWaveTable() override;
};

class OscWaveTableTiangle : public OscWaveTable
{
public:
  OscWaveTableTiangle(unsigned int sampleRate) : OscWaveTable(sampleRate) {
    setupWaveTable();
  }
  void setupWaveTable() override;
};
