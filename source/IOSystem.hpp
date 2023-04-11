#pragma once

#include<string>
#include<vector>

namespace dungeon {

struct IOSystem {
  static constexpr char ANSI_ESC_CLEAR[] = "\x1B[2J";
  static constexpr char ANSI_ESC_CURSOR_RESET[] = "\x1B[;H";

  std::string header;

  IOSystem();

  void clear();
  void print(const std::string& = "", bool = true);
  char inputChar(const std::string& = "");
  std::vector<std::string> inputTokens(const std::string& = "");

  void pause();
  void sleep(int = 1);
};

template<typename T>
IOSystem& operator<<(IOSystem&, const T&);

}
