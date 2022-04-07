#pragma once
#include "DSP-Cpp-filters/lib/filter_common.h"
#include "DSP-Cpp-filters/lib/filter_includes.h"

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

        FILTER_FO_APF,
        FILTER_FO_HPF,
        FILTER_FO_LPF,
        FILTER_FO_SHELVING_HIGH,
        FILTER_FO_SHELVING_LOW,
        FILTER_SO_APF,
        FILTER_SO_BPF,
        FILTER_SO_BSF,
        FILTER_SO_BUTTERWORTH_BPF,
        FILTER_SO_BUTTERWORTH_BSF,
        FILTER_SO_BUTTERWORTH_LPF,
        FILTER_SO_BUTTERWORTH_HPF,
        FILTER_SO_LPF,
        FILTER_SO_HPF,
        FILTER_SO_LINKWITZ_RILEY_HPF,
        FILTER_SO_LINKWITZ_RILEY_LPF,
        FILTER_SO_PARAMETRIC_CQ_BOOST,
        FILTER_SO_PARAMETRIC_CQ_CUT,
        FILTER_SO_PARAMETRIC_NCQ,
      };

      FiltersComponent(const FILTER_TYPE _filterType, unsigned int sampleRate) : fs{sampleRate}
      {
        setFilterType(_filterType);
      }

      void process_fc(std::vector<double> &channelData, std::vector<double> &fc_vector);

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
        case FILTER_FO_SHELVING_HIGH:
          filter.reset(new FO_SHELVING_HIGH);
          break;
        case FILTER_FO_SHELVING_LOW:
          filter.reset(new FO_SHELVING_LOW);
          break;
        case FILTER_SO_APF:
          filter.reset(new SO_APF);
          break;
        case FILTER_SO_BPF:
          filter.reset(new SO_BPF);
          break;
        case FILTER_SO_BSF:
          filter.reset(new SO_BSF);
          break;
        case FILTER_SO_BUTTERWORTH_BPF:
          filter.reset(new SO_BUTTERWORTH_BPF);
          break;
        case FILTER_SO_BUTTERWORTH_BSF:
          filter.reset(new SO_BUTTERWORTH_BSF);
          break;
        case FILTER_SO_BUTTERWORTH_HPF:
          filter.reset(new SO_BUTTERWORTH_HPF);
          break;
        case FILTER_SO_BUTTERWORTH_LPF:
          filter.reset(new SO_BUTTERWORTH_LPF);
          break;
        case FILTER_SO_LPF:
          filter.reset(new SO_LPF);
          break;
        case FILTER_SO_HPF:
          filter.reset(new SO_HPF);
          break;
        case FILTER_SO_LINKWITZ_RILEY_HPF:
          filter.reset(new SO_LINKWITZ_RILEY_HPF);
          break;
        case FILTER_SO_LINKWITZ_RILEY_LPF:
          filter.reset(new SO_LINKWITZ_RILEY_LPF);
          break;
        case FILTER_SO_PARAMETRIC_CQ_BOOST:
          filter.reset(new SO_PARAMETRIC_CQ_BOOST);
          break;
        case FILTER_SO_PARAMETRIC_CQ_CUT:
          filter.reset(new SO_PARAMETRIC_CQ_CUT);
          break;
        case FILTER_SO_PARAMETRIC_NCQ:
          filter.reset(new SO_PARAMETRIC_NCQ);
          break;
        }
      }

      void calculate_coeffs()
      {
        if (filterType == FILTER_FO_APF)
        {
          FO_APF *a = (FO_APF *)filter.get();
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_FO_HPF)
        {
          FO_HPF *a = (FO_HPF *)filter.get();
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_FO_LPF)
        {
          FO_LPF *a = (FO_LPF *)filter.get();
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_FO_SHELVING_HIGH)
        {
          FO_SHELVING_HIGH *a = (FO_SHELVING_HIGH *)filter.get();
          a->calculate_coeffs(gain_db, fc, fs);
        }
        else if (filterType == FILTER_FO_SHELVING_LOW)
        {
          FO_SHELVING_LOW *a = (FO_SHELVING_LOW *)filter.get();
          a->calculate_coeffs(gain_db, fc, fs);
        }
        else if (filterType == FILTER_SO_APF)
        {
          SO_APF *a = (SO_APF *)filter.get();
          a->calculate_coeffs(Q, fs);
        }
        else if (filterType == FILTER_SO_BPF)
        {
          SO_BPF *a = (SO_BPF *)filter.get();
          a->calculate_coeffs(Q, fc, fs);
        }
        else if (filterType == FILTER_SO_BSF)
        {
          SO_BSF *a = (SO_BSF *)filter.get();
          a->calculate_coeffs(Q, fc, fs);
        }
        else if (filterType == FILTER_SO_BUTTERWORTH_BPF)
        {
          SO_BUTTERWORTH_BPF *a = (SO_BUTTERWORTH_BPF *)filter.get();
          a->calculate_coeffs(bw, fc, fs);
        }
        else if (filterType == FILTER_SO_BUTTERWORTH_BSF)
        {
          SO_BUTTERWORTH_BSF *a = (SO_BUTTERWORTH_BSF *)filter.get();
          a->calculate_coeffs(bw, fc, fs);
        }
        else if (filterType == FILTER_SO_BUTTERWORTH_HPF)
        {
          SO_BUTTERWORTH_HPF *a = (SO_BUTTERWORTH_HPF *)filter.get();
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_SO_BUTTERWORTH_LPF)
        {
          SO_BUTTERWORTH_LPF *a = (SO_BUTTERWORTH_LPF *)filter.get();
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_SO_LPF)
        {
          SO_LPF *a = (SO_LPF *)filter.get();
          a->calculate_coeffs(Q, fc, fs);
        }
        else if (filterType == FILTER_SO_HPF)
        {
          SO_HPF *a = (SO_HPF *)filter.get();
          a->calculate_coeffs(Q, fc, fs);
        }
        else if (filterType == FILTER_SO_LINKWITZ_RILEY_HPF)
        {
          SO_LINKWITZ_RILEY_HPF *a = (SO_LINKWITZ_RILEY_HPF *)filter.get();
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_SO_LINKWITZ_RILEY_LPF)
        {
          SO_LINKWITZ_RILEY_LPF *a = (SO_LINKWITZ_RILEY_LPF *)filter.get();
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_SO_PARAMETRIC_CQ_BOOST)
        {
          SO_PARAMETRIC_CQ_BOOST *a = (SO_PARAMETRIC_CQ_BOOST *)filter.get();
          a->calculate_coeffs(gain_db, Q, fc, fs);
        }
        else if (filterType == FILTER_SO_PARAMETRIC_CQ_CUT)
        {
          SO_PARAMETRIC_CQ_CUT *a = (SO_PARAMETRIC_CQ_CUT *)filter.get();
          a->calculate_coeffs(gain_db, Q, fc, fs);
        }
        else if (filterType == FILTER_SO_PARAMETRIC_NCQ)
        {
          SO_PARAMETRIC_NCQ *a = (SO_PARAMETRIC_NCQ *)filter.get();
          a->calculate_coeffs(gain_db, Q, fc, fs);
        }
      }

      void setFc(unsigned int _fc)
      {
        if (_fc != fc)
        {
          fc = _fc;
          calculate_coeffs();
        }
      }

      void setQ(unsigned int _Q)
      {
        if (_Q != Q)
        {
          Q = _Q;
          calculate_coeffs();
        }
      }

      void setGain_db(unsigned int _gain_db)
      {
        if (_gain_db != gain_db)
        {
          gain_db = _gain_db;
          calculate_coeffs();
        }
      }

      void setBw(unsigned int _bw)
      {
        if (_bw != bw)
        {
          bw = _bw;
          calculate_coeffs();
        }
      }

    private:
      unsigned int fs = 48000;
      unsigned int fc = 5000;
      float Q = 1;
      float gain_db = 0;
      float bw = 0;
      FILTER_TYPE filterType = FILTER_SO_LPF;
    };
  }
}