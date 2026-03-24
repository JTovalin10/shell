#include <filesystem>
#include <iostream>

#include "BuiltInCommand.hpp"

namespace Slime {
void insert_files_in_trie();
}  // namespace Slime

namespace fs = std::filesystem;

class CdCommand : public BuiltInCommand {
 public:
  std::string Name() const override { return "cd"; }

  void Execute(const std::vector<std::string>& args) override {
    std::string desired_path = args[1];
    // edge case where its "~"
    if (desired_path == "~") desired_path = std::getenv("HOME");
    if (fs::exists(desired_path) && fs::is_directory(desired_path)) {
      try {
        fs::current_path(desired_path);
        FileAutoComplete::Clear();
        Slime::insert_files_in_trie();
      } catch (const fs::filesystem_error& e) {
        // asumes the path is correct
        std::cerr << "cd: " << desired_path << ": No such file or directory\n";
      }
    } else {
      std::cerr << "cd: " << desired_path << ": No such file or directory\n";
    }
  }
};  // namespace std::filesystem

static bool cd_registred = []() {
  CommandRegistry::Add(std::make_unique<CdCommand>());
  return true;
}();