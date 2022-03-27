#pragma once
#include "OscWaveTable.h"
namespace RtAudioNs
{
namespace Components
{

    class OscWaveTableSine : public OscWaveTable
    {
    public:
      OscWaveTableSine(unsigned int sampleRate) : OscWaveTable(sampleRate)
      {
      }
      void setupWaveTable() override;
    };

}}