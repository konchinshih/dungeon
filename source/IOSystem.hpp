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

namespace dungeon {

struct IOSystem {
  static constexpr char ANSI_ESC_CLEAR[] = "\x1B[2J";
  static constexpr char ANSI_ESC_CURSOR_RESET[] = "\x1B[;H";
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
  void printLevelUp();
};

}
