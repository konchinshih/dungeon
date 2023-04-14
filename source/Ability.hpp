#pragma once

#include"Effect.hpp"

#include<string>
#include<vector>
#include<memory>

namespace dungeon {

struct Ability {
	std::string name;
	// std::string description;
	int baseInterval;
	int baseMotionValuePercent; // Percent
	int motionValuePercentGrow;
	int curLevel, maxLevel;

	std::vector<std::unique_ptr<Effect>> selfEffects;
	std::vector<std::unique_ptr<Effect>> enemyEffects;

	Ability(std::string, int, int, int, int);

	int motionValue()const;
};

}
