#pragma once

#include<string>

namespace dungeon {

struct Ability {
	std::string name;
	// std::string dialog;
	int baseInterval;
	int motionValue;
	int motionValueGrow;
};

struct NormalAttack: Ability {
	int manaGain;
};

struct Skill: Ability {
	int manaGain;
};

struct Burst: Ability {
	int manaCost;
};

}
