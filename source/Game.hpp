#pragma once

#include"IOSystem.hpp"
#include"Character.hpp"
#include"Inventory.hpp"
#include"Map.hpp"

#include<chrono>

namespace dungeon {

struct Game {
  IOSystem ios;
  Map map;
  Character mainChar;
  bool isEnd;

  void initialize();
  void welcome();
  void selectClass();
  void enterName();

  void printMapInfo();
  void action();

  void showStatus();
  void showInventory();

  void talkToNPC();

  void move();
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();

  Game();
  void run();
};

}