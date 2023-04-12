#pragma once

#include"Item.hpp"

#include<iostream>
#include<vector>
#include<memory>
#include<functional>

namespace dungeon {

struct Inventory {
  std::vector<std::unique_ptr<Item>> data;

  void addItem(std::unique_ptr<Item>&&);
};

struct InventoryFilter {
  Inventory& inventory;
  std::function<bool(const std::unique_ptr<Item>&)> cond;

  InventoryFilter(Inventory&, std::function<bool(const std::unique_ptr<Item>&)>);
};

}
