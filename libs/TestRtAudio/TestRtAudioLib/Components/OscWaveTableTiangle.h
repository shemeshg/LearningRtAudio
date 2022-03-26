#include "OscWaveTable.h"
namespace RtAudioNs
{
namespace Components
{
    class OscWaveTableTiangle : public OscWaveTable
    {
    public:
      OscWaveTableTiangle(unsigned int sampleRate) : OscWaveTable(sampleRate)
      {
        setupWaveTable();
      }
      void setupWaveTable() override;
    };

}}