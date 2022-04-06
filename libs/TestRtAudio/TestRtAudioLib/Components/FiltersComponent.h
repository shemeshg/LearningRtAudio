#pragma once
#include "filter_common.h"
#include "filter_includes.h"

namespace RtAudioNs
{
  namespace Components
  {
    class FiltersComponent
    {
    public:
      std::unique_ptr<Biquad> filter;
      enum FILTER_TYPE
      {
        FILTER_SO_LPF,
        FILTER_FO_APF,
        FILTER_FO_HPF,
      };

      FiltersComponent(const FILTER_TYPE _filterType, unsigned int sampleRate) : fs{sampleRate}
      {
        setFilterType(_filterType);
      }

      void setFilterType(const FILTER_TYPE _filterType)
      {
        filterType = _filterType;
        switch (filterType)
        {
        case FILTER_FO_APF:
          filter.reset(new FO_APF);
          break;
        case FILTER_FO_HPF:
          filter.reset(new FO_HPF);
          break;  
        case FILTER_FO_LPF:
          filter.reset(new FO_LPF);
          break;                  
        case FILTER_SO_LPF:
          filter.reset(new SO_LPF);
          break;
        }
      }

      void calculate_coeffs()
      {
        if (filterType == FILTER_FO_APF)
        {
          FO_APF *a = (FO_APF *)filter.get();
          a->calculate_coeffs(fc, fs);
        } else if (filterType == FILTER_FO_HPF)
        {
          FO_HPF *a = (FO_HPF *)filter.get();
          a->calculate_coeffs(fc, fs);
        } else if (filterType == FILTER_FO_LPF)
        {
          FO_LPF *a = (FO_LPF *)filter.get();
          a->calculate_coeffs(fc, fs);
        }

        else if (filterType == FILTER_SO_LPF)
        {
          SO_LPF *a = (SO_LPF *)filter.get();
          a->calculate_coeffs(Q, fc, fs);
        }
      }

    private:
      unsigned int fs = 48000;
      unsigned int fc = 5000;
      float Q = 1;
      FILTER_TYPE filterType = FILTER_SO_LPF;
    };
  }
}