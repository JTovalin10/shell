#include <cstdlib>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#include "FileSys/FileSys.hpp"
#include "ShellHelper/ShellHelper.hpp"

/**
 * Helper function that completes all other operations that are not exit
 *
 * ARGS:
 * user_input - string that contains the user input
 */
void complete_operation(const std::string& user_input) noexcept {
  std::vector<std::string> inputs = user_input | std::views::split(' ') |
                                    std::ranges::to<std::vector<std::string>>();
  std::string command = inputs[0];
  if (Slime::is_input_shell_type(command)) {
    Slime::execute_shell_command(inputs);
  } else if (Slime::is_executable(command, std::getenv("PATH"))) {
    Slime::execute_non_shell_command(command, inputs);
  } else {
    std::cout << user_input << ": command not found\n";
  }
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string user_input;
  while (true) {
    std::cout << "$ ";
    // use get line to get the entire line
    if (!std::getline(std::cin, user_input)) {
      break;
    }
    if (user_input.empty()) {
      continue;
    }
    if (user_input == "exit") {
      break;
    }
    complete_operation(user_input);
  }
  return 0;
}
