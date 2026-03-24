#pragma once

#include <string>
#include <vector>

#include "Trie/Trie.hpp"

class FileAutoComplete {
 public:
  static void Add(const std::string& cmd) { GetTrie().insert(cmd.c_str()); }

  static std::vector<std::string> Run(const char* word) {
    std::vector<std::string> res = GetTrie().autocomplete(word);
    return res;
  }

  static void Clear() { GetTrie().clear(); }

 private:
  static Trie& GetTrie() {
    static Trie instance{};
    return instance;
  }
};