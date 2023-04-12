#include"Inventory.hpp"

#include<utility>

namespace dungeon {

void Inventory::addItem(std::unique_ptr<Item>&& item) {
	data.emplace_back(std::move(item));
}

InventoryFilter::InventoryFilter(Inventory& inventory, std::function<bool(const std::unique_ptr<Item>&)> cond):
	inventory(inventory), cond(cond) {}

}
