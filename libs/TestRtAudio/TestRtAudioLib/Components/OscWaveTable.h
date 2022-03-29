#pragma once
#include <cmath>
#include <vector>

namespace RtAudioNs
{
  namespace Components
  {
    class ItfSetupWaveTable {
      public:
      virtual void setupWaveTable() = 0;
    };

    class OscWaveTable: public ItfSetupWaveTable
    {
    public:
      int gWavetableLength = 512; // The length of the buffer in frames
      unsigned int sampleRate;

      float gFrequency = 220.0; // Frequency

      OscWaveTable(unsigned int sampleRate);
      
      virtual ~OscWaveTable();

      int render(std::vector<double> &channelData, std::vector<double> &cvPitchChange);

    protected:
      float *gWavetable; // Buffer that holds the wavetable
    private:
      double gReadPointer = 0;

      double phaseStep(const double &frequency)
      {
        return gWavetableLength * (frequency / sampleRate);
      }

      float nextGReadPointer(const double &frequency)
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



  }
}
