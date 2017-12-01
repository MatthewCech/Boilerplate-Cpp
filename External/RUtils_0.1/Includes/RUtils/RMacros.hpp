/*!***************************************************************************
@file    RException.hpp
@author  rw
@par     contact@rw0.pw
@date    6/4/2016

@brief
A few debugging macros to assist with quickly printing values or testing.

@copyright (See RUTIL_LICENSE.md)
*****************************************************************************/
#include <iostream>

#define DEBUG_PRINT(x)     do{ std::cout << x << '\n'; } while (0)
#define DEBUG_PRINT_VAR(x) do{ std::cout << #x << " : " << x << '\n'; } while (0)
