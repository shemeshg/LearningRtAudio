#pragma once
#include "OscWaveTable.h"
namespace RtAudioNs
{
namespace Components
{

    namespace {
      constexpr float HarmonyLevel1=0.5;
    }

    class OscWaveTableAddative : public OscWaveTable
    {
    public:
      // Levels 0..1 NOT DBs
      std::vector<float> harmoniesLevels{HarmonyLevel1, 0, 0, 0, 0, 0, 0, 0};

      OscWaveTableAddative(unsigned int sampleRate) : OscWaveTable(sampleRate)
      {
      }
      void setupWaveTable() override;
    };



}}
