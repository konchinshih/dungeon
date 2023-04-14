#include"Monster.hpp"

namespace dungeon {

Monster::Monster(
  ClassType type, std::string name,
  int hp, int atk, int level,
  int cr, int cd,
  std::unique_ptr<Ability>&& na,
  std::unique_ptr<Ability>&& skill,
  int exp, int coin
):
  Entity(
    type, name, hp, atk, level,
    std::move(na), std::move(skill)
  ), expDrop(exp), coinDrop(coin) {
  attr.critRatePercent = cr;
  attr.critDamagePercent = cd;
}

Slime::Slime():
  Monster(
    ClassType::NONE, "Slime",
    10000, 50, 10, 5, 50,
    std::make_unique<SlimeNA>(),
    std::make_unique<SlimeSkill>(),
    100, 5
  ) {}

SlimeNA::SlimeNA():
  Ability("normal attack", 20, 50, 5, 99) {}

SlimeSkill::SlimeSkill():
  Ability("Slow Down!", 100, 0, 0, 1) {
  enemyEffects.push_back(std::make_unique<AtkSpeedDown>());
}

template<>
Goblin<ClassType::SABER>::Goblin():
  Monster(
    ClassType::SABER,
    "Goblin saber",
    5000, 70, 15, 5, 50,
    std::make_unique<GoblinNA>(),
    std::make_unique<GoblinSkill>(),
    50, 10
  ) {}

template<>
Goblin<ClassType::ARCHER>::Goblin():
  Monster(
    ClassType::ARCHER,
    "Goblin archer",
    5000, 50, 15, 15, 50,
    std::make_unique<GoblinNA>(),
    std::make_unique<GoblinSkill>(),
    50, 10
  ) {}

template<>
Goblin<ClassType::LANCER>::Goblin():
  Monster(
    ClassType::LANCER,
    "Goblin lancer",
    7000, 50, 15, 5, 50,
    std::make_unique<GoblinNA>(),
    std::make_unique<GoblinSkill>(),
    50, 10
  ) {}

template<>
Goblin<ClassType::BERSERKER>::Goblin():
  Monster(
    ClassType::BERSERKER,
    "Goblin berserker",
    3000, 100, 15, 5, 50,
    std::make_unique<GoblinNA>(),
    std::make_unique<GoblinSkill>(),
    50, 10
  ) {}

GoblinNA::GoblinNA():
  Ability("normal attack", 15, 50, 5, 99) {}

GoblinSkill::GoblinSkill():
  Ability("Crit Rate UP!", 100, 0, 0, 1) {
  selfEffects.push_back(std::make_unique<CritRateUp>());
}

Boss::Boss(
  ClassType type, std::string name,
  int hp, int atk, int level,
  int cr, int cd,
  std::unique_ptr<Ability>&& na,
  std::unique_ptr<Ability>&& skill
):
  Monster(
    type, name,
    hp, atk, cr, cd, level,
    std::move(na), std::move(skill),
    0, 0
  ) {}

Rimuru::Rimuru():
  Boss(
    ClassType::NONE,
    "Rimuru Tempest",
    1000000, 500, 50, 20, 100,
    std::make_unique<RimuruNA>(),
    std::make_unique<RimuruSkill>()
  ) {}

RimuruNA::RimuruNA():
  Ability("Water blade", 30, 70, 5, 99) {}

RimuruSkill::RimuruSkill():
  Ability("Dark Flame", 200, 300, 5, 99) {
  enemyEffects.push_back(std::make_unique<Burning>());
}

}
