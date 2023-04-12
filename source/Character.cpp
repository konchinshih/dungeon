#include"Character.hpp"

#include<memory>
#include<utility>

namespace dungeon {

void Character::move(DirectionType direction) {
	switch (direction) {
	case DirectionType::UP:
		curX -= 1; break;
	case DirectionType::DOWN:
		curX += 1; break;
	case DirectionType::LEFT:
		curY -= 1; break;
	case DirectionType::RIGHT:
		curY += 1; break;
	default:
		std::unreachable();
	}
}

template<>
CharacterClass<ClassType::SABER>::CharacterClass(const std::string& name) {
	type = ClassType::SABER;
	this->name = name;

	attr.baseHp = 2222;
	attr.baseAtk = 1734;
	attr.critRatePercent = 5;
	attr.critDamagePercent = 50;

	level = coin = 0;
	curHp = attr.hp();

	normalAttack = std::make_unique<CharNA>();
	skill = std::make_unique<CharSkill<ClassType::SABER>>();

	curX = curY = 0, curExp = 0;
}

template<>
CharacterClass<ClassType::ARCHER>::CharacterClass(const std::string& name) {
	type = ClassType::ARCHER;
	this->name = name;

	attr.baseHp = 2134;
	attr.baseAtk = 1742;
	attr.critRatePercent = 5;
	attr.critDamagePercent = 50;

	level = coin = 0;
	curHp = attr.hp();

	normalAttack = std::make_unique<CharNA>();
	skill = std::make_unique<CharSkill<ClassType::ARCHER>>();

	curX = curY = 0, curExp = 0;
}

template<>
CharacterClass<ClassType::LANCER>::CharacterClass(const std::string& name) {
	type = ClassType::LANCER;
	this->name = name;

	attr.baseHp = 2288;
	attr.baseAtk = 1699;
	attr.critRatePercent = 5;
	attr.critDamagePercent = 50;

	level = coin = 0;
	curHp = attr.hp();

	normalAttack = std::make_unique<CharNA>();
	skill = std::make_unique<CharSkill<ClassType::LANCER>>();

	curX = curY = 0, curExp = 0;
}

template<>
CharacterClass<ClassType::BERSERKER>::CharacterClass(const std::string& name) {
	type = ClassType::BERSERKER;
	this->name = name;

	attr.baseHp = 2079;
	attr.baseAtk = 1717;
	attr.critRatePercent = 5;
	attr.critDamagePercent = 50;

	level = coin = 0;
	curHp = attr.hp();

	normalAttack = std::make_unique<CharNA>();
	skill = std::make_unique<CharSkill<ClassType::BERSERKER>>();

	curX = curY = 0, curExp = 0;
}


CharNA::CharNA() {
	name = "Normal Attack";
	baseInterval = 10;
	motionValue = 50;
	motionValueGrow = 5;
	maxLevel = 99;
}

template<>
CharSkill<ClassType::SABER>::CharSkill() {
	name = "Charisma";
	baseInterval = 100;
	motionValue = 0;
	motionValueGrow = 0;
	maxLevel = 1;
	selfEffects.push_back(std::make_unique<AtkPercentUp>());
}

template<>
CharSkill<ClassType::ARCHER>::CharSkill() {
	name = "Instinct";
	baseInterval = 100;
	motionValue = 0;
	motionValueGrow = 0;
	maxLevel = 1;
	selfEffects.push_back(std::make_unique<CritRateUp>());
}

template<>
CharSkill<ClassType::LANCER>::CharSkill() {
	name = "Mana Burst";
	baseInterval = 100;
	motionValue = 0;
	motionValueGrow = 0;
	maxLevel = 1;
	selfEffects.push_back(std::make_unique<CritDamageUp>());
}

template<>
CharSkill<ClassType::BERSERKER>::CharSkill() {
	name = "Sovereign's Invisible Hand";
	baseInterval = 100;
	motionValue = 0;
	motionValueGrow = 0;
	maxLevel = 1;
	selfEffects.push_back(std::make_unique<AtkSpeedUp>());
}

}
