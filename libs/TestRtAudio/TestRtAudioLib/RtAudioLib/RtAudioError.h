#pragma once
#include <iostream>
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