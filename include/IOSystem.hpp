#pragma once

#include"Map.hpp"
#include"Entity.hpp"
#include"Character.hpp"
#include"NPC.hpp"
#include"Ability.hpp"
#include"Effect.hpp"
#include"ClassType.hpp"
#include"DirectionType.hpp"
#include"ActionOption.hpp"
#include"EnhanceOption.hpp"
#include"NPCTalkOption.hpp"
#include"CombatOption.hpp"

#include<string>
#include<memory>
#include<chrono>
#include<deque>
#include<concepts>
#include<type_traits>
#include<functional>

namespace dungeon {

struct IOSystem {
  static constexpr char ANSI_ESC_CLEAR[] = "\x1B[2J";
  static constexpr char ANSI_ESC_CURSOR_RESET[] = "\x1B[;H";

  static constexpr char ANSI_ESC_RED[] = "\x1B[31m";
  static constexpr char ANSI_ESC_GREEN[] = "\x1B[32m";
  static constexpr char ANSI_ESC_YELLOW[] = "\x1B[33m";
  static constexpr char ANSI_ESC_BLUE[] = "\x1B[34m";
  static constexpr char ANSI_ESC_MAGENTA[] = "\x1B[35m";
  static constexpr char ANSI_ESC_CYAN[] = "\x1B[36m";
  static constexpr char ANSI_ESC_COLOR_RESET[] = "\x1B[m";

  static constexpr char PAUSE_MESSAGE[] = "[Press enter to continue]\n";
  static constexpr char HEADER_MESSAGE[] = "OOP Project - Dungeon by Ian Shih\n";

  static constexpr auto INTERVAL_PER_TICK = std::chrono::milliseconds(100);
  static constexpr int MAX_LOG_LINE = 10;

// Combat
  std::deque<std::string> combatLogs;

  IOSystem();

  void clear();
  void pause();
  void sleep(int tick = 1);

  void welcome();

// Game Process
  std::string askMainCharName();
  ClassType askMainCharClass();
  ActionOption askAction();
  DirectionType askMoveDirection();
  EnhanceOption askWhatToEnhance(const Character&);
  NPCTalkOption askWhatToDoWithNPC(const NPC&);
  int askWhichToBuy(const NPC&, const Character&);

  void printCharPos(const Character&);
  void printCharStatus(const Character&);
  void printInventory(const Inventory&);
  void printDialog(const NPC&, std::mt19937&);
  void printEndingMessage();

// Combat
  void clearCombatLog();
  CombatOption askCombatAction();
  void printCombatStatus(const Entity&);
  void printCombatLogs();
  void printAttackEvent(
    const Entity& target,
    const Entity& attacker,
    const Ability& ability,
    int damage
  );
  void printEffectEvent(
    const Entity& target,
    const Effect& effect
  );
  void printReward(const Monster& defeated);
  void printCombatEscape();
  void printLevelUp();

// IO interface
  IOSystem& operator<<(const std::integral auto&);
  IOSystem& operator<<(const std::floating_point auto&);
  IOSystem& operator<<(const std::convertible_to<std::string> auto&);

  IOSystem& operator<<(const std::derived_from<Entity> auto&);
  IOSystem& operator<<(const std::derived_from<Ability> auto&);
  IOSystem& operator<<(const std::derived_from<Effect> auto&);

  IOSystem& operator<<(std::function<IOSystem&(IOSystem&)>);
};

IOSystem& endl(IOSystem&);
IOSystem& flush(IOSystem&);

}
