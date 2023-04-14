#include"IOSystem.hpp"

#include"Inventory.hpp"

#include<iostream>
#include<sstream>
#include<thread>
#include<cctype>
#include<algorithm>
#include<utility>
#include<iomanip>

namespace dungeon {

IOSystem::IOSystem() {
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::ios::sync_with_stdio(false);
}

void IOSystem::clear() {
	std::cout.rdbuf()->sputn(ANSI_ESC_CLEAR, sizeof ANSI_ESC_CLEAR);
	std::cout.rdbuf()->sputn(ANSI_ESC_CURSOR_RESET, sizeof ANSI_ESC_CURSOR_RESET);
	std::cout.rdbuf()->sputn(HEADER_MESSAGE, sizeof HEADER_MESSAGE);
	std::cout.flush();
}

void IOSystem::pause() {
	std::string input;
	std::cout.rdbuf()->sputn(PAUSE_MESSAGE, sizeof PAUSE_MESSAGE);
	std::cout.flush(), std::getline(std::cin, input);
}

void IOSystem::sleep(int tick) {
	std::this_thread::sleep_for(tick * INTERVAL_PER_TICK);
}

void IOSystem::welcome() {
	std::cout << "hello, world" << std::endl;
	pause();
}

std::string IOSystem::askMainCharName() {
	std::cout << "Enter your name: " << std::flush;
	std::string input, ret, tmp;
	std::vector<std::string> tokens;
	while (tokens.empty()) {
		std::getline(std::cin, input);
		std::stringstream ss(input);
		while (ss >> tmp)
			tokens.push_back(tmp);
	}
	for (const auto& token : tokens)
		ret += token + ' ';
	ret.pop_back();
	return ret;
}

ClassType IOSystem::askMainCharClass() {
	std::cout << "Select your class\n"
	          << "A. Saber\n"
	          << "B. Archer\n"
	          << "C. Lancer\n"
	          << "D. Berserker\n"
	          << ": " << std::flush;
	std::string input, tmp;
	while (std::getline(std::cin, input)) {
		std::stringstream ss(input);
		if (!(ss >> tmp)) continue;
		switch (std::tolower(tmp[0])) {
		case 'a':
			return ClassType::SABER;
		case 'b':
			return ClassType::ARCHER;
		case 'c':
			return ClassType::LANCER;
		case 'd':
			return ClassType::BERSERKER;
		default:
			std::cout << "Please enter a valid option: " << std::flush;
		}
	}
	std::unreachable();
}

ActionOption IOSystem::askAction() {
	std::cout << "Select an action\n"
	          << "A. Move\n"
	          << "B. Check Status\n"
	          << "C. Enhance\n"
	          << "D. Open Inventory\n"
	          << ": " << std::flush;
	std::string input, tmp;
	while (std::getline(std::cin, input)) {
		std::stringstream ss(input);
		if (!(ss >> tmp)) continue;
		switch (std::tolower(tmp[0])) {
		case 'a':
			return ActionOption::MOVE;
		case 'b':
			return ActionOption::CHECK_STATUS;
		case 'c':
			return ActionOption::ENHANCE;
		case 'd':
			return ActionOption::OPEN_INVENTORY;
		default:
			std::cout << "Please enter a valid option: " << std::flush;
		}
	}
	std::unreachable();
}

DirectionType IOSystem::askMoveDirection() {
	std::cout << "Select move direction\n"
	          << "A. Up\n"
	          << "B. Down\n"
	          << "C. Left\n"
	          << "D. Right\n"
	          << ": " << std::flush;
	std::string input, tmp;
	while (std::getline(std::cin, input)) {
		std::stringstream ss(input);
		if (!(ss >> tmp)) continue;
		switch (std::tolower(tmp[0])) {
		case 'a':
			return DirectionType::UP;
		case 'b':
			return DirectionType::DOWN;
		case 'c':
			return DirectionType::LEFT;
		case 'd':
			return DirectionType::RIGHT;
		default:
			std::cout << "Please enter a valid opiton: " << std::flush;
		}
	}
	std::unreachable();
}

EnhanceOption IOSystem::askWhatToEnhance(const Character& character) {
	if (!character.abilityPoint) {
		std::cout << "You don't have enough ability point anymore." << std::endl;
		pause();
		return EnhanceOption::EXIT;
	}
	std::cout << "Your current ability point: " << character.abilityPoint << std::endl;
	std::cout << "Select an ability to enhance\n"
	          << "A. Normal Attack\n"
	          << "B. Skill\n"
	          << "C. Exit\n"
	          << ": " << std::flush;
	std::string input, tmp;
	while (std::getline(std::cin, input)) {
		std::stringstream ss(input);
		if (!(ss >> tmp)) continue;
		switch (std::tolower(tmp[0])) {
		case 'a':
			if (character.normalAttack->curLevel == character.normalAttack->maxLevel) {
				std::cout << "Already at max level" << std::endl;
				return EnhanceOption::EXIT;
			}
			return EnhanceOption::NORMAL_ATTACK;
		case 'b':
			if (character.skill->curLevel == character.skill->maxLevel) {
				std::cout << "Already at max level" << std::endl;
				return EnhanceOption::EXIT;
			}
			return EnhanceOption::SKILL;
		case 'c':
			return EnhanceOption::EXIT;
		default:
			std::cout << "Please enter a valid opiton: " << std::flush;
		}
	}
	std::unreachable();
}

NPCTalkOption IOSystem::askWhatToDoWithNPC(const NPC& npc) {
	std::cout << "Select an option to interact with the NPC\n"
	          << "A. Talk\n"
	          << "B. Buy Items\n"
	          << "C. Exit\n"
	          << ": " << std::flush;
	std::string input, tmp;
	while (std::getline(std::cin, input)) {
		std::stringstream ss(input);
		if (!(ss >> tmp)) continue;
		switch (std::tolower(tmp[0])) {
		case 'a':
			return NPCTalkOption::TALK;
		case 'b':
			return NPCTalkOption::BUY_ITEM;
		case 'c':
			return NPCTalkOption::EXIT;
		default:
			std::cout << "Please enter a valid opiton: " << std::flush;
		}
	}
	std::unreachable();
}

int IOSystem::askWhichToBuy(const NPC& npc, const Character& character) {
	std::cout << "Select which item to buy\n";
	std::cout << std::setw( 5) << "No. "
	          << std::setw(20) << "Name"
	          << std::setw( 5) << "Price"
	          << std::setw( 5) << "Left" << std::endl;
	for (int i = 0; i < (int)npc.tradingMenu.size(); i++)
		std::cout << std::setw( 5) << i + 1 << ". "
		          << std::setw(20) << npc.tradingMenu[i].item->name
		          << std::setw(5) << npc.tradingMenu[i].price
		          << std::setw(5) << npc.tradingMenu[i].count << std::endl;
	std::cout << "Item No.: " << std::flush;
	std::string input;
	while (std::getline(std::cin, input)) {
		std::stringstream ss(input);
		int ret;
		if (!(ss >> ret)) continue;
		if (ret > 0 && ret < (int)npc.tradingMenu.size()) {
			if (npc.tradingMenu[ret - 1].count <= 0) {
				std::cout << "Items are sold." << std::endl;
				return -1;
			}
			if (character.coin < npc.tradingMenu[ret - 1].price) {
				std::cout << "Not enough coins." << std::endl;
				return -1;
			}
			return ret;
		}
		std::cout << "Please enter a valid opiton: " << std::flush;
	}
	std::unreachable();
}

void IOSystem::printCharPos(const Character& character) {
	std::cout << "Your current position: x[" << character.curX << "] y[" << character.curY << "]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, InventoryFilter filter) {
	for (const auto& i : filter.inventory.data)
		if (filter.cond(i)) os << i->name << ' ';
	return os;
}

void IOSystem::printCharStatus(const Character& character) {
	std::stringstream expStat;
	expStat << character.level << "[" << character.curExp << "/" << Character::EXP_PER_LEVEL << "]";
	std::cout << "Your Status:\n"
	          << std::setw(15) << "Name" << std::setw(20) << character.name << std::endl
	          << std::setw(15) << "HP" << std::setw(20) << character.attr.hp() << std::endl
	          << std::setw(15) << "ATK" << std::setw(20) << character.attr.atk() << std::endl
	          << std::setw(15) << "Crit Rate" << std::setw(20) << character.attr.critRate() << "%" << std::endl
	          << std::setw(15) << "Crit Damage" << std::setw(20) << character.attr.critDamage() << "%" << std::endl
	          << std::setw(15) << "Level" << std::setw(20) << expStat.str() << std::endl
	          << std::setw(15) << "Equipped Items: " << character.equipped() << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Inventory& inventory) {
	for (const auto& i : inventory.data)
		os << i->name << '\n';
	return os;
}

void IOSystem::printInventory(const Inventory& inventory) {
	std::cout << "Inventory:\n" << inventory << std::endl;
}

void IOSystem::printDialog(const NPC& npc, std::mt19937& rndGen) {
	std::cout << npc.name << ": \"" << npc.dialog(rndGen) << "\"" << std::endl;
}

void IOSystem::printEndingMessage() {
	std::cout << "You have been cleared the game!\n"
	          << ":angry_mention:" << std::endl;
}

CombatOption IOSystem::askCombatAction() {
	std::cout << "Select an action\n"
	          << "A. Attack with Normal Attack\n"
	          << "B. Attack with Skill\n"
	          << "C. Do Nothing\n"
	          << "D. Escape\n"
	          << ": " << std::flush;
	std::string input, tmp;
	while (std::getline(std::cin, input)) {
		std::stringstream ss(input);
		if (!(ss >> tmp)) continue;
		switch (std::tolower(tmp[0])) {
		case 'a':
			return CombatOption::ATTACK_WITH_NA;
		case 'b':
			return CombatOption::ATTACK_WITH_SKILL;
		case 'c':
			return CombatOption::DO_NOTHING;
		case 'd':
			return CombatOption::ESCAPE;
		default:
			std::cout << "Please enter a valid opiton: " << std::flush;
		}
	}
	std::unreachable();
}

// Combat
void IOSystem::clearCombatLog() {
	combatLogs.clear();
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::unique_ptr<Effect>>& vec) {
	for (const auto& i : vec)
		os << i->name << ' ';
	return os;
}

void IOSystem::printCombatStatus(const Entity& entity) {
	std::stringstream hpStat;
	hpStat << "[" << entity.curHp << "/" << entity.attr.hp() << "]";
	std::cout << "Status:\n"
	          << std::setw(10) << "Name" << std::setw(20) << entity.name << std::endl
	          << std::setw(10) << "HP" << std::setw(20) << hpStat.str() << std::endl
	          << std::setw(10) << "Effects" << std::setw(20) << entity.effects << std::endl
	          << std::setw(10) << "Cooldown" << std::setw(20) << entity.curCoolDown << std::endl;
}

void IOSystem::printCombatLogs() {
	std::cout << "Combat Logs" << std::endl;
	for (const auto& log : combatLogs)
		std::cout << log << std::endl;
	std::cout << std::endl;
}

void IOSystem::printAttackEvent(
  const Entity& target,
  const Entity& attacker,
  const Ability& ability,
  int damage
) {
	std::stringstream ss;
	ss << "\'" << attacker.name << "\'"
	   << " attack "
	   << "\'" << target.name << "\'"
	   << " with "
	   << ability.name
	   << " cause "
	   << damage << " damage.";
	combatLogs.push_back(ss.str());
	// std::cout << ss.str() << std::endl;
}

void IOSystem::printEffectEvent(const Entity& target, const Effect& effect) {
	std::stringstream ss;
	ss << "The effect \'" << effect.name << "\' has affect on \'" << target.name << "\'" << std::endl;
	combatLogs.push_back(ss.str());
	// std::cout << ss.str() << std::endl;
}

void IOSystem::printReward(const Monster& monster) {
	std::cout << "Battle finish\n"
	          << "Receive " << monster.expDrop << " exp\n"
	          << "Receive " << monster.coinDrop << " coin" << std::endl;
}

void IOSystem::printLevelUp() {
	std::cout << "Level up!" << std::endl;
}

}
