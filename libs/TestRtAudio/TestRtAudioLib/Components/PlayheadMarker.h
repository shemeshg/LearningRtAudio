#pragma once
#include <vector>
#include "GateConstants.h"

namespace RtAudioNs
{
  namespace Components
  {

    class FramesCounter
    {
    public:
      void start(std::vector<double> &vGateStart)
      {
        if (isCounting)
        {
          return;
        }
        for (unsigned int i = 0; i < vGateStart.size(); i++)
        {
          if (vGateStart[i] > gateThreshold)
          {
            countedFrames = 0;
            countFromFrame = i;
            isCounting = true;
            return;
          }
        }
      }

      int stop(std::vector<double> &vGateStop)
      {
        if (!isCounting)
        {
          return -1;
        }
        for (unsigned int i = countFromFrame; i < vGateStop.size(); i++)
        {
          if (vGateStop[i] > gateThreshold)
          {
            int _countedFrames = countedFrames;
            countFromFrame = 0;
            countedFrames = 0;
            isCounting = false;
            _countedFrames++;
            return _countedFrames;
          }
          countedFrames++;
        }
        countFromFrame = 0;
        return -1;
      }

    private:
      bool isCounting = false;
      int countFromFrame = 0;
      int countedFrames = 0;
    };

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