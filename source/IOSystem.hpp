#pragma once

#include"ClassType.hpp"
#include"DirectionType.hpp"
#include"ActionOption.hpp"
#include"EnhanceOption.hpp"
#include"NPCTalkOption.hpp"
#include"Map.hpp"

#include<string>
#include<memory>

namespace dungeon {

struct IOSystem {
  static constexpr char ANSI_ESC_CLEAR[] = "\x1B[2J";
  static constexpr char ANSI_ESC_CURSOR_RESET[] = "\x1B[;H";
  static constexpr char PAUSE_MESSAGE[] = "[Press enter to continue]\n";
  static constexpr char HEADER_MESSAGE[] = "OOP Project - Dungeon by Ian Shih\n";

  IOSystem();

  void clear();
  void pause();
  void sleep(int = 1);

  void welcome();

  ClassType askMainCharClass();
  std::string askMainCharName();
  ActionOption askAction();
  DirectionType askMoveDirection();
  EnhanceOption askWhatToEnhance(const std::unique_ptr<Character>&);
  NPCTalkOption askWhatToDoWithNPC(const std::unique_ptr<NPC>&);
  int askWhichToBuy(const std::unique_ptr<NPC>&);

  void printMapInfo(const Map&);
  void printCharStatus(const std::unique_ptr<Character>&);
  void printInventory(const Inventory&);
  void printDialog(const std::unique_ptr<NPC>&);

};

}
