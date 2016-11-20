/*!***************************************************************************
@file    Timekeeper.hpp
@author  Reverie Wisp
@par     Contact: contact@rw0.pw
@date    6/4/2016

@brief
A class for timing sections of an application in milliseconds and getting the
average of a series of runs up to a certain number of samples.

@copyright "Don't be a Jerk" (See LICENSE.md)
*****************************************************************************/
#pragma once
#include <chrono> // std::chrono



namespace RUtils
{

  class Timekeeper
  {
  public:
    //Static member functions
    static void StartFrame();
    static void EndFrame();
    static int GetLastTimeMS();
    static int GetAvgTimeMS();
    static void SetMaxSamples(unsigned int samples);

  private:
    //Frame time markers
    static std::chrono::milliseconds startTime_;
    static std::chrono::milliseconds endTime_;

    //Other data for averaging
    static double frameSamples_;
    static double frameAvg_;
    static long long lastTime_;
    static unsigned int maxFrameSamples_;
  };


  //Static time initialization
  std::chrono::milliseconds Timekeeper::startTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
  std::chrono::milliseconds Timekeeper::endTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
  double Timekeeper::frameSamples_ = 0;
  double Timekeeper::frameAvg_ = 0;
  long long Timekeeper::lastTime_ = 0;
  unsigned int Timekeeper::maxFrameSamples_ = 50;


  //Start frame marker. Should be called at the start of a single cycle of the program.
  inline void Timekeeper::StartFrame()
  {
    startTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch());
  }


  //End frame marker. Should be called at the end of a single cycle of the program.
  inline void Timekeeper::EndFrame()
  {
    endTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch());

    lastTime_ = (endTime_ - startTime_).count();
    frameAvg_ = (frameSamples_ * frameAvg_ + lastTime_) / static_cast<double>(frameSamples_ + 1);
    if (frameSamples_ < maxFrameSamples_)
      frameSamples_ += 1;
  }


  //Get the last frame time in MS as an int.
  inline int Timekeeper::GetLastTimeMS()
  {
    return static_cast<int>(lastTime_);
  }


  //Returns the average frame time that has been calculated.
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
