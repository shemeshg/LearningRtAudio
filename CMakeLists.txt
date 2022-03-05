cmake_minimum_required(VERSION 3.0.0)
project(classTest VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)


include(CTest)
enable_testing()

add_subdirectory(RtAudioLib)

add_executable(classTest main.cpp)
target_link_libraries (classTest PUBLIC RtAudioLib ${LINKLIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
