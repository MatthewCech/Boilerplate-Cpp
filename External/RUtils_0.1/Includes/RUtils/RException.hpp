/*!***************************************************************************
@file    RException.hpp
@author  rw
@par     contact@rw0.pw
@date    6/4/2016

@brief
Custom exception class designed to provide specific line and file information.

@copyright (See RUTIL_LICENSE.md)
*****************************************************************************/
#pragma once
#include <ostream> // std::ostream
#include <string>  // std::string
#include <cstring> // strrchr


namespace RUtils
{
  //Undefine the exception structure first to avoid expanding the macro.
  #undef RException
  #undef __FILENAME__
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


    /////////////////////////////
   //RException Implementation//
  /////////////////////////////
  //Handle constructor
  inline RException::RException(std::string file, unsigned int line, std::string message)
  : File(file)
  , Line(line)
  , Message(message)
  {  }

  //Define print formatting 
  inline std::ostream &operator<<(std::ostream &os, const RException &rhs)
  {
    os << "EXCEPTION: " << rhs.File << " line " << rhs.Line << ": " << rhs.Message;
    return os;
  }
  
  
#if defined(_WIN32)
  #define __FILENAME__ (strrchr("\\" __FILE__, '\\') + 1)
#else
  #define __FILENAME__ __FILE__
#endif

  //Redefube macro to allow it to expand here.
  #define RException(a) RException(__FILENAME__, __LINE__, a)
}
