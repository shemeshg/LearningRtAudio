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
    