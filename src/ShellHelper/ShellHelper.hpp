#pragma once

#include <string>
#include <vector>

namespace Slime {
std::vector<std::string> parse_args(const std::string &user_args);

std::string find_redirect(std::vector<std::string> &args);

bool is_input_shell_type(const std::string &input) noexcept;
}; // namespace Slime
