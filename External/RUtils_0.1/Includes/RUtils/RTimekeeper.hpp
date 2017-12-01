/*!***************************************************************************
@file    RTimekeeper.hpp
@author  rw
@par     contact@rw0.pw
@date    1/22/2017

@brief
A class for timing sections of an application in milliseconds and getting the
average of a series of runs up to a certain number of samples. Because this is
all implemented in the header, better or worse everthing is marked inline. 

@copyright (See RUTIL_LICENSE.md)
*****************************************************************************/
#pragma once
#include <chrono> // std::chrono



namespace RUtils
{
  class Timekeeper
  {
  public:
    // Constructor and Destructor
    Timekeeper();
 
    // Static member functions
    void StartFrame();
    void EndFrame();
    int GetLastTimeMS();
    int GetAvgTimeMS();
    void SetMaxSamples(unsigned int samples);

  private:
    // Frame time markers
    std::chrono::milliseconds startTime_;
    std::chrono::milliseconds endTime_;
    
    // Other data for averaging
    double frameSamples_;
    double frameAvg_;
    long long lastTime_;
    unsigned int maxFrameSamples_;
  };
}



// Inline Implementation
namespace RUtils
{
  // Constructor initialization 
  inline Timekeeper::Timekeeper() 
    : startTime_(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()))
    , endTime_(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()))
    , frameSamples_(0)
    , frameAvg_(0)
    , lastTime_(0)
    , maxFrameSamples_(50)
  {  }


  // Start frame marker. Should be called at the start of a single cycle of the program.
  inline void Timekeeper::StartFrame()
  {
    startTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch());
  }


  // End frame marker. Should be called at the end of a single cycle of the program.
  inline void Timekeeper::EndFrame()
  {
    endTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch());

    lastTime_ = (endTime_ - startTime_).count();
    frameAvg_ = (frameSamples_ * frameAvg_ + lastTime_) / static_cast<double>(frameSamples_ + 1);
    if (frameSamples_ < maxFrameSamples_)
      frameSamples_ += 1;
  }


  // Get the last frame time in MS as an int.
  inline int Timekeeper::GetLastTimeMS()
  {
    return static_cast<int>(lastTime_);
  }


  // Returns the average frame time that has been calculated.
  inline int Timekeeper::GetAvgTimeMS()
  {
    return static_cast<int>(frameAvg_);
  }


  //Sets the total number of previous frames to take into account when averaging.
  inline void Timekeeper::SetMaxSamples(unsigned int samples)
  {
    maxFrameSamples_ = samples;
    frameSamples_ = 0;
  }
}
