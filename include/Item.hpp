#pragma once

#include"ClassType.hpp"
#include"Attribute.hpp"

#include<string>
#include<memory>

namespace dungeon {

struct Item {
  ClassType type;
  std::string name;
  // std::string description;
  Attribute attr;
  virtual std::unique_ptr<Item> copy()const = 0;
};


struct WreckingBar: Item {
  WreckingBar();
  std::unique_ptr<Item> copy()const;
};

struct Excalibur: Item {
  Excalibur();
  std::unique_ptr<Item> copy()const;
};

struct WaterPistol: Item {
  WaterPistol();
  std::unique_ptr<Item> copy()const;
};

struct Rhongomyniad: Item {
  Rhongomyniad();
  std::unique_ptr<Item> copy()const;
};

struct AltereactorEngine: Item {
  AltereactorEngine();
  std::unique_ptr<Item> copy()const;
};

struct PhilosophersStone: Item {
  PhilosophersStone();
  std::unique_ptr<Item> copy()const;
};

}
