#include"IOSystem.hpp"

#include"Inventory.hpp"

#include<iostream>
#include<fstream>
#include<sstream>
#include<thread>
#include<cctype>
#include<algorithm>
#include<utility>
#include<iomanip>
#include<cstring>

namespace dungeon {

IOSystem::IOSystem(): cout(*this), cin(std::cin) {
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

void IOSystem::printWelcome() {
	std::fstream fin("./text/Dungeon.txt", std::ios::in);
	std::string file, tmp;
	while (std::getline(fin, tmp))
		file += tmp + '\n';
	std::cout << file << std::endl;
}

std::string IOSystem::askMainCharName() {
	clear();
	std::cout << "Enter your name: " << std::flush;
	std::string input, ret, tmp;
	std::vector<std::string> tokens;
	while (tokens.empty()) {
		std::getline(cin, input);
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
	clear();
	std::cout << "Select your class\n"
	          << "A. Saber\n"
	          << "B. Archer\n"
	          << "C. Lancer\n"
	          << "D. Berserker\n"
	          << ": " << std::flush;
	std::string input, tmp;
	while (std::getline(cin, input)) {
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
			std::cout << "Please enter a valid option\n: " << std::flush;
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
			std::cout << "Please enter a valid option\n: " << std::flush;
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
			std::cout << "Please enter a valid option\n: " << std::flush;
		}
	}
	std::unreachable();
}

EnhanceOption IOSystem::askWhatToEnhance(const Character& character) {
	if (!character.abilityPoint) {
		std::cout << "You don't have enough ability point anymore." << std::endl;
		return EnhanceOption::EXIT;
	}
	std::cout << "Your current ability point: " << character.abilityPoint << std::endl;
	std::cout << ANSI_ESC_COLOR_RESET << "Select an ability to enhance" << std::endl
	          << ANSI_ESC_COLOR_RESET << "A. Normal Attack - "
	          << ANSI_ESC_CYAN << character.normalAttack->name
	          << ANSI_ESC_COLOR_RESET << "["
	          << ANSI_ESC_MAGENTA << character.normalAttack->curLevel
	          << ANSI_ESC_COLOR_RESET << " / "
	          << ANSI_ESC_MAGENTA << character.normalAttack->maxLevel
	          << ANSI_ESC_COLOR_RESET << "]" << std::endl
	          << ANSI_ESC_COLOR_RESET << "B. Skill - "
	          << ANSI_ESC_CYAN << character.skill->name
	          << ANSI_ESC_COLOR_RESET << "["
	          << ANSI_ESC_MAGENTA << character.skill->curLevel
	          << ANSI_ESC_COLOR_RESET << " / "
	          << ANSI_ESC_MAGENTA << character.skill->maxLevel
	          << ANSI_ESC_COLOR_RESET << "]" << std::endl
	          << ANSI_ESC_COLOR_RESET << "C. Exit" << std::endl
	          << ": " << std::flush;
	std::string input, tmp;
	while (std::getline(std::cin, input)) {
		std::stringstream ss(input);
		if (!(ss >> tmp)) continue;
		switch (std::tolower(tmp[0])) {
		case 'a':
			if (character.normalAttack->curLevel == character.normalAttack->maxLevel) {
				std::cout << "Already at max level." << std::endl;
				return EnhanceOption::EXIT;
			}
			return EnhanceOption::NORMAL_ATTACK;
		case 'b':
			if (character.skill->curLevel == character.skill->maxLevel) {
				std::cout << "Already at max level." << std::endl;
				return EnhanceOption::EXIT;
			}
			return EnhanceOption::SKILL;
		case 'c':
			return EnhanceOption::EXIT;
		default:
			std::cout << "Please enter a valid option\n: " << std::flush;
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
			std::cout << "Please enter a valid option\n: " << std::flush;
		}
	}
	std::unreachable();
}

int IOSystem::askWhichToBuy(const NPC& npc, const Character& character) {
	std::cout << "Select which item to buy\n";
	std::cout << std::setw(5) << "No."
	          << std::setw(30) << "Name"
	          << std::setw(15) << "Price"
	          << std::setw(15) << "Left" << std::endl;
	for (int i = 0; i < (int)npc.tradingMenu.size(); i++)
		std::cout << ANSI_ESC_COLOR_RESET << std::setw(5) << i + 1 << ". "
		          << ANSI_ESC_GREEN << std::setw(30) << npc.tradingMenu[i].item->name
		          << ANSI_ESC_MAGENTA << std::setw(15) << npc.tradingMenu[i].price
		          << ANSI_ESC_MAGENTA << std::setw(15) << npc.tradingMenu[i].count
		          << ANSI_ESC_COLOR_RESET << std::endl;
	std::cout << "Item No. (0 to exit): " << std::flush;
	std::string input;
	while (std::getline(std::cin, input)) {
		std::stringstream ss(input);
		int ret;
		if (!(ss >> ret)) continue;
		if (ret > 0 && ret <= (int)npc.tradingMenu.size()) {
			if (npc.tradingMenu[ret - 1].count <= 0) {
				std::cout << "Items are sold." << std::endl; pause();
				return -1;
			}
			if (character.coin < npc.tradingMenu[ret - 1].price) {
				std::cout << "Not enough coins." << std::endl; pause();
				return -1;
			}
			return ret - 1;
		}
		if (ret == 0)
			return -1;
		std::cout << "Please enter a valid option\n: " << std::flush;
	}
	std::unreachable();
}

void IOSystem::printCharPos(const Character& character) {
	std::cout << ANSI_ESC_COLOR_RESET << "Your current position: x["
	          << ANSI_ESC_MAGENTA << character.curX
	          << ANSI_ESC_COLOR_RESET << "] y["
	          << ANSI_ESC_MAGENTA << character.curY
	          << ANSI_ESC_COLOR_RESET << "]" << std::endl
	          << ANSI_ESC_COLOR_RESET << std::endl;
}

void IOSystem::printCharStatus(const Character& character) {
	std::cout << "Your Status:\n"
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "Name"
	          << ANSI_ESC_BLUE << std::setw(15) << character.name << std::endl
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "Class"
	          << ANSI_ESC_RED << std::setw(15) << character.type << std::endl
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "HP"
	          << ANSI_ESC_MAGENTA << std::setw(15) << character.attr.hp() << std::endl
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "ATK"
	          << ANSI_ESC_MAGENTA << std::setw(15) << character.attr.atk() << std::endl
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "Crit Rate"
	          << ANSI_ESC_MAGENTA << std::setw(15) << character.attr.critRate()
	          << ANSI_ESC_COLOR_RESET << " %" << std::endl
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "Crit Damage"
	          << ANSI_ESC_MAGENTA << std::setw(15) << character.attr.critDamage()
	          << ANSI_ESC_COLOR_RESET << " %" << std::endl
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "Level"
	          << ANSI_ESC_MAGENTA << std::setw(15) << character.level
	          << ANSI_ESC_COLOR_RESET << " ["
	          << ANSI_ESC_MAGENTA << character.curExp
	          << ANSI_ESC_COLOR_RESET << " / "
	          << ANSI_ESC_MAGENTA << Character::EXP_PER_LEVEL
	          << ANSI_ESC_COLOR_RESET << "]" << std::endl
	          << ANSI_ESC_COLOR_RESET << std::endl;

	std::cout << ANSI_ESC_COLOR_RESET << std::setw(15) << "Normal Attack"
	          << ANSI_ESC_CYAN << std::setw(30) << character.normalAttack->name << std::endl
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "Skill"
	          << ANSI_ESC_CYAN << std::setw(30) << character.skill->name << std::endl
	          << ANSI_ESC_COLOR_RESET << std::endl;
}

void IOSystem::printInventory(const Character& character) {
	std::cout << "Inventory:\n" << std::endl;
	std::cout << std::setw(30) << "Item"
	          << std::setw(15) << "Class"
	          << std::setw(15) << "Status" << std::endl;
	auto filter = character.equipped();
	for (auto i = filter.inventory.data.begin(); i != filter.inventory.data.end(); i++) {
		std::cout << ANSI_ESC_GREEN << std::setw(30) << (*i)->name
		          << ANSI_ESC_RED << std::setw(15) << (*i)->type;
		if (filter.cond(*i))
			std::cout << ANSI_ESC_COLOR_RESET << std::setw(15) << "[equipped]";
		std::cout << ANSI_ESC_COLOR_RESET << std::endl;
	}
}

void IOSystem::printDialog(const NPC& npc, std::mt19937& rndGen) {
	std::cout << ANSI_ESC_BLUE << npc.name
	          << ANSI_ESC_COLOR_RESET << ": \"" << npc.dialog(rndGen) << "\"" << std::endl;
}

void IOSystem::printRoomInfo(const Room& room) {
	switch (room.type) {
	case RoomType::NOTHING:
		std::cout << "You have entered an empty room." << std::endl; break;
	case RoomType::TREASURE:
		std::cout << "You have entered an treasure room." << std::endl; break;
	case RoomType::NPC:
		std::cout << "You have entered an NPC room." << std::endl; break;
	case RoomType::MONSTER:
		std::cout << "You have entered an monster room." << std::endl; break;
	case RoomType::BOSS:
		std::cout << "You have entered an boss room." << std::endl; break;
	}
}

void IOSystem::printItemReceived(const Item& item) {
	std::cout << ANSI_ESC_COLOR_RESET << "You have received an item \'"
	          << ANSI_ESC_GREEN << item.name << "\'"
	          << ANSI_ESC_COLOR_RESET << std::endl;
}

void IOSystem::printGameWinMessage() {
	std::cout << "You have been cleared the game!" << std::endl;
	std::fstream fin("./text/YOU_WIN.txt", std::ios::in);
	std::string file, tmp;
	while (std::getline(fin, tmp))
		file += tmp + '\n';
	std::cout << file << std::endl;
}

void IOSystem::printGameLoseMessage() {
	std::cout << "Mamma mia!" << std::endl;
	std::fstream fin("./text/YOU_LOSE.txt", std::ios::in);
	std::string file, tmp;
	while (std::getline(fin, tmp))
		file += tmp + '\n';
	std::cout << file << std::endl;
}

// Combat
void IOSystem::clearCombatLog() {
	combatLogs.clear();
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
			std::cout << "Please enter a valid option\n: " << std::flush;
		}
	}
	std::unreachable();
}

void IOSystem::printCombatStart() {
	std::cout << "Enemy Encountered!" << std::endl;
	sleep(10);
}

std::ostream& operator<<(std::ostream& os, const std::set<std::unique_ptr<Effect>>& li) {
	for (auto i = li.begin(); i != li.end(); i++) {
		if (i != li.begin())
			os << ", " << ANSI_ESC_YELLOW;
		os << (*i)->name << ANSI_ESC_COLOR_RESET;
	}
	return os;
}

void IOSystem::printCombatStatus(const Entity& entity) {
	std::cout << "Status:\n"
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "Name"
	          << ANSI_ESC_BLUE << std::setw(15) << entity.name << std::endl
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "Class"
	          << ANSI_ESC_RED << std::setw(15) << entity.type << std::endl
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "HP"
	          << ANSI_ESC_MAGENTA << std::setw(15) << entity.curHp
	          << ANSI_ESC_COLOR_RESET << " / "
	          << ANSI_ESC_MAGENTA << entity.attr.hp() << std::endl
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "Cooldown"
	          << ANSI_ESC_MAGENTA << std::setw(15) << entity.curCoolDown << std::endl
	          << ANSI_ESC_COLOR_RESET << std::setw(15) << "Effects"
	          << ANSI_ESC_YELLOW << std::setw(15) << entity.effects << std::endl
	          << ANSI_ESC_COLOR_RESET << std::endl;
}

void IOSystem::printCombatLogs() {
	while (combatLogs.size() > MAX_LOG_LINE)
		combatLogs.pop_front();
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
	ss << ANSI_ESC_COLOR_RESET << "\'"
	   << ANSI_ESC_BLUE << attacker.name
	   << ANSI_ESC_COLOR_RESET << "\' attack \'"
	   << ANSI_ESC_BLUE << target.name
	   << ANSI_ESC_COLOR_RESET << "\' with \'"
	   << ANSI_ESC_CYAN << ability.name
	   << ANSI_ESC_COLOR_RESET << "\' cause "
	   << ANSI_ESC_MAGENTA << damage
	   << ANSI_ESC_COLOR_RESET << " damage.";
	combatLogs.push_back(ss.str());
	// cout << ss.str() << std::endl;
}

void IOSystem::printEffectEvent(const Entity& target, const Effect& effect) {
	std::stringstream ss;
	ss << ANSI_ESC_COLOR_RESET << "The effect \'"
	   << ANSI_ESC_YELLOW << effect.name
	   << ANSI_ESC_COLOR_RESET << "\' has affect on \'"
	   << ANSI_ESC_BLUE << target.name
	   << ANSI_ESC_COLOR_RESET << "\'";
	combatLogs.push_back(ss.str());
	// cout << ss.str() << std::endl;
}

void IOSystem::printReward(const Monster& monster) {
	std::cout << ANSI_ESC_COLOR_RESET << "Battle finish\n"
	          << ANSI_ESC_COLOR_RESET << "Receive "
	          << ANSI_ESC_MAGENTA << monster.expDrop
	          << ANSI_ESC_COLOR_RESET << " exp\n"
	          << ANSI_ESC_COLOR_RESET << "Receive "
	          << ANSI_ESC_MAGENTA << monster.coinDrop
	          << ANSI_ESC_COLOR_RESET << " coin" << std::endl;
}

void IOSystem::printCombatEscape() {
	std::cout << "Escape from combat" << std::endl;
}

void IOSystem::printLevelUp() {
	std::cout << "Level up!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, ClassType type) {
	std::string typeName;
	switch (type) {
	case ClassType::SABER:
		typeName = "Saber"; break;
	case ClassType::ARCHER:
		typeName = "Archer"; break;
	case ClassType::LANCER:
		typeName = "Lancer"; break;
	case ClassType::BERSERKER:
		typeName = "Berserker"; break;
	case ClassType::NONE:
		typeName = "None"; break;
	case ClassType::ANY:
		typeName = "Any"; break;
	default:
		std::unreachable();
	}
	return os << typeName;
}

// IO interface

// IOSystem& IOSystem::operator<<(const std::integral auto& val) {
// 	std::cout.width(std::cout.width() + std::strlen(ANSI_ESC_MAGENTA) + std::strlen(ANSI_ESC_COLOR_RESET));
// 	std::stringstream ss;
// 	ss << ANSI_ESC_MAGENTA << val << ANSI_ESC_COLOR_RESET;
// 	std::cout << ss.str();
// 	return *this;
// }

// IOSystem& IOSystem::operator<<(const std::floating_point auto& val) {
// 	std::cout.width(std::cout.width() + std::strlen(ANSI_ESC_MAGENTA) + std::strlen(ANSI_ESC_COLOR_RESET));
// 	std::stringstream ss;
// 	ss << ANSI_ESC_MAGENTA << val << ANSI_ESC_COLOR_RESET;
// 	std::cout << ss.str();
// 	return *this;
// }

// IOSystem& IOSystem::operator<<(ExceptionType auto& obj) {
// 	std::cout << obj; return *this;
// }

// IOSystem& IOSystem::operator<<(const auto& obj) {
// 	std::cout << obj; return *this;
// }

// std::ostream& operator<<(std::ostream& os, ClassType type) {
// 	std::string typeName;
// switch (type) {
// case ClassType::SABER:
// 	typeName = "Saber"; break;
// case ClassType::ARCHER:
// 	typeName = "Archer"; break;
// case ClassType::LANCER:
// 	typeName = "Lancer"; break;
// case ClassType::BERSERKER:
// 	typeName = "Berserker"; break;
// case ClassType::NONE:
// 	typeName = "None"; break;
// case ClassType::ANY:
// 	typeName = "Any"; break;
// default:
// 	std::unreachable();
// }
// 	os.width(os.width() + std::strlen(ANSI_ESC_RED) + std::strlen(ANSI_ESC_COLOR_RESET));
// 	return os << ANSI_ESC_RED + typeName + ANSI_ESC_COLOR_RESET;
// }

// std::ostream& operator<<(std::ostream& os, const std::derived_from<Entity> auto& entity) {
// 	os.width(os.width() + std::strlen(ANSI_ESC_BLUE) + std::strlen(ANSI_ESC_COLOR_RESET));
// 	return os << ANSI_ESC_BLUE + entity.name + ANSI_ESC_COLOR_RESET;
// }

// std::ostream& operator<<(std::ostream& os, const std::derived_from<Effect> auto& effect) {
// 	os.width(os.width() + std::strlen(ANSI_ESC_YELLOW) + std::strlen(ANSI_ESC_COLOR_RESET));
// 	std::stringstream ss;
// 	ss << ANSI_ESC_YELLOW
// 	   << effect.name
// 	   << ANSI_ESC_COLOR_RESET
// 	   << "[" << effect.timeLeft << "]";
// 	return os << ss.str();
// }

// std::ostream& operator<<(std::ostream& os, const std::derived_from<Item> auto& item) {
// 	os.width(os.width() + std::strlen(ANSI_ESC_GREEN) + std::strlen(ANSI_ESC_COLOR_RESET));
// 	return os << ANSI_ESC_GREEN + item.name + ANSI_ESC_COLOR_RESET;
// }


// std::ostream& operator<<(std::ostream& os, const std::derived_from<Ability> auto& ability) {
// 	os.width(os.width() + std::strlen(ANSI_ESC_CYAN) + std::strlen(ANSI_ESC_COLOR_RESET));
// 	std::stringstream ss;
// 	ss << ANSI_ESC_CYAN
// 	   << ability.name
// 	   << ANSI_ESC_COLOR_RESET
// 	   << "[" << ability.curLevel << "/" << ability.maxLevel << "]";
// 	return os << ss.str();
// }


}
