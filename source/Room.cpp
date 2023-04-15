#include"Room.hpp"

#include"Game.hpp"
#include"Combat.hpp"
#include"IOSystem.hpp"

#include<utility>

namespace dungeon {

Room::Room(RoomType type): type(type) {}

TreasureRoom::TreasureRoom(std::unique_ptr<Item>&& item):
  Room(RoomType::TREASURE), isActionDone(false), item(std::move(item)) {}

NPCRoom::NPCRoom(std::unique_ptr<NPC>&& npc):
  Room(RoomType::NPC), npc(std::move(npc)) {}

MonsterRoom::MonsterRoom(std::unique_ptr<Monster>&& monster):
  Room(RoomType::MONSTER), isActionDone(false), monster(std::move(monster)) {}

BossRoom::BossRoom(std::unique_ptr<Boss>&& boss):
  Room(RoomType::BOSS), boss(std::move(boss)) {}

void Room::doAction(Game& game) {
  game.ios.pause();
}

void TreasureRoom::doAction(Game& game) {
  if (isActionDone) return;
  game.ios.printItemReceived(*item);
  game.mainChar->addItem(std::move(item));
  isActionDone = true;
  game.ios.pause();
}

void NPCRoom::doAction(Game& game) {
  game.talkToNPC(*npc);
}

void MonsterRoom::doAction(Game& game) {
  if (isActionDone) return;
  Combat combat(game.rndGen, game.ios, *game.mainChar, *monster);
  combat.run();
  if (combat.isLose)
    game.isGameEnded = true;
  if (combat.isWon)
    isActionDone = true;
}

void BossRoom::doAction(Game& game) {
  Combat combat(game.rndGen, game.ios, *game.mainChar, *boss);
  combat.run();
  if (combat.isLose)
    game.isGameEnded = true;
  if (combat.isWon)
    game.isWon = game.isGameEnded = true;
}

}
