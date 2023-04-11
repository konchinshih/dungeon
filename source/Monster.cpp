#include"Monster.hpp"

namespace dungeon {

Slime::Slime() {
  type = Class::none;
  name = "Slime";
  hpBase = 10000;
  atkBase = 50;
  critRateBase = 5;
  critDamageBase = 50;
  energy = 5;
  curHp = hp();
}

template<>
Goblin<Class::saber>::Goblin() {
  type = Class::saber;
  name = "Goblin saber";
  hpBase = 5000;
  atkBase = 70;
  critRateBase = 5;
  critDamageBase = 50;
  curHp = hp();
}

template<>
Goblin<Class::archer>::Goblin() {
  type = Class::archer;
  name = "Goblin archer";
  hpBase = 5000;
  atkBase = 50;
  critRateBase = 15;
  critDamageBase = 50;
  curHp = hp();
}

template<>
Goblin<Class::lancer>::Goblin() {
  type = Class::lancer;
  name = "Goblin lancer";
  hpBase = 7000;
  atkBase = 50;
  critRateBase = 5;
  critDamageBase = 50;
  curHp = hp();
}

template<>
Goblin<Class::berserker>::Goblin() {
  type = Class::berserker;
  name = "Goblin berserker";
  hpBase = 3000;
  atkBase = 100;
  critRateBase = 5;
  critDamageBase = 50;
  curHp = hp();
}

Rimuru::Rimuru() {
  type = Class::none;
  name = "Rimuru Tempest";
  hpBase = 1000000;
  atkBase = 500;
  critRateBase = 20;
  critDamageBase = 100;
  curHp = hp();
}

}