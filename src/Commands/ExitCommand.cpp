#include <string>
#include <vector>

#include "BuiltInCommand.hpp"

class ExitCommand : public BuiltInCommand {
 public:
  std::string Name() const override { return "exit"; }

  void Execute(const std::vector<std::string>& args) override {}
};

static bool exit_registered = []() {
  CommandRegistry::Add(std::make_unique<ExitCommand>());
  return true;
}();
