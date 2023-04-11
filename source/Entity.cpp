#include"Entity.hpp"

#include<utility>
#include<cmath>

namespace dungeon {

int Entity::hp() {
  return (hpBase + inventory.total.hpAdd) *
         (1 + inventory.total.hpPercentAdd / 100.0);
}

int Entity::atk() {
  return (atkBase + inventory.total.atkAdd) *
         (1 + inventory.total.atkPercentAdd / 100.0);
}

int Entity::critRate() {
  return critRateBase + inventory.total.critRateAdd;
}

int Entity::critDamage() {
  return critDamageBase + inventory.total.critDamageAdd;
}

int Entity::atkInterval(const Ability& ability) {
  return ability.baseInterval +
         (ability.baseInterval - MIN_ATTACK_INTERVAL) * std::tanh(atkSpeed / ATKSPEED_MAGIC_NUMBER);
}

Filter Entity::equipped() {
  return Filter(inventory, [&](const std::unique_ptr<Item>& item) {
    return item->type == type || item->type == Class::any;
  });
}

}