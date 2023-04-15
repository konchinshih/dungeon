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

// template<typename T>
// concept ExceptionType =
// !std::integral<T> &&
// !std::floating_point<T> &&
// !std::convertible_to<T, std::string> &&
// !std::derived_from<T, Entity> &&
// !std::derived_from<T, Item> &&
// !std::derived_from<T, Ability> &&
// !std::derived_from<T, Effect>;


// ANSI Escape Code for Text Colors
static constexpr char ANSI_ESC_RED[] = "\x1B[31m";         // ClassType
static constexpr char ANSI_ESC_GREEN[] = "\x1B[32m";       // Item
static constexpr char ANSI_ESC_YELLOW[] = "\x1B[33m";      // Effect
static constexpr char ANSI_ESC_BLUE[] = "\x1B[34m";        // Entity, NPC
static constexpr char ANSI_ESC_MAGENTA[] = "\x1B[35m";     // Number
static constexpr char ANSI_ESC_CYAN[] = "\x1B[36m";        // Ability
static constexpr char ANSI_ESC_COLOR_RESET[] = "\x1B[m";

struct IOSystem {
// ANSI Escape Code for Clearing UI
  static constexpr char ANSI_ESC_CLEAR[] = "\x1B[2J";
  static constexpr char ANSI_ESC_CURSOR_RESET[] = "\x1B[;H";

// Messages
  static constexpr char PAUSE_MESSAGE[] = "[Press enter to continue]\n";
  static constexpr char HEADER_MESSAGE[] = "OOP Project - Dungeon by Ian Shih\n";

// Constants
  static constexpr auto INTERVAL_PER_TICK = std::chrono::milliseconds(100);
  static constexpr int MAX_LOG_LINE = 5;

  IOSystem& cout;
  std::istream& cin;

  IOSystem();

// Healper functions
  void clear();
  void pause();
  void sleep(int tick = 1);


// Game Process
  std::string askMainCharName();
  ClassType askMainCharClass();
  ActionOption askAction();
  DirectionType askMoveDirection();
  EnhanceOption askWhatToEnhance(const Character&);
  NPCTalkOption askWhatToDoWithNPC(const NPC&);
  int askWhichToBuy(const NPC&, const Character&);

  void printWelcome();
  void printCharPos(const Character&);
  void printCharStatus(const Character&);
  void printInventory(const Character&);
  void printDialog(const NPC&, std::mt19937&);
  void printRoomInfo(const Room&);
  void printItemReceived(const Item&);
  void printGameWinMessage();
  void printGameLoseMessage();

// Combat
  std::deque<std::string> combatLogs;
  void clearCombatLog();

  CombatOption askCombatAction();

  void printCombatStart();
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
  // IOSystem& operator<<(const std::integral auto&);
  // IOSystem& operator<<(const std::floating_point auto&);
  // IOSystem& operator<<(ExceptionType auto&);
  // IOSystem& operator<<(const auto&);
  // IOSystem& operator<<(auto);
};

std::ostream& operator<<(std::ostream&, ClassType);
// std::ostream& operator<<(std::ostream&, const std::derived_from<Entity> auto&);
// std::ostream& operator<<(std::ostream&, const std::derived_from<Effect> auto&);
// std::ostream& operator<<(std::ostream&, const std::derived_from<Item> auto&);
// std::ostream& operator<<(std::ostream&, const std::derived_from<Ability> auto&);

}
