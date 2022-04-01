#pragma once
#include <string>
#include <sndfile.hh>
#include <iostream>
#include <vector>

namespace RtAudioNs
{
  namespace Components
  {
    class PlayWavFile
    {
    public:
      PlayWavFile(const std::string &filename)
          : _filename(filename) {}
      const std::string &getFilename() const { return _filename; }
      void openFile();
      const unsigned int getChannels() const {return sndfile->channels();}

      std::vector<std::vector<double>> getVectorStream(unsigned int bufferSize, const unsigned int channels);

    private:
      const std::string _filename;
      std::unique_ptr<SndfileHandle> sndfile;
      bool isLoopback = true;
    };

  }
}