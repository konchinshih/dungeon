#include"Game.hpp"

#include"ActionOption.hpp"
#include"EnhanceOption.hpp"
#include"Combat.hpp"

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
    ios.printCharPos(*mainChar);
    action();
  }
  ios.printEndingMessage();
}

void Game::action() {
  switch (ios.askAction()) {
  case ActionOption::MOVE:
    move(); break;
  case ActionOption::CHECK_STATUS:
    ios.printCharStatus(*mainChar);
    ios.pause(); break;
  case ActionOption::ENHANCE:
    enhance(); break;
  case ActionOption::OPEN_INVENTORY:
    ios.printInventory(mainChar->inventory);
    ios.pause(); break;
  default:
    std::unreachable();
  }
}

void Game::move() {
  mainChar->move(ios.askMoveDirection());
  map.at(*mainChar)->doAction(*this);
}

void Game::enhance() {
  bool isEnhanceEnded = false;
  while (!isEnhanceEnded) {
    switch (ios.askWhatToEnhance(*mainChar)) {
    case EnhanceOption::NORMAL_ATTACK:
      mainChar->enhance(*mainChar->normalAttack); break;
    case EnhanceOption::SKILL:
      mainChar->enhance(*mainChar->skill); break;
    case EnhanceOption::EXIT:
      isEnhanceEnded = true; break;
    default:
      std::unreachable();
    }
  }
}

void Game::talkToNPC(NPC& npc) {
  bool isTalkEnded = false;
  while (!isTalkEnded) {
    switch (ios.askWhatToDoWithNPC(npc)) {
    case NPCTalkOption::TALK:
      ios.printDialog(npc, rndGen);
      ios.pause(); break;
    case NPCTalkOption::BUY_ITEM:
      buyItemFromNPC(npc); break;
    case NPCTalkOption::EXIT:
      isTalkEnded = true; break;
    default:
      std::unreachable();
    }
  }
}

void Game::buyItemFromNPC(NPC& npc) {
  while (true) {
    int which = ios.askWhichToBuy(npc, *mainChar);
    if (which == -1) break;
    mainChar->addItem(npc.tradingMenu[which].sell());
  }
}

}
