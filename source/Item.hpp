#pragma once

#include"Class.hpp"

#include<iostream>
#include<string>

namespace dungeon {

struct Inventory;
struct Entity;

struct Item {
  Class type;
  std::string name;
  // std::string description;
  int hpAdd, atkAdd;
  int hpPercentAdd, atkPercentAdd;
  int critRateAdd, critDamageAdd;

  Item();
  Item& operator+=(const Item&);
};

struct WreckingBar: Item {
  WreckingBar();
};

struct Excalibur: Item {
  Excalibur();
};

struct WaterPistol: Item {
  WaterPistol();
};

struct Rhongomyniad: Item {
  Rhongomyniad();
};

struct AltereactorEngine: Item {
  AltereactorEngine();
};

struct PhilosophersStone: Item {
  PhilosophersStone();
};

}
