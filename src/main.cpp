#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string user_input;
  while (true) {
    std::cout << "$ ";
    std::cin >> user_input;
    if (user_input.size() >= 0) {
      std::cout << user_input + ": command not found";
    }
    user_input.clear()
  }
  std::cout << "$ ";
  std::string user_input;

}
