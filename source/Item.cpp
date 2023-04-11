#include"Item.hpp"

namespace dungeon {

Item::Item() {
	hpAdd = atkAdd = 0;
	hpPercentAdd = atkPercentAdd = 0;
	critRateAdd = critDamageAdd = 0;
}

Item& Item::operator+=(const Item& item) {
	hpAdd += item.hpAdd;
	atkAdd += item.atkAdd;
	hpPercentAdd += item.hpPercentAdd;
	atkPercentAdd += item.atkPercentAdd;
	critRateAdd += item.critRateAdd;
	critDamageAdd += item.critDamageAdd;
	return *this;
}

WreckingBar::WreckingBar() {
	type = Class::any;
	name = "Wrecking Bar";
	hpAdd = 0;
	atkAdd = 100;
	hpPercentAdd = 0;
	atkPercentAdd = 0;
	critRateAdd = 5;
	critDamageAdd = 0;
}

Excalibur::Excalibur() {
	type = Class::saber;
	name = "Excalibur";
	hpAdd = 0;
	atkAdd = 1000;
	hpPercentAdd = 0;
	atkPercentAdd = 20;
	critRateAdd = 10;
	critDamageAdd = 0;
}

WaterPistol::WaterPistol() {
	type = Class::archer;
	name = "Water Pistol";
	hpAdd = 0;
	atkAdd = 1000;
	hpPercentAdd = 0;
	atkPercentAdd = 0;
	critRateAdd = 10;
	critDamageAdd = 20;
}

Rhongomyniad::Rhongomyniad() {
	type = Class::lancer;
	name = "Rhongomyniad";
	hpAdd = 0;
	atkAdd = 1000;
	hpPercentAdd = 20;
	atkPercentAdd = 0;
	critRateAdd = 10;
	critDamageAdd = 0;
}

AltereactorEngine::AltereactorEngine() {
	type = Class::any;
	name = "Altereactor Engine";
	hpAdd = 0;
	atkAdd = 1000;
	hpPercentAdd = -10;
	atkPercentAdd = 15;
	critRateAdd = 10;
	critDamageAdd = 15;
}

PhilosophersStone::PhilosophersStone() {
	type = Class::any;
	name = "Philosopher's Stone";
	hpAdd = 5;
	atkAdd = 5;
	hpPercentAdd = 5;
	atkPercentAdd = 5;
	critRateAdd = 5;
	critDamageAdd = 10;
}

}