#pragma once
#include <vector>

namespace RtAudioNs
{
  namespace Components
  {
    class SimpleAdsrComponent {
      public:
      void render(std::vector<double> &vGate);

      private:
      enum SimpleAdsrStatus
      {
        idle, //idle
        a,
        d,
        s,
        r
      };
      SimpleAdsrStatus simpleAdsrStatus = SimpleAdsrStatus::idle;
    };
  }
}