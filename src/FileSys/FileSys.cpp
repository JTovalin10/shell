#include "FileSys.hpp"

#include "Commands/BuiltInCommand.hpp"

namespace Slime {

void execute_shell_command(const std::vector<std::string>& inputs) {
  CommandRegistry::Run(inputs[0], inputs);
}

void execute_non_shell_command(const std::string& command,
                               const std::vector<std::string>& inputs) {
  pid_t pid = fork();
  // we already parsed inputs and cleaned it so we have to use this so the
  // library doesnt attempt to parse it again
  if (pid == 0) {
    // child process
    std::vector<char*> argv;
    argv.reserve(inputs.size());
    for (const auto& s : inputs) {
      argv.push_back(const_cast<char*>(s.c_str()));
    }
    argv.push_back(nullptr);
    execvp(command.c_str(), argv.data());
  } else {
    // parent thread
    int status;
    waitpid(pid, &status, 0);
  }
}

std::vector<std::string> get_directories(const char* char_path) {
  if (!char_path) return {};
  std::string_view path(char_path);
  std::vector<std::string> result;

  for (auto&& word : path | std::views::split(':')) {
    result.emplace_back(word.begin(), word.end());
  }
  return result;
}

bool check_file_permission_status(const fs::path& path) {
  auto status = fs::status(path);
  auto permissions = status.permissions();
  return (permissions & fs::perms::owner_exec) != fs::perms::none;
}

std::string find_in_path(const std::string& command, const char* path) {
  if (!path) {
    return "";
  }
  std::vector<std::string> directories = get_directories(path);

  for (const auto& dir : directories) {
    fs::path full_path = fs::path(dir) / command;
    if (fs::exists(full_path)) {
      if (!check_file_permission_status(full_path)) continue;
      return full_path.string();
    }
  }
  return "";
}

bool is_executable(const std::string& command) {
  const char* path = std::getenv("PATH");
  std::string full_path = find_in_path(command, path);
  return !full_path.empty();
}

std::string find_in_file_system(const std::string& command) noexcept {
  char* path = std::getenv("PATH");
  // base case
  return find_in_path(command, path);
}

}  // namespace Slime