#include "ShellHelper.hpp"

#include "Commands/BuiltInCommand.hpp"

namespace Slime {

bool is_input_shell_type(const std::string& input) noexcept {
  return CommandRegistry::IsBuiltIn(input);
}

}  // namespace Slime