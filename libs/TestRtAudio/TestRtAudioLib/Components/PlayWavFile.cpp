#include "PlayWavFile.h"
#include "GateConstants.h"
namespace RtAudioNs
{
  namespace Components
  {

    void PlayWavFile::openFile()
    {
      sndfile = std::make_unique<SndfileHandle>(_filename);
      std::cout << "Opened file" << _filename << "\n";
      std::cout << "    Sample rate : " << sndfile->samplerate() << "\n";
      std::cout << "    Channels : " << sndfile->channels() << "\n";
      channels = sndfile->channels();
    }

    std::vector<std::vector<double>> PlayWavFile::render(std::vector<double> &triggerIn, std::vector<double> &isLoopbackIn)
    {
      std::vector<std::vector<double>> v;
      const unsigned int bufferSize=triggerIn.size();
      for (unsigned int ch = 0; ch < channels; ch++)
      {
        std::vector<double> v1(bufferSize, 0.0);
        v.push_back(v1);
      }

      unsigned int play_begin = -1;
      for (unsigned int i = 0; i < bufferSize; i++)
      {
        if (play_begin == -1 && triggerIn[i] > gateThreshold)
        {
          play_begin = i;
        }
        else if (play_begin != -1 && triggerIn[i] < gateThreshold )
        {
          std::vector<std::vector<double>> vs=getVectorStream(i-play_begin);

          setVectorStreamFromPosition(v,play_begin, i-play_begin);
          // LOOP COPY
          play_begin=-1;          
        }
        else if (play_begin != -1 && i == bufferSize - 1 ){
          setVectorStreamFromPosition(v,play_begin, i-play_begin + 1);
        }
        
      }

      return v;
    }

    void PlayWavFile::setVectorStreamFromPosition(std::vector<std::vector<double>>  &v,unsigned int play_begin, unsigned int play_count){      
      const auto _ret = getVectorStream(play_count);
         
      for (unsigned int channelIdx = 0;channelIdx<_ret.size();channelIdx++){
        for (unsigned int bufIdx=0;bufIdx<play_count;bufIdx++){
          v[channelIdx][play_begin + bufIdx] = _ret[channelIdx][bufIdx];
        }        
      }
      
    }

    std::vector<std::vector<double>> PlayWavFile::getVectorStream(unsigned int bufferSize)
    {
      std::vector<std::vector<double>> v;
      if (channels * bufferSize == 0){return v;}

      double buffer[channels * bufferSize];
      double *bufferStart = &buffer[0];
      double *bufferCurrent = &buffer[0];

      int icount = 0;
      if ((icount = sndfile->readf(buffer, bufferSize)) != bufferSize && isLoopback)
      {
        bufferCurrent += icount;
        sndfile->seek(0, 0);
        sndfile->readf(bufferCurrent, bufferSize - icount);
      }

      for (unsigned int ch = 0; ch < channels; ch++)
      {
        std::vector<double> v1(bufferSize, 0.0);
        v.push_back(v1);
      }

      for (unsigned int i = 0; i < bufferSize; i++)
      {

        for (unsigned int ch = 0; ch < channels; ch++)
        {
          v[ch][i] = *(bufferStart + i * (channels));
        }
      }
      return v;
    }

  }
}
