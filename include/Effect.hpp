#pragma once

#include<string>
#include<memory>

namespace dungeon {

struct Entity;

struct Effect {
	std::string name;
	int timeLeft;

	Effect(std::string);
	virtual std::unique_ptr<Effect> copy()const = 0;
	virtual void begin(Entity&) = 0;
	virtual void affect(Entity&) = 0;
	virtual void end(Entity&) = 0;
};

struct Poison: Effect {
	static constexpr int DURATION = 200;
	static constexpr int DAMAGE_OVER_TIME = 1;

	Poison();
	std::unique_ptr<Effect> copy()const;
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct Burning: Effect {
	static constexpr int DURATION = 100;
	static constexpr int DAMAGE_OVER_TIME = 2;

	Burning();
	std::unique_ptr<Effect> copy()const;
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct AtkPercentDown: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 20;

	AtkPercentDown();
	std::unique_ptr<Effect> copy()const;
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct AtkSpeedDown: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 20;

	AtkSpeedDown();
	std::unique_ptr<Effect> copy()const;
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct AtkPercentUp: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 20;

	AtkPercentUp();
	std::unique_ptr<Effect> copy()const;
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct CritRateUp: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 15;

	CritRateUp();
	std::unique_ptr<Effect> copy()const;
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct CritDamageUp: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 30;

	CritDamageUp();
	std::unique_ptr<Effect> copy()const;
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

struct AtkSpeedUp: Effect {
	static constexpr int DURATION = 100;
	static constexpr int AMOUNT = 20;

	AtkSpeedUp();
	std::unique_ptr<Effect> copy()const;
	void begin(Entity&);
	void affect(Entity&);
	void end(Entity&);
};

}
