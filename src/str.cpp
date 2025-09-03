#include "str.h"
#include <string>

std::string str::make_bold (std::string str) {
  return "\033[1m" + str + "\033[0m";
}

std::string str::make_gray (std::string str) {
  return "\033[90m" + str + "\033[0m";
}

std::string str::make_red (std::string str) {
  return "\033[31m" + str + "\033[0m";
}

std::string str::make_green (std::string str) {
  return "\033[32m" + str + "\033[0m";
}