#pragma once

template <int ARRAY_LEN>

class RtWaveTableCallback
{
public:
  int gWavetableLength = ARRAY_LEN; // The length of the buffer in frames
  float gWavetable[ARRAY_LEN];      // Buffer that holds the wavetable
  int gReadPointer = 0;             // Position of the last frame we played

  float gAmplitude = 0.2;   // Amplitude of the playback
  float gFrequency = 220.0; // Frequency (TODO: not implemented yet)

  RtWaveTableCallback<ARRAY_LEN>()
  {
    setup();
  }

  int render(void *outputBuffer, void *inputBuffer, unsigned int &nBufferFrames,
              double &streamTime, RtAudioStreamStatus &status)
  {
    static double frequency = 100.0;

    unsigned int i, j;
    double *buffer = (double *)outputBuffer;

    if (status)
      std::cout << "Stream underflow detected!" << std::endl;

    // Write interleaved audio data.
    for (i = 0; i < nBufferFrames; i++)
    {
       *buffer++ =  this->gWavetable[i];    
    }
    

    return 0;
  }

  void coutGWavetable()
  {
    for (unsigned int n = 0; n < gWavetableLength; n++)
    {
      std::cout << n / 2 << "," << gWavetable[n++] << "," << gWavetable[n] << "\n";
    }
  }

private:
  void setup()
  {
    // Generate a triangle waveform (ramp from -1 to 1, then 1 to -1)
    // and store it in the buffer. Notice: generating the wavetable does
    // not depend on the audio sample rate (why not?)
    for (unsigned int n = 0; n < gWavetableLength / 2; n++)
    {
      gWavetable[n] = -1.0 + 4.0 * (float)n / (float)gWavetableLength;
    }
    for (unsigned int n = gWavetableLength / 2; n < gWavetableLength; n++)
    {
      gWavetable[n] = 1.0 - 4.0 * (float)(n - gWavetableLength / 2) / (float)gWavetableLength;
    }
  }
};


int waveTable(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData)
{

  RtWaveTableCallback<512> *userDataCasted = (RtWaveTableCallback<512> *)userData;
  return userDataCasted->render(outputBuffer, inputBuffer, nBufferFrames, streamTime, status);

  
}