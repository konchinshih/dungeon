#pragma once

#include"Item.hpp"

#include<string>
#include<vector>
#include<random>
#include<memory>

namespace dungeon {

struct TradingItem {
	std::unique_ptr<Item> item;
	int price, count;

	TradingItem(std::unique_ptr<Item>&&, int, int = 1);
	std::unique_ptr<Item> sell();
};

struct NPC {
	std::string name;
	std::vector<std::string> dialogs;
	std::vector<TradingItem> tradingMenu;

	std::string dialog(std::mt19937&)const;
};

struct Yuuka: NPC {
	Yuuka();
};

}
