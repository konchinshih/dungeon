#pragma once

#include"Class.hpp"
#include"Inventory.hpp"
#include"Ability.hpp"
#include"Effect.hpp"

#include<string>
#include<vector>
#include<memory>

namespace dungeon {

struct Entity {
	static constexpr int MIN_ATTACK_INTERVAL = 300;
	static constexpr double ATKSPEED_MAGIC_NUMBER = 100.0;

	Class type;
	std::string name;
	Inventory inventory;
	int level;
	int hpBase, atkBase;
	int critRateBase, critDamageBase;
	int curHp;
	int atkSpeed;
	int energy;

	int coin;

	std::unique_ptr<NormalAttack> normalAttack;
	std::unique_ptr<Skill> skill;
	std::unique_ptr<Burst> burst;

	std::vector<std::unique_ptr<Effect>> effects;

	int hp();
	int atk();
	int critRate();
	int critDamage();
	int atkInterval(const Ability&);

	Filter equipped();
};

}
