#include "RangeUtils.h"

float rescaleRange(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double amplitudeFromDb(double amp)
{
  return pow(10.0, amp / 20.0);
}

float constrainRange(float x, float min_val, float max_val)
{
  if (x < min_val)
    return min_val;
  if (x > max_val)
    return max_val;
  return x;
}

float midiNoteToFrequency(float noteNumber)
{
  return 440.0 * pow(2.0, (noteNumber - 69) / 12.0);
};