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
            countFromFrame = (int)i;
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

    namespace {
        constexpr unsigned int defaultMetronomBpm=120;
    }
    class MetronomParams
    {
    public:
      unsigned int metronomUpperNum = 4;
      const unsigned int metronomLowerNum = 4;

      unsigned int metronomBpm = defaultMetronomBpm;

    };

    namespace {
        constexpr unsigned int defaultFramesEvery=100;
        constexpr int defaultFramesLen = 7;
        constexpr int defaultFrameStart = 2000;
        constexpr int defaultRepeatCount = -1;
    }
    class PlayheadEvent
    {
    public:
      void render(std::vector<double> &triggerIn, std::vector<double> &triggerResetIn);
      unsigned int &getFramesEvery(){
          return framesEvery;
      }

      int &getFramesLen(){
          return framesLen;
      }

      int &getFrameStart(){
          return frameStart;
      }

      int &getRepeatCount(){
          return repeatCount;
      }

      unsigned long int &getMarkerBufferFrames(){
          return markerBufferFrames;
      }
    private:
      unsigned int framesEvery = defaultFramesEvery;
      int framesLen = defaultFramesLen;
      int frameStart = defaultFrameStart;
      int repeatCount = defaultRepeatCount;
      unsigned long int markerBufferFrames = 0;

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

      unsigned long int getMarkerBufferFrames()
      {
        return markerBufferFrames;
      }

      double getMarkerSeconds()
      {
        return (double)markerBufferFrames / (double)sampleRate;
      }
      
      double getMarkerBufferBar(){
          constexpr double secPerMin=60;
         return (double)markerBufferFrames / ( (double)sampleRate * ( secPerMin / (double)metronomParams.metronomBpm) );
       }

      unsigned int getMarkerBufferBarNumUpper(){
         return (int)getMarkerBufferBar()  % metronomParams.metronomUpperNum ;
       }

      MetronomParams &getMetronomParams(){
          return metronomParams;
      }
    private:
      const unsigned int sampleRate;
      const unsigned int nBufferFrames;
      unsigned long int markerBufferFrames = 0;
      MetronomParams metronomParams;
    };

  }
}
