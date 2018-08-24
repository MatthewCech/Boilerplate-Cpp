/*!***************************************************************************
@file    GStrings.hpp
@author  Matthew Cech
@date    8/24/2018

@brief
Custom exception class designed to provide specific line and file information.
Part of the General Utilities project.

@copyright (See LICENSE.md)
*****************************************************************************/
#pragma once
#include <algorithm> // std::find_if
#include <ostream>   // std::ostream
#include <string>    // std::string, std::getline
#include <cstring>   // std::isspace, strrchr
#include <sstream>   // std::istringstream



namespace GStrings
{
  // Splits a string on a specific character
  std::vector<std::string> Split(std::string input, char splitChar)
  {
    std::vector<std::string> output = std::vector<std::string>();

    if (input.size() == 0)
      return output;

    std::istringstream ss(input);
    std::string token;

    while (std::getline(ss, token, splitChar))
      output.push_back(token);

    return output;
  }

  // Removes isspace defined characters at the beginning of a string
  void TrimStart(std::string &str)
  {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int character) {
      return !std::isspace(character);
    }));
  }

  // Removes isspace defined characters at the end of a string
  void TrimEnd(std::string &str)
  {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int character) {
      return !std::isspace(character);
    }).base(), str.end());
  }

  // Removes isspace defined characters from the beginning and end of a string
  void Trim(std::string &str)
  {
    TrimStart(str);
    TrimEnd(str);
  }
}
