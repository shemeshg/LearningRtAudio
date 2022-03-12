#pragma once

class RtWaveTableCallback
{
public:
  int gWavetableLength; // The length of the buffer in frames
  float *gWavetable;    // Buffer that holds the wavetable

  float gAmplitude = 0.5;   // Amplitude of the playback
  float gFrequency = 220.0; // Frequency (TODO: not implemented yet)
  const int gChannelsCount = 2;

  RtWaveTableCallback(int gWavetableLength) : gWavetableLength{gWavetableLength}
  {
    gWavetable = (float *)std::calloc(gWavetableLength * 2, sizeof(float));
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

      for (int frameCount = 0; frameCount < nBufferFrames && i < rowsCount; frameCount++)
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

      float nextGReadPointer = gReadPointer + phaseStep;
      if (nextGReadPointer >= gWavetableLength)
      {
        nextGReadPointer -= gWavetableLength;
      }

      buffer[bufferPosition++] = gAmplitude * getLinearInterpolation(gReadPointer, 0);
      buffer[bufferPosition++] = gAmplitude * getLinearInterpolation(gReadPointer, 1);
      gReadPointer = nextGReadPointer;
    }
    //scopeLog(buffer, nBufferFrames);
    return 0;
  }

private:
  float getLinearInterpolation(double gReadPointer, int chid)
  {
    const int currentGReadPointer = (int)gReadPointer;
    float currentGReadRemainder = gReadPointer - (int)gReadPointer;
    int nextGReadPointerInt = currentGReadPointer + 1 >= gWavetableLength ? 0 : currentGReadPointer + 1;

    float ch = this->gWavetable[currentGReadPointer * gChannelsCount + chid] +
                currentGReadRemainder * 
                (this->gWavetable[nextGReadPointerInt * gChannelsCount + chid] - this->gWavetable[currentGReadPointer * gChannelsCount + chid]);

    return ch;
  }

  void setup()
  {
    // Generate a triangle waveform (ramp from -1 to 1, then 1 to -1)
    // and store it in the buffer. Notice: generating the wavetable does
    // not depend on the audio sample rate (why not?)

    for (unsigned int n = 0; n < gWavetableLength / 2; n++)
    {
      gWavetable[n * gChannelsCount] = -1.0 + 4.0 * (float)n / (float)gWavetableLength;
      for (unsigned int i=1;i<gChannelsCount;i++){
        gWavetable[n * gChannelsCount + i] = gWavetable[n * gChannelsCount];
      }
      
    }
    for (unsigned int n = gWavetableLength / 2; n < gWavetableLength; n++)
    {
      gWavetable[n * gChannelsCount] = 1.0 - 4.0 * (float)(n - gWavetableLength / 2) / (float)gWavetableLength;
      for (unsigned int i=1;i<gChannelsCount;i++){
        gWavetable[n * gChannelsCount + i] = gWavetable[n * gChannelsCount];
      }
    }
  }
};

int waveTable(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
              double streamTime, RtAudioStreamStatus status, void *userData)
{

  RtWaveTableCallback *userDataCasted = (RtWaveTableCallback *)userData;
  return userDataCasted->render(outputBuffer, inputBuffer, nBufferFrames, streamTime, status);
}