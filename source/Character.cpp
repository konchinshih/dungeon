#include"Character.hpp"

#include<memory>
#include<utility>

namespace dungeon {

Character::Character(
  ClassType type,
  std::string name,
  int hp, int atk,
  std::unique_ptr<Ability>&& na,
  std::unique_ptr<Ability>&& skill
):
	Entity(type, name, hp, atk, 1, std::move(na), std::move(skill)),
	curX(0), curY(0), curExp(0), coin(0), abilityPoint(0) {}

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

void Character::enhance(Ability& ability) {
	abilityPoint--, ability.curLevel++;
}

void Character::levelUp() {
	int incLevel = curExp / EXP_PER_LEVEL;
	curExp %= EXP_PER_LEVEL;
	level += incLevel, abilityPoint += incLevel;
}

template<>
CharacterClass<ClassType::SABER>::CharacterClass(const std::string& name):
	Character(
	  ClassType::SABER, name,
	  2222, 1734,
	  std::make_unique<CharNA>(),
	  std::make_unique<CharSkill<ClassType::SABER>>()
	)
{}

template<>
CharacterClass<ClassType::ARCHER>::CharacterClass(const std::string& name):
	Character(
	  ClassType::ARCHER, name,
	  2134, 1742,
	  std::make_unique<CharNA>(),
	  std::make_unique<CharSkill<ClassType::ARCHER>>()
	)
{}

template<>
CharacterClass<ClassType::LANCER>::CharacterClass(const std::string& name):
	Character(
	  ClassType::LANCER, name,
	  2288, 1699,
	  std::make_unique<CharNA>(),
	  std::make_unique<CharSkill<ClassType::LANCER>>()
	)
{}

template<>
CharacterClass<ClassType::BERSERKER>::CharacterClass(const std::string& name):
	Character(
	  ClassType::BERSERKER, name,
	  2079, 1717,
	  std::make_unique<CharNA>(),
	  std::make_unique<CharSkill<ClassType::BERSERKER>>()
	)
{}


CharNA::CharNA():
	Ability("Normal Attack", 10, 50, 5, 99) {}

template<>
CharSkill<ClassType::SABER>::CharSkill():
	Ability("Charisma",	100, 0, 0, 1) {
	selfEffects.push_back(std::make_unique<AtkPercentUp>());
}

template<>
CharSkill<ClassType::ARCHER>::CharSkill():
	Ability("Instinct",	100, 0, 0, 1) {
	selfEffects.push_back(std::make_unique<CritRateUp>());
}

template<>
CharSkill<ClassType::LANCER>::CharSkill():
	Ability("Mana Burst",	100, 0, 0, 1) {
	selfEffects.push_back(std::make_unique<CritDamageUp>());
}

template<>
CharSkill<ClassType::BERSERKER>::CharSkill():
	Ability("Sovereign's Invisible Hand",	100, 0, 0, 1) {
	selfEffects.push_back(std::make_unique<AtkSpeedUp>());
}

}
