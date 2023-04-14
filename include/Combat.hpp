#pragma once

#include"IOSystem.hpp"
#include"Character.hpp"
#include"Monster.hpp"
#include"CombatOption.hpp"

#include<chrono>
#include<random>

namespace dungeon {

struct Combat {
  std::mt19937& rndGen;
  IOSystem& ios;
  Character& mainChar;
  Monster& enemy;

  bool isWon, isCombatEnded;

  Combat(
    std::mt19937&,
    IOSystem&,
    Character&,
    Monster&
  );

  bool isActionAvailable();

  void run();
  void action();
  void enemyAction();
  void takeEffect(Entity&);

  void attack(
    Entity& target,
    Entity& attacker,
    const Ability& ability
  );
  void getReward();
};

}
