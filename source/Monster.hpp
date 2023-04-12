#pragma once

#include"Entity.hpp"
#include"ClassType.hpp"
#include"Ability.hpp"

namespace dungeon {

struct Monster: Entity {
  int expDrop;
};

struct Slime: Monster {
  Slime();
};

template<ClassType C>
struct Goblin: Monster {
  Goblin();
};

struct Boss: Monster {};

struct Rimuru: Boss {
  Rimuru();
};

}