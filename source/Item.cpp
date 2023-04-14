#include"Item.hpp"

namespace dungeon {

WreckingBar::WreckingBar() {
	type = ClassType::ANY;
	name = "Wrecking Bar";

	attr.baseAtk = 100;
	attr.critRatePercent = 5;
}

std::unique_ptr<Item> WreckingBar::copy()const {
	return std::make_unique<WreckingBar>();
}

Excalibur::Excalibur() {
	type = ClassType::SABER;
	name = "Excalibur";

	attr.baseAtk = 1000;
	attr.critRatePercent = 10;
	attr.atkPercent = 20;
}

std::unique_ptr<Item> Excalibur::copy()const {
	return std::make_unique<Excalibur>();
}

WaterPistol::WaterPistol() {
	type = ClassType::ARCHER;
	name = "Water Pistol";

	attr.baseAtk = 1000;
	attr.critRatePercent = 10;
	attr.critDamagePercent = 20;
}

std::unique_ptr<Item> WaterPistol::copy()const {
	return std::make_unique<WaterPistol>();
}

Rhongomyniad::Rhongomyniad() {
	type = ClassType::LANCER;
	name = "Rhongomyniad";

	attr.baseAtk = 1000;
	attr.critRatePercent = 10;
	attr.hpPercent = 20;
}

std::unique_ptr<Item> Rhongomyniad::copy()const {
	return std::make_unique<Rhongomyniad>();
}

AltereactorEngine::AltereactorEngine() {
	type = ClassType::BERSERKER;
	name = "Altereactor Engine";

	attr.baseAtk = 1000;
	attr.critRatePercent = 10;
	attr.atkPercent = 15;
	attr.critDamagePercent = 15;
	attr.hpPercent = -10;
}

std::unique_ptr<Item> AltereactorEngine::copy()const {
	return std::make_unique<AltereactorEngine>();
}

PhilosophersStone::PhilosophersStone() {
	type = ClassType::ANY;
	name = "Philosopher's Stone";

	attr.hpPercent = 5;
	attr.atkPercent = 5;
	attr.flatHp = 5;
	attr.flatAtk = 5;
	attr.critRatePercent = 5;
	attr.critDamagePercent = 10;
}

std::unique_ptr<Item> PhilosophersStone::copy()const {
	return std::make_unique<PhilosophersStone>();
}

}