#pragma once

#include<string>

namespace dungeon {

struct Entity;

struct Effect {
	std::string name;
	int timeLeft;

	Effect(std::string);
	virtual void begin(Entity&) = 0;
	virtual void affect(Entity&) = 0;
	virtual void end(Entity&) = 0;
};

struct Poison: Effect {
	static constexpr int DURATION = 200;
	static constexpr int DAMAGE_OVER_TIME = 1;

	Poison();
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct Burning: Effect {
	static constexpr int DURATION = 100;
	static constexpr int DAMAGE_OVER_TIME = 2;

	Burning();
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct AtkPercentDown: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 20;

	AtkPercentDown();
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct AtkSpeedDown: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 20;

	AtkSpeedDown();
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct AtkPercentUp: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 20;

	AtkPercentUp();
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct CritRateUp: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 15;

	CritRateUp();
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct CritDamageUp: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 30;

	CritDamageUp();
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct AtkSpeedUp: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 20;

	AtkSpeedUp();
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

}
