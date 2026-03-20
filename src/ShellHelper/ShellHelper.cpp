#include "ShellHelper.hpp"

#include <algorithm>
#include <cstddef>

#include "Commands/BuiltInCommand.hpp"

enum class STATE { NORMAL, SINGLE_QUOTE, DOUBLE_QUOTE, BACKSLASH };

static constexpr char squote = '\'';
static constexpr char dquote = '"';
static constexpr char bslash = '\\';
static constexpr char space = ' ';

namespace Slime {
std::vector<std::string> parse_args(const std::string& user_args) {
  STATE state = STATE::NORMAL;
  std::vector<std::string> parsed_args{};
  std::string scurr{};
  const int size = user_args.size();
  parsed_args.reserve(size);

  for (int i = 0; i < size; ++i) {
    char curr = user_args[i];
    switch (state) {
      case STATE::NORMAL:
        if (curr == squote) {
          state = STATE::SINGLE_QUOTE;
        } else if (curr == dquote) {
          state = STATE::DOUBLE_QUOTE;
        } else if (curr == bslash) {
          state = STATE::BACKSLASH;
        } else if (curr == space) {
          if (!scurr.empty()) {
            parsed_args.push_back(scurr);
            scurr.clear();
          }
        } else {
          scurr += curr;
        }
        break;
      case STATE::SINGLE_QUOTE:
        if (curr == squote) {
          state = STATE::NORMAL;
        } else {
          scurr += curr;
        }
        break;
      case STATE::DOUBLE_QUOTE:
        if (curr == dquote) {
          state = STATE::NORMAL;
        } else if (curr == bslash && i + 1 < size) {
          char next = user_args[i + 1];
          if (next == dquote || next == bslash) {
            scurr += next;
            ++i;
          } else {
            scurr += curr;
          }
        } else {
          scurr += curr;
        }
        break;
      case STATE::BACKSLASH:
        // add the word into it and reset back to normal
        scurr += curr;
        state = STATE::NORMAL;
        break;
      default:
        break;
    }
  }
  if (!scurr.empty()) parsed_args.push_back(scurr);
  return parsed_args;
}

/**
 * Find the last directory as that is what we will output to.
 * anything that comes after the file will be treated as flags
 *
 * example: ls > example.txt hello -> ls hello > example.txt
 */
RedirectInfo find_redirect(std::vector<std::string>& args) {
  RedirectInfo info;
  int stdout_idx{-1};
  int stderr_idx{-1};
  for (size_t i{}; i < args.size(); ++i) {
    if ((args[i] == ">" || args[i] == "1>") && i + 1 < args.size()) {
      info.stdout_file = args[i + 1];
      stdout_idx = i;
    } else if (args[i] == "2>" && i + 1 < args.size()) {
      info.stderr_file = args[i + 1];
      stderr_idx = i;
    }
  }
  std::vector<int> to_remove{};
  if (stdout_idx != -1) to_remove.push_back(stdout_idx);
  if (stderr_idx != -1) to_remove.push_back(stderr_idx);
  // we want to reverse from the back to front to avoid shifting issues
  std::sort(to_remove.rbegin(), to_remove.rend());
  for (const int& i : to_remove) {
    args.erase(args.begin() + i, args.begin() + i + 2);
  }
  return info;
}

bool is_built_in(const std::string& command) noexcept {
  return CommandRegistry::IsBuiltIn(command);
}

}  // namespace Slime
