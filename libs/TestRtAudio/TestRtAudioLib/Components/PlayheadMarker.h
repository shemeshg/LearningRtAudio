#pragma once
#include <vector>

namespace RtAudioNs
{
  namespace Components
  {

    class PlayheadEvent
    {
    public:
      unsigned int framesEvery = 100;
      int framesLen = 7;
      int frameStart = 2000;
      int repeatCount = -1;
      unsigned long int markerBufferFrames = 0;
      void render(std::vector<double> &triggerIn, std::vector<double> &triggerResetIn);

    private:
      int framesRemainedToPLay = 0;
    };

    class PlayheadMarker
    {
    public:
      PlayheadMarker(unsigned int _sampleRate, unsigned int _nBufferFrames);      

      void incrementMarkerNext()
      {
        markerBufferFrames += nBufferFrames;
      }

      const unsigned long int getMarkerBufferFrames()
      {
        return markerBufferFrames;
      }
  
      const double getMarkerSeconds()
      {
        return (double)markerBufferFrames / (double)sampleRate;
      }
      

    private:
      const unsigned int sampleRate;
      const unsigned int nBufferFrames;
      unsigned long int markerBufferFrames = 0;
    };

  }
}