#pragma once

#include"Entity.hpp"
#include"ClassType.hpp"
#include"Ability.hpp"

namespace dungeon {

struct Monster: Entity {
  int expDrop, coinDrop;
  Monster(
    ClassType, std::string name,
    int hp, int atk, int level,
    int cr, int cd,
    std::unique_ptr<Ability>&& na,
    std::unique_ptr<Ability>&& skill,
    int exp, int coin
  );
};

struct Slime: Monster {
  Slime();
};

struct SlimeNA: Ability {
  SlimeNA();
};

struct SlimeSkill: Ability {
  SlimeSkill();
};

template<ClassType C>
struct Goblin: Monster {
  Goblin();
};

struct GoblinNA: Ability {
  GoblinNA();
};

struct GoblinSkill: Ability {
  GoblinSkill();
};

struct Boss: Monster {
  Boss(
    ClassType, std::string name,
    int hp, int atk, int level,
    int cr, int cd,
    std::unique_ptr<Ability>&& na,
    std::unique_ptr<Ability>&& skill
  );
};

struct Rimuru: Boss {
  Rimuru();
};

struct RimuruNA: Ability {
  RimuruNA();
};

struct RimuruSkill: Ability {
  RimuruSkill();
};

}