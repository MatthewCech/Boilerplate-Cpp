/*!***************************************************************************
@file    RTest.hpp
@author  Reverie Wisp
@par     Contact: contact@rw0.pw
@date    6/4/2016

@brief
Testing and debug tools to just throw in a project and use.
File contains basic timekeeping class and basic exception structure. Quickly
smashed the implementation into the header.

@copyright "Don't be a Jerk" (See LICENSE.md)
*****************************************************************************/
#pragma once
#include <string>
#include <ostream>



//Defines for asserts doing floating point math
#define RTest_NEAR_FLOAT  .0006
#define RTest_NEAR_DOUBLE .00006

//Turns on or off an assert. If there is an assert that fails, a custom exception type is thrown. 
//Place the following line in your project or compile with the following defined: #define RTest_ASSERT_ON
#ifndef RTest_ASSERT_OFF                                       
  #define RTest_ASSERT(a) do{ if(!(a)) { throw(RTest::RException("Assert Failed!")); } } while (0)                                                  
#endif


#pragma once

//Prototypes:
namespace RException
{
  //Undefine the exception structure first to avoid expanding the macro.
  #undef RException
  struct RException
  {
    //Constructor
    RException(std::string file, unsigned int line, std::string message);

    //Member functions and Friends
    friend std::ostream &operator<<(std::ostream &os, const RException &rhs);

    //Data
    std::string File;
    unsigned int Line;
    std::string Message;
  };
}

namespace RTest
{
    /////////////////////////////////
   //Testing functions for asserts//
  /////////////////////////////////
  bool Near(double a, double b)
  {
    if (a + RTest_NEAR_DOUBLE > b && a - RTest_NEAR_DOUBLE < b)
      return true;
    return false;
  }

  bool Near(float a, float b)
  {
    if (a + RTest_NEAR_FLOAT > b && a - RTest_NEAR_FLOAT < b)
      return true;
    return false;
  }






    //////////////
   //RException//
  //////////////
  //Handle constructor
  RException::RException(std::string file, unsigned int line, std::string message)
  : File(file)
  , Line(line)
  , Message(message)
  {  }

  //Define print formatting 
  std::ostream &operator<<(std::ostream &os, const RException &rhs)
  {
    os << "!! EXCEPTION: " << rhs.File << " line " << rhs.Line << ": " << rhs.Message;
    return os;
  }
  
  //Redefube macro to allow it to expand here.
  #define RException(a) RException(__FILE__, __LINE__, a)

}
