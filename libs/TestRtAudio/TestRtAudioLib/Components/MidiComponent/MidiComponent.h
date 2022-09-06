#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "RtMidi.h"

namespace RtAudioNs
{
  namespace Components
  {
    class MidiInPort
    {
    public:
      int portId = -1;
      std::string portName = "";
      std::unique_ptr<RtMidiIn> rtMidiIn;
      bool isOpened = false;
    };

    class MidiComponent
    {
    public:
      std::map<int, MidiInPort> midiInPorts;
      void refrehInPorts()
      {
        midiInPorts.clear();
        try
        {
          rtMidiIn = std::make_unique<RtMidiIn>();
        }
        catch (RtMidiError &error)
        {
          error.printMessage();
          throw error;
        }

        // Check inputs.
        unsigned int nPorts = rtMidiIn->getPortCount();
        std::string portName;
        for (unsigned int i = 0; i < nPorts; i++)
        {
          try
          {
            portName = rtMidiIn->getPortName(i);
          }
          catch (RtMidiError &error)
          {
            error.printMessage();
            throw error;
          }
          MidiInPort mip;
          mip.portId = i;
          mip.portName = portName;
          midiInPorts[i] = std::move(mip);
        }        
      }

      void printInPorts()
      {
        std::cout << "Midi:\n";
        for (const auto &[key, value] : midiInPorts)
        {
          std::cout<< "  Input Port #" << key << ": " << value.portName << '\n';
        }
      }

      void openInPort(int portNumber)
      {
        MidiInPort &mip = midiInPorts.at(portNumber);
        if (mip.isOpened)
        {
          return;
        }
        else
        {
          mip.rtMidiIn = std::make_unique<RtMidiIn>();
          mip.rtMidiIn->openPort(portNumber);          
          // Don't ignore sysex, timing, or active sensing messages.
          mip.rtMidiIn->ignoreTypes( false, false, false );
          mip.isOpened = true;
        }
      }

      void getMessage(int portNumber){
        std::vector<unsigned char> message;
        int nBytes;
        double stamp;
        stamp = midiInPorts[portNumber].rtMidiIn->getMessage( &message );
        nBytes = message.size();
        if ( nBytes > 0 ){
          std::cout << "stamp = " << stamp << " first char"<<(int)message[0]<<std::endl;
        } 
          
      }

    private:
      std::unique_ptr<RtMidiIn> rtMidiIn;
    };
  }
}