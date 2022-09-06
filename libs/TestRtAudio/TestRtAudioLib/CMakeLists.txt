cmake_minimum_required(VERSION 3.0.0)
project(TestRtAudioLib VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include(loadLibSndFile.cmake)

include_directories(DSP-Cpp-filters/lib)

set(TestRtAudioLib_SRCS
  TestRtAudio.cpp  
  waveTable.h 
  waveTable.cpp
  WaveTableCallback.h 
  WaveTableCallback.cpp
  Components/RangeUtils.h
  Components/RangeUtils.cpp
  Components/OscWaveTable.h 
  Components/OscWaveTable.cpp
  Components/OscWaveTableAddative.h
  Components/OscWaveTableAddative.cpp
  Components/OscWaveTable2Addative.h
  Components/OscWaveTable2Addative.cpp
  Components/VcaGateComponent.h
  Components/VcaGateComponent.cpp
  Components/SwitchAmpComponent.h
  Components/SwitchAmpComponent.cpp
  Components/SwitchNHoldComponent.h
  Components/SwitchNHoldComponent.cpp
  Components/PlayWavFile.h 
  Components/PlayWavFile.cpp
  Components/FiltersComponent.h
  Components/FiltersComponent.cpp
  Components/PlayheadMarker.h
  Components/PlayheadMarker.cpp
  Components/Envelopes/SimpleAdsrComponent.h
  Components/Envelopes/SimpleAdsrComponent.cpp
  Components/Envelopes/PercussiveEnvelope.h
  Components/Envelopes/PercussiveEnvelope.cpp
  Components/Envelopes/AdsrStep.h
  Components/Envelopes/AdsrStep.cpp
  Components/Envelopes/RampageEnvelope.h 
  Components/Envelopes/RampageEnvelope.cpp
  Components/MetronomeComponent.h
  Components/MetronomeComponent.cpp
  Components/DebounceVca.h
  Components/DebounceVca.cpp
  Components/Envelopes/ExponentialAdsr.h
  Components/Envelopes/ExponentialAdsr.cpp
  Components/Envelopes/LinearAdsr.h
  Components/Envelopes/LinearAdsr.cpp
  Components/Envelopes/AdsrStepTimeDomainPower.h
  Components/Envelopes/AdsrStepTimeDomainPower.cpp
  Components/Envelopes/AdsrRender.h
  Components/Envelopes/AdsrRender.cpp
  Components/MidiComponent/MidiComponent.h
  Components/MidiComponent/MidiComponent.cpp
)

add_subdirectory(RtAudioLib)
add_subdirectory(RtMidiLib)

# Declare the library
add_library(TestRtAudioLib STATIC
    ${TestRtAudioLib_SRCS}
)
target_link_libraries (TestRtAudioLib PUBLIC RtAudioLib RtMidiLib ${LINKLIBS})

target_link_libraries(TestRtAudioLib PRIVATE ${LIBSNDFILE_LIBRARIES})

# Specify here the include directories exported
# by this library
target_include_directories(TestRtAudioLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)



