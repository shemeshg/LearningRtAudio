# Learning RtAudio

My path for Learning RtAudio with the excellent Bela.io tutorial

https://learn.bela.io/tutorials/c-plus-plus-for-real-time-audio-programming/real-time/

For now developing on local computer until having the actual Bela device...

I use these resources for personal learning, nothing proffesional.

* For emlating analog output/input i chose 
    https://github.com/ExistentialAudio/BlackHole
    and 
    https://vcvrack.com/
* fourie visualisation I use Pandas workbook (runs on Anaconda) or VCV module.

See in tools folder.

* Had to remember to do `git submodule update --init` since using DSP-Cpp-filters

* for some reasone  (OS Security settings) Audio Inputs produce zores when run directlly from QtCreator,
    When running from the build directory in terminal it runs fine (outputs from QtCreate works also fine).
    
## Branches lessons

It is one to one the assignments in the course, but adjusted to desktop

- Lesson 1-2 Settingup RtAudio libSndfile, Playing Recorded Samples, Play sin wave
- Lesson 3   Wavetables
- Lesson 4   Parameters control using Qt QWidgets
- Lesson 5   Wavetable harmonies and aliassing
- Lesson 6   Read Input generated in VCV rack using Blackhole
- Lesson 7   Gate, trigger, and switch component tp seitch between different streams.
- Lesson 8   Filters (Havent done any homework assignment, just encapsulated DSP-Cpp-filters)
- Lesson 9   Time - Scheduale events with a concept of Gate and Reset
- lesson10   latency
- lesson11   Circular_Buffers
- lesson12   envelopes
- lesson13   State Machines DebounceVca