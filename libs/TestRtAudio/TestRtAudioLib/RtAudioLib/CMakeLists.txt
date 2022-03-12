cmake_minimum_required(VERSION 3.0.0)
project(RtAudioLib VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)


set(RtAudioLib_SRCS
RtAudio.h
RtAudio.cpp
)

option(RTAUDIO_API_CORE "Build CoreAudio API" ${APPLE})
# CoreAudio
if (RTAUDIO_API_CORE)
  find_library(COREAUDIO_LIB CoreAudio)
  find_library(COREFOUNDATION_LIB CoreFoundation)
  list(APPEND LINKLIBS ${COREAUDIO_LIB} ${COREFOUNDATION_LIB})
  #list(APPEND LIBS_REQUIRES "-framework CoreAudio -framework CoreFoundation")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__MACOSX_CORE__")
  #list(APPEND API_LIST "core")
endif()

# Declare the library
add_library(RtAudioLib STATIC
    ${RtAudioLib_SRCS}
)
target_link_libraries (RtAudioLib PUBLIC ${LINKLIBS})
# Specify here the include directories exported
# by this library
target_include_directories(RtAudioLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)



