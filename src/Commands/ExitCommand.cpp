#include <cstdlib>
#include <string>
#include <vector>

#include "BuiltInCommand.hpp"

class ExitCommand : public BuiltInCommand {
 public:
  std::string Name() const override { return "exit"; }

  // this will never exectue
  void Execute(const std::vector<std::string>& args) override {
    int exit_code = 0;
    if (args.size() > 1) {
      try {
        exit_code = std::stoi(args[1]);
      } catch (...) {
        exit_code = 0;
      }
    }
    std::exit(exit_code);
  }
};

static bool exit_registered = []() {
  CommandRegistry::Add(std::make_unique<ExitCommand>());
  return true;
}();
