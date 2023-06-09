#pragma once

#include"Room.hpp"
#include<memory>
#include<random>
#include<vector>
#include<map>

namespace dungeon {

struct Character;

struct Map {
  std::mt19937& rndGen;
  std::vector<std::unique_ptr<Room>> roomPool;
  std::map<std::pair<int, int>, std::unique_ptr<Room>> roomMap;

  Map(std::mt19937&);
  void reGenPool();
  std::unique_ptr<Room>& at(const Character&);
};

}
