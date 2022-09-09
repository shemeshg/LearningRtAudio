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

        ItfSetupWaveTable(){}
        virtual ~ItfSetupWaveTable() = default;
        ItfSetupWaveTable(const ItfSetupWaveTable&) = delete;
        ItfSetupWaveTable(ItfSetupWaveTable&&) = delete;
        ItfSetupWaveTable& operator=(const ItfSetupWaveTable&)= delete;
        ItfSetupWaveTable& operator=(ItfSetupWaveTable&&) = delete;

    };

    namespace{
        constexpr int defaultGWavetableLength=512;
        constexpr float defaultGFrequency=220;
    }

    class OscWaveTable: public ItfSetupWaveTable
    {
    public:

      OscWaveTable(unsigned int sampleRate);
      


      int render(std::vector<double> &channelData, std::vector<double> &cvPitchChange);

      const int &getGWavetableLength(){
          return gWavetableLength;
      }

      unsigned int &getSampleRate(){
          return sampleRate;
      }

      float &getGFrequency(){
          return gFrequency;
      }
    protected:
      std::vector<float> &getGWavetable(){
          return gWavetable;
      }
    private:
      std::vector<float> gWavetable; // Buffer that holds the wavetable
      unsigned int sampleRate;
      float gFrequency = defaultGFrequency; // Frequency


      int gWavetableLength = defaultGWavetableLength; // The length of the buffer in frames
      double gReadPointer = 0;

      double phaseStep(const double &frequency)
      {
        return gWavetableLength * (frequency / sampleRate);
      }

      double nextGReadPointer(const double &frequency)
      {
        double p = gReadPointer + phaseStep(frequency);
        if (p >= gWavetableLength)
        {
          p -= gWavetableLength;
        }
        return p;
      }

      double getLinearInterpolation();
    };



  }
}
