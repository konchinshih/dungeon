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

	std::unique_ptr<Ability> normalAttack;
	std::unique_ptr<Ability> skill;

	Attribute attr;

	int level;

	// only use in combat
	int curHp, curCoolDown;
	std::vector<std::unique_ptr<Effect>> effects;

	Entity(
	  ClassType type,
	  std::string name,
	  int hp, int atk, int level,
	  std::unique_ptr<Ability>&& na,
	  std::unique_ptr<Ability>&& skill
	);

	InventoryFilter equipped()const;
	void addItem(std::unique_ptr<Item>&&);

	// only use in combat
	int atkInterval(const Ability&)const;
	void nextTick();
};

}
