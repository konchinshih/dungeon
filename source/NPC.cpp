#include"NPC.hpp"

#include<chrono>
#include<utility>
#include<cassert>

namespace dungeon {

TradingItem::TradingItem(std::unique_ptr<Item>&& item, int price, int count):
	item(std::move(item)), price(price), count(count) {}

std::unique_ptr<Item> TradingItem::sell() {
	assert(count > 0), count -= 1;
	return item->copy();
}

std::string NPC::dialog(std::mt19937& rndGen)const {
	std::uniform_int_distribution<> dis(0, dialogs.size() - 1);
	return dialogs[dis(rndGen)];
}

Yuuka::Yuuka() {
	name = "Hayase Yuuka";
	dialogs.emplace_back("Lucky? No, it's just as calculated.");
	dialogs.emplace_back("Calculations complete. I will never lose...!");
	tradingMenu.emplace_back(std::make_unique<PhilosophersStone>(), 49, 3);
}

}
