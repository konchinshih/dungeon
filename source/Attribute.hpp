#pragma once

namespace dungeon {

struct Ability;

struct Attribute {
	static constexpr int MIN_ATTACK_INTERVAL = 300;
	static constexpr double ATKSPEED_MAGIC_NUMBER = 100.0;

	int baseHp;
	int baseAtk;
	int baseAtkSpeed;
	int baseExp;

	int hpPercent;
	int atkPercent;
	int atkSpeedPercent;
	int critRatePercent;
	int critDamagePercent;
	int expGainPercent;

	int flatHp;
	int flatAtk;
	int flatExp;

	Attribute();

	int hp()const;
	int atk()const;
	int critRate()const;
	int critDamage()const;
	int atkInterval(const Ability&)const;

	Attribute& operator+=(const Attribute&);
	Attribute& operator-=(const Attribute&);
};


}
