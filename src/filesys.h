#ifndef FILESYS_H_
#define FILESYS_H_

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace f_sys = std::filesystem;

namespace Slime {

void execute_command(const std::string &command,
                     std::vector<std::string> inputs) {
  // executes the command
  std::string full_argument = command;
  for (int i = 1; i < inputs.size(); ++i) {
    full_argument += " " + inputs[i];
  }
  int system = std::system(full_argument.c_str());
}

std::vector<std::string> get_directories(const char *char_path) {
  std::string_view path(char_path);
  std::vector<std::string> result;

  for (auto &&word : path | std::views::split(':')) {
    result.emplace_back(word.begin(), word.end());
  }
  return result;
}

bool check_file_permission_status(const f_sys::path &path) {
  auto status = f_sys::status(path);
  auto permissions = status.permissions();
  // if ((permissions & f_sys::perms::owner_write) != f_sys::perms::none) return
  // false; if ((permissions & f_sys::perms::owner_read) != f_sys::perms::none)
  // return false;
  if ((permissions & f_sys::perms::owner_exec) != f_sys::perms::none)
    return true;
  return false;
}

std::string find_in_path(const std::string &command, const char *path) {
  if (!path) {
    return "";
  }
  std::vector<std::string> directories = std::move(get_directories(path));

  for (const auto &dir : directories) {
    f_sys::path full_path = f_sys::path(dir) / command;
    if (f_sys::exists(full_path)) {
      if (check_file_permission_status(full_path) == false)
        continue;
      return full_path.string();
    }
  }
  return "";
}

bool is_executable(const std::string &command, const char *path) {
  std::string &&full_path = std::move(find_in_path(command, path));
  return full_path.size() > 0;
}

} // namespace Slime

#endif // FILESYS_H_
