cmake_minimum_required(VERSION 3.0.0)
project(TestRtAudioLib VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)


set(TestRtAudioLib_SRCS
  TestRtAudio.cpp  
  waveTable.h 
  waveTable.cpp
  WaveTableCallback.h 
  WaveTableCallback.cpp
  RangeUtils.h
  RangeUtils.cpp
  Components/OscWaveTable.h 
  Components/OscWaveTable.cpp
  Components/OscWaveTableAddative.h
  Components/OscWaveTableAddative.cpp
)

add_subdirectory(RtAudioLib)

# Declare the library
add_library(TestRtAudioLib STATIC
    ${TestRtAudioLib_SRCS}
)
target_link_libraries (TestRtAudioLib PUBLIC RtAudioLib ${LINKLIBS})
# Specify here the include directories exported
# by this library
target_include_directories(TestRtAudioLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)



