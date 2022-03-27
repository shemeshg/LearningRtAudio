#pragma once
#include <string>
#include "OscWaveTable.h"

namespace RtAudioNs
{
  namespace Components
  {

    class RtGuiControl
    {
    public:
      RtGuiControl(std::string name, float &val, float min, float max, float step) : name(name), val(val), min(min), max(max), step(step)
      {
      }

      virtual ~RtGuiControl() {}

      void virtual setVal(float v) = 0;
      float const &getVal() const { return val; }
      std::string const &getName() const { return name; }
      float const &getMin() const { return min; }
      float const &getMax() const { return max; }
      float const &getStep() const { return step; }

    protected:
      float &val;

    private:
      float min;
      float max;
      float step;
      std::string name;
    };

    class RtGuiSlider : public RtGuiControl
    {
    public:
      RtGuiSlider(std::string name, float &val, float min, float max, float step) : RtGuiControl{name, val, min, max, step}
      {
      }

      void setVal(float v) override
      {
        val = v;
      }
    };

    class RtGuiSliderRefreshTableSetter : public RtGuiControl
    {
    public:
      ItfSetupWaveTable &owt;
      RtGuiSliderRefreshTableSetter(ItfSetupWaveTable &owt, std::string name, float &val, float min, float max, float step) : RtGuiControl{name, val, min, max, step}, owt{owt}
      {
      }

      void setVal(float v) override
      {
        val = v;
        owt.setupWaveTable();
      }
    };
  }
}