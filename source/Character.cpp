#include"Character.hpp"
#include"Error.hpp"
#include"Item.hpp"
#include"Game.hpp"

#include<memory>

namespace dungeon {

Character::Character(): curX(0), curY(0) {
	critRateBase = 5, critDamageBase = 50;
	inventory.addItem(std::make_unique<WreckingBar>());
}

void Character::initialize() {
	switch (type) {
	case Class::saber:
		hpBase = 2222, atkBase = 1734;
		break;
	case Class::archer:
		hpBase = 2134, atkBase = 1742;
		break;
	case Class::lancer:
		hpBase = 2288, atkBase = 1699;
		break;
	// case Class::rider:
	// 	hpBase = 2090, atkBase = 1665;
	// 	break;
	// case Class::caster:
	// 	hpBase = 2112, atkBase = 1629;
	// 	break;
	// case Class::assassin:
	// 	hpBase = 1862, atkBase = 1817;
	// 	break;
	case Class::berserker:
		hpBase = 2079, atkBase = 1717;
		break;
	default:
		throw TypeError();
	}
	curHp = hp();
}

template<>
CharNA<Class::saber>::CharNA() {

}

}