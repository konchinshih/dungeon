#include"Entity.hpp"

#include<utility>

namespace dungeon {

Entity::Entity(
  ClassType type,
  std::string name,
  int hp, int atk, int level,
  std::unique_ptr<Ability>&& na,
  std::unique_ptr<Ability>&& skill
):
  type(type), name(name),
  normalAttack(std::move(na)),
  skill(std::move(skill)),
  attr(hp, atk, 1, 0, 0, 0, 0, 5, 50, 0, 0, 0, 0),
  level(level) {}

InventoryFilter Entity::equipped()const {
  return InventoryFilter(inventory, [&](const std::unique_ptr<Item>& item) {
    return item->type == type || item->type == ClassType::ANY;
  });
}

void Entity::addItem(std::unique_ptr<Item>&& item) {
  if (item->type == type || item->type == ClassType::ANY)
    attr += item->attr;
  inventory.addItem(std::move(item));
}

// only use in combat
void Entity::nextTick() {
  if (curCoolDown > 0)
    curCoolDown--;
  for (auto i = effects.begin(); i != effects.end(); i++) {
    (*i)->timeLeft--;
    if ((*i)->timeLeft <= 0) {
      (*i)->end(*this);
      i = effects.erase(i);
    }
  }
}

bool operator==(const std::unique_ptr<Effect>& a, const std::unique_ptr<Effect>& b) {
  return a->name == b->name;
}

bool operator<(const std::unique_ptr<Effect>& a, const std::unique_ptr<Effect>& b) {
  return a->name < b->name;
}

}