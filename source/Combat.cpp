#include"Combat.hpp"

#include<utility>
#include<array>
#include<algorithm>

namespace dungeon {

Combat::Combat(
  std::mt19937& rndGen,
  IOSystem& ios,
  Character& mainChar,
  Monster& enemy
): rndGen(rndGen), ios(ios), mainChar(mainChar), enemy(enemy),
	isWon(false), isCombatEnded(false) {
	mainChar.curHp = mainChar.attr.hp();
	mainChar.curCoolDown = 0;
	enemy.curHp = enemy.attr.hp();
	enemy.curCoolDown = 0;
	ios.clearCombatLog();
}

void Combat::run() {
	while (!isCombatEnded) {
		ios.clear();
		ios.printCombatStatus(enemy);
		ios.printCombatStatus(mainChar);
		ios.printCombatLogs();

		if (!mainChar.curCoolDown)
			action();
		if (enemy.curHp <= 0) {
			isWon = isCombatEnded = true; break;
		}
		if (!enemy.curCoolDown)
			enemyAction();
		if (mainChar.curHp <= 0) {
			isCombatEnded = true; break;
		}

		takeEffect(mainChar);
		if (mainChar.curHp <= 0) {
			isCombatEnded = true; break;
		}
		takeEffect(enemy);
		if (enemy.curHp <= 0) {
			isWon = isCombatEnded = true; break;
		}

		ios.sleep();
		mainChar.nextTick();
		enemy.nextTick();
	}
	getReward();
}

void Combat::takeEffect(Entity& entity) {
	for (auto& effect : entity.effects) {
		effect->affect(entity);
		ios.printEffectEvent(entity, *effect);
	}
}

void Combat::action() {
	switch (ios.askCombatAction()) {
	case CombatOption::ATTACK_WITH_NA:
		attack(enemy, mainChar, *mainChar.normalAttack); break;
	case CombatOption::ATTACK_WITH_SKILL:
		attack(enemy, mainChar, *mainChar.skill); break;
	case CombatOption::DO_NOTHING: break;
	case CombatOption::ESCAPE:
		isCombatEnded = true; break;
	default:
		std::unreachable();
	}
}

void Combat::enemyAction() {
	const std::array<CombatOption, 3> options{
		CombatOption::ATTACK_WITH_NA,
		CombatOption::ATTACK_WITH_SKILL,
		CombatOption::DO_NOTHING
	};
	std::uniform_int_distribution<> dis(0, options.size() - 1);
	switch (options[dis(rndGen)]) {
	case CombatOption::ATTACK_WITH_NA:
		attack(mainChar, enemy, *enemy.normalAttack); break;
	case CombatOption::ATTACK_WITH_SKILL:
		attack(mainChar, enemy, *enemy.skill); break;
	case CombatOption::DO_NOTHING: break;
	default:
		std::unreachable();
	}
}

void Combat::attack(Entity& target, Entity& attacker, const Ability& ability) {
	std::uniform_real_distribution<> critDistribution(0, 100);
	int isCrit = attacker.attr.critRate() < critDistribution(rndGen);

	int levelMultiplier = 100 + (attacker.level - target.level) * 20;
	levelMultiplier = std::max(levelMultiplier, 50);
	levelMultiplier = std::min(levelMultiplier, 150);

	int damage = (long long)attacker.attr.atk()
	             * ability.motionValue()
	             * (100 + isCrit * attacker.attr.critDamage())
	             * levelMultiplier / 1000000;

	ios.printAttackEvent(target, attacker, ability, damage);
	target.curHp -= damage;
	attacker.curCoolDown += attacker.attr.atkInterval(ability);
}

void Combat::getReward() {
	ios.printReward(enemy);
	mainChar.curExp += enemy.expDrop;
	mainChar.coin += enemy.coinDrop;
	if (mainChar.curExp >= Character::EXP_PER_LEVEL) {
		ios.printLevelUp();
		mainChar.levelUp();
	}
	ios.pause();
}

}
