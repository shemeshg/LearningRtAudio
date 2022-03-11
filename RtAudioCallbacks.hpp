#pragma once

// Two-channel sawtooth wave generator.
int sawWave(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData)
{
  unsigned int i, j;
  double *buffer = (double *)outputBuffer;
  double *lastValues = (double *)userData;
  if (status)
    std::cout << "Stream underflow detected!" << std::endl;
  // Write interleaved audio data.
  for (i = 0; i < nBufferFrames; i++)
  {
    for (j = 0; j < 2; j++)
    {
      *buffer++ = lastValues[j];
      lastValues[j] += 0.005 * (j + 1 + (j * 0.1));
      if (lastValues[j] >= 1.0)
        lastValues[j] -= 2.0;
    }
  }
  return 0;
}

int fplay(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
          double streamTime, RtAudioStreamStatus status, void *userData)
{

  double *buffer = (double *)outputBuffer;
  SndfileHandle *sndfile = reinterpret_cast<SndfileHandle *>(userData);

  if (status)
  {
    std::cout << "Stream underflow detected!" << std::endl;
  }

  int icount = 0;
  if ((icount = sndfile->readf(buffer, nBufferFrames)) != nBufferFrames)
  {
    buffer = buffer + icount;
    sndfile->seek(0, 0);
    sndfile->readf(buffer, icount);

    // std::cout << icount << " " << "Loop back\n" << std::endl;
  }

  return 0;
}

int sinWave(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData)
{
  static double frequency = 100.0;
  static double currentPhase = 0;
  static int monitorCounter = 0;

  unsigned int i, j;
  double *buffer = (double *)outputBuffer;
  double *lastValues = (double *)userData;

  if (status)
    std::cout << "Stream underflow detected!" << std::endl;

  // Write interleaved audio data.
  for (i = 0; i < nBufferFrames; i++)
  {
    const double phaseStep = (2.0 * M_PI * frequency) / 44100.0;
    currentPhase = currentPhase + phaseStep;
    if (currentPhase > 2.0 * M_PI)
    {
      currentPhase = currentPhase - 2.0 * M_PI;
    }

    for (j = 0; j < 2; j++)
    {
      *buffer++ = lastValues[j];

      lastValues[j] = sin(currentPhase);

      if (j == 0 && monitorCounter < 2000)
      {
        std::cout << monitorCounter << "," << lastValues[j] << "," << currentPhase << "," << frequency << "\n";

        monitorCounter++;
      }
    }
  }
  frequency = frequency + 3;

  return 0;
}





