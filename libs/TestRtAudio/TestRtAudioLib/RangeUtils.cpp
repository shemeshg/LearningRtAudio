#include "RangeUtils.h"

float rescaleRange(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float constrainRange(float x, float min_val, float max_val)
{
  if (x < min_val)
    return min_val;
  if (x > max_val)
    return max_val;
  return x;
}