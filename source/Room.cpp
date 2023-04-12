#include"Room.hpp"

#include"Game.hpp"

#include<utility>

namespace dungeon {

Room::Room() {
  type = RoomType::NOTHING;
}

TreasureRoom::TreasureRoom(std::unique_ptr<Item>&& item) {
  type = RoomType::TREASURE;
  this->item = std::move(item);
}

NPCRoom::NPCRoom(std::unique_ptr<NPC>&& npc) {
  type = RoomType::NPC;
  this->npc = std::move(npc);
}

MonsterRoom::MonsterRoom(std::unique_ptr<Monster>&& monster) {
  type = RoomType::MONSTER;
  this->monster = std::move(monster);
}

BossRoom::BossRoom(std::unique_ptr<Boss>&& boss) {
  type = RoomType::BOSS;
  this->boss = std::move(boss);
}

void Room::doAction(Game&) {} // do nothing

void TreasureRoom::doAction(Game& game) {
  game.mainChar->addItem(std::move(item));
  game.map.at(game.mainChar) = std::make_unique<Room>();
}

void NPCRoom::doAction(Game& game) {
  game.talkToNPC(npc);
}

void MonsterRoom::doAction(Game& game) {
  // TODO: combat
}

void BossRoom::doAction(Game& game) {
  // TODO: combat
  game.isGameEnded = true;
}

}
