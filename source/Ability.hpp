#pragma once

#include"Effect.hpp"

#include<string>
#include<vector>
#include<memory>

namespace dungeon {

struct Ability {
	std::string name;
	// std::string dialog;
	int baseInterval;
	int motionValue; // Percent
	int motionValueGrow;
	int maxLevel;

	std::vector<std::unique_ptr<Effect>> selfEffects;
	std::vector<std::unique_ptr<Effect>> enemyEffects;
};

struct NormalAttack: Ability {};

struct Skill: Ability {};

}
