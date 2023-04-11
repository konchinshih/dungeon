#pragma once

#include"Item.hpp"

#include<string>
#include<vector>
#include<random>
#include<memory>

namespace dungeon {

struct TradingItem {
	std::unique_ptr<Item> item;
	int price;
	TradingItem(std::unique_ptr<Item>&&, int);
};

struct NPC {
	std::string name;
	std::mt19937 rndGen;
	std::vector<std::string> dialogs;
	std::vector<TradingItem> tradingMenu;

	std::string dialog();
};

struct Yuuka: NPC {
	Yuuka();
};

}
