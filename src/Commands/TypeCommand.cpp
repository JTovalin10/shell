#include <iostream>
#include <string>
#include <vector>

#include "../FileSys/FileSys.hpp"
#include "BuiltInCommand.hpp"

class TypeCommand : public BuiltInCommand {
 public:
  std::string Name() const override { return "type"; }

  void Execute(const std::vector<std::string>& args) override {
    if (args.size() < 2) return;
    std::string type = args[1];
    if (CommandRegistry::IsBuiltIn(type)) {
      std::cout << type << " is a shell builtin\n";
      return;
    }
    std::string path = Slime::find_in_file_system(type);
    if (!path.empty()) {
      std::cout << type << " is " << path << "\n";
      return;
    }
    std::cout << type << ": not found\n";
  }
};

static bool type_registered = []() {
  CommandRegistry::Add(std::make_unique<TypeCommand>());
  return true;
}();
