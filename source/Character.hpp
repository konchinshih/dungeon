#pragma once

#include"Entity.hpp"
#include"Ability.hpp"
#include"ClassType.hpp"
#include"DirectionType.hpp"

#include<string>

namespace dungeon {

struct Character: Entity {
	static constexpr int EXP_PER_LEVEL = 100;
	int curX, curY;
	int curExp, coin;
	int abilityPoint;

	Character(
	  ClassType type,
	  std::string name,
	  int hp, int atk,
	  std::unique_ptr<Ability>&& na,
	  std::unique_ptr<Ability>&& skill
	);

	void move(DirectionType);
	void enhance(Ability&);
	void levelUp();
};

template<ClassType C>
struct CharacterClass: Character {
	CharacterClass(const std::string&);
};

struct CharNA: Ability {
	CharNA();
};

template<ClassType C>
struct CharSkill: Ability {
	CharSkill();
};


}
