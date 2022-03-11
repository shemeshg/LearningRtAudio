#pragma once

class RtWaveTableCallback
{
public:
  int gWavetableLength; // The length of the buffer in frames
  float *gWavetable;    // Buffer that holds the wavetable

  float gAmplitude = 0.5;   // Amplitude of the playback
  float gFrequency = 220.0; // Frequency (TODO: not implemented yet)

  RtWaveTableCallback(int gWavetableLength) : gWavetableLength{gWavetableLength}
  {
    gWavetable = (float *)std::calloc(gWavetableLength, sizeof(float));
    assert(gWavetable);
    setup();
  }

  ~RtWaveTableCallback()
  {
    free(gWavetable);
    gWavetable = NULL;
  }

  void scopeLog(double *buffer, unsigned int &nBufferFrames, int channels = 2, int rowsCount = 2000)
  {
    static int i = 0;
    int bufferPosition = 0;
    if (i < rowsCount)
    {
      
      for (int frameCount = 0; frameCount < nBufferFrames && i < rowsCount;frameCount++)
      {
        std::cout << i;
        for (int ch = 0; ch < channels; ch++)
        {
          std::cout << "," << buffer[bufferPosition++];
        }
        std::cout << "\n";
        i++;
      }
    }
  }

  int render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
             double &streamTime, RtAudioStreamStatus &status)
  {

    double *buffer = (double *)outputBuffer;
    int bufferPosition = 0;

    static double gReadPointer = 0; // Position of the last frame we played

    if (status)
      std::cout << "Stream underflow detected!" << std::endl;

    const double phaseStep = gWavetableLength * (gFrequency / 44100.0);
    for (unsigned int i = 0; i < nBufferFrames; i++)
    {
      buffer[bufferPosition++] = gAmplitude * this->gWavetable[(int)gReadPointer];
      buffer[bufferPosition++] = gAmplitude * this->gWavetable[(int)gReadPointer];
      gReadPointer = gReadPointer + phaseStep;
      if (gReadPointer >= gWavetableLength)
      {
        gReadPointer -= gWavetableLength;
      }
    }
    scopeLog(buffer, nBufferFrames);
    return 0;
  }

private:
  void setup()
  {
    // Generate a triangle waveform (ramp from -1 to 1, then 1 to -1)
    // and store it in the buffer. Notice: generating the wavetable does
    // not depend on the audio sample rate (why not?)
    int singleChannelLen = gWavetableLength / 2;
    for (unsigned int n = 0; n < singleChannelLen / 2; n++)
    {
      gWavetable[n * 2] = -1.0 + 4.0 * (float)n / (float)singleChannelLen;
      gWavetable[n * 2 + 1] = gWavetable[n * 2];
    }
    for (unsigned int n = singleChannelLen / 2; n < singleChannelLen; n++)
    {
      gWavetable[n * 2] = 1.0 - 4.0 * (float)(n - singleChannelLen / 2) / (float)singleChannelLen;
      gWavetable[n * 2 + 1] = gWavetable[n * 2];
    }
  }
};

int waveTable(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
              double streamTime, RtAudioStreamStatus status, void *userData)
{

  RtWaveTableCallback *userDataCasted = (RtWaveTableCallback *)userData;
  return userDataCasted->render(outputBuffer, inputBuffer, nBufferFrames, streamTime, status);
}