#include "OscWaveTable.h"
namespace RtAudioNs
{
namespace Components
{


    class OscWaveTableAddative : public OscWaveTable
    {
    public:
      // Levels 0..1 NOT DBs
      std::vector<float> harmoniesLevels{0.5, 0, 0, 0, 0, 0, 0, 0};

      OscWaveTableAddative(unsigned int sampleRate) : OscWaveTable(sampleRate)
      {
        setupWaveTable();
      }
      void setupWaveTable() override;
    };



}}