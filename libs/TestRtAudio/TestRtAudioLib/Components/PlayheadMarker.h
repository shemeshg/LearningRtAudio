#pragma once

namespace RtAudioNs
{
  namespace Components
  {
    class PlayheadMarker
    {
    public:
      PlayheadMarker(unsigned int _sampleRate,unsigned int  _nBufferFrames);

      void incrementMarkerNext(){
        markerBufferFrames+=nBufferFrames;
      }

      const unsigned long int getMarkerBufferFrames(){
        return markerBufferFrames;
      }

      const double getMarkerSeconds(){
        return (double)markerBufferFrames/(double)sampleRate;
      }
    private:
      const unsigned int sampleRate;
      const unsigned int nBufferFrames;
      unsigned long int markerBufferFrames = 0;
    };

  }
}