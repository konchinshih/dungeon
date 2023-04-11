#include"Inventory.hpp"

#include<utility>

namespace dungeon {

void Inventory::addItem(std::unique_ptr<Item>&& item) {
	total += *item;
	data.emplace_back(std::move(item));
}

std::ostream& operator<<(std::ostream& os, const Inventory& inventory) {
	for (const auto& i : inventory.data)
		os << i->name << ' ';
	return os;
}

Filter::Filter(Inventory& inventory, std::function<bool(const std::unique_ptr<Item>&)> cond):
	inventory(inventory), cond(cond) {}

std::ostream& operator<<(std::ostream& os, const Filter& filter) {
	for (const auto& i : filter.inventory.data)
		if (filter.cond(i))
			os << i->name << ' ';
	return os;
}

}
