#include"Game.hpp"

#include<sstream>
#include<iostream>
#include<cctype>
#include<string>
#include"Error.hpp"

namespace dungeon {

Game::Game(): isEnd(false) {
  initialize();
}

void Game::welcome() {
  ios.clear();
  ios.print("hello, world");
  ios.pause();
}

void Game::selectClass() {
  ios.clear();
  ios.print("Select your Class");
  ios.print("A. Saber");
  ios.print("B. Archer");
  ios.print("C. Lancer");
  // ios.print("D. Rider");
  // ios.print("E. Caster");
  // ios.print("F. Assassin");
  ios.print("G. Berserker");
  switch (ios.inputChar()) {
  case 'A':
    mainChar.type = Class::saber; break;
  case 'B':
    mainChar.type = Class::archer; break;
  case 'C':
    mainChar.type = Class::lancer; break;
  // case 'D':
  //   mainChar.type = Class::rider; break;
  // case 'E':
  //   mainChar.type = Class::caster; break;
  // case 'F':
  //   mainChar.type = Class::assassin; break;
  case 'G':
    mainChar.type = Class::berserker; break;
  default:
    throw TypeError();
  }
}

void Game::enterName() {
  using namespace std::literals;
  auto input = ios.input("Enter your name: ");
  mainChar.name = input.front();
  for (int i = 1; i < (int)input.size(); i++)
    mainChar.name += " "s + input[i];
}

void Game::initialize() {
  welcome();
  selectClass();
  enterName();
  mainChar.initialize();
  mainChar.curPos = map.at(0, 0);
}

void Game::printMapInfo() {
  std::stringstream ss;
  ss << "current position in map: "
     << "x [" << mainChar.curX << "] "
     << "y [" << mainChar.curY << "]\n";
  ss << "Current room type: ";
  switch (mainChar.curPos->type) {
  case RoomType::nothing:
    ss << "nothing"; break;
  case RoomType::treasure:
    ss << "treasure"; break;
  case RoomType::npc:
    ss << "npc"; break;
  case RoomType::monster:
    ss << "monster"; break;
  default:
    throw TypeError();
  }
  ios.print(ss.str());
}

void Game::move() {
  ios.print("Where do you want to go?");
  ios.print("A. Go up");
  ios.print("B. Go down");
  ios.print("C. Go left");
  ios.print("D. Go right");
  auto input = ios.input();
  switch (std::toupper(input[0][0])) {
  case 'A':
    mainChar.curX -= 1; break;
  case 'B':
    mainChar.curX += 1; break;
  case 'C':
    mainChar.curY -= 1; break;
  case 'D':
    mainChar.curY += 1; break;
  default:
    ios.print("wrong input");
  }
  mainChar.curPos = map.at(mainChar.curX, mainChar.curY);

// big problem here

  switch (mainChar.curPos->type) {
  case RoomType::monster: {
    Battle battle(mainChar, mainChar.curPos->monster);
    if (!battle.result()) isEnd = true;
    map.at(mainChar.curX, mainChar.curY) = std::make_shared<Room>();
  } break;
  case RoomType::treasure: {
    mainChar.inventory.addItem(std::move(mainChar.curPos->item));

    map.at(mainChar.curX, mainChar.curY) = std::make_shared<Room>();
  } break;
  default:
  }

  ios.pause();
}

void Game::showStatus() {
  std::stringstream ss;
  ss << "Status:\n"
     << mainChar.name << "\n"
     << "> HP: ["  << mainChar.curHp << "/" << mainChar.hp() << "]\n"
     << "> ATK: " << mainChar.atk() << "\n"
     << "> Crit Rate: " << mainChar.critRate() << "\n"
     << "> Crit DMG: " << mainChar.critDamage() << "\n"
     << "> Equipped Items: " << mainChar.equipped() << "\n";
  ios.print(ss.str());
  ios.pause();
}

void Game::showInventory() {
  std::stringstream ss;
  ss << "Inventory: " << mainChar.inventory;
  ios.print(ss.str());
  ios.pause();
}

void Game::talkToNPC() {
  std::stringstream ss;
  ss << "\"" << mainChar.curPos->npc->name << "\": " << mainChar.curPos->npc->dialog() << "\n";
  ss << "\"" << mainChar.curPos->npc->name << "\": Anyway, What do you want to do?";
  ios.print(ss.str());
  ios.print("A. Buy something");
  ios.print("B. Leave");
  swtich(ios.inputChar())
  ios.pause();
}

void Game::action() {
  ios.print("What do you want to do?");
  ios.print("A. Move");
  ios.print("B. Check Status");
  // ios.print("C. Enhance (use ability points)");
  ios.print("D. Open Inventory");
  if (mainChar.curPos->type == RoomType::npc) {
    std::stringstream ss("E. Talk to NPC");
    ss << " \"" << mainChar.curPos->npc->name << "\"";
    ios.print(ss.str());
  }
  switch (ios.inputChar()) {
  case 'A':
    move(); break;
  case 'B':
    showStatus(); break;
  case 'C':
    break;
  case 'D':
    showInventory(); break;
  case 'E':
    if (mainChar.curPos->type == RoomType::npc) {
      talkToNPC(); break;
    } else
      [[fallthrough]];
  default:
    ios.print("Wrong input");
    ios.pause();
  }
}

void Game::run() {
  while (!isEnd) {
    ios.clear();
    printMapInfo();
    action();
  }
}


}
