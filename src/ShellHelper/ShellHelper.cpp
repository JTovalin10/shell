#include "ShellHelper.hpp"

#include "Commands/BuiltInCommand.hpp"

enum class STRING_STATE { NORMAL, SINGLE_QUOTE, DOUBLE_QUOTE, BACKSLASH };

namespace Slime {

// we remove constness so that we can do parsed_args[i] =
// std::move(user_args[j])
std::vector<std::string> parse_args(std::vector<std::string>& user_args) {
  STRING_STATE state = STRING_STATE::NORMAL;
  // reserver the space for the size so that we dont need to resize
  std::vector<std::string> parsed_args(user_args.size());
  // on normal whenever we reach a " ", append it to the list
  return parsed_args;
}

bool is_input_shell_type(const std::string& input) noexcept {
  return CommandRegistry::IsBuiltIn(input);
}

}  // namespace Slime