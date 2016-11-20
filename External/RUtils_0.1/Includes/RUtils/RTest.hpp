/*!***************************************************************************
@file    RTest.hpp
@author  Reverie Wisp
@par     Contact: contact@rw0.pw
@date    6/4/2016

@brief
Testing and debug tools to just throw in a project and use.

@copyright "Don't be a Jerk" (See LICENSE.md)
*****************************************************************************/
#pragma once
#include <string>
#include <ostream>
#include "RException.hpp"



//Defines for asserts doing floating point math
#define RTest_NEAR_FLOAT  .0006
#define RTest_NEAR_DOUBLE .00006

//Turns on or off an assert. If there is an assert that fails, a custom exception type is thrown. 
//Place the following line in your project or compile with the following defined: #define RTest_ASSERT_ON
#ifndef RTest_ASSERT_OFF                                       
  #define RTest_ASSERT(a) do{ if(!(a)) { throw(RUtils::RException("Assert Failed!")); } } while (0)                                                  
#endif


  /////////////////////////////////
 //Testing functions for asserts//
/////////////////////////////////
inline bool Near(double a, double b)
{
  if (a + RTest_NEAR_DOUBLE > b && a - RTest_NEAR_DOUBLE < b)
    return true;
  return false;
}


inline bool Near(float a, float b)
{
  if (a + RTest_NEAR_FLOAT > b && a - RTest_NEAR_FLOAT < b)
    return true;
  return false;
}
