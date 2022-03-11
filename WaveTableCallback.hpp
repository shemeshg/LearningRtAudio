#pragma once

template <int ARRAY_LEN>

class RtWaveTableCallback
{
public:
  int gWavetableLength = ARRAY_LEN; // The length of the buffer in frames
  float gWavetable[ARRAY_LEN];      // Buffer that holds the wavetable

  float gAmplitude = 0.5;   // Amplitude of the playback
  float gFrequency = 220.0; // Frequency (TODO: not implemented yet)

  RtWaveTableCallback<ARRAY_LEN>()
  {
    setup();
  }

  int render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
             double &streamTime, RtAudioStreamStatus &status)
  {

    double *buffer = (double *)outputBuffer;
    static double gReadPointer = 0; // Position of the last frame we played

    if (status)
      std::cout << "Stream underflow detected!" << std::endl;

    const double phaseStep = gWavetableLength * (gFrequency / 44100.0);
    for (unsigned int i = 0; i < nBufferFrames; i++)
    {
      *buffer++ = gAmplitude * this->gWavetable[(int)gReadPointer];
      *buffer++ = gAmplitude * this->gWavetable[(int)gReadPointer];
      gReadPointer = gReadPointer + phaseStep;
      if (gReadPointer >= gWavetableLength)
      {
        gReadPointer -= gWavetableLength;
      }
    }

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

  RtWaveTableCallback<512> *userDataCasted = (RtWaveTableCallback<512> *)userData;
  return userDataCasted->render(outputBuffer, inputBuffer, nBufferFrames, streamTime, status);
}