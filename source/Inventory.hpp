#pragma once

#include"Item.hpp"

#include<iostream>
#include<vector>
#include<memory>
#include<functional>

namespace dungeon {

struct Entity;

struct Inventory {
  std::vector<std::unique_ptr<Item>> data;
  Item total;

  void addItem(std::unique_ptr<Item>&&);
};

struct Filter {
  Inventory& inventory;
  std::function<bool(const std::unique_ptr<Item>&)> cond;

  Filter(Inventory&, std::function<bool(const std::unique_ptr<Item>&)>);
};

std::ostream& operator<<(std::ostream&, const Inventory&);
std::ostream& operator<<(std::ostream&, const Filter&);

}
