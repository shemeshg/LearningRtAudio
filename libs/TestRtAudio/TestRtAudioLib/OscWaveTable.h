#pragma once
#include <cmath>
#include <vector>

class OscWaveTable
{
public:
  int gWavetableLength = 512; // The length of the buffer in frames

  float gAmplitudeDb = -10; // Amplitude of the playback
  float gFrequency = 220.0; // Frequency (TODO: not implemented yet)
  const int gChannelsCount = 2;

  OscWaveTable();
  virtual void setupWaveTable() = 0;
  virtual ~OscWaveTable();
  enum RenderMode
  {
    setBuffer,
    addBuffer
  };

  int render(double *buffer, unsigned int &nBufferFrames, RenderMode renderMode);

protected:
  float *gWavetable; // Buffer that holds the wavetable
private:
  double gReadPointer = 0;

  float gAmplitude()
  {
    return pow(10.0, gAmplitudeDb / 20.0);
  }

  double phaseStep()
  {
    return gWavetableLength * (gFrequency / 44100.0);
  }

  float nextGReadPointer()
  {
    float p = gReadPointer + phaseStep();
    if (p >= gWavetableLength)
    {
      p -= gWavetableLength;
    }
    return p;
  }

  float getLinearInterpolation(int chid);
};

class OscWaveTableSine : public OscWaveTable
{
public:
  OscWaveTableSine() : OscWaveTable() {
    setupWaveTable();
  }
  void setupWaveTable() override;
};

class OscWaveTableAddative : public OscWaveTable
{
public:
  // Levels 0..1 NOT DBs
  std::vector<float> harmoniesLevels{0.5,0,0,0,0,0,0,0};

  OscWaveTableAddative() : OscWaveTable() {
    setupWaveTable();
  }
  void setupWaveTable() override;
};

class OscWaveTableTiangle : public OscWaveTable
{
public:
  OscWaveTableTiangle() : OscWaveTable(){
    setupWaveTable();
  }
  void setupWaveTable() override;
};
