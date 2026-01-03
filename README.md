# Learning RtAudio

A personal learning project following the excellent Bela.io real‑time audio programming tutorials:

https://learn.bela.io/tutorials/c-plus-plus-for-real-time-audio-programming/real-time/

The main DSP configuration file is here (start by modifying this one):

https://github.com/shemeshg/LearningRtAudio/blob/master/libs/TestRtAudio/TestRtAudioLib/WaveTableCallback.cpp

If you don’t have Qt installed, you can run the project from the command line using:

https://github.com/shemeshg/LearningRtAudio/blob/master/libs/TestRtAudio/main/main.cpp

This project is purely for personal learning.

## Tools & Resources

- **Virtual audio routing:**  
  - BlackHole — https://github.com/ExistentialAudio/BlackHole  
  - VCV Rack — https://vcvrack.com/

- **Fourier / signal visualization:**  
  - Pandas workbook (Anaconda)  
  - VCV Rack modules  

See the `tools` folder for related utilities.

- Remember to run:  
  `git submodule update --init`  
  (required for DSP-Cpp-filters)

- Note: Due to OS security settings, audio *input* returns zeros when running inside QtCreator.  
  Running the built binary directly from the terminal works correctly.  
  (Audio output from QtCreator works fine.)

## Branch Overview (Lessons)

These branches follow the Bela course assignments, adapted for desktop development:

- **Lesson 1–2:** RtAudio setup, libsndfile, playing samples, sine wave  
- **Lesson 3:** Wavetables  
- **Lesson 4:** Parameter control with Qt Widgets  
- **Lesson 5:** Wavetable harmonics & aliasing  
- **Lesson 6:** Input from VCV Rack via BlackHole  
- **Lesson 7:** Gate, trigger, and switching between streams  
- **Lesson 8:** Filters (DSP-Cpp-filters wrapper)  
- **Lesson 9:** Time & event scheduling (Gate + Reset concepts)  
- **Lesson 10:** Latency  
- **Lesson 11:** Circular buffers  
- **Lesson 12:** Envelopes — linear ADSR (time domain)  
- **Lesson 13:** State machines, DebounceVCA  
- **Lesson 14:** Exponential ADSR
