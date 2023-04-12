#include"Monster.hpp"

namespace dungeon {

Slime::Slime() {
  type = ClassType::NONE;
  name = "Slime";

  attr.baseHp = 10000;
  attr.baseAtk = 50;
  attr.critRatePercent = 5;
  attr.critDamagePercent = 50;
  curHp = attr.hp();
}

template<>
Goblin<ClassType::SABER>::Goblin() {
  type = ClassType::SABER;
  name = "Goblin saber";

  attr.baseHp = 5000;
  attr.baseAtk = 70;
  attr.critRatePercent = 5;
  attr.critDamagePercent = 50;
  curHp = attr.hp();
}

template<>
Goblin<ClassType::ARCHER>::Goblin() {
  type = ClassType::ARCHER;
  name = "Goblin archer";

  attr.baseHp = 5000;
  attr.baseAtk = 50;
  attr.critRatePercent = 15;
  attr.critDamagePercent = 50;
  curHp = attr.hp();
}

template<>
Goblin<ClassType::LANCER>::Goblin() {
  type = ClassType::LANCER;
  name = "Goblin lancer";

  attr.baseHp = 7000;
  attr.baseAtk = 50;
  attr.critRatePercent = 5;
  attr.critDamagePercent = 50;
  curHp = attr.hp();
}

template<>
Goblin<ClassType::BERSERKER>::Goblin() {
  type = ClassType::BERSERKER;
  name = "Goblin berserker";

  attr.baseHp = 3000;
  attr.baseAtk = 100;
  attr.critRatePercent = 5;
  attr.critDamagePercent = 50;
  curHp = attr.hp();
}

Rimuru::Rimuru() {
  type = ClassType::NONE;
  name = "Rimuru Tempest";

  attr.baseHp = 1000000;
  attr.baseAtk = 500;
  attr.critRatePercent = 20;
  attr.critDamagePercent = 100;
  curHp = attr.hp();
}

}