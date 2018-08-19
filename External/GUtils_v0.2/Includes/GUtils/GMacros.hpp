/*!***************************************************************************
@file    GMacros.hpp
@author  Matthew Cech
@date    6/4/2016

@brief
A few debugging macros to assist with quickly printing values or testing.
Part of the General Utilities project.

@copyright (See LICENSE.md)
*****************************************************************************/
#include <iostream> // Debug printing
#include <chrono>   // MS_SINCE_EPOCH 

// Which OS style? Windows or *Nix?
#if defined (windows | WINDOWS | WIN32 | _WIN32 | _WIN32_)
  #define OS_WINDOWS
#else
  #define OS_NIX
#endif

// Useful for dumping variable names and values in a standard way.
#define DEBUG_PRINT(x)     do{ std::cout << x << '\n'; } while (0)
#define DEBUG_PRINT_VAR(x) do{ std::cout << #x << " : " << x << '\n'; } while (0)

// More clear than writing =0 when creating abstract classes
#define ABSTRACT =0

// Gets milliseconds since epoch but hides the <chrono> gymnastics for you
#define MS_SINCE_EPOCH (std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count())
