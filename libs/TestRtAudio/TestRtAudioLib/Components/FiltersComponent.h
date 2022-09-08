#pragma once
#include "DSP-Cpp-filters/lib/filter_common.h"
#include "DSP-Cpp-filters/lib/filter_includes.h"

namespace {
    constexpr int default_fs = 48000;
    constexpr int default_fc = 5000;
}

namespace RtAudioNs
{
  namespace Components
  {
    class FiltersComponent
    {
    public:

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

      FiltersComponent(const FILTER_TYPE _filterType,  int sampleRate) : fs{sampleRate}
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
          filter = std::make_unique<FO_APF>();
          break;
        case FILTER_FO_HPF:
          filter = std::make_unique<FO_HPF>();
          break;
        case FILTER_FO_LPF:
          filter = std::make_unique<FO_LPF>();
          break;
        case FILTER_FO_SHELVING_HIGH:
          filter = std::make_unique<FO_SHELVING_HIGH>();
          break;
        case FILTER_FO_SHELVING_LOW:
          filter = std::make_unique<FO_SHELVING_LOW>();
          break;
        case FILTER_SO_APF:
          filter = std::make_unique<SO_APF>();
          break;
        case FILTER_SO_BPF:
          filter = std::make_unique<SO_BPF>();
          break;
        case FILTER_SO_BSF:
          filter = std::make_unique<SO_BSF>();
          break;
        case FILTER_SO_BUTTERWORTH_BPF:
          filter = std::make_unique<SO_BUTTERWORTH_BPF>();
          break;
        case FILTER_SO_BUTTERWORTH_BSF:
          filter = std::make_unique<SO_BUTTERWORTH_BSF>();
          break;
        case FILTER_SO_BUTTERWORTH_HPF:
          filter = std::make_unique<SO_BUTTERWORTH_HPF>();
          break;
        case FILTER_SO_BUTTERWORTH_LPF:
          filter = std::make_unique<SO_BUTTERWORTH_LPF>();
          break;
        case FILTER_SO_LPF:
          filter = std::make_unique<SO_LPF>();
          break;
        case FILTER_SO_HPF:
          filter = std::make_unique<SO_HPF>();
          break;
        case FILTER_SO_LINKWITZ_RILEY_HPF:
          filter = std::make_unique<SO_LINKWITZ_RILEY_HPF>();
          break;
        case FILTER_SO_LINKWITZ_RILEY_LPF:
          filter = std::make_unique<SO_LINKWITZ_RILEY_LPF>();
          break;
        case FILTER_SO_PARAMETRIC_CQ_BOOST:
          filter = std::make_unique<SO_PARAMETRIC_CQ_BOOST>();
          break;
        case FILTER_SO_PARAMETRIC_CQ_CUT:
          filter = std::make_unique<SO_PARAMETRIC_CQ_CUT>();
          break;
        case FILTER_SO_PARAMETRIC_NCQ:
          filter = std::make_unique<SO_PARAMETRIC_NCQ>();
          break;
        }
      }

      void calculate_coeffs()
      {
        if (filterType == FILTER_FO_APF)
        {
          FO_APF *a =  dynamic_cast<FO_APF *>(filter.get());
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_FO_HPF)
        {
          FO_HPF *a = dynamic_cast<FO_HPF *>(filter.get());
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_FO_LPF)
        {
          FO_LPF *a = dynamic_cast<FO_LPF *>(filter.get());
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_FO_SHELVING_HIGH)
        {
          FO_SHELVING_HIGH *a = dynamic_cast<FO_SHELVING_HIGH *>(filter.get());
          a->calculate_coeffs(gain_db, fc, fs);
        }
        else if (filterType == FILTER_FO_SHELVING_LOW)
        {
          FO_SHELVING_LOW *a = dynamic_cast<FO_SHELVING_LOW *>(filter.get());
          a->calculate_coeffs(gain_db, fc, fs);
        }
        else if (filterType == FILTER_SO_APF)
        {
          SO_APF *a = dynamic_cast<SO_APF *>(filter.get());
          a->calculate_coeffs(Q, fs);
        }
        else if (filterType == FILTER_SO_BPF)
        {
          SO_BPF *a =dynamic_cast<SO_BPF *>(filter.get());
          a->calculate_coeffs(Q, fc, fs);
        }
        else if (filterType == FILTER_SO_BSF)
        {
          SO_BSF *a = dynamic_cast<SO_BSF *>(filter.get());
          a->calculate_coeffs(Q, fc, fs);
        }
        else if (filterType == FILTER_SO_BUTTERWORTH_BPF)
        {
          SO_BUTTERWORTH_BPF *a = dynamic_cast<SO_BUTTERWORTH_BPF *>(filter.get());
          a->calculate_coeffs(bw, fc, fs);
        }
        else if (filterType == FILTER_SO_BUTTERWORTH_BSF)
        {
          SO_BUTTERWORTH_BSF *a = dynamic_cast<SO_BUTTERWORTH_BSF *>(filter.get());
          a->calculate_coeffs(bw, fc, fs);
        }
        else if (filterType == FILTER_SO_BUTTERWORTH_HPF)
        {
          SO_BUTTERWORTH_HPF *a = dynamic_cast<SO_BUTTERWORTH_HPF *>(filter.get());
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_SO_BUTTERWORTH_LPF)
        {
          SO_BUTTERWORTH_LPF *a = dynamic_cast<SO_BUTTERWORTH_LPF *>(filter.get());
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_SO_LPF)
        {
          SO_LPF *a = dynamic_cast<SO_LPF *>(filter.get());
          a->calculate_coeffs(Q, fc, fs);
        }
        else if (filterType == FILTER_SO_HPF)
        {
          SO_HPF *a = dynamic_cast<SO_HPF *>(filter.get());
          a->calculate_coeffs(Q, fc, fs);
        }
        else if (filterType == FILTER_SO_LINKWITZ_RILEY_HPF)
        {
          SO_LINKWITZ_RILEY_HPF *a = dynamic_cast<SO_LINKWITZ_RILEY_HPF *>(filter.get());
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_SO_LINKWITZ_RILEY_LPF)
        {
          SO_LINKWITZ_RILEY_LPF *a = dynamic_cast<SO_LINKWITZ_RILEY_LPF *>(filter.get());
          a->calculate_coeffs(fc, fs);
        }
        else if (filterType == FILTER_SO_PARAMETRIC_CQ_BOOST)
        {
          SO_PARAMETRIC_CQ_BOOST *a = dynamic_cast<SO_PARAMETRIC_CQ_BOOST *>(filter.get());
          a->calculate_coeffs(gain_db, Q, fc, fs);
        }
        else if (filterType == FILTER_SO_PARAMETRIC_CQ_CUT)
        {
          SO_PARAMETRIC_CQ_CUT *a = dynamic_cast<SO_PARAMETRIC_CQ_CUT *>(filter.get());
          a->calculate_coeffs(gain_db, Q, fc, fs);
        }
        else if (filterType == FILTER_SO_PARAMETRIC_NCQ)
        {
          SO_PARAMETRIC_NCQ *a = dynamic_cast<SO_PARAMETRIC_NCQ *>(filter.get());
          a->calculate_coeffs(gain_db, Q, fc, fs);
        }
      }

      void setFc(int _fc)
      {
        if (_fc != fc)
        {
          fc = _fc;
          calculate_coeffs();
        }
      }

      void setQ(float _Q)
      {
        if (_Q != Q)
        {
          Q = _Q;
          calculate_coeffs();
        }
      }

      void setGain_db(float _gain_db)
      {
        if (_gain_db != gain_db)
        {
          gain_db = _gain_db;
          calculate_coeffs();
        }
      }

      void setBw(float _bw)
      {
        if (_bw != bw)
        {
          bw = _bw;
          calculate_coeffs();
        }
      }

    private:
      std::unique_ptr<Biquad> filter;
      int fs = default_fs;
      int fc = default_fc;
      float Q = 1;
      float gain_db = 0;
      float bw = 0;
      FILTER_TYPE filterType = FILTER_SO_LPF;
    };
  }
}
