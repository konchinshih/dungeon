#include"Game.hpp"

#include"ActionOption.hpp"
#include"EnhanceOption.hpp"

#include<chrono>
#include<utility>

namespace dungeon {

Game::Game(): rndGen(std::chrono::steady_clock::now().time_since_epoch().count()), map(rndGen) {
  ios.clear(), ios.welcome();
  auto name = ios.askMainCharName();
  switch (ios.askMainCharClass()) {
  case ClassType::SABER:
    mainChar = std::make_unique<CharacterClass<ClassType::SABER>>(name); break;
  case ClassType::ARCHER:
    mainChar = std::make_unique<CharacterClass<ClassType::ARCHER>>(name); break;
  case ClassType::LANCER:
    mainChar = std::make_unique<CharacterClass<ClassType::LANCER>>(name); break;
  case ClassType::BERSERKER:
    mainChar = std::make_unique<CharacterClass<ClassType::BERSERKER>>(name); break;
  default:
    std::unreachable();
  }
  mainChar->inventory.addItem(std::make_unique<WreckingBar>());
}

void Game::run() {
  while (!isGameEnded) {
    ios.clear();
    ios.printMapInfo(map);
    action();
  }
}

void Game::action() {
  switch (ios.askAction()) {
  case ActionOption::MOVE:
    move(); break;
  case ActionOption::CHECK_STATUS:
    ios.printCharStatus(mainChar); break;
  case ActionOption::ENHANCE:
    enhance(); break;
  case ActionOption::OPEN_INVENTORY:
    ios.printInventory(mainChar->inventory); break;
  default:
    std::unreachable();
  }
}

void Game::move() {
  mainChar->move(ios.askMoveDirection());
  // possible outcome:
  // 1. nothing
  // 2. combat
  // 3. get item
  // 4. talk to npc (only when entering the room or re-entering the room)
  map.at(mainChar)->doAction(*this);
}

void Game::enhance() {
// TODO
  bool isEnhanceEnded = false;
  while (!isEnhanceEnded) {
    switch (ios.askWhatToEnhance(mainChar)) {
    case EnhanceOption::NORMAL_ATTACK:
      break;
    case EnhanceOption::SKILL:
      break;
    case EnhanceOption::EXIT:
      isEnhanceEnded = true; break;
    default:
      std::unreachable();
    }
  }
}

void Game::talkToNPC(const std::unique_ptr<NPC>& npc) {
  bool isTalkEnded = false;
  while (!isTalkEnded) {
    switch (ios.askWhatToDoWithNPC(npc)) {
    case NPCTalkOption::TALK:
      ios.printDialog(npc); break;
    case NPCTalkOption::BUY_ITEM:
      buyItemFromNPC(npc); break;
    case NPCTalkOption::EXIT:
      isTalkEnded = true; break;
    default:
      std::unreachable();
    }
  }
}

void Game::buyItemFromNPC(const std::unique_ptr<NPC>& npc) {
  while (true) {
    int which = ios.askWhichToBuy(npc);
    if (which == -1) break;
    if (mainChar->coin >= npc->tradingMenu[which].price)
      mainChar->addItem(npc->tradingMenu[which].sell());
  }
}

}
