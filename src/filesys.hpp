#pragma once

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include "Commands/BuiltInCommand.hpp"

namespace fs = std::filesystem;

namespace Slime {

inline void execute_shell_command(const std::vector<std::string>& inputs) {
  CommandRegistry::Run(inputs[0], inputs);
}

inline void execute_non_shell_command(const std::string &command,
                                      const std::vector<std::string> &inputs) {
  // executes the command
  std::string full_argument = command;
  for (size_t i = 1; i < inputs.size(); ++i) {
    full_argument += " " + inputs[i];
  }
  (void)std::system(full_argument.c_str());
}

inline std::vector<std::string> get_directories(const char *char_path) {
  if (!char_path)
    return {};
  std::string_view path(char_path);
  std::vector<std::string> result;

  for (auto &&word : path | std::views::split(':')) {
    result.emplace_back(word.begin(), word.end());
  }
  return result;
}

inline bool check_file_permission_status(const fs::path &path) {
  auto status = fs::status(path);
  auto permissions = status.permissions();
  return (permissions & fs::perms::owner_exec) != fs::perms::none;
}

inline std::string find_in_path(const std::string &command, const char *path) {
  if (!path) {
    return "";
  }
  std::vector<std::string> directories = get_directories(path);

  for (const auto &dir : directories) {
    fs::path full_path = fs::path(dir) / command;
    if (fs::exists(full_path)) {
      if (!check_file_permission_status(full_path))
        continue;
      return full_path.string();
    }
  }
  return "";
}

inline bool is_executable(const std::string &command, const char *path) {
  std::string full_path = find_in_path(command, path);
  return !full_path.empty();
}

inline bool is_input_shell_type(const std::string &input) noexcept {
  return CommandRegistry::IsBuiltIn(input);
}

inline std::string find_in_file_system(const std::string &command) noexcept {
  char *path = std::getenv("PATH");
  // base case
  return find_in_path(command, path);
}

} // namespace Slime
