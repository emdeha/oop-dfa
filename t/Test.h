#pragma once

#include <iostream>


namespace T {
void okay(bool test, std::string message) {
  if (test) {
    std::cout << "\033[32;2m   Check! \033[0m" << message << "\n";
  } else {
    std::cout << "\033[31;2m    Fail! \033[0m" << message << "\n";
  }
}
}
