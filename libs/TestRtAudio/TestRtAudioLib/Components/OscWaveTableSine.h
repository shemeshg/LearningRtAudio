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
        setupWaveTable();
      }
      void setupWaveTable() override;
    };

}}