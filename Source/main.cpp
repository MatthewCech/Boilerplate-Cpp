/*!***************************************************************************
@file    main.cpp
@author  <author>
@par     <email/contact info>
@date    <date here>

@brief 
<you can put a multiline description of your application here...>

@copyright See LICENSE.md <remember to add a LICENSE.md file!>
*****************************************************************************/
#include <iostream>               // std::cout
#include <GUtils/GTimekeeper.hpp> // Rutils::RException


// Application entry point
int main(int argc, char** argv)
{
  // Timing start
  GUtils::Timekeeper t;
  t.StartFrame();   
  
  // <Some code that does things>
  int totalLines = 20;
  for (int i = 0; i < totalLines; ++i)
    std::cout << "I'm printed line number " << i + 1 << " of " << totalLines << '\n';

  // Timing end
  t.EndFrame(); 
  std::cout << "Printing all that took: " << t.GetLastTimeMS() << "ms" << std::endl;
  std::cin.ignore();
  return 0;
}
