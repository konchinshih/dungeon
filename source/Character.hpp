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
	int curExp;

	void move(DirectionType);
};

template<ClassType C>
struct CharacterClass: Character {
	CharacterClass(const std::string&);
};

struct CharNA: NormalAttack {
	CharNA();
};

template<ClassType C>
struct CharSkill: Skill {
	CharSkill();
};


}
