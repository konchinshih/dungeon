#pragma once

#include"IOSystem.hpp"
#include"Character.hpp"
#include"Inventory.hpp"
#include"Map.hpp"

#include<random>
#include<memory>

namespace dungeon {

struct Game {
  std::mt19937 rndGen;
  IOSystem ios;
  Map map;
  bool isGameEnded, isWon;

  std::unique_ptr<Character> mainChar;

  Game();
  void run();
  void action();
  void move();
  void enhance();
  void talkToNPC(NPC&);
  void buyItemFromNPC(NPC&);
};

}