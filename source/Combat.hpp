#pragma once

#include"IOSystem.hpp"
#include"Character.hpp"
#include"Monster.hpp"

#include<chrono>

namespace dungeon {

struct Combat {
  static constexpr auto INTERVAL_PER_TICK = std::chrono::milliseconds(100);
  IOSystem& ios;
  Character& mainChar;
  Monster& enemy;

  Combat(IOSystem&, Character&, Monster&);
  void run();
  void showEnemyStatus();
  void showCharStatus();
  bool actionAvailable();
  void action();
};

}
