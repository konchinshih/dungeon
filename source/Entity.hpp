#pragma once

#include"ClassType.hpp"
#include"Inventory.hpp"
#include"Ability.hpp"
#include"Effect.hpp"
#include"Attribute.hpp"

#include<string>
#include<vector>
#include<memory>

namespace dungeon {

struct Entity {
	ClassType type;
	std::string name;
	Inventory inventory;

	Attribute attr;

	int level;
	int coin;
	int curHp;

	std::unique_ptr<NormalAttack> normalAttack;
	std::unique_ptr<Skill> skill;

	std::vector<std::unique_ptr<Effect>> effects;

	int hp();
	int atk();
	int critRate();
	int critDamage();
	int atkInterval(const Ability&);

	InventoryFilter equipped();
	void addItem(std::unique_ptr<Item>&&);
};

}
