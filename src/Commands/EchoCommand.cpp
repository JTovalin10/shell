#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "BuiltInCommand.hpp"

class EchoCommand : public BuiltInCommand {
 public:
  std::string Name() const override { return "echo"; }

  void Execute(const std::vector<std::string>& args) override {
    int i = 1;
    for (i = 1; i < args.size() - 1; ++i) {
      std::cout << args[i] << " ";
    }
    if (i < args.size()) {
      std::cout << args[i];
    }
    std::cout << std::endl;
  }
};

static bool echo_registered = []() {
  CommandRegistry::Add(std::make_unique<EchoCommand>());
  return true;
}();
