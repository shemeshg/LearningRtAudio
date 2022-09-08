#include "RangeUtils.h"

double rescaleRange(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double amplitudeFromDb(double amp)
{
  constexpr double dbBase = 10.0;
  constexpr double dbPow = 10.0;
  return pow(dbBase, amp / dbPow);
}

double constrainRange(double x, double min_val, double max_val)
{
  if (x < min_val)
    return min_val;
  if (x > max_val)
    return max_val;
  return x;
}

double midiNoteToFrequency(double noteNumber)
{
  return freqA * pow(octavePow, (noteNumber - baseNoteMidiNumber) / octaveSemitons);
};