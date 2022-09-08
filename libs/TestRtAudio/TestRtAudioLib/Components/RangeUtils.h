#pragma once
#include <cmath>
#include <vector>

double rescaleRange(double x, double in_min, double in_max, double out_min, double out_max);

double constrainRange(double x, double min_val, double max_val);

double midiNoteToFrequency(double noteNumber);

double amplitudeFromDb(double amp);

inline int mod(int a, int b)
{
  int ret = a % b;
  return ret >= 0 ? ret : ret + b;
}

namespace
{
  constexpr double eTemperament_1 = 440.00;
  constexpr double eTemperament_2 = 466.16;
  constexpr double eTemperament_3 = 493.88;
  constexpr double eTemperament_4 = 523.25;
  constexpr double eTemperament_5 = 554.37;
  constexpr double eTemperament_6 = 587.33;
  constexpr double eTemperament_7 = 622.25;
  constexpr double eTemperament_8 = 659.25;
  constexpr double eTemperament_9 = 698.46;
  constexpr double eTemperament_10 = 739.99;
  constexpr double eTemperament_11 = 783.99;
  constexpr double eTemperament_12 = 830.61;

  constexpr int baseNoteMidiNumber = 69;
  constexpr double octavePow = 2.0;
  constexpr double octaveSemitons = 12.0;
  constexpr double freqA = 440.0;
}

class CustomMidiScale
{
public:
  double cMidiNoteToFrequency(double noteNumber)
  {
    double curr = midiNoteIntToFrequency(noteNumber);
    double next = midiNoteIntToFrequency(noteNumber + 1);

    double logScaleIntNoteNumber = midiLogScaleToFrequency((int)noteNumber);
    double logScaleStep = midiLogScaleToFrequency((int)noteNumber + 1) - logScaleIntNoteNumber;
    double logScaleRemain = midiLogScaleToFrequency(noteNumber) - logScaleIntNoteNumber;

    return curr + (next - curr) * (logScaleRemain / logScaleStep);
  }

private:
  // Equal temperament
  std::vector<double> scale{eTemperament_1, eTemperament_2, eTemperament_3, eTemperament_4, eTemperament_5,
                            eTemperament_6, eTemperament_7, eTemperament_8, eTemperament_9, eTemperament_10, eTemperament_11, eTemperament_12};
  double midiLogScaleToFrequency(double noteNumber)
  {
    return scale.at(0) * pow(octavePow, (noteNumber - baseNoteMidiNumber) / (float)scale.size());
  };

  double midiNoteIntToFrequency(double noteNumber)
  {
    int scaleLen = (int)scale.size();
    double dOctave = (noteNumber - baseNoteMidiNumber) / scaleLen;
    int octave = (int)dOctave;
    if (dOctave < 0)
    {
      octave = (int)dOctave - 1;
    }
    int mod = ((int)noteNumber - baseNoteMidiNumber) % scaleLen;
    if (mod < 0)
    {
      mod += scaleLen;
    }
    return scale.at(mod) * pow(2, octave);
  }
};
