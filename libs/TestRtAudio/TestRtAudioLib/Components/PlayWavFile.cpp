#include "PlayWavFile.h"
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
    }

    std::vector<std::vector<double>> PlayWavFile::getVectorStream(unsigned int bufferSize, const unsigned int channels){
        std::vector<std::vector<double>> v;
        double buffer[channels * bufferSize];
        double *bufferStart = &buffer[0];
        double *bufferCurrent = &buffer[0];

        int icount = 0;
        if ((icount = sndfile->readf(buffer, bufferSize)) != bufferSize)
        {
          bufferCurrent += icount;
          sndfile->seek(0, 0);
          sndfile->readf(bufferCurrent, bufferSize - icount);
          // std::cout << icount << " " << "Loop back\n" << std::endl;
        }

        for (unsigned int ch=0;ch<channels;ch++){
          std::vector<double> v1(bufferSize,0.0);
          v.push_back(v1); 
        }
        
        for (unsigned int i=0;i<bufferSize;i++){
          
          for (unsigned int ch=0;ch<channels;ch++){
              v[ch][i]= *(bufferStart+i*(channels));
          
          }
        }   
        return v;
      }

  }
}
