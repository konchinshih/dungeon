#include"NPC.hpp"

#include<chrono>
#include<utility>

namespace dungeon {

TradingItem::TradingItem(std::unique_ptr<Item>&& item, int price):
	item(std::move(item)), price(price) {}

std::string NPC::dialog() {
	std::uniform_int_distribution<> dis(0, dialogs.size() - 1);
	return dialogs[dis(rndGen)];
}

Yuuka::Yuuka() {
	name = "Hayase Yuuka";
	rndGen.seed(std::chrono::steady_clock::now().time_since_epoch().count());
	dialogs.emplace_back("Lucky? No, it's just as calculated.");
	dialogs.emplace_back("Calculations complete. I will never lose...!");
	tradingMenu.emplace_back(std::make_unique<PhilosophersStone>(), 49);
}

}
