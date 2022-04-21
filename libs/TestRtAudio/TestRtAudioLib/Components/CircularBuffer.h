#pragma once
#include <vector>

namespace RtAudioNs
{
  namespace Components
  {
    inline int mod(int a, int b)
    {
      int ret = a % b;
      return ret >= 0 ? ret : ret + b;
    }

    class CircularBuffer
    {
    public:
      CircularBuffer(int m_size) : vec(m_size, 0)
      {
      }

      void render(std::vector<double> &inVector,
                  std::vector<double> &outVector,
                  std::vector<int> &posisionOffset,
                  std::vector<double> &feedback)
      {
        const int size = vec.size();
        for (int i = 0; i < outVector.size(); i++)
        {
          const int readHeadPosision = mod((writeHead - posisionOffset[i]), size);
          double feedbackVal = feedback[i] * vec[readHeadPosision];
          vec[writeHead] = inVector[i] + feedbackVal;
          outVector[i] = vec[readHeadPosision];
          writeHead = (writeHead + 1) % size;
        }
      }

      // private:
      std::vector<double> vec;
      int writeHead = 0;
    };
  }
}