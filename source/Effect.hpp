#pragma once

namespace dungeon {

struct Entity;

struct Effect {
	int startTime, duration;
	virtual void begin(Entity&) = 0;
	virtual void affect(Entity&) = 0;
	virtual void end(Entity&) = 0;
};

struct Poison: Effect {
	static constexpr int DURATION = 20;
	static constexpr int DAMAGE_OVER_TIME = 10;

	virtual void begin(Entity&);
	virtual void affect(Entity&);
	virtual void end(Entity&);
};

struct Burning: Effect {
	static constexpr int DURATION = 10;
	static constexpr int DAMAGE_OVER_TIME = 20;

	virtual void begin(Entity&);
	virtual void affect(Entity&);
	virtual void end(Entity&);
};

struct AtkPercentDown: Effect {
	static constexpr int DURATION = 10;
	static constexpr int AMOUNT = 20;

	virtual void begin(Entity&);
	virtual void affect(Entity&);
	virtual void end(Entity&);
};

struct AtkSpeedDown: Effect {
	static constexpr int DURATION = 10;
	static constexpr int AMOUNT = 20;

	virtual void begin(Entity&);
	virtual void affect(Entity&);
	virtual void end(Entity&);
};

}