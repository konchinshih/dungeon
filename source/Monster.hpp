#pragma once

#include"Entity.hpp"
#include"Class.hpp"
#include"Ability.hpp"

namespace dungeon {

struct Monster: Entity {
  int expDrop;
};

struct Slime: Monster {
  Slime();
};

template<Class C>
struct Goblin: Monster {
  Goblin();
};

struct Boss: Monster {};

struct Rimuru: Boss {
  Rimuru();
};

}