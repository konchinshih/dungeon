#pragma once

#include"Room.hpp"
#include<memory>
#include<random>
#include<deque>
#include<map>

namespace dungeon {

struct Game;

struct Map {
  std::mt19937 rndGen;
  std::deque<std::shared_ptr<Room>> roomQue;
  std::map<std::pair<int, int>, std::shared_ptr<Room>> roomMap;

  Map();
  void regenerate();
  std::shared_ptr<Room>& at(int, int);
};

}
