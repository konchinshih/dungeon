#pragma once

#include"Entity.hpp"
#include"Room.hpp"
#include"Ability.hpp"

#include<memory>

namespace dungeon {

struct Game;

struct Character: Entity {
	static constexpr int EXP_PER_LEVEL = 100;
	int curX, curY;
	std::shared_ptr<Room> curPos;
	int curExp;

	Character();
	void initialize();
};

template<Class C>
struct CharNA: NormalAttack {
	CharNA();
};

template<Class C>
struct CharSkill: Skill {
	CharSkill();
};

template<Class C>
struct CharBurst: Burst {
	CharBurst();
};

}
