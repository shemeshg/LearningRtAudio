#pragma once
#include <cmath>
#include <vector>
float rescaleRange(float x, float in_min, float in_max, float out_min, float out_max);

float constrainRange(float x, float min_val, float max_val);

float midiNoteToFrequency(float noteNumber)
{
  return 440.0 * pow(2.0, (noteNumber - 69) / 12.0);
};

class CustomMidiScale
{
public:
  // Equal temperament
  std::vector<double> scale{440.00, 466.16, 493.88, 523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61};
  float cMidiNoteToFrequency(float noteNumber)
  {
    double curr = midiNoteIntToFrequency(noteNumber);
    double next = midiNoteIntToFrequency(noteNumber + 1);
    double reminder = noteNumber - (int)noteNumber;

    double logScaleIntNoteNumber = midiNoteToFrequency((int)noteNumber);
    double logScaleStep = midiNoteToFrequency((int)noteNumber+1) - logScaleIntNoteNumber;
    double logScaleRemain = midiNoteToFrequency(noteNumber) - logScaleIntNoteNumber;

    return curr + (next - curr) * (logScaleRemain/logScaleStep);
  }

private:
  float midiNoteIntToFrequency(float noteNumber)
  {
    int scaleLen = scale.size();
    double dOctave = (noteNumber - 69) / scaleLen;
    int octave = (int)dOctave;
    if (dOctave < 0)
    {
      octave = (int)dOctave - 1;
    }
    int mod = ((int)noteNumber - 69) % scaleLen;
    if (mod < 0)
    {
      mod += scaleLen;
    }
    return scale.at(mod) * pow(2, octave);
  }
};