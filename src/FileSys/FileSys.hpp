#pragma once

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

namespace fs = std::filesystem;

namespace Slime {

void execute_shell_command(const std::vector<std::string>& inputs);

void execute_non_shell_command(const std::string& command,
                               const std::vector<std::string>& inputs);

std::vector<std::string> get_directories(const char* char_path);

bool check_file_permission_status(const fs::path& path);

std::string find_in_path(const std::string& command, const char* path);

bool is_executable(const std::string& command);

std::string find_in_file_system(const std::string& command) noexcept;

}  // namespace Slime
