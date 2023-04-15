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
	isWon(false), isLose(false), isCombatEnded(false) {
	mainChar.curHp = mainChar.attr.hp();
	mainChar.curCoolDown = 0;
	enemy.curHp = enemy.attr.hp();
	enemy.curCoolDown = 0;
	ios.clearCombatLog();
	ios.printCombatStart();
}

Combat::~Combat() {
	for (auto& effect : mainChar.effects)
		effect->end(mainChar);
	mainChar.effects.clear();
}

void Combat::run() {
	while (true) {
		ios.clear();
		ios.printCombatStatus(enemy);
		ios.printCombatStatus(mainChar);
		ios.printCombatLogs();

		if (isCombatEnded) break;

		if (!mainChar.curCoolDown)
			action();
		if (enemy.curHp <= 0) {
			isWon = isCombatEnded = true; continue;
		}
		if (!enemy.curCoolDown)
			enemyAction();
		if (mainChar.curHp <= 0) {
			isLose = isCombatEnded = true; continue;
		}

		takeEffect(mainChar);
		if (mainChar.curHp <= 0) {
			isLose = isCombatEnded = true; continue;
		}
		takeEffect(enemy);
		if (enemy.curHp <= 0) {
			isWon = isCombatEnded = true; continue;
		}

		ios.sleep();
		mainChar.nextTick();
		enemy.nextTick();
	}
	if (isWon)
		getReward();
	else
		ios.printCombatEscape();
}

void Combat::takeEffect(Entity& entity) {
	for (auto& effect : entity.effects)
		effect->affect(entity);
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
// Effect application
	for (auto& effect : ability.selfEffects) {
		auto tmp = std::move(effect->copy());
		tmp->begin(attacker), ios.printEffectEvent(attacker, *tmp);
		if (attacker.effects.count(tmp))
			attacker.effects.erase(tmp);
		attacker.effects.insert(std::move(tmp));
	}
	for (auto& effect : ability.enemyEffects) {
		auto tmp = std::move(effect->copy());
		tmp->begin(target), ios.printEffectEvent(target, *tmp);
		if (target.effects.count(tmp))
			target.effects.erase(tmp);
		target.effects.insert(std::move(tmp));
	}

// Damage Calculation
	std::uniform_real_distribution<> critDistribution(0, 100);
	int isCrit = attacker.attr.critRate() < critDistribution(rndGen);
	double critMultiplier = (100 + isCrit * attacker.attr.critDamage()) / 100.0;

	double levelMultiplier = (100 + (attacker.level - target.level) * 20) / 100.0;
	levelMultiplier = std::max(levelMultiplier, 0.50);
	levelMultiplier = std::min(levelMultiplier, 1.50);

	double classMultiplier = 1.00;
	if (
	  (attacker.type == ClassType::SABER && target.type == ClassType::LANCER) ||
	  (attacker.type == ClassType::ARCHER && target.type == ClassType::SABER) ||
	  (attacker.type == ClassType::LANCER && target.type == ClassType::ARCHER)
	)
		classMultiplier = 2.00;
	if (
	  (attacker.type == ClassType::SABER && target.type == ClassType::ARCHER) ||
	  (attacker.type == ClassType::ARCHER && target.type == ClassType::LANCER) ||
	  (attacker.type == ClassType::LANCER && target.type == ClassType::SABER)
	)
		classMultiplier = 0.50;
	if (target.type == ClassType::BERSERKER)
		classMultiplier = 2.00;
	if (attacker.type == ClassType::BERSERKER)
		classMultiplier = 1.50;

	int damage = attacker.attr.atk()
	             * ability.motionValue() / 100.0
	             * critMultiplier
	             * classMultiplier
	             * levelMultiplier;

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
