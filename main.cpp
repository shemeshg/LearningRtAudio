
#include <iostream>
#include <cmath>
#include <sndfile.hh>
#include "RtAudio.h"

class RtAudioError : public std::runtime_error
{
public:
  enum Type
  {
    WARNING,
    DEBUG_WARNING,
    UNSPECIFIED,
    NO_DEVICES_FOUND,
    INVALID_DEVICE,
    MEMORY_ERROR,
    INVALID_PARAMETER,
    INVALID_USE,
    DRIVER_ERROR,
    SYSTEM_ERROR,
    THREAD_ERROR
  };

  RtAudioError(const std::string &message,
               Type type = RtAudioError::UNSPECIFIED)
      : std::runtime_error(message), type_(type) {}

  virtual void printMessage(void) const
  {
    std::cerr << '\n'
              << what() << "\n\n";
  }

  virtual const Type &getType(void) const { return type_; }

  virtual const std::string getMessage(void) const
  {
    return std::string(what());
  }

protected:
  Type type_;
};

// Two-channel sawtooth wave generator.
int sawWave(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData)
{
  unsigned int i, j;
  double *buffer = (double *)outputBuffer;
  double *lastValues = (double *)userData;
  if (status)
    std::cout << "Stream underflow detected!" << std::endl;
  // Write interleaved audio data.
  for (i = 0; i < nBufferFrames; i++)
  {
    for (j = 0; j < 2; j++)
    {
      *buffer++ = lastValues[j];
      lastValues[j] += 0.005 * (j + 1 + (j * 0.1));
      if (lastValues[j] >= 1.0)
        lastValues[j] -= 2.0;
    }
  }
  return 0;
}

int fplay( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{


  double *buffer = (double *)outputBuffer;

  // ok, i know this is not the best way to do file i/o in the audio thread, but 
  // this is just for demonstration purposes ... 
  SndfileHandle *sndfile = reinterpret_cast<SndfileHandle*>(userData);

  // Error handling !
  if ( status ){
    std::cout << "Stream underflow detected!" << std::endl;
  }

  int icount=0;
  if ( (icount=sndfile->readf(buffer, nBufferFrames)) != nBufferFrames){
    buffer=buffer+icount;
    sndfile->seek(0,0);
    sndfile->readf(buffer, icount);
       
    //std::cout << icount << " " << "Loop back\n" << std::endl;
  }

  return 0;
}


int sinWave(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData)
{
  static double frequency = 100.0;
  static double currentPhase = 0;
  static int monitorCounter = 0;

  unsigned int i, j;
  double *buffer = (double *)outputBuffer;
  double *lastValues = (double *)userData;

  if (status)
    std::cout << "Stream underflow detected!" << std::endl;

  // Write interleaved audio data.
  for (i = 0; i < nBufferFrames; i++)
  {
    const double phaseStep = (2.0 * M_PI * frequency) / 44100.0;
    currentPhase = currentPhase + phaseStep;
    if (currentPhase > 2.0 * M_PI)
    {
      currentPhase = currentPhase - 2.0 * M_PI;
    }

    for (j = 0; j < 2; j++)
    {
      *buffer++ = lastValues[j];

      lastValues[j] = sin(currentPhase);

      if (j == 0 && monitorCounter < 2000)
      {
        std::cout << monitorCounter << "," << lastValues[j] << "," << currentPhase << "," << frequency << "\n";

        monitorCounter++;
      }
    }
  }
  frequency = frequency + 100;

  return 0;
}

class TestRtAudio
{
public:
  TestRtAudio(RtAudio::Api api = RtAudio::Api::UNSPECIFIED, RtAudioErrorCallback &&errorCallback = 0) : audio{api, std::move(errorCallback)}
  {
  }

  ~TestRtAudio()
  {
    if (audio.isStreamOpen())
      audio.closeStream();
  }

  static void coutListApis()
  {
    std::vector<RtAudio::Api> apis;
    RtAudio ::getCompiledApi(apis);

    std::cout << "\nCompiled APIs:\n";
    for (size_t i = 0; i < apis.size(); i++)
      std::cout << "  " << i << ". " << RtAudio::getApiDisplayName(apis[i])
                << " (" << RtAudio::getApiName(apis[i]) << ")" << std::endl;

    return;
  }

  void coutDevicesInfo()
  {
    std::cout << "API: " << RtAudio::getApiDisplayName(audio.getCurrentApi()) << "\n";
    // Determine the number of devices available
    unsigned int devices = audio.getDeviceCount();
    // Scan through devices for various capabilities
    RtAudio::DeviceInfo info;
    for (unsigned int i = 0; i < devices; i++)
    {
      info = audio.getDeviceInfo(i);
      if (info.probed == true)
      {
        // Print, for example, the maximum number of output channels for each device
        std::cout << "  device: " << i << "\n";
        std::cout << "    probed: " << info.probed << "\n";
        std::cout << "    name: " << info.name << "\n";

        std::cout << "    outputChannels: " << info.outputChannels << "\n";
        std::cout << "    inputChannels: " << info.inputChannels << "\n";
        std::cout << "    duplexChannels: " << info.duplexChannels << "\n";
        std::cout << "    isDefaultOutput: " << info.isDefaultOutput << "\n";
        std::cout << "    isDefaultInput: " << info.isDefaultInput << "\n";

        std::cout << "    sampleRates:";
        for (int sampleRate : info.sampleRates)
        {
          std::cout << " " << sampleRate;
        }
        std::cout << "\n";

        std::cout << "    preferredSampleRate: " << info.preferredSampleRate << "\n";
        std::cout << "    nativeFormats: " << nativeFormatStr(info.nativeFormats) << "\n";
        std::cout << "\n";
      }
    }
    return;
  }

  #define		BUFFER_LEN		1024
  void playWavFile(int deviceId = -1)
  {  
    std::string fname = "//Volumes//TEMP/DeleteME//tmp//file_example_WAV_1MG.wav";
    fname = "//Volumes//TEMP//DeleteME//tmp//sample-player//slow-drum-loop.wav";  
    SndfileHandle file;

    file = SndfileHandle(fname);

    std::cout<<"Opened file"<<fname<<"\n";
    std::cout<<"    Sample rate : " << file.samplerate()<<"\n";
    std::cout<<"    Channels : " << file.channels()<<"\n";

    
    /*
    static short buffer[BUFFER_LEN];    
    file.read(buffer, BUFFER_LEN);
    */
 if (deviceId == -1)
    {
      deviceId = audio.getDefaultOutputDevice();
    }
    RtAudio::StreamParameters parameters;
    parameters.deviceId = deviceId;
    parameters.nChannels = 2;
    parameters.firstChannel = 0;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 256; // 256 sample frames
    double data[2] = {0, 0};
    try
    {
      audio.openStream(&parameters, NULL, RTAUDIO_FLOAT64,
                       sampleRate, &bufferFrames, &fplay, (void *)&file);
      audio.startStream();
    }
    catch (RtAudioError &e)
    {
      e.printMessage();
      exit(0);
    }

    char input;
    // std::cout << "\nPlaying ... press <enter> to quit.\n";
    std::cin.get(input);

    try
    {
      // Stop the stream
      audio.stopStream();
    }
    catch (RtAudioError &e)
    {
      e.printMessage();
    }   
  }

  void playSin(int deviceId = -1)
  {
    if (deviceId == -1)
    {
      deviceId = audio.getDefaultOutputDevice();
    }
    RtAudio::StreamParameters parameters;
    parameters.deviceId = deviceId;
    parameters.nChannels = 2;
    parameters.firstChannel = 0;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 256; // 256 sample frames
    double data[2] = {0, 0};
    try
    {
      audio.openStream(&parameters, NULL, RTAUDIO_FLOAT64,
                       sampleRate, &bufferFrames, &sinWave, (void *)&data);
      audio.startStream();
    }
    catch (RtAudioError &e)
    {
      e.printMessage();
      exit(0);
    }

    char input;
    // std::cout << "\nPlaying ... press <enter> to quit.\n";
    std::cin.get(input);

    try
    {
      // Stop the stream
      audio.stopStream();
    }
    catch (RtAudioError &e)
    {
      e.printMessage();
    }
  }

private:
  RtAudio audio;

  std::string const nativeFormatStr(RtAudioFormat const &i)
  {
    if (i & RTAUDIO_SINT8)
      return " 8-bit int";
    else if (i & RTAUDIO_SINT16)
      return "16-bit int";
    else if (i & RTAUDIO_SINT24)
      return "24-bit int";
    else if (i & RTAUDIO_SINT32)
      return "32-bit int";
    else if (i & RTAUDIO_FLOAT32)
      return "32-bit float";
    else if (i & RTAUDIO_FLOAT64)
      return "64-bit float";
    else
      return "No natively supported data formats(?)!";
  }
};

int main()
{
  // TestRtAudio::coutListApis();
  TestRtAudio tra;
  // tra.coutDevicesInfo();
  // tra.playSin(2);
  tra.playWavFile();
  return 0;
}