/*!***************************************************************************
@file    main.cpp
@author  Reverie Wisp
@date    11/20/2016

@brief 
The application entry point and boilerplate main. 

@copyright "Don't be a Jerk" (See LICENSE.md)
*****************************************************************************/
#include <iostream>               // std::cout
#include <RUtils\RException.hpp>  // Rutils::RException



// Application entry point
int main(int argc, char** argv) try
{
  if (argc == 1)
    std::cout << "Hello world!" << std::endl;
  else
    throw RUtils::RException("More than one argument!");

  // Return normally.
  return 0;
}
catch(RUtils::RException e)
{
  std::cout << e << std::endl;
}
