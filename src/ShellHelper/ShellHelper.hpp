#pragma once

#include <string>
#include <vector>

namespace Slime {
std::vector<std::string> parse_args(
    const std::vector<std::string>& user_args);

bool is_input_shell_type(const std::string& input) noexcept;
};  // namespace Slime
