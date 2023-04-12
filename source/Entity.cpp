#include"Entity.hpp"

#include<utility>

namespace dungeon {

InventoryFilter Entity::equipped() {
  return InventoryFilter(inventory, [&](const std::unique_ptr<Item>& item) {
    return item->type == type || item->type == ClassType::ANY;
  });
}

void Entity::addItem(std::unique_ptr<Item>&& item) {
  attr += item->attr;
  inventory.addItem(std::move(item));
}

}