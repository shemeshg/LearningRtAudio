# Learning RtAudio

My path for learning RtAudio using the excellent Bela.io tutorial:

https://learn.bela.io/tutorials/c-plus-plus-for-real-time-audio-programming/real-time/

The configuration file that manages the DSP blocks is here. Start by modifying this file:

https://github.com/shemeshg/LearningRtAudio/blob/master/libs/TestRtAudio/TestRtAudioLib/WaveTableCallback.cpp

For now, I’m developing on my local computer until I have the actual Bela device.

I use these resources for personal learning, nothing professional.

* For emulating analog input/output I chose:
    https://github.com/ExistentialAudio/BlackHole  
    and  
    https://vcvrack.com/
* For Fourier visualization I use a Pandas workbook (running on Anaconda) or a VCV Rack module.

See the tools folder.

* I had to remember to run `git submodule update --init` since I'm using DSP-Cpp-filters.

* For some reason (likely OS security settings), audio inputs produce zeros when running directly from QtCreator.  
  When running from the build directory in the terminal, it works fine. (Output from QtCreator works fine as well.)

## Branch lessons

These follow the course assignments one-to-one, but adapted for desktop development:

- Lesson 1–2: Setting up RtAudio, libsndfile, playing recorded samples, playing a sine wave
- Lesson 3: Wavetables
- Lesson 4: Parameter control using Qt Widgets
- Lesson 5: Wavetable harmonies and aliasing
- Lesson 6: Reading input generated in VCV Rack using BlackHole
- Lesson 7: Gate, trigger, and switch components to switch between different streams
- Lesson 8: Filters (I haven’t done the homework assignments, just encapsulated DSP-Cpp-filters)
- Lesson 9: Time — scheduling events using Gate and Reset concepts
- Lesson 10: Latency
- Lesson 11: Circular buffers
- Lesson 12: Envelopes, linear ADSR in the *time domain*
- Lesson 13: State machines, DebounceVCA
- Lesson 14: Exponential ADSR
